#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <random>
#include <chrono>
#include <iostream>
#include <cfloat>
#include "Game.h"
#include <thread>

Memory apex_mem;
Memory client_mem;

bool firing_range = false;
bool active = true;
uintptr_t aimentity = 0;
uintptr_t tmp_aimentity = 0;
uintptr_t lastaimentity = 0;
float max = 999.0f;
float max_dist = 200.0f*40.0f;
int team_player = 0;
float max_fov = 15;
const int toRead = 100;
int aim = false;
bool esp = false;
bool item_glow = false;
bool player_glow = false;
extern bool aim_no_recoil;
bool aiming = false;
extern float smooth;
extern float aggressive_smooth;
extern float aggressive_aim_threshold;
extern float extreme_smooth;
extern float extreme_aim_threshold;
extern float smooth;
extern int bone;
bool thirdperson = false;
bool chargerifle = false;
bool shooting = false;
int skinchanger = false;

bool actions_t = false;
bool esp_t = false;
bool aim_t = false;
bool vars_t = false;
bool item_t = false;
uint64_t g_Base;
uint64_t c_Base;
bool next = false;
bool valid = false;
bool lock = false;

typedef struct player
{
	float dist = 0;
	int entity_team = 0;
	float boxMiddle = 0;
	float h_y = 0;
	float width = 0;
	float height = 0;
	float b_x = 0;
	float b_y = 0;
	bool knocked = false;
	bool visible = false;
	int health = 0;
	int shield = 0;
	char name[33] = { 0 };
}player;

//struct kbutton_t {
//	int down[2];
//	int state;
//};

int tapstrafe = false;
uint32_t air_flag = false;
//kbutton_t forward_flag = false;

//// Controls the game's state of kbutton_t instance.
//struct InState {
//	// The raw button state.
//	kbutton_t button;
//
//	// True if the button is held down.
//	bool state;
//	// Set to true if the button should be overriden.
//	bool force;
//	// Force the button to be pressed.
//	bool press;
//	// Force the button to be released.
//	bool release;
//
//	//void update(const GameProcess& process, uint32_t address)
//	//{
//	//	process.read(process.r5apex_exe + address, button);
//	//	state = (button.state & 1) != 0;
//	//}
//	//void post(const GameProcess& process, uint32_t address)
//	//{
//	//	// If active get the most recent state of the button
//	//	if (force && process.read(process.r5apex_exe + address, button)) {
//	//		// Get the desired state of the button
//	//		int state;
//	//		if (press && !release) {
//	//			state = 5; //0...0101
//	//		}
//	//		else if (!press && release) {
//	//			state = 4;//0...0100
//	//		}
//	//		else {
//	//			state = button.down[0] == 0 && button.down[1] == 0 ? 4 : 5;
//	//		}
//	//		// Gently tell the game to that nobody will be harmed if they just do as told
//	//		if (button.state != state) {
//	//			process.write(process.r5apex_exe + address + 8, state);
//	//		}
//	//	}
//	//}
//};

struct Matrix
{
	float matrix[16];
};

float lastvis_esp[toRead];
float lastvis_aim[toRead];

int tmp_spec = 0, spectators = 0;
int tmp_all_spec = 0, allied_spectators = 0;

//////////////////////////////////////////////////////////////////////////////////////////////////

void ProcessPlayer(Entity& LPlayer, Entity& target, uint64_t entitylist, int index)
{
	int entity_team = target.getTeamId();

	if (!target.isAlive())
	{
		float localyaw = LPlayer.GetYaw();
		float targetyaw = target.GetYaw();

		if(localyaw==targetyaw)
		{
			if(LPlayer.getTeamId() == entity_team)
				tmp_all_spec++;
			else
				tmp_spec++;
		}
		return;
	}

	Vector EntityPosition = target.getPosition();
	Vector LocalPlayerPosition = LPlayer.getPosition();
	float dist = LocalPlayerPosition.DistTo(EntityPosition);
	if (dist > max_dist) return;

	if(!firing_range)
		if (entity_team < 0 || entity_team>50 || entity_team == team_player) return;
	
	if(aim==2)
	{
		if((target.lastVisTime() > lastvis_aim[index]))
		{
			float fov = CalculateFov(LPlayer, target);
			if (fov < max)
			{
				max = fov;
				tmp_aimentity = target.ptr;
			}
		}
		else
		{
			if(aimentity==target.ptr)
			{
				aimentity=tmp_aimentity=lastaimentity=0;
			}
		}
	}
	else
	{
		float fov = CalculateFov(LPlayer, target);
		if (fov < max)
		{
			max = fov;
			tmp_aimentity = target.ptr;
		}
	}
	lastvis_aim[index] = target.lastVisTime();
}

void DoActions()
{
	actions_t = true;
	while (actions_t)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		bool tmp_thirdperson = false;
		bool tmp_chargerifle = false;
		uint32_t counter = 0;
		

		while (g_Base!=0 && c_Base!=0)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(30));	

			uint64_t LocalPlayer = 0;
			apex_mem.Read<uint64_t>(g_Base + OFFSET_LOCAL_ENT, LocalPlayer);
			if (LocalPlayer == 0) continue;

			Entity LPlayer = getEntity(LocalPlayer);

			team_player = LPlayer.getTeamId();
			if (team_player < 0 || team_player>50)
			{
				continue;
			}

			if(thirdperson && !tmp_thirdperson)
			{
				if(!aiming)
				{
					apex_mem.Write<int>(g_Base + OFFSET_THIRDPERSON, 1);
					apex_mem.Write<int>(LPlayer.ptr + OFFSET_THIRDPERSON_SV, 1);
					tmp_thirdperson = true;
				}			
			}
			else if((!thirdperson && tmp_thirdperson) || aiming)
			{
				if(tmp_thirdperson)
				{
					apex_mem.Write<int>(g_Base + OFFSET_THIRDPERSON, -1);
					apex_mem.Write<int>(LPlayer.ptr + OFFSET_THIRDPERSON_SV, 0);
					tmp_thirdperson = false;
				}	
			}

			uint64_t entitylist = g_Base + OFFSET_ENTITYLIST;

			uint64_t baseent = 0;
			apex_mem.Read<uint64_t>(entitylist, baseent);
			if (baseent == 0)
			{
				continue;
			}

			max = 999.0f;
			tmp_aimentity = 0;
			tmp_spec = 0;
			tmp_all_spec = 0;
			if(firing_range)
			{
				int c=0;
				for (int i = 0; i < 10000; i++)
				{
					uint64_t centity = 0;
					apex_mem.Read<uint64_t>(entitylist + ((uint64_t)i << 5), centity);
					if (centity == 0) continue;
					if (LocalPlayer == centity) continue;

					Entity Target = getEntity(centity);
					if (!Target.isDummy())
					{
						continue;
					}

					if(player_glow && !Target.isGlowing())
					{
						Target.enableGlow();
					}
					else if(!player_glow && Target.isGlowing())
					{
						Target.disableGlow();
					}

					ProcessPlayer(LPlayer, Target, entitylist, c);
					c++;
				}
			}
			else
			{
				for (int i = 0; i < toRead; i++)
				{
					uint64_t centity = 0;
					apex_mem.Read<uint64_t>(entitylist + ((uint64_t)i << 5), centity);
					if (centity == 0) continue;
					if (LocalPlayer == centity) continue;

					Entity Target = getEntity(centity);
					if (!Target.isPlayer())
					{
						continue;
					}
					
					ProcessPlayer(LPlayer, Target, entitylist, i);

					int entity_team = Target.getTeamId();
					if (entity_team == team_player)
					{
						continue;
					}

					if(player_glow && !Target.isGlowing())
					{
						Target.enableGlow();
					}
					else if(!player_glow && Target.isGlowing())
					{
						Target.disableGlow();
					}
				}
			}

			if(!spectators && !allied_spectators)
			{
				spectators = tmp_spec;
				allied_spectators = tmp_all_spec;
			}
			else
			{
				//refresh spectators count every ~2 seconds
				counter++;
				if(counter==70)
				{
					spectators = tmp_spec;
					allied_spectators = tmp_all_spec;
					counter = 0;
				}
			}

			if(!lock)
				aimentity = tmp_aimentity;
			else
				aimentity = lastaimentity;

			if(chargerifle)
			{
				charge_rifle_hack(LocalPlayer);
				tmp_chargerifle = true;
			}
			else
			{
				if(tmp_chargerifle)
				{
					apex_mem.Write<float>(g_Base + OFFSET_TIMESCALE + 0x68, 1.f);
					tmp_chargerifle = false;
				}
			}
			if (skinchanger)
			{
				apex_mem.Write<int>(LocalPlayer + OFFSET_SKIN, static_cast<int>(skinchanger));
			}
			
			apex_mem.Read<uint32_t>(LocalPlayer + OFFSET_m_fFlags, air_flag);
			//when player is in air
			if (!(air_flag & 0x1))
			{
				//1. air step
				if (tapstrafe >= 0)
				{
					if (!tapstrafe)
					{
						//release forward key
						apex_mem.Write<int>(LocalPlayer + OFFSET_IN_FORWARD + 8, static_cast<int>(4));
					}
					tapstrafe++;
					if (tapstrafe >= 20)
					{
						tapstrafe = -1;
						//hold forward key
						apex_mem.Write<int>(LocalPlayer + OFFSET_IN_FORWARD + 8, static_cast<int>(5));
					}
				}
			}
			else
			{
				//2. hit ground step
				if (tapstrafe < 0)
				{
					if (tapstrafe == -1)
						apex_mem.Write<int>(LocalPlayer + OFFSET_IN_FORWARD + 8, static_cast<int>(5));
					tapstrafe--;
					if (tapstrafe <= -10)
					{
						tapstrafe = 0;
					}
				}
			}

		}
	}
	actions_t = false;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////

player players[toRead];

static void EspLoop()
{
	esp_t = true;
	while(esp_t)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		while(g_Base!=0 && c_Base!=0)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			if (esp)
			{
				valid = false;

				uint64_t LocalPlayer = 0;
				apex_mem.Read<uint64_t>(g_Base + OFFSET_LOCAL_ENT, LocalPlayer);
				if (LocalPlayer == 0)
				{
					next = true;
					while(next && g_Base!=0 && c_Base!=0 && esp)
					{
						std::this_thread::sleep_for(std::chrono::milliseconds(1));
					}
					continue;
				}
				Entity LPlayer = getEntity(LocalPlayer);
				int team_player = LPlayer.getTeamId();
				if (team_player < 0 || team_player>50)
				{
					next = true;
					while(next && g_Base!=0 && c_Base!=0 && esp)
					{
						std::this_thread::sleep_for(std::chrono::milliseconds(1));
					}
					continue;
				}
				Vector LocalPlayerPosition = LPlayer.getPosition();

				uint64_t viewRenderer = 0;
				apex_mem.Read<uint64_t>(g_Base + OFFSET_RENDER, viewRenderer);
				uint64_t viewMatrix = 0;
				apex_mem.Read<uint64_t>(viewRenderer + OFFSET_MATRIX, viewMatrix);
				Matrix m = {};
				apex_mem.Read<Matrix>(viewMatrix, m);

				uint64_t entitylist = g_Base + OFFSET_ENTITYLIST;
				
				memset(players,0,sizeof(players));
				if(firing_range)
				{
					int c=0;
					for (int i = 0; i < 10000; i++)
					{
						uint64_t centity = 0;
						apex_mem.Read<uint64_t>( entitylist + ((uint64_t)i << 5), centity);
						if (centity == 0)
						{
							continue;
						}		
						
						if (LocalPlayer == centity)
						{
							continue;
						}

						Entity Target = getEntity(centity);

						if (!Target.isDummy())
						{
							continue;
						}

						if (!Target.isAlive())
						{
							continue;
						}
						int entity_team = Target.getTeamId();

						Vector EntityPosition = Target.getPosition();
						float dist = LocalPlayerPosition.DistTo(EntityPosition);
						if (dist > max_dist || dist < 50.0f)
						{	
							continue;
						}
						
						Vector bs = Vector();
						WorldToScreen(EntityPosition, m.matrix, 1920, 1080, bs);
						if (bs.x > 0 && bs.y > 0)
						{
							Vector hs = Vector();
							Vector HeadPosition = Target.getBonePositionByHitbox(0);
							WorldToScreen(HeadPosition, m.matrix, 1920, 1080, hs);
							float height = abs(abs(hs.y) - abs(bs.y));
							float width = height / 2.0f;
							float boxMiddle = bs.x - (width / 2.0f);
							int health = Target.getHealth();
							int shield = Target.getShield();
							players[c] = 
							{
								dist,
								entity_team,
								boxMiddle,
								hs.y,
								width,
								height,
								bs.x,
								bs.y,
								0,
								(Target.lastVisTime() > lastvis_esp[c]),
								health,
								shield	
							};
							Target.get_name(g_Base, i-1, &players[c].name[0]);
							lastvis_esp[c] = Target.lastVisTime();
							valid = true;
							c++;
						}
					}
				}	
				else
				{
					for (int i = 0; i < toRead; i++)
					{
						uint64_t centity = 0;
						apex_mem.Read<uint64_t>( entitylist + ((uint64_t)i << 5), centity);
						if (centity == 0)
						{
							continue;
						}
						
						if (LocalPlayer == centity)
						{
							continue;
						}

						Entity Target = getEntity(centity);
						
						if (!Target.isPlayer())
						{
							continue;
						}

						if (!Target.isAlive())
						{
							continue;
						}

						int entity_team = Target.getTeamId();
						if (entity_team < 0 || entity_team>50 || entity_team == team_player)
						{
							continue;
						}

						Vector EntityPosition = Target.getPosition();
						float dist = LocalPlayerPosition.DistTo(EntityPosition);
						if (dist > max_dist || dist < 50.0f)
						{	
							continue;
						}

						Vector bs = Vector();
						WorldToScreen(EntityPosition, m.matrix, 1920, 1080, bs);
						if (bs.x > 0 && bs.y > 0)
						{
							Vector hs = Vector();
							Vector HeadPosition = Target.getBonePositionByHitbox(0);
							WorldToScreen(HeadPosition, m.matrix, 1920, 1080, hs);
							float height = abs(abs(hs.y) - abs(bs.y));
							float width = height / 2.0f;
							float boxMiddle = bs.x - (width / 2.0f);
							int health = Target.getHealth();
							int shield = Target.getShield();
							
							players[i] = 
							{
								dist,
								entity_team,
								boxMiddle,
								hs.y,
								width,
								height,
								bs.x,
								bs.y,
								Target.isKnocked(),
								(Target.lastVisTime() > lastvis_esp[i]),
								health,
								shield
							};
							Target.get_name(g_Base, i-1, &players[i].name[0]);
							lastvis_esp[i] = Target.lastVisTime();
							valid = true;
						}
					}
				}

				next = true;
				while(next && g_Base!=0 && c_Base!=0 && esp)
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(1));
				}
			}
		}
	}
	esp_t = false;
}

static void AimbotLoop()
{
	aim_t = true;
	while (aim_t)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		while (g_Base!=0 && c_Base!=0)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			if (aim>0)
			{
				if (aimentity == 0 || !aiming)
				{
					lock=false;
					lastaimentity=0;
					continue;
				}
				lock=true;
				lastaimentity = aimentity;
				uint64_t LocalPlayer = 0;
				apex_mem.Read<uint64_t>(g_Base + OFFSET_LOCAL_ENT, LocalPlayer);
				if (LocalPlayer == 0) continue;
				Entity LPlayer = getEntity(LocalPlayer);
				QAngle Angles = CalculateBestBoneAim(LPlayer, aimentity, max_fov);
				if (Angles.x == 0 && Angles.y == 0)
				{
					lock=false;
					lastaimentity=0;
					continue;
				}
				LPlayer.SetViewAngles(Angles);
			}
		}
	}
	aim_t = false;
}

static void set_vars(uint64_t add_addr)
{
	printf("Reading client vars...\n");
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	//Get addresses of client vars
	uint64_t check_addr = 0;
	client_mem.Read<uint64_t>(add_addr, check_addr);
	uint64_t aim_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t), aim_addr);
	uint64_t esp_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*2, esp_addr);
	uint64_t aiming_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*3, aiming_addr);
	uint64_t g_Base_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*4, g_Base_addr);
	uint64_t next_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*5, next_addr);
	uint64_t player_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*6, player_addr);
	uint64_t valid_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*7, valid_addr);
	uint64_t max_dist_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*8, max_dist_addr);
	uint64_t item_glow_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*9, item_glow_addr);
	uint64_t player_glow_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*10, player_glow_addr);
	uint64_t aim_no_recoil_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*11, aim_no_recoil_addr);
	uint64_t smooth_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*12, smooth_addr);
	uint64_t max_fov_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*13, max_fov_addr);
	uint64_t bone_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*14, bone_addr);
	uint64_t thirdperson_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*15, thirdperson_addr);
	uint64_t spectators_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*16, spectators_addr);
	uint64_t allied_spectators_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*17, allied_spectators_addr);
	uint64_t chargerifle_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*18, chargerifle_addr);
	uint64_t shooting_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*19, shooting_addr);
	uint64_t skinchanger_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t) * 20, skinchanger_addr);
	uint64_t aggressive_smooth_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t) * 21, aggressive_smooth_addr);
	uint64_t aggressive_aim_threshold_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t) * 22, aggressive_aim_threshold_addr);
	uint64_t extreme_smooth_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t) * 23, extreme_smooth_addr);
	uint64_t extreme_aim_threshold_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t) * 24, extreme_aim_threshold_addr);
	
	// uint64_t tapstrafe_addr = 0;
	// client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t) * 21, tapstrafe_addr);
	

	uint32_t check = 0;
	client_mem.Read<uint32_t>(check_addr, check);
	
	if(check != 0xABCD)
	{
		printf("Incorrect values read. Check if the add_off is correct. Quitting.\n");
		active = false;
		return;
	}
	vars_t = true;
	while(vars_t)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		if(c_Base!=0 && g_Base!=0)
		{
			client_mem.Write<uint32_t>(check_addr, 0);
			printf("\nReady\n");
		}

		while(c_Base!=0 && g_Base!=0)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			client_mem.Write<uint64_t>(g_Base_addr, g_Base);
			client_mem.Write<int>(spectators_addr, spectators);
			client_mem.Write<int>(allied_spectators_addr, allied_spectators);

			client_mem.Read<int>(aim_addr, aim);
			client_mem.Read<bool>(esp_addr, esp);
			client_mem.Read<bool>(aiming_addr, aiming);
			client_mem.Read<float>(max_dist_addr, max_dist);
			client_mem.Read<bool>(item_glow_addr, item_glow);
			client_mem.Read<bool>(player_glow_addr, player_glow);
			client_mem.Read<bool>(aim_no_recoil_addr, aim_no_recoil);
			client_mem.Read<float>(smooth_addr, smooth);
			client_mem.Read<float>(max_fov_addr, max_fov);
			client_mem.Read<int>(bone_addr, bone);
			client_mem.Read<bool>(thirdperson_addr, thirdperson);
			client_mem.Read<bool>(shooting_addr, shooting);
			client_mem.Read<bool>(chargerifle_addr, chargerifle);
			client_mem.Read<int>(skinchanger_addr, skinchanger);
			// dynamic smooth
			client_mem.Read<float>(aggressive_smooth_addr, aggressive_smooth);
			client_mem.Read<float>(aggressive_aim_threshold_addr, aggressive_aim_threshold);
			client_mem.Read<float>(extreme_smooth_addr, extreme_smooth);
			client_mem.Read<float>(extreme_aim_threshold_addr, extreme_aim_threshold);
			
			if(esp && next)
			{
				if(valid)
					client_mem.WriteArray<player>(player_addr, players, toRead);
				client_mem.Write<bool>(valid_addr, valid);
				client_mem.Write<bool>(next_addr, true); //next

				bool next_val = false;
				do
				{
					client_mem.Read<bool>(next_addr, next_val);
					std::this_thread::sleep_for(std::chrono::milliseconds(1));
				} while (next_val && g_Base!=0 && c_Base!=0);
				
				next = false;
			}
		}
	}
	vars_t = false;
}

static void item_glow_t()
{
	item_t = true;
	while(item_t)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		int k = 0;
		while(g_Base!=0 && c_Base!=0)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			uint64_t entitylist = g_Base + OFFSET_ENTITYLIST;
			if (item_glow)
			{
				for (int i = 0; i < 10000; i++)
				{
					uint64_t centity = 0;
					apex_mem.Read<uint64_t>(entitylist + ((uint64_t)i << 5), centity);
					if (centity == 0) continue;
					Item item = getItem(centity);

					if(item.isItem() && !item.isGlowing())
					{
						item.enableGlow();
					}
				}
				k=1;
				std::this_thread::sleep_for(std::chrono::milliseconds(600));
			}
			else
			{		
				if(k==1)
				{
					for (int i = 0; i < 10000; i++)
					{
						uint64_t centity = 0;
						apex_mem.Read<uint64_t>(entitylist + ((uint64_t)i << 5), centity);
						if (centity == 0) continue;

						Item item = getItem(centity);

						if(item.isItem() && item.isGlowing())
						{
							item.disableGlow();
						}
					}
					k=0;
				}
			}	
		}
	}
	item_t = false;
}

int main(int argc, char *argv[])
{
	if(geteuid() != 0)
	{
		printf("Error: %s is not running as root\n", argv[0]);
		return 0;
	}

	const char* cl_proc = "node.exe";
	const char* ap_proc = "R5Apex.exe";
	//const char* ap_proc = "EasyAntiCheat_launcher.exe";

	//Client "add" offset
	uint64_t add_off = 0x4f890;

	std::thread aimbot_thr;
	std::thread esp_thr;
	std::thread actions_thr;
	std::thread itemglow_thr;
	std::thread vars_thr;
	while(active)
	{
		if(apex_mem.get_proc_status() != process_status::FOUND_READY)
		{
			if(aim_t)
			{
				aim_t = false;
				esp_t = false;
				actions_t = false;
				item_t = false;
				g_Base = 0;

				aimbot_thr.~thread();
				esp_thr.~thread();
				actions_thr.~thread();
				itemglow_thr.~thread();
			}

			std::this_thread::sleep_for(std::chrono::seconds(1));
			printf("Searching for apex process...\n");

			apex_mem.open_proc(ap_proc);

			if(apex_mem.get_proc_status() == process_status::FOUND_READY)
			{
				g_Base = apex_mem.get_proc_baseaddr();
				printf("\nApex process found\n");
				printf("Base: %lx\n", g_Base);

				aimbot_thr = std::thread(AimbotLoop);
				esp_thr = std::thread(EspLoop);
				actions_thr = std::thread(DoActions);
				itemglow_thr = std::thread(item_glow_t);
				aimbot_thr.detach();
				esp_thr.detach();
				actions_thr.detach();
				itemglow_thr.detach();
			}
		}
		else
		{
			apex_mem.check_proc();
		}

		if(client_mem.get_proc_status() != process_status::FOUND_READY)
		{
			if(vars_t)
			{
				vars_t = false;
				c_Base = 0;

				vars_thr.~thread();
			}
			
			std::this_thread::sleep_for(std::chrono::seconds(1));
			printf("Searching for client process...\n");

			client_mem.open_proc(cl_proc);

			if(client_mem.get_proc_status() == process_status::FOUND_READY)
			{
				c_Base = client_mem.get_proc_baseaddr();
				printf("\nClient process found\n");
				printf("Base: %lx\n", c_Base);

				vars_thr = std::thread(set_vars, c_Base + add_off);
				vars_thr.detach();
			}
		}
		else
		{
			client_mem.check_proc();
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	return 0;
}
#define ORIGIN 1
#define STEAM 2

#define VERSION STEAM

#if VERSION == STEAM

#define OFFSET_ENTITYLIST 0x1d89048 //cl_entitylist
#define OFFSET_LOCAL_ENT 0x0213a640 + 0x8 //LocalPlayer 0x02139480 + 0x8
#define OFFSET_NAME_LIST 0xbd28d20 //NameList
#define OFFSET_THIRDPERSON 0x01d187c0 + 0x6c //thirdperson_override + 0x6c
#define OFFSET_TIMESCALE 0x016cdd10 //host_timescale

#define OFFSET_TEAM 0x044c //m_iTeamNum
#define OFFSET_HEALTH 0x043c //m_iHealth
#define OFFSET_SHIELD 0x0170 //m_shieldHealth
#define OFFSET_MAXSHIELD 0x0174 //m_shieldHealthMax
#define OFFSET_ARMORTYPE 0x464c //armortype
#define OFFSET_NAME 0x0589 //m_iName
#define OFFSET_SIGN_NAME 0x0580 //m_iSignifierName
#define OFFSET_ABS_VELOCITY 0x0140 //m_vecAbsVelocity
#define OFFSET_VISIBLE_TIME 0x1a80 //CPlayer!lastVisibleTime
#define OFFSET_ZOOMING 0x1c61 //m_bZooming
#define OFFSET_THIRDPERSON_SV 0x36e0 //m_thirdPersonShoulderView
#define OFFSET_YAW 0x22c4 - 0x8 //m_currentFramePlayer.m_ammoPoolCount - 0x8

#define OFFSET_LIFE_STATE 0x0798 //m_lifeState, >0 = dead
#define OFFSET_BLEED_OUT_STATE 0x2750 //m_bleedoutState, >0 = knocked

#define OFFSET_ORIGIN 0x014c //m_vecAbsOrigin - 3rd offset after the first int and vector


#define OFFSET_BONES 0x0e98 + 0x48 //m_nForceBone + 0x48
#define OFFSET_STUDIOHDR 0x10f0 //CBaseAnimating!m_pStudioHdr


#define OFFSET_AIMPUNCH 0x24c0 //m_currentFrameLocalPlayer.m_vecPunchWeapon_Angle
#define OFFSET_CAMERAPOS 0x1f58 //CPlayer!camera_origin
#define OFFSET_VIEWANGLES 0x25bc - 0x14 //m_ammoPoolCapacity - 0x14
#define OFFSET_BREATH_ANGLES OFFSET_VIEWANGLES - 0x10
#define OFFSET_OBSERVER_MODE 0x34ec //m_iObserverMode
#define OFFSET_OBSERVING_TARGET 0x34f8 //m_hObserverTarget

#define OFFSET_MATRIX 0x11a350 //ViewMatrix
#define OFFSET_RENDER 0x7401d50 //ViewRender

#define OFFSET_WEAPON 0x1a24 //m_latestPrimaryWeapons
#define OFFSET_BULLET_SPEED 0x1f50 //CWeaponX!m_flProjectileSpeed
#define OFFSET_BULLET_SCALE 0x1f58 //CWeaponX!m_flProjectileScale
#define OFFSET_ZOOM_FOV 0x16c0 + 0xb8 //m_playerData + m_curZoomFOV
#define OFFSET_AMMO 0x1644 //m_ammoInClip first offset 

#define OFFSET_ITEM_GLOW 0x02c0 //m_highlightFunctionBits
#define OFFSET_ITEM_ID 0x1628 // item id?
#define OFFSET_MODELNAME 0x0030 // m_ModelName
#define OFFSET_M_CUSTOMSCRIPTINT 0x1648 //m_customScriptInt
#define OFFSET_MINIMAP_SCALE 0x4638 //m_minimapTargetZoomScale, float

#define OFFSET_GLOW_T1 0x262 //16256 = enabled, 0 = disabled
#define OFFSET_GLOW_T2 0x2dc //1193322764 = enabled, 0 = disabled
#define OFFSET_GLOW_ENABLE 0x3c8 //7 = enabled, 2 = disabled
#define OFFSET_GLOW_THROUGH_WALLS 0x3d0 //2 = enabled, 5 = disabled
#define OFFSET_SKIN			        0x0e54 //m_nSkin
#define OFFSET_m_fFlags             0x0098 //player is in air
#define OFFSET_IN_FORWARD           0x074045a0 //player is in forward

#elif VERSION == ORIGIN

#define OFFSET_ENTITYLIST 0x1d89048 //cl_entitylist
#define OFFSET_LOCAL_ENT 0x0213a640 + 0x8 //LocalPlayer 0x02139480 + 0x8
#define OFFSET_NAME_LIST 0xbd28d20 //NameList
#define OFFSET_THIRDPERSON 0x01d187c0 + 0x6c //thirdperson_override + 0x6c
#define OFFSET_TIMESCALE 0x016cdd10 //host_timescale

#define OFFSET_TEAM 0x044c //m_iTeamNum
#define OFFSET_HEALTH 0x043c //m_iHealth
#define OFFSET_SHIELD 0x0170 //m_shieldHealth
#define OFFSET_MAXSHIELD 0x0174 //m_shieldHealthMax
#define OFFSET_ARMORTYPE 0x464c //armortype
#define OFFSET_NAME 0x0589 //m_iName
#define OFFSET_SIGN_NAME 0x0580 //m_iSignifierName
#define OFFSET_ABS_VELOCITY 0x0140 //m_vecAbsVelocity
#define OFFSET_VISIBLE_TIME 0x1a80 //CPlayer!lastVisibleTime
#define OFFSET_ZOOMING 0x1c61 //m_bZooming
#define OFFSET_THIRDPERSON_SV 0x36e0 //m_thirdPersonShoulderView
#define OFFSET_YAW 0x22c4 - 0x8 //m_currentFramePlayer.m_ammoPoolCount - 0x8

#define OFFSET_LIFE_STATE 0x0798 //m_lifeState, >0 = dead
#define OFFSET_BLEED_OUT_STATE 0x2750 //m_bleedoutState, >0 = knocked

#define OFFSET_ORIGIN 0x014c //m_vecAbsOrigin - 3rd offset after the first int and vector


#define OFFSET_BONES 0x0e98 + 0x48 //m_nForceBone + 0x48
#define OFFSET_STUDIOHDR 0x10f0 //CBaseAnimating!m_pStudioHdr


#define OFFSET_AIMPUNCH 0x24c0 //m_currentFrameLocalPlayer.m_vecPunchWeapon_Angle
#define OFFSET_CAMERAPOS 0x1f58 //CPlayer!camera_origin
#define OFFSET_VIEWANGLES 0x25bc - 0x14 //m_ammoPoolCapacity - 0x14
#define OFFSET_BREATH_ANGLES OFFSET_VIEWANGLES - 0x10
#define OFFSET_OBSERVER_MODE 0x34ec //m_iObserverMode
#define OFFSET_OBSERVING_TARGET 0x34f8 //m_hObserverTarget

#define OFFSET_MATRIX 0x11a350 //ViewMatrix
#define OFFSET_RENDER 0x7401d50 //ViewRender

#define OFFSET_WEAPON 0x1a24 //m_latestPrimaryWeapons
#define OFFSET_BULLET_SPEED 0x1f50 //CWeaponX!m_flProjectileSpeed
#define OFFSET_BULLET_SCALE 0x1f58 //CWeaponX!m_flProjectileScale
#define OFFSET_ZOOM_FOV 0x16c0 + 0xb8 //m_playerData + m_curZoomFOV
#define OFFSET_AMMO 0x1644 //m_ammoInClip first offset 

#define OFFSET_ITEM_GLOW 0x02c0 //m_highlightFunctionBits
#define OFFSET_ITEM_ID 0x1628 // item id?
#define OFFSET_MODELNAME 0x0030 // m_ModelName
#define OFFSET_M_CUSTOMSCRIPTINT 0x1648 //m_customScriptInt
#define OFFSET_MINIMAP_SCALE 0x4638 //m_minimapTargetZoomScale, float

#define OFFSET_GLOW_T1 0x262 //16256 = enabled, 0 = disabled
#define OFFSET_GLOW_T2 0x2dc //1193322764 = enabled, 0 = disabled
#define OFFSET_GLOW_ENABLE 0x3c8 //7 = enabled, 2 = disabled
#define OFFSET_GLOW_THROUGH_WALLS 0x3d0 //2 = enabled, 5 = disabled
#define OFFSET_SKIN			        0x0e54 //m_nSkin
#define OFFSET_m_fFlags             0x0098 //player is in air
#define OFFSET_IN_FORWARD           0x074045a0 //player is in forward

#endif

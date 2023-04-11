#define ORIGIN 1
#define STEAM 2

#define VERSION STEAM

#if VERSION == STEAM

#define OFFSET_ENTITYLIST 0x1d10ef8 //cl_entitylist
#define OFFSET_LOCAL_ENT 0x20c21d0 //LocalPlayer
#define OFFSET_NAME_LIST 0xbfffd00 //NameList
#define OFFSET_THIRDPERSON 0x01cf5a60 + 0x6c //thirdperson_override + 0x6c
#define OFFSET_TIMESCALE 0x016ab1a0 //host_timescale

#define OFFSET_TEAM 0x044c //m_iTeamNum
#define OFFSET_HEALTH 0x043c //m_iHealth
#define OFFSET_SHIELD 0x0170 //m_shieldHealth
#define OFFSET_MAXSHIELD 0x0174 //m_shieldHealthMax
#define OFFSET_ARMORTYPE 0x4634 //armortype
#define OFFSET_NAME 0x0589 //m_iName
#define OFFSET_SIGN_NAME 0x0580 //m_iSignifierName
#define OFFSET_ABS_VELOCITY 0x0140 //m_vecAbsVelocity
#define OFFSET_VISIBLE_TIME 0x1a78 //CPlayer!lastVisibleTime
#define OFFSET_ZOOMING 0x1c51 //m_bZooming
#define OFFSET_THIRDPERSON_SV 0x36c8 //m_thirdPersonShoulderView
#define OFFSET_YAW 0x22b4 - 0x8 //m_currentFramePlayer.m_ammoPoolCount - 0x8

#define OFFSET_LIFE_STATE 0x0798 //m_lifeState, >0 = dead
#define OFFSET_BLEED_OUT_STATE 0x2740 //m_bleedoutState, >0 = knocked

#define OFFSET_ORIGIN 0x014c //m_vecAbsOrigin - 3rd offset after the first int and vector


#define OFFSET_BONES 0x0e98 + 0x48 //m_nForceBone + 0x48
#define OFFSET_STUDIOHDR 0x10f0 //CBaseAnimating!m_pStudioHdr


#define OFFSET_AIMPUNCH 0x24b0 //m_currentFrameLocalPlayer.m_vecPunchWeapon_Angle
#define OFFSET_CAMERAPOS 0x1f48 //CPlayer!camera_origin
#define OFFSET_VIEWANGLES 0x25ac - 0x14 //m_ammoPoolCapacity - 0x14
#define OFFSET_BREATH_ANGLES OFFSET_VIEWANGLES - 0x10
#define OFFSET_OBSERVER_MODE 0x34d4 //m_iObserverMode
#define OFFSET_OBSERVING_TARGET 0x34e0 //m_hObserverTarget

#define OFFSET_MATRIX 0x11a210 //ViewMatrix
#define OFFSET_RENDER 0x7870410 //ViewRender

#define OFFSET_WEAPON 0x1a1c //m_latestPrimaryWeapons
#define OFFSET_BULLET_SPEED 0x1f48 //CWeaponX!m_flProjectileSpeed
#define OFFSET_BULLET_SCALE 0x1f50 //CWeaponX!m_flProjectileScale
#define OFFSET_ZOOM_FOV 0x16c0 + 0xb8 //m_playerData + m_curZoomFOV
#define OFFSET_AMMO 0x1644 //m_ammoInClip first offset 

#define OFFSET_ITEM_GLOW 0x02c0 //m_highlightFunctionBits
#define OFFSET_ITEM_ID 0x1628 // item id?
#define OFFSET_MODELNAME 0x0030 // m_ModelName
#define OFFSET_M_CUSTOMSCRIPTINT 0x1648 //m_customScriptInt
#define OFFSET_MINIMAP_SCALE 0x4620 //m_minimapTargetZoomScale, float

#define OFFSET_GLOW_T1 0x262 //16256 = enabled, 0 = disabled
#define OFFSET_GLOW_T2 0x2dc //1193322764 = enabled, 0 = disabled
#define OFFSET_GLOW_ENABLE 0x3c8 //7 = enabled, 2 = disabled
#define OFFSET_GLOW_THROUGH_WALLS 0x3d0 //2 = enabled, 5 = disabled
#define OFFSET_SKIN			        0x0e54 //m_nSkin
#define OFFSET_m_fFlags             0x0098 //player is in air
#define OFFSET_IN_FORWARD           0x07872c60 //player is in forward

#elif VERSION == ORIGIN

#define OFFSET_ENTITYLIST 0x1b0d678 //cl_entitylist
#define OFFSET_LOCAL_ENT 0x1ebe3e8 //LocalPlayer
#define OFFSET_NAME_LIST 0xbbd07c0 //NameList
#define OFFSET_THIRDPERSON 0x01af2520 + 0x6c //thirdperson_override + 0x6c
#define OFFSET_TIMESCALE 0x014ac600 //host_timescale

#define OFFSET_TEAM 0x044c //m_iTeamNum
#define OFFSET_HEALTH 0x043c //m_iHealth
#define OFFSET_SHIELD 0x0170 //m_shieldHealth
#define OFFSET_MAXSHIELD 0x0174 //m_shieldHealthMax
#define OFFSET_ARMORTYPE 0x460c //armortype
#define OFFSET_NAME 0x0589 //m_iName
#define OFFSET_SIGN_NAME 0x0580 //m_iSignifierName
#define OFFSET_ABS_VELOCITY 0x0140 //m_vecAbsVelocity
#define OFFSET_VISIBLE_TIME 0x1a70 //CPlayer!lastVisibleTime
#define OFFSET_ZOOMING 0x1c31 //m_bZooming
#define OFFSET_THIRDPERSON_SV 0x36a0 //m_thirdPersonShoulderView
#define OFFSET_YAW 0x228c - 0x8 //m_currentFramePlayer.m_ammoPoolCount - 0x8

#define OFFSET_LIFE_STATE 0x0798 //m_lifeState, >0 = dead
#define OFFSET_BLEED_OUT_STATE 0x2718 //m_bleedoutState, >0 = knocked

#define OFFSET_ORIGIN 0x014c //m_vecAbsOrigin - 3rd offset after the first int and vector


#define OFFSET_BONES 0x0e98 + 0x48 //m_nForceBone + 0x48
#define OFFSET_STUDIOHDR 0x10f0 //CBaseAnimating!m_pStudioHdr


#define OFFSET_AIMPUNCH 0x2488 //m_currentFrameLocalPlayer.m_vecPunchWeapon_Angle
#define OFFSET_CAMERAPOS 0x1f28 //CPlayer!camera_origin
#define OFFSET_VIEWANGLES 0x2584 - 0x14 //m_ammoPoolCapacity - 0x14
#define OFFSET_BREATH_ANGLES OFFSET_VIEWANGLES - 0x10
#define OFFSET_OBSERVER_MODE 0x34ac //m_iObserverMode
#define OFFSET_OBSERVING_TARGET 0x34b8 //m_hObserverTarget

#define OFFSET_MATRIX 0x11a210 //ViewMatrix
#define OFFSET_RENDER 0x763e7b0 //ViewRender

#define OFFSET_WEAPON 0x1a14 //m_latestPrimaryWeapons
#define OFFSET_BULLET_SPEED 0x1ef0 //CWeaponX!m_flProjectileSpeed
#define OFFSET_BULLET_SCALE 0x1ef8 //CWeaponX!m_flProjectileScale
#define OFFSET_ZOOM_FOV 0x16b8 + 0xb8 //m_playerData + m_curZoomFOV
#define OFFSET_AMMO 0x1644 //m_ammoInClip first offset 

#define OFFSET_ITEM_GLOW 0x02c0 //m_highlightFunctionBits
#define OFFSET_ITEM_ID 0x1628 // item id?
#define OFFSET_MODELNAME 0x0030 // m_ModelName
#define OFFSET_M_CUSTOMSCRIPTINT 0x1648 //m_customScriptInt
#define OFFSET_MINIMAP_SCALE 0x45f8 //m_minimapTargetZoomScale, float

#define OFFSET_GLOW_T1 0x262 //16256 = enabled, 0 = disabled
#define OFFSET_GLOW_T2 0x2dc //1193322764 = enabled, 0 = disabled
#define OFFSET_GLOW_ENABLE 0x3c8 //7 = enabled, 2 = disabled
#define OFFSET_GLOW_THROUGH_WALLS 0x3d0 //2 = enabled, 5 = disabled

#endif
#pragma once
namespace Game
{
	// ‰æ–Êî•ñ‚ğ’è”’è‹`
	constexpr int kScreenWidth = 1280;
	constexpr int kScreenHeight = 640;
	constexpr int kColorBitNum = 32;

	constexpr bool kDefaultWindowMode = true;
}


#define SHOT 18

#define PLAYER_LIFE 3
#define BOSS_LIFE 50

#ifdef _DEBUG
#define DISP_COLLISION
#endif

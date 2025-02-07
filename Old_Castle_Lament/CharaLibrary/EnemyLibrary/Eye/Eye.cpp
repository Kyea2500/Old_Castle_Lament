#include "Eye.h"
#include"../プロジェクトに追加すべきファイル_VC用/DxLib.h"
#include"../../../GameProcess/Game.h"
namespace
{
	constexpr int kGraphWidth = 32;
	constexpr int kGraphHeight = 28;
	constexpr int kGraphSize = 32;

	constexpr float ChangeSize = 3.5f;
	constexpr int half = 2;

	constexpr float E_CircleX= kGraphWidth;
	constexpr float E_CircleY = kGraphHeight*1.7;
	constexpr float E_CircleR = kGraphSize/1.5;

	constexpr int kSingleAnimFrame = 5;
	constexpr int kDeadAnimFrame = 10;
	constexpr int kFryAnimNum = 4;
	constexpr int kDeadAnimNum = 4;

	constexpr int SpawnY = Game::kScreenHeight-30;
	constexpr float kSpeed = 5.0f;
	constexpr float kAccel = 0.2f;
	constexpr float kHighSpeed = 1.0f;
	constexpr float kLowSpeed = 5.0f;

	constexpr float DownStertY = 30.0f;
	constexpr float UpStertY = 50.0f;

	constexpr int Endlessly_Ahead = 2000;


}
Eye::Eye() :
	EyeFry(-1),
	EyeDead(-1),
	Eye_pos(Game::kScreenWidth, SpawnY),
	Eye_animFrame(0),
	EyeDamageFlag(false),
	EyeSpeed(0.0f),
	EyeAccel(false)
{
}

Eye::~Eye()
{
}

void Eye::Init()
{
	EyeFry = LoadGraph(L"../date/image/eyeball_fry.png");
	EyeDead = LoadGraph(L"../date/image/eyeball_dead.png");
}

float Eye::Eye_HitCircleX()
{
	return Eye_pos.x - E_CircleX;
}

float Eye::Eye_HitCircleY()
{
	return Eye_pos.y - E_CircleY;
}

float Eye::Eye_HitCircleRad()
{
	return E_CircleR;
}

void Eye::Update()
{
	if (!EyeDamageFlag)
	{
		UpdateMove();
#ifdef DISP_COLLISION
		if (CheckHitKey(KEY_INPUT_W))
		{
			EyeDamageFlag = true;
		}
#endif
	}

	if (EyeDamageFlag)
	{
		UpdateDead();
#ifdef DISP_COLLISION
		if (CheckHitKey(KEY_INPUT_R))
		{
			Spawn();
			EyeDamageFlag = false;
		}
#endif
	}


	Draw();
}

void Eye::Draw()
{
	int useHandle = EyeFry;
	int animNo = Eye_animFrame / kSingleAnimFrame;
	if (EyeDamageFlag)
	{
		useHandle = EyeDead;
	}
	DrawRectRotaGraph(static_cast<int>(Eye_pos.x - kGraphWidth / half), static_cast<int>(Eye_pos.y - kGraphHeight),
		animNo * kGraphWidth, 0, kGraphWidth, kGraphHeight, ChangeSize, 0,
		useHandle, true, true, false);

#ifdef DISP_COLLISION
	DrawCircle(Eye_HitCircleX(), Eye_HitCircleY(), Eye_HitCircleRad(), 0xffffff, false);
#endif
}

void Eye::OnDamage()
{
	EyeDamageFlag = true;
}

void Eye::End()
{
	DeleteGraph(EyeFry);
	DeleteGraph(EyeDead);
}

void Eye::Spawn()
{
	Init();
	Eye_pos.x = Game::kScreenWidth;
	Eye_pos.y = SpawnY;
}

void Eye::UpdateMove()
{
	Eye_animFrame++;
	EyeSpeed = kSpeed;
	Eye_pos.x -= EyeSpeed;
	if (!EyeAccel)
	{
		EyeSpeed += kAccel;
		if (EyeSpeed > kHighSpeed)
		{
			EyeAccel = true;
		}
	}
	if (EyeAccel)
	{
		EyeSpeed -= kAccel;
		if (EyeSpeed < kLowSpeed)
		{
			EyeAccel = false;
		}
	}
	if (Eye_pos.x < 0)
	{
		Eye_pos.x = Game::kScreenWidth + kGraphWidth;
		Eye_pos.y -= UpStertY;
	}
	if (Eye_pos.y < 0)
	{
		Eye_pos.y = Game::kScreenHeight - DownStertY;
	}
	int totalFrame = kFryAnimNum * kSingleAnimFrame;
	if (Eye_animFrame >= totalFrame)
	{
		Eye_animFrame = 0;
	}
}

void Eye::UpdateDead()
{
	Eye_pos.y += EyeSpeed/half;
	Eye_animFrame++;
	int totalFrame = kDeadAnimNum * kDeadAnimFrame;
	if (Eye_animFrame >= totalFrame)
	{
		Eye_pos.y = Endlessly_Ahead;

	}
	if (Eye_pos.y >= Game::kScreenHeight + kGraphSize)
	{
		EyeDamageFlag = false;
		Spawn();
	}

}

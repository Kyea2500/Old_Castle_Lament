#include "Bat.h"
#include"../プロジェクトに追加すべきファイル_VC用/DxLib.h"
#include"../../../GameProcess/Game.h"
namespace
{
	constexpr int kGraphWidth = 16;
	constexpr int kGraphHeight = 20;
	constexpr int kGraphSize = 20;

	constexpr float ChangeSize = 3.0f;
	constexpr int half = 2;

	constexpr float bat_CircleX = kGraphWidth / 2;
	constexpr float bat_CircleY = kGraphHeight;
	constexpr float bat_CircleR = kGraphSize / 2;

	constexpr int kSingleAnimFrame = 5;
	constexpr int kFryAnimNum = 5;
	constexpr int kDeadAnimNum = 5;

	constexpr float kSpeed = 2.0f;

	constexpr float DownStertY = 50.0f;
	constexpr float UpStertY = 50.0f;
}

Bat::Bat() :
	BatEry(-1),
	BatDead(-1),
	Bat_pos(Game::kScreenWidth,Game::kScreenHeight/2),
	Bat_animFrame(0),
	BatDamageFlag(false),
	BatSpeed(0.0f),
	FollorFry(0.5f),
	BatFoll(false)
{
}

Bat::~Bat()
{
}

void Bat::Init()
{
	BatEry = LoadGraph(L"../date/image/Bat_Fly.png");
	BatDead = LoadGraph(L"../date/image/Bat_Dead.png");
}

void Bat::Update()
{
	if (!BatDamageFlag)
	{
		UpdateMove();
	}
	if(BatDamageFlag)
	{
		UpdateDead();
	}

}
void Bat::OnDamage()
{
	BatDamageFlag = true;
}

void Bat::End()
{
	DeleteGraph(BatEry);
	DeleteGraph(BatDead);
}

void Bat::Spawn()
{
	Bat_pos.x = Game::kScreenWidth;
	Bat_pos.y = Game::kScreenHeight / half;
}

float Bat::Bat_HitCircleX()
{
	return Bat_pos.x- bat_CircleX;
}

float Bat::Bat_HitCircleY()
{
	return Bat_pos.y- bat_CircleY;
}

float Bat::Bat_HitCircleRad()
{
	return bat_CircleR;
}

void Bat::UpdateMove()
{
	Bat_animFrame++;
	BatSpeed = kSpeed;
	Bat_pos.x -= BatSpeed;
	int totalFrame = kFryAnimNum * kSingleAnimFrame;
	if (Bat_pos.x < 0)
	{
		Bat_pos.x = Game::kScreenWidth + kGraphWidth;
		Bat_pos.y += DownStertY;
		if (Bat_pos.y > Game::kScreenHeight)
		{
			Bat_pos.y = UpStertY;
		}
	}
	if (Bat_animFrame >= totalFrame)
	{
		Bat_animFrame = 0;
	}
}

void Bat::UpdateDead()
{
	Bat_animFrame++;
	Bat_pos.y += BatSpeed;
	int totalFrame = kDeadAnimNum * kSingleAnimFrame;
	if (Bat_pos.y >= Game::kScreenHeight + kGraphHeight)
	{
		BatDamageFlag = false;
		Init();
		Spawn();
	}
}

void Bat::Draw()
{
	int useHandle = BatEry;

	if (BatDamageFlag)
	{
		useHandle = BatDead;
	}

	int animNo = Bat_animFrame / kSingleAnimFrame;
	DrawRectRotaGraph(static_cast<int>(Bat_pos.x - kGraphWidth / half), static_cast<int>(Bat_pos.y - kGraphHeight),
		animNo * kGraphWidth, 0, kGraphWidth, kGraphHeight, ChangeSize, 0,
		useHandle, true, true, false);
#ifdef DISP_COLLISION
	DrawCircle(Bat_HitCircleX(),Bat_HitCircleY(), Bat_HitCircleRad(), 0xffffff, false);
#endif
}


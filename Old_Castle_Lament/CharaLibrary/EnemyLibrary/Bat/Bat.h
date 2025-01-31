#pragma once
#include "../../../Vec2/Vec2.h"
class Bat
{
public:
	Bat();
	~Bat();
	void Init();
	void Update();
	void Draw();
	void OnDamage();
	void End();
	void Spawn();
	float Bat_HitCircleX();
	float Bat_HitCircleY();
	float Bat_HitCircleRad();
private:
	void UpdateMove();
	void UpdateDead();

	int BatEry;
	int BatDead;
	Vec2 Bat_pos;
	int Bat_animFrame;
	bool BatDamageFlag;
	float BatSpeed;
	float FollorFry;
	bool BatFoll;
};


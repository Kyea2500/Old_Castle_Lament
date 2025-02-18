#pragma once
#include "../../../Vec2/Vec2.h"
class Eye
{
public:
	Eye();
	~Eye();
	void Init();
	void Update();
	void Draw();
	void OnDamage();
	void End();
	void Spawn();
	float Eye_HitCircleX();
	float Eye_HitCircleY();
	float Eye_HitCircleRad();
private:
	void UpdateMove();
	void UpdateDead();

	int EyeFry;
	int EyeDead;
	Vec2 Eye_pos;
	int Eye_animFrame;
	bool EyeDamageFlag;
	float EyeSpeed;
	bool EyeAccel;
};


#pragma once
#include "../SceneManager/SceneManager.h"
#include "../../CharaLibrary/PlayerLibrary/Player.h"
#include"../../CharaLibrary/EnemyLibrary/Boss/Boss.h"
#include"../../CharaLibrary/EnemyLibrary/Bat/Bat.h"
#include"../../CharaLibrary/EnemyLibrary/Eye/Eye.h"

class SceneGame
{
public:
	SceneGame();
	~SceneGame();

	void Init();
	//void Update();
	SceneManager::SceneKind Update();
	void Draw();
	void End();
	void ObjectCol();
	void BulletCol();
private:
	// �������񂷂ׂē������Ă��邱�ƂƂ���
	bool HitPlayer;
	bool HitShot;
	bool HitBoss;
	bool HitBat;
	bool HitEye;
	bool m_isGameEnd;

	bool isHitPlayerToEnemy;
	bool isHitShotToEnemy;

	int ChangeCount;

	Player player;	//�R���X�g���N�^�ɓ���	//�����������ɓ���
	Boss boss;
	Bat bat;
	Eye eye;
};




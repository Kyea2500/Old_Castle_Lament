#pragma once
#include "../../Vec2/Vec2.h"
/// プレイヤークラス
/// </summary>
class Player
{
public:
	Player();		//コンストラクタ
	~Player();		//デストラクタ

	void Init();	//初期化
	void Update();	//更新
	void Draw();	//描画
	void End();		//解放
public:
	void OnDamage();

	void UpdateNormal(); // ゲーム中のUpdate
	void UpdateDead();   // 死亡後のUpdate
	void InitShot();
	void UpdateShot();
	void DrawShot();
	void EndShot();

	// プレイヤーの当たり判定
	float Player_HitCircleX();
	float Player_HitCircleY();
	float Player_HitCircleRad();
	
	// 弾の当たり判定
	float Shot_CircleX();
	float Shot_CircleY();
	float Shot_CircleRad();

private:
	void UpdateMove();
	void UpdateAttack();
	void UpdateDash();
	void UpdateChange();
	

	// ↓ 各種に必要な関数
	// 待機
	int m_handleIdle;
	// 移動
	int m_handleMove;
	// 攻撃
	int m_handleAttack;
	// 弾の種類
	int m_handleIce_Shot;		// 氷弾　火力が高く、速度は遅い
	int m_handleThunder_Shot;	// 雷弾　火力が中間、速度も中間
	int m_handleAir_Shot;		// 風弾　火力が低く、速度は早い
	//耐久値ゲージ
	int m_handleLife;
	// 死亡
	int m_handleDead;
	bool m_isDead;
	// プレイヤーの表示位置
	Vec2 m_pos;
	// 弾の表示位置
	Vec2 shot_pos;

	// 体力処理
	int m_Life;
	bool m_isDamage;

	//　移動方向　
	bool m_isDirLeft;	// true:左向き 
	bool m_isDirRight;	// true:右向き 
	bool m_isDirUp;		// true:上に	
	bool m_isDirDown;	// true:下に

	// キャラクターが向いている方向
	bool m_ishir;	// true:左向き　false:右向き

	// アニメーション関連
	int m_animFrame; // フレーム数を数える

	// 移動処理
	bool m_isMove;		// true:動いている	false:待機
	// 移動値を入れるもの
	float m_isSpeed;

	// ダッシュ処理
	bool m_isDash;		// true:素早く移動　false:変化なし
	// ダッシュ値を入れるもの
	float m_DashSpeed;
	// ダッシュボタンのトリガー判定
	// 1つ前のフレームにダッシュボタンが押されていたかどうかを覚えておく
	bool m_isLastDashButton;

	// 攻撃の処理
	bool m_isAttack;	// true:攻撃　false:変化なし
	// true:弾を撃っている　false:弾を撃っていない
	bool m_isShot;
	// true:射撃ボタンを押した　false:射撃ボタンを押していない
	bool m_ShotBotton;

	// 魔法の切り替え処理
	bool m_isChange;	//true:切り替え　false:変化なし
	// 再度切り替えるためのクールタイム(連続切り替え禁止処理)
	float m_isChargingFrame;
	int m_Chant;
	// 弾の切り替え　0:氷弾　1:雷弾　2:風弾
	int m_Change;

	int m_blinktime;
};


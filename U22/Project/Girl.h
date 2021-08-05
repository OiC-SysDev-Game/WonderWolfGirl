#pragma once
#include "U22.h"
#include "Wolf.h"

//相互インクルード処理
class CWolf;

class CGirl
{
private:
	//とりあえず適当な数値
	int maxHealth = 3;
	float accelerateSpd = 0.2;
	float decelerateSpd = 0.14;
	float maxSpd = 2.7;
	float gravity = 0.45;

	float invicibleTime = 2;
	float invicibleWait = 0;

	//std::clamp(丸め込み)

	int health;		//初期値3

	bool isRide;	//狼に乗っているか
	bool isRight;	//右向きかどうか
	bool isMove;

	float Xpos;
	float Ypos;
	float Xspd;
	float Yspd;

	float XbackPos;
	float YbackPos;

	CTexture texture[4];
	SpriteAnimationController motion;

	CWolf* wolf;

	enum motionID
	{
		emWait,
		emWalk,
		emHit,
		emDown,
		emRide,
		emJump,
		emEnd
	};

	//motionIDに対応する当たり判定
	float motionOffset[6][4] = { {15,15,-5,0},{25,5,-35,-8},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0} };

public:
	CGirl();
	~CGirl();
	bool Load();
	void Initialize(CWolf* arg);
	void Update();
	void Render(CCamera* _camera);
	void RenderDebug(CCamera* _camera);
	void Release();

	int GetHealth() { return health; }
	bool GetCarry() { return isRide; }
	void SetCarry(bool arg) { isRide = arg; }
	bool GetDirection() { return isRight; }
	void SetDirection(bool arg) { if (motion.GetMotionNo() != emDown) isRight = arg; }
	bool GetMove() { return isMove; }
	void SetMove(bool arg) { if (motion.GetMotionNo() != emDown) isMove = arg; }

	CRectangle GetRect();
	CRectangle GetBackRect();

	bool TakeDamage(int damage);		//被ダメージ処理 体力が0以下になるとfalseが戻る	第2引数で割合処理

	void Acceleration();	//移動状態
	void Neutral();			//停止状態
	void Move();			//移動処理

	void CollisionObject(float ox, float oy);
};


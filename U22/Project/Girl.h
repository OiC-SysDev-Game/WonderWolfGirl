#pragma once
#include "U22.h"
#include "Wolf.h"

//相互インクルード処理
class CWolf;

class CGirl
{
private:
	//とりあえず適当な数値
	int max_Health = 3;
	float accelerate_Spd = 0.2;
	float decelerate_Spd = 0.14;
	float max_Spd = 2.7;
	float gravity = 0.45;

	float invicibleTime = 1;
	float invicibleWait = 0;

	//後で削除
	//float width = 35;
	//float height = 70;

	int health;		//初期値3

	bool isRide;	//狼に乗っているか
	bool isRight;	//右向きかどうか
	bool isMove;

	float Xpos;
	float Ypos;
	float Xspd;
	float Yspd;

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

public:
	CGirl();
	~CGirl();
	bool Load();
	void Initialize(CWolf* arg);
	void Update();
	void Render(CCamera* _camera);
	void RenderDebug(CCamera* _camera);
	void Release();

	int GetHealth(void) { return health; }
	bool GetCarry(void) { return isRide; }
	void SetCarry(bool arg) { isRide = arg; }
	bool GetDirection(void) { return isRight; }
	void SetDirection(bool arg) { isRight = arg; }
	bool GetMove(void) { return isMove; }
	void SetMove(bool arg) { isMove = arg; }

	CRectangle GetRect(void);

	bool TakeDamage(int damage);		//被ダメージ処理 体力が0以下になるとfalseが戻る	第2引数で割合処理

	void Acceleration(void);	//移動状態
	void Neutral(void);			//停止状態
	void Move(void);			//移動処理
};


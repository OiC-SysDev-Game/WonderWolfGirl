#pragma once
#include "U22.h"
#include "Girl.h"

//相互インクルード処理
class CGirl;

class CWolf
{
private:
	//とりあえず適当な数値
	int maxHealth = 100;
	float maxSpd = 5;
	float accelerateSpd = 0.5;
	float decelerateSpd = 0.25;
	float jumpSpd = 18;
	float gravity = 0.45;

	int health;		//初期値100

	bool isCarry;	//少女を乗せているか
	bool isRight;	//右向きかどうか
	bool canJump;

	float Xpos;
	float Ypos;
	float Xspd;
	float Yspd;

	//stage側処理
	float XbackPos;
	float YbackPos;

	CGirl* girl;

	CTexture texture[1];
	SpriteAnimationController motion;

	enum motionID
	{
		emWait,
		emWalk,
		emJump,
		emAtk,
		emCarry,
		emHit,
		emDown
	};

public:
	CWolf();
	~CWolf();
	bool Load();
	void Initialize(CGirl* arg);
	void Update();
	void Render(CCamera* _camera);
	void RenderDebug(CCamera* _camera);
	void Release();

	int GetHealth() { return health; }
	bool GetCarry() { return isCarry; }
	bool GetDirection() { return isRight; }
	CRectangle GetRect();
	CRectangle GetBackRect();

	bool TakeDamage(int damage, bool isRatio);		//被ダメージ処理 体力が0以下になるとfalseが戻る	第2引数で割合処理

	void Acceleration(bool isRight);				//左右入力
	void Jump();								//ジャンプ入力
	void Neutral();								//入力無し
	void Move();								//移動処理

	void Attack();
	void Howling();
	void Carry();

	void CollisionObject(float ox,float oy);
};


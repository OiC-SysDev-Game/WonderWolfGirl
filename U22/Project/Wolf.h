#pragma once
#include "U22.h"
#include "Girl.h"

//相互インクルード処理
class CGirl;

class CWolf
{
private:
	//とりあえず適当な数値
	const int max_Health = 100;
	const float max_Spd = 5;
	const float accelerate_Spd = 0.5;
	const float decelerate_Spd = 0.25;
	const float jump_Spd = 10;
	const float gravity = 0.45;

	//後で削除
	const int width = 320;
	const int height = 180;

	int health;		//初期値100

	bool isCarry;	//少女を乗せているか
	bool isRight;	//右向きかどうか
	bool canJump;

	float Xpos;
	float Ypos;
	float Xspd;
	float Yspd;

	CGirl* girl;

	enum motionID
	{
		eWait,
		eMove,
		eJump,
		eAtk,
		eCarry,
		eHit,
		eDown
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

	int GetHealth(void) { return health; }
	bool GetCarry(void) { return isCarry; }
	bool GetDirection(void) { return isRight; }
	CRectangle GetRect(void) { return CRectangle{ Xpos,Ypos,Xpos + width,Ypos + height }; }

	bool TakeDamage(int damage, bool isRatio);		//被ダメージ処理 体力が0以下になるとfalseが戻る	第2引数で割合処理

	void Acceleration(bool isRight);				//左右入力
	void Jump(void);								//ジャンプ入力
	void Neutral(void);								//入力無し
	void Move(void);								//移動処理

	void Attack(void);
	void Howling(void);
	void Carry(void);
};


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

	/*後で削除
	int width = 320;
	int height = 180;*/

	int health;		//初期値100

	bool isCarry;	//少女を乗せているか
	bool isRight;	//右向きかどうか
	bool canJump;

	float Xpos;
	float Ypos;
	float Xspd;
	float Yspd;

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

	int GetHealth(void) { return health; }
	bool GetCarry(void) { return isCarry; }
	bool GetDirection(void) { return isRight; }
	CRectangle GetRect(void);

	bool TakeDamage(int damage, bool isRatio);		//被ダメージ処理 体力が0以下になるとfalseが戻る	第2引数で割合処理

	void Acceleration(bool isRight);				//左右入力
	void Jump(void);								//ジャンプ入力
	void Neutral(void);								//入力無し
	void Move(void);								//移動処理

	void Attack(void);
	void Howling(void);
	void Carry(void);
};


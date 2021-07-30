#pragma once
#include "U22.h"
#include "Girl.h"

//相互インクルード処理
class CGirl;

class CWolf
{
private:
	//仮の画像
	CTexture WolfImage;

	//とりあえず適当な数値
	int maxHealth = 100;
	float maxSpd = 5;
	float accelerateSpd = 0.5;
	float decelerateSpd = 0.25;
	float jumpSpd = 12;
	float gravity = 0.20f;

	//後で削除
	float width = 400;
	float height = 170;

	int health;		//初期値100

	bool isCarry;	//少女を乗せているか
	bool isRight;	//右向きかどうか
	bool canJump;

	float Xpos;
	float Ypos;

	float XBackPos;
	float YBackPos;

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
	CRectangle GetRect(void) { return CRectangle{ Xpos - width / 2, Ypos - height / 2, Xpos + width / 2, Ypos + height / 2 }; }
	CRectangle GetBackRect(void) { return CRectangle{ XBackPos - width / 2, YBackPos - height / 2, XBackPos + width / 2, YBackPos + height / 2 }; }

	bool TakeDamage(int damage, bool isRatio);		//被ダメージ処理 体力が0以下になるとfalseが戻る	第2引数で割合処理

	void Acceleration(bool isRight);				//左右入力
	void Jump(void);								//ジャンプ入力
	void Neutral(void);								//入力無し
	void Move(void);								//移動処理

	void Attack(void);
	void Howling(void);
	void Carry(void);

	void CollisionObject(float ox, float oy);
};


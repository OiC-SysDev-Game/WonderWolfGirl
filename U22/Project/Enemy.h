#pragma once
#include "U22.h"

class CEnemy
{
protected:
	int maxHealth;
	int health;

	int atk;
	float attackInterval;	//攻撃間隔
	float invicibleTime;	//無敵時間
	float search_Range;

	float attackWait = 0;
	float invicibleWait = 0;

	float max_Spd;
	float accelerate_Spd;
	float decelerate_Spd;
	float jump_Spd;
	float gravity;

	bool isRight;

	float Xpos;
	float Ypos;
	float Xspd;
	float Yspd;

	CTexture texture;
	SpriteAnimationController motion;

public:
	CEnemy() {
	}

	~CEnemy()
	{};
	virtual bool Load() = 0;
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Render(CCamera* _camera) = 0;
	virtual void RenderDebug(CCamera* _camera);
	virtual void Release() = 0;

	bool TakeDamage();		//被ダメージ処理 体力が0以下になるとfalseが戻る	第2引数で割合処理

	bool GetDirection(void) { return isRight; }
	float GetXPos(void) { return Xpos; }
	float GetYPos(void) { return Ypos; }
};
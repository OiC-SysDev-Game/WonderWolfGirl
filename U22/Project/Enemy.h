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
	float searchRange;

	float attackWait = 0;
	float invicibleWait = 0;

	float maxSpd;
	float accelerateSpd;
	float decelerateSpd;
	float jumpSpd;
	float gravity;

	bool isRight;
	bool isShow;

	float Xpos;
	float Ypos;
	float Xspd;
	float Yspd;

	CTexture texture;
	SpriteAnimationController motion;

public:
	virtual bool Load() = 0;
	virtual void Initialize() = 0;
	virtual void Update(CRectangle girl,CRectangle wolf) = 0;
	virtual void Render(CCamera* _camera) = 0;
	virtual void RenderDebug(CCamera* _camera);
	virtual void Release() = 0;

	virtual bool TakeDamage() = 0;		//被ダメージ処理 体力が0以下になるとfalseが戻る	第2引数で割合処理

	bool GetDirection(void) { return isRight; }
	bool GetShow(void) { return isShow; }
	float GetXPos(void) { return Xpos; }
	float GetYPos(void) { return Ypos; }
};


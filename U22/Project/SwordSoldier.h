#pragma once
#include "U22.h"
#include "Enemy.h"

class CSwordSoldier : public CEnemy
{
private:
	bool isMove = false;
	bool isAttack = false;

	float height = 240;
	float width = 130;

	float searchRange = 300;
	float attackSerchRange = 150;
	float invicibleTime = 1;
	float attackInterval = 3;

	CTexture texture[2];
	SpriteAnimationController motion;

	enum motionID
	{
		emWait,
		emWalk,
		emAttack,
		emHit,
		emDown,
		emEnd
	};

	float motionOffset[6][4] = { {95,100,-110,-10},{95,100,-110,-10},{95,100,-110,-10},{0,0,0,0},{0,0,0,0},{0,0,0,0} };

public:
	bool Load();
	void Initialize();
	void Update(CRectangle girl, CRectangle wolf);
	void Render(CCamera* _camera);
	void RenderDebug(CCamera* _camera);
	void Release();

	void Acceleration();
	void Neutral();
	void Move();
	void Attack();

	void SearchAllies(CRectangle girl, CRectangle wolf);
	bool TakeDamage();
	bool GetAttack() { return motion.GetMotionNo() == emAttack; }
	CRectangle GetRect();
	CRectangle GetAttackRect();
	CRectangle GetSerchRect();
	CRectangle GetAttackSerchRect();
};
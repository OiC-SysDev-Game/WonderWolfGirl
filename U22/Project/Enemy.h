#pragma once
#include "U22.h"

class CEnemy
{
protected:
	int maxHealth;
	int health;

	int atk;
	float attackInterval;	//�U���Ԋu
	float invicibleTime;	//���G����
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
	virtual bool Load() = 0;
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Render(CCamera* _camera) = 0;
	virtual void RenderDebug(CCamera* _camera);
	virtual void Release() = 0;

	bool TakeDamage();		//��_���[�W���� �̗͂�0�ȉ��ɂȂ��false���߂�	��2�����Ŋ�������

	bool GetDirection(void) { return isRight; }
	float GetXPos(void) { return Xpos; }
	float GetYPos(void) { return Ypos; }
};
#pragma once
#include "U22.h"
#include "Girl.h"

//���݃C���N���[�h����
class CGirl;

class CWolf
{
private:
	//�Ƃ肠�����K���Ȑ��l
	int maxHealth = 100;
	float maxSpd = 5;
	float accelerateSpd = 0.5;
	float decelerateSpd = 0.25;
	float jumpSpd = 18;
	float gravity = 0.45;

	int health;		//�����l100

	bool isCarry;	//�������悹�Ă��邩
	bool isRight;	//�E�������ǂ���
	bool canJump;

	float Xpos;
	float Ypos;
	float Xspd;
	float Yspd;

	//stage������
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

	bool TakeDamage(int damage, bool isRatio);		//��_���[�W���� �̗͂�0�ȉ��ɂȂ��false���߂�	��2�����Ŋ�������

	void Acceleration(bool isRight);				//���E����
	void Jump();								//�W�����v����
	void Neutral();								//���͖���
	void Move();								//�ړ�����

	void Attack();
	void Howling();
	void Carry();

	void CollisionObject(float ox,float oy);
};


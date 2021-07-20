#pragma once
#include "U22.h"
#include "Wolf.h"

//���݃C���N���[�h����
class CWolf;

class CGirl
{
private:
	//�Ƃ肠�����K���Ȑ��l
	int max_Health = 3;
	float accelerate_Spd = 0.2;
	float decelerate_Spd = 0.14;
	float max_Spd = 2.7;
	float gravity = 0.45;

	float invicibleTime = 1;
	float invicibleWait = 0;

	//��ō폜
	//float width = 35;
	//float height = 70;

	int health;		//�����l3

	bool isRide;	//�T�ɏ���Ă��邩
	bool isRight;	//�E�������ǂ���
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

	bool TakeDamage(int damage);		//��_���[�W���� �̗͂�0�ȉ��ɂȂ��false���߂�	��2�����Ŋ�������

	void Acceleration(void);	//�ړ����
	void Neutral(void);			//��~���
	void Move(void);			//�ړ�����
};


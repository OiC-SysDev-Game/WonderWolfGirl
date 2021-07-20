#pragma once
#include "U22.h"
#include "Girl.h"

//���݃C���N���[�h����
class CGirl;

class CWolf
{
private:
	//�Ƃ肠�����K���Ȑ��l
	const int max_Health = 100;
	const float max_Spd = 5;
	const float accelerate_Spd = 0.5;
	const float decelerate_Spd = 0.25;
	const float jump_Spd = 10;
	const float gravity = 0.45;

	//��ō폜
	const int width = 320;
	const int height = 180;

	int health;		//�����l100

	bool isCarry;	//�������悹�Ă��邩
	bool isRight;	//�E�������ǂ���
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

	bool TakeDamage(int damage, bool isRatio);		//��_���[�W���� �̗͂�0�ȉ��ɂȂ��false���߂�	��2�����Ŋ�������

	void Acceleration(bool isRight);				//���E����
	void Jump(void);								//�W�����v����
	void Neutral(void);								//���͖���
	void Move(void);								//�ړ�����

	void Attack(void);
	void Howling(void);
	void Carry(void);
};


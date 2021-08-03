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

	/*��ō폜
	int width = 320;
	int height = 180;*/

	int health;		//�����l100

	bool isCarry;	//�������悹�Ă��邩
	bool isRight;	//�E�������ǂ���
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

	bool TakeDamage(int damage, bool isRatio);		//��_���[�W���� �̗͂�0�ȉ��ɂȂ��false���߂�	��2�����Ŋ�������

	void Acceleration(bool isRight);				//���E����
	void Jump(void);								//�W�����v����
	void Neutral(void);								//���͖���
	void Move(void);								//�ړ�����

	void Attack(void);
	void Howling(void);
	void Carry(void);
};


#pragma once
#include "U22.h"
#include "Wolf.h"

//���݃C���N���[�h����
class CWolf;

class CGirl
{
private:
	//�Ƃ肠�����K���Ȑ��l
	int maxHealth = 3;
	float accelerateSpd = 0.2;
	float decelerateSpd = 0.14;
	float maxSpd = 2.7;
	float gravity = 0.45;

	float invicibleTime = 2;
	float invicibleWait = 0;

	//��ō폜
	//float width = 35;
	//float height = 70;
	// 
	//std::clamp(�ۂߍ���)
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

	//motionID�ɑΉ����铖���蔻��
	float motionOffset[6][4] = { {15,15,-5,0},{25,5,-35,-8},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0} };

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
	void SetDirection(bool arg) { if (motion.GetMotionNo() != emDown) isRight = arg; }
	bool GetMove(void) { return isMove; }
	void SetMove(bool arg) { if (motion.GetMotionNo() != emDown) isMove = arg; }

	CRectangle GetRect(void);

	bool TakeDamage(int damage);		//��_���[�W���� �̗͂�0�ȉ��ɂȂ��false���߂�	��2�����Ŋ�������

	void Acceleration(void);	//�ړ����
	void Neutral(void);			//��~���
	void Move(void);			//�ړ�����
};


#pragma once
#include "U22.h"
#include "Girl.h"

//���݃C���N���[�h����
class CGirl;

class CWolf
{
private:
	//���̉摜
	CTexture WolfImage;

	//�Ƃ肠�����K���Ȑ��l
	int maxHealth = 100;
	float maxSpd = 5;
	float accelerateSpd = 0.5;
	float decelerateSpd = 0.25;
	float jumpSpd = 12;
	float gravity = 0.20f;

	//��ō폜
	float width = 400;
	float height = 170;

	int health;		//�����l100

	bool isCarry;	//�������悹�Ă��邩
	bool isRight;	//�E�������ǂ���
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

	bool TakeDamage(int damage, bool isRatio);		//��_���[�W���� �̗͂�0�ȉ��ɂȂ��false���߂�	��2�����Ŋ�������

	void Acceleration(bool isRight);				//���E����
	void Jump(void);								//�W�����v����
	void Neutral(void);								//���͖���
	void Move(void);								//�ړ�����

	void Attack(void);
	void Howling(void);
	void Carry(void);

	void CollisionObject(float ox, float oy);
};


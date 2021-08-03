#include "Wolf.h"

CWolf::CWolf() {
}

CWolf::~CWolf() 
{
	Release();
};

bool CWolf::Load() 
{
	//幅、高さ、コマ数
	texture[0].Load("Character/Wolf/Wolf_Walk_400_278_30.png");

	SpriteAnimationCreate anim[] = 
	{
		{
		"Wait",
		0,0,
		400,278,
		TRUE,{{2,0,0}}
		},
		{
		"Walk",
		0,0,
		400,278,
		TRUE,{{2,0,0},{2,1,0},{2,2,0},{2,3,0},{2,4,0},{2,0,1},{2,1,1},{2,2,1},{2,3,1},{2,4,1},{2,0,2},{2,1,2},{2,2,2},{2,3,2},{2,4,2},{2,0,3},{2,1,3},{2,2,3},{2,3,3},{2,4,3},{2,0,4},{2,1,4},{2,2,4},{2,3,4},{2,4,4},{2,0,5},{2,1,5},{2,2,5},{2,3,5},{2,4,5}}
		},
	};

	//本来はemEnd
	motion.Create(anim, 2);
	motion.ChangeMotion(0);
	
	return true;
}

void CWolf::Initialize(CGirl* arg) 
{
	health = maxHealth;
	isCarry = false;
	isRight = true;
	canJump = true;

	Xpos = 0;
	Ypos = 0;
	Xspd = 0;
	Yspd = 0;

	girl = arg;

	Load();
}

void CWolf::Update() 
{
	if (g_pInput->IsHold(u22::input::KeyCode::D)) Acceleration(true);
	else if (g_pInput->IsHold(u22::input::KeyCode::A)) Acceleration(false);
	else Neutral();

	if (g_pInput->IsPush(u22::input::KeyCode::Space)) Jump();

	Move();

	if (g_pInput->IsPush(u22::input::MouseButton::Left)) Attack();
	if (g_pInput->IsPush(u22::input::MouseButton::Right)) Howling();
	if (g_pInput->IsPush(u22::input::KeyCode::W)) Carry();

	motion.AddTimer(g_pClock->GetFrameSecond());
}

void CWolf::Render(CCamera* _camera) 
{
	CRectangle rect = motion.GetSourceRectangle();

	if (!isRight) {
		float tmp = rect.right;
		rect.right = rect.left;
		rect.left = tmp;
	}

	if (motion.GetMotionNo() == 0) {
		texture[0].Render({ Xpos,Ypos }, rect, *_camera);
	}
	else
	{
		texture[motion.GetMotionNo() - 1].Render({ Xpos,Ypos }, rect, *_camera);
	}

	::GraphicsUtilities::RenderLineRectangle(GetRect(), color::rgba::kGreen, *_camera);
}

void CWolf::RenderDebug(CCamera* _camera) 
{

}

void CWolf::Release() 
{

}

bool CWolf::TakeDamage(int damage, bool isRatio)
{
	if (!isRatio) health -= damage;
	else health -= int(maxHealth * (damage / 100));

	if (isCarry)
	{
		isCarry = false;
		girl->SetCarry(false);
	}

	return health > 0;
}

void CWolf::Acceleration(bool isRight)
{
	if (isRight)
	{
		Xspd += accelerateSpd;
		if (Xspd > maxSpd) Xspd = maxSpd;
	}
	else
	{
		Xspd -= accelerateSpd;
		if (Xspd < -maxSpd) Xspd = -maxSpd;
	}

	if (motion.GetMotionNo() == emWait)
		motion.ChangeMotion(emWalk);
}

void CWolf::Jump(void)
{
	if (canJump)
	{
		Yspd = -jumpSpd;
		canJump = false;
	}
}

void CWolf::Neutral(void)
{
	if (Xspd > 0)
	{
		Xspd -= decelerateSpd;
		if (Xspd <= 0) Xspd = 0;
	}
	else if (Xspd < 0)
	{
		Xspd += decelerateSpd;
		if (Xspd >= 0) Xspd = 0;
	}

	if (Xspd == 0 && motion.GetMotionNo() == emWalk)
		motion.ChangeMotion(emWait);
}

void CWolf::Move(void)
{
	Yspd += gravity;

	Xpos += Xspd;
	Ypos += Yspd;

	//着地処理
	if (GetRect().bottom > 700)
	{
		Ypos = 700 - GetRect().GetHeight();
		Yspd = 0;
		canJump = true;

		if (Xspd > 0)
		{
			isRight = true;
		}
		else if (Xspd < 0)
		{
			isRight = false;
		}
	}
}

void CWolf::Attack(void)
{
	if (!isCarry)
	{

	}
}

void CWolf::Howling(void)
{
	if (!isCarry)
	{
		if (girl->GetMove())
		{
			girl->SetMove(false);
		}
		else
		{
			girl->SetMove(true);
			girl->SetDirection(isRight);
		}
	}
}

void CWolf::Carry(void)
{
	if (!isCarry)
	{
		if (GetRect().CollisionRectangle
		(CRectangle(girl->GetRect())) && girl->GetHealth() > 0 && canJump)
		{
			//少女を同期
			isCarry = true;
			girl->SetCarry(true);
			girl->SetMove(false);
		}
	}
	else
	{
		if (canJump)
		{
			//降ろす
			isCarry = false;
			girl->SetCarry(false);
		}
	}
}

CRectangle CWolf::GetRect(void) 
{
	CRectangle rect = motion.GetSourceRectangle();
	rect.SetBounds({ Xpos,Ypos }, motion.GetSourceRectangle().GetSize());
	return rect;
}
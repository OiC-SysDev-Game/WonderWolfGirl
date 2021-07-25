#include "Wolf.h"

CWolf::CWolf() {
}

CWolf::~CWolf()
{
	Release();
};

bool CWolf::Load() {
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
}

void CWolf::Render(CCamera* _camera)
{
	::GraphicsUtilities::RenderLineRectangle(CRectangle(Xpos, Ypos, Xpos + width, Ypos + height), color::rgba::kRed, *_camera);
	if (isRight)
	{
		::GraphicsUtilities::RenderLineRectangle(
			CRectangle(Xpos + 270, Ypos + 35, Xpos + 290, Ypos + 70),
			color::rgba::kRed, *_camera);
	}
	else
	{
		::GraphicsUtilities::RenderLineRectangle(
			CRectangle(Xpos + 30, Ypos + 35, Xpos + 50, Ypos + 70),
			color::rgba::kRed, *_camera);
	}
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
}

void CWolf::Move(void)
{
	Yspd += gravity;

	Xpos += Xspd;
	Ypos += Yspd;

	//’…’nˆ—
	if (Ypos + height > 700)
	{
		Ypos = 700 - height;
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
		if (CRectangle(Xpos, Ypos, Xpos + width, Ypos + height).CollisionRectangle
		(CRectangle(girl->GetRect())) && canJump)
		{
			//­—‚ð“¯Šú
			isCarry = true;
			girl->SetCarry(true);
			girl->SetMove(false);
		}
	}
	else
	{
		if (canJump)
		{
			//~‚ë‚·
			isCarry = false;
			girl->SetCarry(false);
		}
	}
}

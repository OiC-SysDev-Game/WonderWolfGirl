#include "SwordSoldier.h"

void CSwordSoldier::Initialize(void)
{
	maxHealth = 2;
	health = maxHealth;
	atk = 10;

	accelerate_Spd = 0.2;
	decelerate_Spd = 0.14;
	max_Spd = 2.7;
	gravity = 0.45;
	isRight = true;

	Xpos = 1100;
	Ypos = 100;
	Xspd = 0;
	Yspd = 0;
}

void CSwordSoldier::Update(void)
{
	if (false)
	{
		isMove = true;
		//Œü‚«ŒŸ’m
		if (false) isRight = true;
		else isRight = false;
	}
	else isMove = false;


	if (isMove) Acceleration();
	else Neutral();

	Move();
}

void CSwordSoldier::Render(CCamera* _camera)
{
	::GraphicsUtilities::RenderLineRectangle(CRectangle(Xpos - 300, Ypos, Xpos + width + 300, Ypos + height), color::rgba::kBlue, *_camera);
	::GraphicsUtilities::RenderLineRectangle(CRectangle(Xpos, Ypos, Xpos + width, Ypos + height), color::rgba::kGreen, *_camera);

}

void CSwordSoldier::RenderDebug(CCamera* _camera)
{

}

void CSwordSoldier::Release(void)
{

}

bool CSwordSoldier::Load(void)
{
	return true;
}

void CSwordSoldier::Acceleration(void)
{
	if (isRight)
	{
		Xspd += accelerate_Spd;
		if (Xspd > max_Spd) Xspd = max_Spd;
	}
	else
	{
		Xspd += -accelerate_Spd;
		if (Xspd < -max_Spd) Xspd = -max_Spd;
	}
}

void CSwordSoldier::Neutral(void)
{
	if (Xspd > 0)
	{
		Xspd -= decelerate_Spd;
		if (Xspd <= 0) Xspd = 0;
	}
	else if (Xspd < 0)
	{
		Xspd += decelerate_Spd;
		if (Xspd >= 0) Xspd = 0;
	}
}

void CSwordSoldier::Move(void)
{
	Yspd += gravity;

	Xpos += Xspd;
	Ypos += Yspd;

	if (Ypos + height >= 700)
	{
		Ypos = 700 - height;
		Yspd = 0;
	}
}

void CSwordSoldier::Attack(void)
{

}
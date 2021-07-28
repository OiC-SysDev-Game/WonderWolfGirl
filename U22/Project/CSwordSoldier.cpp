#include "SwordSoldier.h"

void CSwordSoldier::Initialize() 
{
	maxHealth = 2;
	health = maxHealth;
	atk = 10;

	accelerateSpd = 0.2;
	decelerateSpd = 0.14;
	maxSpd = 2.7;
	gravity = 0.45;
	isRight = false;

	Xpos = 1100;
	Ypos = 100;
	Xspd = 0;
	Yspd = 0;

	attackWait = 0;

	Load();
}

void CSwordSoldier::Update(CRectangle girl, CRectangle wolf)
{
	SearchAllies(girl, wolf);

	if (isAttack && attackWait <= 0 && Xspd == 0) Attack();
	
	if (isMove) 
	{	
		Acceleration();
	}
	else Neutral();

	Move();

	motion.AddTimer(g_pClock->GetFrameSecond());
	attackWait -= g_pClock->GetFrameSecond();

	if (motion.IsEndMotion() && motion.GetMotionNo() == emAttack) motion.ChangeMotion(emWait);
}

void CSwordSoldier::Render(CCamera* _camera)
{
	CRectangle rect = motion.GetSourceRectangle();

	if (isRight) {
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

	rect = motion.GetSourceRectangle();
	rect.SetBounds({ Xpos,Ypos }, rect.GetSize());
	::GraphicsUtilities::RenderLineRectangle(rect, color::rgba::kGreen, *_camera);

	//::GraphicsUtilities::RenderLineRectangle(CRectangle(Xpos, Ypos, Xpos + width, Ypos + height), color::rgba::kGreen, *_camera);
	::GraphicsUtilities::RenderLineRectangle(CRectangle((Xpos + (motion.GetSourceRectangle().GetWidth() * 0.5f)) - searchRange, Ypos, (Xpos + (motion.GetSourceRectangle().GetWidth() * 0.5f)) + searchRange, Ypos + height), color::rgba::kBlue, *_camera);
}

void CSwordSoldier::RenderDebug(CCamera* _camera) 
{

}

void CSwordSoldier::Release() 
{

}

bool CSwordSoldier::Load() 
{
	texture[0].Load("Character/Robot/Sword/Sword_Walk_296_256_12.png");
	texture[1].Load("Character/Robot/Sword/Sword_Attack_296_256_12.png");

	SpriteAnimationCreate anim[] =
	{
		{
			"Wait",
				0, 0,
				296, 256,
				TRUE, { {2,0,0} }
		},
		{
			"Walk",
				0, 0,
				296, 256,
				TRUE, { {2,0,0},{2,1,0},{2,2,0},{2,0,1},{2,1,1},{2,2,1},{2,0,2},{2,1,2},{2,2,2},{2,0,3},{2,1,3},{2,2,3} }
		},
		{
			"Attack",
				0, 0,
				296, 256,
				FALSE, { {2,0,0},{2,1,0},{2,2,0},{2,0,1},{2,1,1},{2,2,1},{2,0,2},{2,1,2},{2,2,2},{2,0,3},{2,1,3},{2,2,3} }
		},
	};
	//–{—ˆ‚ÍemEnd
	motion.Create(anim, 3);
	motion.ChangeMotion(0);

	return true;
}

void CSwordSoldier::Acceleration()
{
	if (isRight)
	{
		Xspd += accelerateSpd;
		if (Xspd > maxSpd) Xspd = maxSpd;
	}
	else
	{
		Xspd += -accelerateSpd;
		if (Xspd < -maxSpd) Xspd = -maxSpd;
	}

	if (motion.GetMotionNo() == emWait)
		motion.ChangeMotion(emWalk);
}

void CSwordSoldier::Neutral()
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

void CSwordSoldier::Move()
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

void CSwordSoldier::Attack()
{
	motion.ChangeMotion(emAttack);
	attackWait = attackInterval;
}

void CSwordSoldier::SearchAllies(CRectangle girl, CRectangle wolf)
{
	if (std::abs((girl.left + (girl.GetWidth() * 0.5f)) - (Xpos + (motion.GetSourceRectangle().GetWidth() * 0.5f))) < std::abs((wolf.left + (wolf.GetWidth() * 0.5f)) - (Xpos + (motion.GetSourceRectangle().GetWidth() * 0.5f))))
	{
		if (girl.CollisionRectangle(CRectangle((Xpos + (motion.GetSourceRectangle().GetWidth() * 0.5f)) - searchRange, Ypos, (Xpos + (motion.GetSourceRectangle().GetWidth() * 0.5f)) + searchRange, Ypos + height)))
		{
			(Xpos + (motion.GetSourceRectangle().GetWidth() * 0.5f) > girl.left + (girl.GetWidth() * 0.5f)) ? isRight = false : isRight = true;

			if (girl.CollisionRectangle(CRectangle((Xpos + (motion.GetSourceRectangle().GetWidth() * 0.5f)) - 125, Ypos, (Xpos + (motion.GetSourceRectangle().GetWidth() * 0.5f)) + 125, Ypos + height)))
			{
				isMove = false;
				isAttack = true;
			}
			else isMove = true;
		}
		else
		{
			isMove = false;
			isAttack = false;
		}
	}
	else 
	{
		if (wolf.CollisionRectangle(CRectangle((Xpos + (motion.GetSourceRectangle().GetWidth() * 0.5f)) - searchRange, Ypos, (Xpos + (motion.GetSourceRectangle().GetWidth() * 0.5f)) + searchRange, Ypos + height)))
		{
			(Xpos + (motion.GetSourceRectangle().GetWidth() * 0.5f) > wolf.left + (wolf.GetWidth() * 0.5f)) ? isRight = false : isRight = true;

			if (wolf.CollisionRectangle(CRectangle((Xpos + (motion.GetSourceRectangle().GetWidth() * 0.5f)) - 125, Ypos, (Xpos + (motion.GetSourceRectangle().GetWidth() * 0.5f)) + 125, Ypos + height)))
			{
				isMove = false;
				isAttack = true;
			}
			else isMove = true;
		}
		else
		{
			isMove = false;
			isAttack = false;
		}
	}
}
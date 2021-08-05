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
	isShow = true;

	Xpos = 1100;
	Ypos = 100;
	Xspd = 0;
	Yspd = 0;

	XbackPos = 0;
	YbackPos = 0;

	attackWait = 0;

	Load();
}

void CSwordSoldier::Update(CRectangle girl, CRectangle wolf)
{
	if (isShow) 
	{
		XbackPos = Xpos;
		YbackPos = Ypos;

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
}

void CSwordSoldier::Render(CCamera* _camera)
{
	if (isShow) 
	{
		CRectangle rect = motion.GetSourceRectangle();

		if (isRight) {
			float tmp = rect.right;
			rect.right = rect.left;
			rect.left = tmp;
		}


		if ((int)(invicibleWait * 10) % 2 == 0)
		{
			//歩きで代用
			if (motion.GetMotionNo() == 0) {
				texture[motion.GetMotionNo()].Render({ Xpos,Ypos - motionOffset[motion.GetMotionNo()][1] }, rect, *_camera);
			}
			else 
			{
				texture[motion.GetMotionNo() - 1].Render({ Xpos,Ypos - motionOffset[motion.GetMotionNo()][1] }, rect, *_camera);
			}
		}

		rect = motion.GetSourceRectangle();
		rect.SetBounds({ Xpos,Ypos }, rect.GetSize());
		::GraphicsUtilities::RenderLineRectangle(rect, color::rgba::kGreen, *_camera);

		rect = GetRect();

		//当たり判定　無敵だと白
		if (invicibleWait > 0) ::GraphicsUtilities::RenderLineRectangle(rect, color::rgba::kWhite, *_camera);
		else ::GraphicsUtilities::RenderLineRectangle(rect, color::rgba::kRed, *_camera);

		::GraphicsUtilities::RenderLineRectangle(GetSerchRect(), color::rgba::kBlue, *_camera);

		if (motion.GetMotionNo() == emAttack)
		{
			::GraphicsUtilities::RenderLineRectangle(GetAttackRect(), color::rgba::kRed, *_camera);
		}
	}
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
	//本来はemEnd
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

	//着地判定はCollisionObjectに移動
	/*
	if (Ypos + GetRect().GetHeight() > 700)
	{
		Ypos = 700 - GetRect().GetHeight();
		Yspd = 0;
	}
	*/
}

void CSwordSoldier::Attack()
{
	motion.ChangeMotion(emAttack);
	attackWait = attackInterval;
}

void CSwordSoldier::SearchAllies(CRectangle girl, CRectangle wolf)
{
	if (std::abs((girl.left + (girl.GetWidth() * 0.5f)) - (GetRect().left + (GetRect().GetWidth() * 0.5f))) < std::abs((wolf.left + (wolf.GetWidth() * 0.5f)) - (GetRect().left + (GetRect().GetWidth() * 0.5f))))
	{
		if (girl.CollisionRectangle(GetSerchRect()))
		{
			(GetRect().left + (GetRect().GetWidth() * 0.5f) > girl.left + (girl.GetWidth() * 0.5f)) ? isRight = false : isRight = true;

			if (girl.CollisionRectangle(GetAttackSerchRect()))
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
		if (wolf.CollisionRectangle(GetSerchRect()))
		{
			(GetRect().left + (GetRect().GetWidth() * 0.5f) > wolf.left + (wolf.GetWidth() * 0.5f)) ? isRight = false : isRight = true;

			if (wolf.CollisionRectangle(GetAttackSerchRect()))
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

bool CSwordSoldier::TakeDamage() 
{
	health--;

	if (health > 0) 
	{
		invicibleWait = invicibleTime;

		return true;
	}
	
	motion.ChangeMotion(emDown);
	return false;
}

CRectangle CSwordSoldier::GetRect() 
{
	CRectangle rect = motion.GetSourceRectangle();
	rect.SetBounds({ Xpos,Ypos - motionOffset[motion.GetMotionNo()][1] }, rect.GetSize());

	rect.top += motionOffset[motion.GetMotionNo()][1];
	rect.bottom += motionOffset[motion.GetMotionNo()][3];

	if (!isRight)
	{
		rect.left -= motionOffset[motion.GetMotionNo()][2];
		rect.right -= motionOffset[motion.GetMotionNo()][0];
	}
	else
	{
		rect.left += motionOffset[motion.GetMotionNo()][0];
		rect.right += motionOffset[motion.GetMotionNo()][2];
	}

	return rect;
}

CRectangle CSwordSoldier::GetBackRect()
{
	CRectangle rect = motion.GetSourceRectangle();
	rect.SetBounds({ XbackPos,YbackPos - motionOffset[motion.GetMotionNo()][1] }, rect.GetSize());

	rect.top += motionOffset[motion.GetMotionNo()][1];
	rect.bottom += motionOffset[motion.GetMotionNo()][3];

	if (!isRight)
	{
		rect.left -= motionOffset[motion.GetMotionNo()][2];
		rect.right -= motionOffset[motion.GetMotionNo()][0];
	}
	else
	{
		rect.left += motionOffset[motion.GetMotionNo()][0];
		rect.right += motionOffset[motion.GetMotionNo()][2];
	}

	return rect;
}

CRectangle CSwordSoldier::GetAttackRect() 
{
	if (isRight) 
	{
		return CRectangle((GetRect().left + GetRect().GetWidth() * 0.5f) + 15, GetRect().top - 20, (GetRect().left + GetRect().GetWidth() * 0.5f) + 130, GetRect().top + GetRect().GetHeight() - 10);
	}
	else 
	{
		return CRectangle((GetRect().left + GetRect().GetWidth() * 0.5f) - 130, GetRect().top - 20, (GetRect().left + GetRect().GetWidth() * 0.5f) - 20, GetRect().top + GetRect().GetHeight() - 10);
	}
}

CRectangle CSwordSoldier::GetSerchRect() 
{
	return CRectangle((GetRect().left + GetRect().GetWidth() * 0.5f) - searchRange, GetRect().top, (GetRect().left + GetRect().GetWidth() * 0.5f) + searchRange, GetRect().bottom);
}

CRectangle CSwordSoldier::GetAttackSerchRect() 
{
	return CRectangle((GetRect().left + (GetRect().GetWidth() * 0.5f)) - attackSerchRange, GetRect().top, (GetRect().left + (GetRect().GetWidth() * 0.5f)) + attackSerchRange, GetRect().top + GetRect().GetHeight());
}
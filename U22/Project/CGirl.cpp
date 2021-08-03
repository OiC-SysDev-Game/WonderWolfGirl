#include "Girl.h"

CGirl::CGirl() {
}

CGirl::~CGirl()
{};

bool CGirl::Load() 
{
	//幅、高さ、コマ数
	texture[0].Load("Character/Girl/Girl_Wait_91_246_30.png");
	texture[1].Load("Character/Girl/Girl_Walk_136_246_25.png");
	texture[2].Load("Character/Girl/Girl_Hit_106_246_10.png");
	texture[3].Load("Character/Girl/Girl_Down_260_240_30.png");

	SpriteAnimationCreate anim[] =
	{
		{
			"Wait",
			0,0,
			91,246,
			TRUE,{{3,0,0},{3,1,0},{3,2,0},{3,3,0},{3,4,0},{3,5,0},{3,6,0},{3,7,0},{3,8,0},{3,9,0},{3,10,0},{3,0,1},{3,1,1},{3,2,1},{3,3,1},{3,4,1},{3,5,1},{3,6,1},{3,7,1},{3,8,1},{3,9,1},{3,10,1},{3,0,2},{3,1,2},{3,2,2},{3,3,2},{3,4,2},{3,5,2},{3,6,2},{3,7,2}}
		},
		{
			"Walk",
			0,0,
			136,246,
			TRUE,{{2,0,0},{2,1,0},{2,2,0},{2,3,0},{2,4,0},{2,5,0},{2,6,0},{2,0,1},{2,1,1},{2,2,1},{2,3,1},{2,4,1},{2,5,1},{2,6,1},{2,0,2},{2,1,2},{2,2,2},{2,3,2},{2,4,2},{2,5,2},{2,6,2},{2,0,3},{2,1,3},{2,2,3},{2,3,3}}
		},
		{
			"Hit",
			0,0,
			106,246,
			FALSE,{{1,0,0},{1,1,0},{3,2,0},{4,3,0},{3,4,0},{4,5,0},{3,6,0},{3,7,0},{3,8,0},{3,0,1}}
		},
		{
			"Down",
			0,0,
			266,246,
			FALSE,{{1,0,0},{1,1,0},{1,2,0},{1,3,0},{1,4,0},{1,5,0},{1,6,0},{1,0,1},{1,1,1},{1,2,1},{1,3,1},{1,4,1},{1,5,1},{1,6,1},{1,0,2},{1,1,2},{1,2,2},{1,3,2},{1,4,2},{1,5,2},{1,6,2},{1,0,3},{1,1,3},{1,2,3},{1,3,3},{1,4,3},{1,5,3},{1,6,3},{1,0,4},{1,1,4}}
		},
	};

	//本来はemEnd
	motion.Create(anim, 4);
	motion.ChangeMotion(0);
	return true;
}

void CGirl::Initialize(CWolf* arg)
{
	health = maxHealth;

	isRide = false;
	isMove = false;
	isRight = true;

	Xpos = 10;
	Ypos = 0;
	Xspd = 0;
	Yspd = 0;

	wolf = arg;

	Load();
}

void CGirl::Update() 
{
	if (isMove && motion.GetMotionNo() != emDown) Acceleration();
	else Neutral();

	Move();

	motion.AddTimer(g_pClock->GetFrameSecond());

	if (motion.GetMotionNo() == emHit && motion.IsEndMotion()) 
	{
		motion.ChangeMotion(emWait);
	}

	if (invicibleWait > 0) invicibleWait -= g_pClock->GetFrameSecond();
}

void CGirl::Render(CCamera* _camera) 
{
	CRectangle rect = motion.GetSourceRectangle();

	if (!isRight) {
		float tmp = rect.right;
		rect.right = rect.left;
		rect.left = tmp;
	}

	if ((int)(invicibleWait * 10) % 2 == 0) 
	{
		texture[motion.GetMotionNo()].Render({ Xpos,Ypos - motionOffset[motion.GetMotionNo()][1] }, rect, *_camera);
	}

	//画像の大きさ
	rect = motion.GetSourceRectangle();
	rect.SetBounds({ Xpos,Ypos - motionOffset[motion.GetMotionNo()][1] }, rect.GetSize());
	::GraphicsUtilities::RenderLineRectangle(rect, color::rgba::kGreen, *_camera);

	rect = GetRect();

	//当たり判定　無敵だと白
	if (invicibleWait > 0) ::GraphicsUtilities::RenderLineRectangle(rect, color::rgba::kWhite, *_camera);
	else ::GraphicsUtilities::RenderLineRectangle(rect, color::rgba::kRed, *_camera);

}

void CGirl::RenderDebug(CCamera* _camera) {
}

void CGirl::Release() 
{
	motion.Release();

	//本来はi < emEnd
	for (int i = 0; i < 4; i++) {
		texture[i].Release();
	}
}

bool CGirl::TakeDamage(int damage)
{
	if (invicibleWait <= 0 && motion.GetMotionNo() != emDown) 
	{
		health -= damage;

		(isRight) ? Xspd = -5 : Xspd = 5;

		if (health <= 0) 
		{
			Xpos -= 100;

			motion.ChangeMotion(emDown);
			return true;
		}
		else 
		{
			invicibleWait = invicibleTime;

			motion.ChangeMotion(emHit);
			return false;
		}
	}
}

void CGirl::Acceleration(void)
{
	if (motion.GetMotionNo() == emDown || motion.GetMotionNo() == emHit) return;

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
	{
		motion.ChangeMotion(emWalk);
		if (!isRight) 
		{
			Xpos -= 25;
		}
	}
}

void CGirl::Neutral(void)
{
	if (Xspd > 0)
	{
		Xspd -= decelerateSpd;
		if (Xspd <= 0) 
		{
			Xspd = 0;
		}
	}
	else if(Xspd < 0)
	{
		Xspd += decelerateSpd;
		if (Xspd >= 0)
		{
			Xspd = 0;
		}
	}

	if (Xspd == 0 && motion.GetMotionNo() == emWalk) 
	{
		motion.ChangeMotion(emWait);
		if (!isRight) Xpos += 35;
		else Xpos += 15;
	}
}

void CGirl::Move(void)
{
	if (isRide)
	{
		//狼と同期
		CRectangle rect = wolf->GetRect();

		Xpos = rect.left + (rect.GetWidth() * 0.5f) - (motion.GetSourceRectangle().GetWidth() * 0.5f);
		Ypos = rect.top - 25;
		isRight = wolf->GetDirection();
	}
	else
	{
		Yspd += gravity;

		Xpos += Xspd;
		Ypos += Yspd;

		if (Ypos + GetRect().GetHeight() > 700) //height >= 700) 
		{
			Ypos = 700 - GetRect().GetHeight(); //height;
			Yspd = 0;
		}
	}
}

CRectangle CGirl::GetRect(void)
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

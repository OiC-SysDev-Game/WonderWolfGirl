#include "Girl.h"

CGirl::CGirl() {
}

CGirl::~CGirl()
{};

bool CGirl::Load() 
{
	texture[0].Load("Character/Girl/wait_91_246_30.png");
	texture[1].Load("Character/Girl/walk_136_246_25.png");
	texture[2].Load("Character/Girl/hit_106_246_30.png");
	texture[3].Load("Character/Girl/down_260_240_30.png");

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

	//–{—ˆ‚ÍemEnd
	motion.Create(anim, 4);
	motion.ChangeMotion(0);
	return true;
}

void CGirl::Initialize(CWolf* arg)
{
	health = max_Health;

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
	if (isMove) Acceleration();
	else Neutral();

	Move();

	motion.AddTimer(g_pClock->GetFrameSecond());
}

void CGirl::Render(CCamera* _camera) 
{
	CRectangle rect = motion.GetSourceRectangle();

	//‰f‚ç‚È‚¢
	if (!isRight) {
		float tmp = rect.right;
		rect.right = rect.left;
		rect.left = tmp;
	}

	texture[motion.GetMotionNo()].Render({ Xpos,Ypos }, rect, *_camera);

	rect = motion.GetSourceRectangle();
	rect.SetBounds({ Xpos,Ypos }, rect.GetSize());
	::GraphicsUtilities::RenderLineRectangle(rect, color::rgba::kRed, *_camera);
}

void CGirl::RenderDebug(CCamera* _camera) {
}

void CGirl::Release() 
{
	motion.Release();

	//–{—ˆ‚Íi < emEnd
	for (int i = 0; i < 4; i++) {
		texture[i].Release();
	}
}

bool CGirl::TakeDamage(int damage)
{
	health -= damage;

	if (health < 0) 
	{
		motion.ChangeMotion(emDown);

		return true;
	}
	else 
	{
		motion.ChangeMotion(emHit);
		return false;
	}
}

void CGirl::Acceleration(void)
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

	if (motion.GetMotionNo() == emWait)
		motion.ChangeMotion(emWalk);
}

void CGirl::Neutral(void)
{
	if (Xspd > 0)
	{
		Xspd -= decelerate_Spd;
		if (Xspd <= 0) 
		{
			Xspd = 0;
		}
	}
	else if(Xspd < 0)
	{
		Xspd += decelerate_Spd;
		if (Xspd >= 0)
		{
			Xspd = 0;
		}
	}

	if (Xspd == 0 && motion.GetMotionNo() == emWalk)
		motion.ChangeMotion(emWait);
}

void CGirl::Move(void)
{
	if (isRide)
	{
		//˜T‚Æ“¯Šú
		float a = wolf->GetRect().left;
		float b = wolf->GetRect().top;

		Xpos = a + 60;
		Ypos = b - 75;
		isRight = wolf->GetDirection();
	}
	else
	{
		Yspd += gravity;

		Xpos += Xspd;
		Ypos += Yspd;

		if (Ypos + motion.GetSourceRectangle().GetHeight() > 700) //height >= 700) 
		{
			Ypos = 700 - motion.GetSourceRectangle().GetHeight(); //height;
			Yspd = 0;
		}
	}
}

CRectangle CGirl::GetRect(void)
{
	CRectangle rect = motion.GetSourceRectangle();
	rect.SetBounds({ Xpos,Ypos }, motion.GetSourceRectangle().GetSize());
	return rect;
}

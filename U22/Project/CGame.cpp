#include "GameApplicaion.h"
#include "Game.h"
#include "Wolf.h"
#include "Girl.h"
#include "SwordSoldier.h"

CWolf wolf;
CGirl girl;
CSwordSoldier swordSoldier;


CGame::CGame() :
	CSceneBase(){
}

CGame::~CGame()
{
	Release();
};

bool CGame::Load() {

	return true;
}

void CGame::Initialize() {
	_camera.Initalize2DCamera();

	girl.Initialize(&wolf);
	wolf.Initialize(&girl);
	swordSoldier.Initialize();
}

void CGame::Update() {

	wolf.Update();
	girl.Update();
	swordSoldier.Update(girl.GetRect(),wolf.GetRect());

	if (swordSoldier.GetShow() && swordSoldier.GetAttack())
	{
		if (girl.GetRect().CollisionRectangle(swordSoldier.GetAttackRect())) 
		{
			girl.TakeDamage(1);
		}
	}

	/*
	//（仮）Nキーでタイトルシーンへ移行
	if (g_pInput->IsPush(u22::input::KeyCode::N))
	{
		bEnd = true;
		NextScene = SCENENO_TITLE;
	}*/
}

void CGame::Render(CCamera* _camera) {
	//std::string text = "ゲーム画面\nNキーで次の画面へすっとばせるよ";
	//::GraphicsUtilities::RenderString(Vector2(10, 10), color::rgba::kWhite, text, *_camera);

	::GraphicsUtilities::RenderFillRectangle(CRectangle(0, 700, 1280, 720), { (0.0f),(0.5f),(0.5f),(1.0f) }, *_camera);

	wolf.Render(_camera);
	girl.Render(_camera);
	swordSoldier.Render(_camera);
}

void CGame::RenderDebug(CCamera* _camera) {
}

void CGame::Release()
{
	wolf.Release();
	girl.Release();
	swordSoldier.Release();
}

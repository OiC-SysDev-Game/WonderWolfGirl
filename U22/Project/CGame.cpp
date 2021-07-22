#include "GameApplicaion.h"
#include "Game.h"

CGame::CGame() :
	CSceneBase(){
}

CGame::~CGame()
{};

bool CGame::Load() {
	return true;
}

void CGame::Initialize() {
}

void CGame::Update() {
	//（仮）Nキーでタイトルシーンへ移行
	if (g_pInput->IsPush(u22::input::KeyCode::N))
	{
		bEnd = true;
		NextScene = SCENENO_TITLE;
	}
}

void CGame::Render(CCamera* _camera) {
	std::string text = "ゲーム画面\nNキーで次の画面へすっとばせるよ";
	::GraphicsUtilities::RenderString(Vector2(10, 10), color::rgba::kWhite, text, *_camera);
}

void CGame::RenderDebug(CCamera* _camera) {
}

void CGame::Release() {
}

void CGame::FeedIn() {
	//フェードイン処理
}
void CGame::FeedOut() {
	//フェードアウト処理
}

bool CGame::FeedInEndCheck() {
	return true;
}
bool CGame::FeedOutEndCheck() {
	return true;
}

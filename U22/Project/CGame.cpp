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
	switch (G_ScenePhase)
	{
	case G_PHASE_START:
		//導入処理
		FeedIn();
		if (FeedInEndCheck())
		{
			G_ScenePhase++;
		}
		break;
	case G_PHASE_UNDER:
		//操作中処理

		break;
	case G_PHASE_NEXT:
		//次の画面への処理
		FeedOut();
		if (FeedOutEndCheck())
		{
			switch (G_NextAction)
			{
			case G_ACTION_NEXTMAP:
				break;
			case G_ACTION_GAMECLEAR:
				break;
			case G_ACTION_GAMEOVER:
				break;

			case G_ACTION_RESTART:
				G_BackGroundBGM.Stop();
				Initialize();
				break;

			case G_ACTION_EXITSTAGE:
				bEnd = true;
				NextScene = SCENENO_STAGESELECT;
				break;

			case G_ACTION_TITLEBACK:
				bEnd = true;
				NextScene = SCENENO_TITLE;
				break;

			default:
				break;
			}
		}
		break;
	default:
		break;
	}

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

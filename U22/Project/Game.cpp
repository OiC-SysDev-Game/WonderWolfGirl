#include "GameApplicaion.h"
#include "Game.h"
#include "Stage.h"
#include "Wolf.h"
#include "Girl.h"
#include "SwordSoldier.h"

CStage stage;

CWolf wolf;
CGirl girl;
CSwordSoldier swordSoldier;


CGame::CGame() :
	CSceneBase() {
}

CGame::~CGame()
{
	Release();
};

bool CGame::Load() {

	return true;
}

void CGame::Initialize() {
	Load();
	stage.Initialize();
	girl.Initialize(&wolf);
	wolf.Initialize(&girl);
	swordSoldier.Initialize();
}

void CGame::Update() {

	wolf.Update();
	girl.Update();
	swordSoldier.Update();

	//シーン状態による分岐
	switch (G_ScenePhase)
	{
		//ゲームスタート
	case G_PHASE_START:
		FeedIn();
		if (FeedInEndCheck())
		{
			G_ScenePhase++;
		}
		break;

		//操作中
	case G_PHASE_UNDER:
		break;

		//画面変化
	case G_PHASE_NEXT:
		FeedOut();
		if (FeedOutEndCheck())
		{
			//G_NextActionの中身を参照し、対応した処理を実行する
			switch (G_NextAction)
			{
				//マップ移動
			case G_ACTION_NEXTMAP:
				break;
				//ゲームクリア
			case G_ACTION_GAMECLEAR:
				break;
				//ゲームオーバー
			case G_ACTION_GAMEOVER:
				break;
				//リスタート(メニュー画面コマンド)
			case G_ACTION_RESTART:
				break;
				//ステージ選択へ戻る(メニュー画面コマンド)
			case G_ACTION_EXITSTAGE:
				break;
				//タイトルへ戻る(メニュー画面コマンド)
			case G_ACTION_TITLEBACK:
				break;
			}
		}
		break;
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
	stage.Render(_camera);
}

void CGame::RenderDebug(CCamera* _camera) {

}

void CGame::Release()
{
	wolf.Release();
	girl.Release();
	swordSoldier.Release();
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
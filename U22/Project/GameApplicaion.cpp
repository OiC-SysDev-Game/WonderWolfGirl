#include "GameApplicaion.h"
#include "SceneBase.h"
#include "Title.h"
#include "StageSelect.h"
#include "Game.h"

CSceneBase* pScene = NULL;
CCamera _camera;

u22::GameApplication::GameApplication() {
}

u22::GameApplication::~GameApplication() {
}

bool u22::GameApplication::Initialize(void) {
    SetCurrentPath();
	_camera.Initalize2DCamera();
    //初回に実行されるシーンの初期化
    pScene = new CGame();
    pScene->Initialize();
    return true;
}

bool u22::GameApplication::Update(void) {
	if (g_pInput->IsPush(Keycode::Escape))
	{
		::PostQuitMessage(0);
	}
	//シーンの更新
	pScene->Update();
	//シーンチェンジ
	if (pScene->IsEnd())
	{
		//次のシーンを取得
		int change = pScene->GetNextScene();
		int stageno = pScene->GetNo();
		//古いシーンを消去
		delete pScene;
		//次のシーン番号に応じてシーンを作って初期化
		switch (change) {
			//タイトル
		case SCENENO_TITLE:
			pScene = new CTitle();
			break;
			//メニュー
		case SCENENO_STAGESELECT:
			pScene = new CStageSelect();
			break;
			//ゲーム
		case SCENENO_GAME:
			pScene = new CGame();
			break;
		case SCENENO_END:
			//PostQuitMessage(0)が正常に動作しないため、仮でタイトルに
			pScene = new CTitle();
			break;
		}
		pScene->SetNo(stageno);
		pScene->Initialize();
	}
    return true;
}

bool u22::GameApplication::Render(void) {
    g_pGraphics->RenderStart();
    g_pGraphics->ClearTarget(color::rgba::kBlack, 1.0f, 1.0f);

	//シーン描画
	pScene->Render(&_camera);
	//デバッグ描画
	pScene->RenderDebug(&_camera);
    return true;
}

bool u22::GameApplication::Release(void) {
	if (pScene)
	{
		delete pScene;
		pScene = NULL;
	}
    return true;
}
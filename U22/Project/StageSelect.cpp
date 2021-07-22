#include "GameApplicaion.h"
#include "StageSelect.h"


CStageSelect::CStageSelect() :
	CSceneBase(),
	S_BackGroundBGM(),
	S_SelectSound(),
	S_DecideSound(),
	S_ExitSound(),
	S_BackImage(),
	S_StageImage(),
	S_StageSelectButtonImage(),
	S_BackButtonImage(),
	S_ScenePhase(0),
	S_MenuSelectNo(-1),
	S_DefaultAlpha(0)
{
}

CStageSelect::~CStageSelect()
{};

bool CStageSelect::Load() {
	return true;
}

void CStageSelect::Initialize() {
}

void CStageSelect::Update() {
	//（仮）Nキーでゲームシーンへ移行
	if (g_pInput->IsPush(u22::input::KeyCode::N))
	{
		bEnd = true;
		NextScene = SCENENO_GAME;
	}
}

void CStageSelect::Render(CCamera* _camera) {
}

void CStageSelect::RenderDebug(CCamera* _camera) {
	std::string text = "ステージ選択画面\nNキーで次の画面へすっとばせるよ";
	::GraphicsUtilities::RenderString(Vector2(10, 10), color::rgba::kWhite, text, *_camera);
}

void CStageSelect::Release() {
}

void CStageSelect::MouseControl() {

}

void CStageSelect::FeedIn() {
	//フェードイン処理
	S_DefaultAlpha = MaxOrMinAdjust(S_DefaultAlpha, STSELECT_TEXTUREALPHAINC, 1, 0);
}
void CStageSelect::FeedOut() {
	//フェードアウト処理
	S_DefaultAlpha = MaxOrMinAdjust(S_DefaultAlpha, -STSELECT_TEXTUREALPHAINC, 1, 0);
}

bool CStageSelect::FeedInEndCheck() {
	if (S_DefaultAlpha < 1)
	{
		return false;
	}
	return true;
}
bool CStageSelect::FeedOutEndCheck() {
	if (S_DefaultAlpha > 0)
	{
		return false;
	}
	return true;
}

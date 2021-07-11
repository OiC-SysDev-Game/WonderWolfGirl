#include "GameApplicaion.h"
#include "Title.h"

CTitle::CTitle() :
	CSceneBase(){
}

CTitle::~CTitle()
{};

bool CTitle::Load() {
	return true;
}

void CTitle::Initialize() {

}

void CTitle::Update() {
	//（仮）Nキーでステージ選択シーンへ移行
	if (g_pInput->IsPush(u22::input::KeyCode::N))
	{
		bEnd = true;
		NextScene = SCENENO_STAGESELECT;
	}
}

void CTitle::Render(CCamera* _camera) {
}

void CTitle::RenderDebug(CCamera* _camera) {
	std::string text = "タイトル画面\nNキーで次の画面へすっとばせるよ";
	::GraphicsUtilities::RenderString(Vector2(10, 10), color::rgba::kWhite, text, *_camera);
}

void CTitle::Release() {
}

#include "GameApplicaion.h"
#include "StageSelect.h"


CStageSelect::CStageSelect() :
	CSceneBase() {
}

CStageSelect::~CStageSelect()
{};

bool CStageSelect::Load() {
	return true;
}

void CStageSelect::Initialize() {
}

void CStageSelect::Update() {
	//�i���jN�L�[�ŃQ�[���V�[���ֈڍs
	if (g_pInput->IsPush(u22::input::KeyCode::N))
	{
		bEnd = true;
		NextScene = SCENENO_GAME;
	}
}

void CStageSelect::Render(CCamera* _camera) {
}

void CStageSelect::RenderDebug(CCamera* _camera) {
	std::string text = "�X�e�[�W�I�����\nN�L�[�Ŏ��̉�ʂւ����Ƃ΂����";
	::GraphicsUtilities::RenderString(Vector2(10, 10), color::rgba::kWhite, text, *_camera);
}

void CStageSelect::Release() {
}

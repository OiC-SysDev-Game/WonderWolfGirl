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
	//�i���jN�L�[�ŃX�e�[�W�I���V�[���ֈڍs
	if (g_pInput->IsPush(u22::input::KeyCode::N))
	{
		bEnd = true;
		NextScene = SCENENO_STAGESELECT;
	}
}

void CTitle::Render(CCamera* _camera) {
}

void CTitle::RenderDebug(CCamera* _camera) {
	std::string text = "�^�C�g�����\nN�L�[�Ŏ��̉�ʂւ����Ƃ΂����";
	::GraphicsUtilities::RenderString(Vector2(10, 10), color::rgba::kWhite, text, *_camera);
}

void CTitle::Release() {
}

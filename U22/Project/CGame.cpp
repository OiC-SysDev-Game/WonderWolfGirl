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
	//�i���jN�L�[�Ń^�C�g���V�[���ֈڍs
	if (g_pInput->IsPush(u22::input::KeyCode::N))
	{
		bEnd = true;
		NextScene = SCENENO_TITLE;
	}
}

void CGame::Render(CCamera* _camera) {
	std::string text = "�Q�[�����\nN�L�[�Ŏ��̉�ʂւ����Ƃ΂����";
	::GraphicsUtilities::RenderString(Vector2(10, 10), color::rgba::kWhite, text, *_camera);
}

void CGame::RenderDebug(CCamera* _camera) {
}

void CGame::Release() {
}
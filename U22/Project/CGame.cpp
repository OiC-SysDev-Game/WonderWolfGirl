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
	switch (G_ScenePhase)
	{
	case G_PHASE_START:
		//��������
		FeedIn();
		if (FeedInEndCheck())
		{
			G_ScenePhase++;
		}
		break;
	case G_PHASE_UNDER:
		//���쒆����

		break;
	case G_PHASE_NEXT:
		//���̉�ʂւ̏���
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
	//�t�F�[�h�C������
}
void CGame::FeedOut() {
	//�t�F�[�h�A�E�g����
}

bool CGame::FeedInEndCheck() {
	return true;
}
bool CGame::FeedOutEndCheck() {
	return true;
}

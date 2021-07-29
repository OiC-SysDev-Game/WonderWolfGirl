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

	//�V�[����Ԃɂ�镪��
	switch (G_ScenePhase)
	{
		//�Q�[���X�^�[�g
	case G_PHASE_START:
		FeedIn();
		if (FeedInEndCheck())
		{
			G_ScenePhase++;
		}
		break;

		//���쒆
	case G_PHASE_UNDER:
		break;

		//��ʕω�
	case G_PHASE_NEXT:
		FeedOut();
		if (FeedOutEndCheck())
		{
			//G_NextAction�̒��g���Q�Ƃ��A�Ή��������������s����
			switch (G_NextAction)
			{
				//�}�b�v�ړ�
			case G_ACTION_NEXTMAP:
				break;
				//�Q�[���N���A
			case G_ACTION_GAMECLEAR:
				break;
				//�Q�[���I�[�o�[
			case G_ACTION_GAMEOVER:
				break;
				//���X�^�[�g(���j���[��ʃR�}���h)
			case G_ACTION_RESTART:
				break;
				//�X�e�[�W�I���֖߂�(���j���[��ʃR�}���h)
			case G_ACTION_EXITSTAGE:
				break;
				//�^�C�g���֖߂�(���j���[��ʃR�}���h)
			case G_ACTION_TITLEBACK:
				break;
			}
		}
		break;
	}

	/*
	//�i���jN�L�[�Ń^�C�g���V�[���ֈڍs
	if (g_pInput->IsPush(u22::input::KeyCode::N))
	{
		bEnd = true;
		NextScene = SCENENO_TITLE;
	}*/
}

void CGame::Render(CCamera* _camera) {
	//std::string text = "�Q�[�����\nN�L�[�Ŏ��̉�ʂւ����Ƃ΂����";
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
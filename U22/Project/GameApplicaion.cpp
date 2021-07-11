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
    //����Ɏ��s�����V�[���̏�����
    pScene = new CTitle();
    pScene->Initialize();
    return true;
}

bool u22::GameApplication::Update(void) {
	//�V�[���̍X�V
	pScene->Update();
	//�V�[���`�F���W
	if (pScene->IsEnd())
	{
		//���̃V�[�����擾
		int change = pScene->GetNextScene();
		int stageno = pScene->GetNo();
		//�Â��V�[��������
		delete pScene;
		//���̃V�[���ԍ��ɉ����ăV�[��������ď�����
		switch (change) {
			//�^�C�g��
		case SCENENO_TITLE:
			pScene = new CTitle();
			break;
			//���j���[
		case SCENENO_STAGESELECT:
			pScene = new CStageSelect();
			break;
			//�Q�[��
		case SCENENO_GAME:
			pScene = new CGame();
		}
		pScene->SetNo(stageno);
		pScene->Initialize();
	}
    return true;
}

bool u22::GameApplication::Render(void) {
    g_pGraphics->RenderStart();
    g_pGraphics->ClearTarget(color::rgba::kBlue, 1.0f, 1.0f);

	//�V�[���`��
	pScene->Render(&_camera);
	//�f�o�b�O�`��
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
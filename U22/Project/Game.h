#pragma once
#include "SceneBase.h" 
class CGame : public CSceneBase
{
private:
	CSoundBuffer		G_BackGroundBGM;					//���j���\��ʂ�BGM
	CSoundBuffer		G_SelectMoveSound;					//�J�[�\���ړ����̌��ʉ�
	CSoundBuffer		G_DecideSound;						//����{�^�����������̌��ʉ�
	CSoundBuffer		G_ExitSound;						//�߂�{�^�����������̌��ʉ�

	int					G_ScenePhase;						//���݂̃V�[���i�s�x����
	int					G_NextAction;						//���Ɏ��s���铮��

	int					G_CurrentMapNum;					//���݂̃}�b�v�ԍ�

	//�V�[���̏��
	enum G_GAMEPHASE {
		G_PHASE_START,
		G_PHASE_UNDER,
		G_PHASE_NEXT,
	};

	//�t�F�[�h�A�E�g��ɍs������
	enum G_NEXTACTION {
		G_ACTION_NEXTMAP,
		G_ACTION_GAMECLEAR,
		G_ACTION_GAMEOVER,
		G_ACTION_RESTART,
		G_ACTION_EXITSTAGE,
		G_ACTION_TITLEBACK,
	};
protected:
	void FeedIn();
	bool FeedInEndCheck();
	void FeedOut();
	bool FeedOutEndCheck();
public:
	CGame();
	~CGame();
	bool Load();
	void Initialize();
	void Update();
	void Render(CCamera* _camera);
	void RenderDebug(CCamera* _camera);
	void Release();
};


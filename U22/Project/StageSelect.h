#pragma once
#include "SceneBase.h" 

#define STSELECT_STAGE_COUNT		3

#define STSELECT_STAGE_ANKERX		100.0f
#define STSELECT_STAGE_ANKERY		200.0f
#define STSELECT_STAGEBUTTON_ANKERX 50.0f
#define STSELECT_STAGEBUTTON_ANKERY 200.0f

#define	STSELECT_FEEDTIME			20.0f
#define	STSELECT_FEEDSPACEY			400.0f
#define	STSELECT_FEEDTIMINGALPHA	0.5f

class CStageSelect : public CSceneBase
{
private:
	CSoundBuffer		S_BackGroundBGM;					//���j���\��ʂ�BGM
	CSoundBuffer		S_SelectSound;						//�J�[�\���ړ����̌��ʉ�
	CSoundBuffer		S_DecideSound;						//����{�^�����������̌��ʉ�
	CSoundBuffer		S_ExitSound;						//�߂�{�^�����������̌��ʉ�

	CTexture			S_BackImage;
	CTexture			S_StageImage[STSELECT_STAGE_COUNT];
	CTexture			S_SelectButtonImage;
	CTexture			S_SelectButtonImage_Select;
	CTexture			S_BackButtonImage;

	int					S_ScenePhase;						//���݂̃V�[���i�s�x����
	int					S_StageSelectNo;					//���j���[�I��ԍ�

	float				S_DefaultAlpha;							//�C���X�g�̓����x(�t�F�[�h�C�����Ɏg�p)
	float				S_FeedInPopAlpha[STSELECT_STAGE_COUNT];	//�t�F�[�h�C�����̊e�|�b�v�ɑΉ������A���t�@�l
	float				S_FeedOutPopAlpha;						//�t�F�[�h�A�E�g���̃|�b�v�ɑΉ������A���t�@�l
	float				S_FeedInOffsetY[STSELECT_STAGE_COUNT];	//�t�F�[�h�C�����̈ړ���
	int					S_FeedPopNow;							//�t�F�[�h�C�����A���݃t�F�[�h�������s���Ă���|�b�v�ԍ�

	enum S_TITLEPHASE {
		S_PHASE_START,
		S_PHASE_UNDER,
		S_PHASE_NEXT,
	};

	enum S_POP {
		S_POP_SELECT,
		S_POP_OPTION,
		S_POP_BACK,
	};

	const char* StageImageName[STSELECT_STAGE_COUNT] = {
		"Image/StageSelect/Stage1.png",
		"Image/StageSelect/Stage2.png",
		"Image/StageSelect/Stage3.png",
	};

	void MouseControl();

protected:
	void FeedIn();
	bool FeedInEndCheck();
	void FeedOut();
	bool FeedOutEndCheck();

public:
	CStageSelect();
	~CStageSelect();
	bool Load();
	void Initialize();
	void Update();
	void Render(CCamera* _camera);
	void RenderDebug(CCamera* _camera);
	void Release();
};


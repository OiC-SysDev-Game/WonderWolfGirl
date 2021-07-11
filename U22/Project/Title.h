#pragma once
#include "SceneBase.h"

#define			TITLE_MENUCOUNT			3
#define			TITLE_POPSPACE			220.0f
#define			TITLE_POPTOPSPACE		50.0f
#define			TITLE_TITLETOPSPACE		50.0f

#define			TITLE_FEEDALPHASPEED	0.02f
#define			TITLE_FEEDSPEEDX		30.0f
#define			TITLE_FEEDSPACEX		-600.0f
#define			TITLE_FEEDTIMINGALPHA	0.5f

class CTitle : public CSceneBase
{
private:
	enum T_TITLEPHASE {
		PHASE_START,
		PHASE_UNDER,
		PHASE_NEXT,
	};
	//�|�b�v�̎��
	enum T_POP {
		POP_SELECT,
		POP_OPTION,
		POP_END,
	};
	//���j���[�|�b�v��(��I����)
	const char* T_PopNames[TITLE_MENUCOUNT] = {
	"Image/SELECT.png",
	"Image/OPTION.png",
	"Image/END.png",
	};
	//���j���[�|�b�v��(�I����/�ʏ�)
	const char* T_PopSelectNames[TITLE_MENUCOUNT] = {
	"Image/SELECT_Select.png",
	"Image/OPTION_Select.png",
	"Image/END_Select.png"
	};

	CSoundBuffer		T_BackGroundBGM;					//���j���\��ʂ�BGM
	CSoundBuffer		T_SelectSound;						//�J�[�\���ړ����̌��ʉ�
	CSoundBuffer		T_DecideSound;						//����{�^�����������̌��ʉ�
	CSoundBuffer		T_ExitSound;						//�߂�{�^�����������̌��ʉ�

	CTexture			T_BackImage;						//�w�i�摜
	CTexture			T_Title;							//�^�C�g���摜
	CTexture			T_Pop[TITLE_MENUCOUNT];				//�|�b�v�摜(��I����)
	CTexture			T_PopSelect[TITLE_MENUCOUNT];		//�|�b�v�摜(�I����/�ʏ�)

	int					T_ScenePhase;						//���݂̃V�[���i�s�x����
	int					T_MenuSelectNo;						//���j���[�I��ԍ�

	float				T_DefaultAlpha;						//�C���X�g�̓����x(�t�F�[�h�C�����Ɏg�p)

	float				T_FeedInPopAlpha[TITLE_MENUCOUNT];	//�t�F�[�h�C�����̊e�|�b�v�ɑΉ������A���t�@�l
	float				T_FeedOutPopAlpha;					//�t�F�[�h�A�E�g���̃|�b�v�ɑΉ������A���t�@�l
	float				T_FeedInOffsetX[TITLE_MENUCOUNT];	//�t�F�[�h�C�����̈ړ���
	int					T_FeedPopNow;						//�t�F�[�h�C�����A���݃t�F�[�h�������s���Ă���|�b�v�ԍ�

	void FeedIn();
	bool FeedInEndCheck();
	void FeedOut();
	bool FeedOutEndCheck();
	void GamePadControl();

public:
	CTitle();
	~CTitle();
	bool Load();
	void Initialize();
	void Update();
	void Render(CCamera* _camera);
	void RenderDebug(CCamera* _camera);
	void Release();
};


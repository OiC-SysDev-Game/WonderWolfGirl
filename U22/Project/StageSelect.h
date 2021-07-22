#pragma once
#include "SceneBase.h" 

#define STSELECT_STAGE_COUNT		3

#define STSELECT_STAGE_ANKERX		50
#define STSELECT_STAGE_ANKERY		200

#define STSELECT_TEXTUREALPHAINC	0.01f

class CStageSelect : public CSceneBase
{
private:
	CSoundBuffer		S_BackGroundBGM;					//���j���\��ʂ�BGM
	CSoundBuffer		S_SelectSound;						//�J�[�\���ړ����̌��ʉ�
	CSoundBuffer		S_DecideSound;						//����{�^�����������̌��ʉ�
	CSoundBuffer		S_ExitSound;						//�߂�{�^�����������̌��ʉ�

	CTexture			S_BackImage;
	CTexture*			S_StageImage;
	CTexture			S_StageSelectButtonImage;
	CTexture			S_BackButtonImage;

	int					S_ScenePhase;						//���݂̃V�[���i�s�x����
	int					S_MenuSelectNo;						//���j���[�I��ԍ�

	float				S_DefaultAlpha;						//�C���X�g�̓����x(�t�F�[�h�C�����Ɏg�p)

	const char* StageImageName[STSELECT_STAGE_COUNT] = {
		"Stage1.png",
		"Stage2.png",
		"Stage3.png",
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


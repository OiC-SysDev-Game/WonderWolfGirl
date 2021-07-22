#pragma once
#include "SceneBase.h" 

#define STSELECT_STAGE_COUNT		3

#define STSELECT_STAGE_ANKERX		50
#define STSELECT_STAGE_ANKERY		200

#define STSELECT_TEXTUREALPHAINC	0.01f

class CStageSelect : public CSceneBase
{
private:
	CSoundBuffer		S_BackGroundBGM;					//メニュ―画面のBGM
	CSoundBuffer		S_SelectSound;						//カーソル移動時の効果音
	CSoundBuffer		S_DecideSound;						//決定ボタン押した時の効果音
	CSoundBuffer		S_ExitSound;						//戻るボタン押した時の効果音

	CTexture			S_BackImage;
	CTexture*			S_StageImage;
	CTexture			S_StageSelectButtonImage;
	CTexture			S_BackButtonImage;

	int					S_ScenePhase;						//現在のシーン進行度合い
	int					S_MenuSelectNo;						//メニュー選択番号

	float				S_DefaultAlpha;						//イラストの透明度(フェードイン時に使用)

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


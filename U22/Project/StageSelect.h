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
	CSoundBuffer		S_BackGroundBGM;					//メニュ―画面のBGM
	CSoundBuffer		S_SelectSound;						//カーソル移動時の効果音
	CSoundBuffer		S_DecideSound;						//決定ボタン押した時の効果音
	CSoundBuffer		S_ExitSound;						//戻るボタン押した時の効果音

	CTexture			S_BackImage;
	CTexture			S_StageImage[STSELECT_STAGE_COUNT];
	CTexture			S_SelectButtonImage;
	CTexture			S_SelectButtonImage_Select;
	CTexture			S_BackButtonImage;

	int					S_ScenePhase;						//現在のシーン進行度合い
	int					S_StageSelectNo;					//メニュー選択番号

	float				S_DefaultAlpha;							//イラストの透明度(フェードイン時に使用)
	float				S_FeedInPopAlpha[STSELECT_STAGE_COUNT];	//フェードイン時の各ポップに対応したアルファ値
	float				S_FeedOutPopAlpha;						//フェードアウト時のポップに対応したアルファ値
	float				S_FeedInOffsetY[STSELECT_STAGE_COUNT];	//フェードイン時の移動量
	int					S_FeedPopNow;							//フェードイン時、現在フェード処理を行っているポップ番号

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


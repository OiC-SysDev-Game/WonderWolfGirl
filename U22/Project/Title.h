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
	//ポップの種類
	enum T_POP {
		POP_SELECT,
		POP_OPTION,
		POP_END,
	};
	//メニューポップ名(非選択時)
	const char* T_PopNames[TITLE_MENUCOUNT] = {
	"Image/SELECT.png",
	"Image/OPTION.png",
	"Image/END.png",
	};
	//メニューポップ名(選択時/通常)
	const char* T_PopSelectNames[TITLE_MENUCOUNT] = {
	"Image/SELECT_Select.png",
	"Image/OPTION_Select.png",
	"Image/END_Select.png"
	};

	CSoundBuffer		T_BackGroundBGM;					//メニュ―画面のBGM
	CSoundBuffer		T_SelectSound;						//カーソル移動時の効果音
	CSoundBuffer		T_DecideSound;						//決定ボタン押した時の効果音
	CSoundBuffer		T_ExitSound;						//戻るボタン押した時の効果音

	CTexture			T_BackImage;						//背景画像
	CTexture			T_Title;							//タイトル画像
	CTexture			T_Pop[TITLE_MENUCOUNT];				//ポップ画像(非選択時)
	CTexture			T_PopSelect[TITLE_MENUCOUNT];		//ポップ画像(選択時/通常)

	int					T_ScenePhase;						//現在のシーン進行度合い
	int					T_MenuSelectNo;						//メニュー選択番号

	float				T_DefaultAlpha;						//イラストの透明度(フェードイン時に使用)

	float				T_FeedInPopAlpha[TITLE_MENUCOUNT];	//フェードイン時の各ポップに対応したアルファ値
	float				T_FeedOutPopAlpha;					//フェードアウト時のポップに対応したアルファ値
	float				T_FeedInOffsetX[TITLE_MENUCOUNT];	//フェードイン時の移動量
	int					T_FeedPopNow;						//フェードイン時、現在フェード処理を行っているポップ番号

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


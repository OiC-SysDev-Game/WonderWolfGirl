#pragma once
#include "SceneBase.h" 
class CGame : public CSceneBase
{
private:
	CSoundBuffer		G_BackGroundBGM;					//メニュ―画面のBGM
	CSoundBuffer		G_SelectMoveSound;					//カーソル移動時の効果音
	CSoundBuffer		G_DecideSound;						//決定ボタン押した時の効果音
	CSoundBuffer		G_ExitSound;						//戻るボタン押した時の効果音

	int					G_ScenePhase;						//現在のシーン進行度合い
	int					G_NextAction;						//次に実行する動作

	int					G_CurrentMapNum;					//現在のマップ番号

	//シーンの状態
	enum G_GAMEPHASE {
		G_PHASE_START,
		G_PHASE_UNDER,
		G_PHASE_NEXT,
	};

	//フェードアウト後に行う動作
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


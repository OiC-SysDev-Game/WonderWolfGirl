#pragma once
#include "SceneBase.h"

class COption : public CSceneBase
{
private:
	CTexture BackImage;
	CTexture BGMText;
	CTexture SEText;
	CTexture Slider;
	CTexture Slider_Fill;
	CTexture CreditIllust;
	CTexture BackButton;

	enum O_OPTIONPHASE {
		PHASE_START,
		PHASE_UNDER,
		PHASE_NEXT,
	};

	int BGMVolumeMeter;
	int SEVolumeMeter;
	int ScreenScaleMeter;
	bool FullScreenFlg;

	int O_ScenePhase;
	float TextureAlpha;

	void FeedIn();
	bool FeedInEndCheck();
	void FeedOut();
	bool FeedOutEndCheck();
	void MouseControl();
	float MaxOrMinAdjust(float value, float IorDvalue, float max, float min);
	void SlideBGMBar();
	void SlideSEBar();
	void SlideScreenScaleBar();

public:
	COption();
	~COption();
	bool Load();
	void Initialize();
	void Update();
	void Render(CCamera* _camera);
	void RenderDebug(CCamera* _camera);
	void Release();
};


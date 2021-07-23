#pragma once
#include "SceneBase.h"

#define		FILEKEY					0x65

#define		SOUNDVOLUME_INTERVAL		0.05f
#define		SOUNDVOLUME_POINTCOUNT		21

#define		SCREENSCALE_WIDTHINTERVAL 	160
#define		SCREENSCALE_HEIGHTINTERVAL 	90
#define		SCREENSCALE_POINTCOUNT		7

#define		OPTION_TEXTUREALPHAINC		0.01f

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

	void MouseControl();
	void SlideBGMBar();
	void SlideSEBar();
	void SlideScreenScaleBar();

protected:
	void FeedIn();
	bool FeedInEndCheck();
	void FeedOut();
	bool FeedOutEndCheck();

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


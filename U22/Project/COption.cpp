#include "GameApplicaion.h"
#include "Option.h"

#define		FILEKEY					0x65

#define		SOUNDVOLUME_INTERVAL		0.05f
#define		SOUNDVOLUME_POINTCOUNT		21
#define		SCREENSCALE_WIDTHINTERVAL 	160
#define		SCREENSCALE_HEIGHTINTERVAL 	90
#define		SCREENSCALE_POINTCOUNT		7

#define		OPTION_TEXTUREALPHAINC		0.01f

COption::COption() :
	CSceneBase(),
	BackImage(),
	BGMText(),
	SEText(),
	Slider(),
	Slider_Fill(),
	CreditIllust(),
	BackButton(),
	BGMVolumeMeter(SOUNDVOLUME_POINTCOUNT),
	SEVolumeMeter(SOUNDVOLUME_POINTCOUNT),
	ScreenScaleMeter(SCREENSCALE_POINTCOUNT),
	FullScreenFlg(false),
	TextureAlpha(0){
}

COption::~COption()
{};

void fencwrite(void* pdat, int s, FILE* fp) {
	char* psrc = (char*)pdat;
	char* pout = (char*)malloc(s);
	for (int i = 0; i < s; i++)
	{
		pout[i] = psrc[i] ^ FILEKEY;
	}
	fwrite(pout, s, 1, fp);
	free(pout);
}

void fdecread(void* pdat, int s, FILE* fp) {
	char* pout = (char*)pdat;
	char* psrc = (char*)malloc(s);
	fread(psrc, s, 1, fp);
	for (int i = 0; i < s; i++)
	{
		pout[i] = psrc[i] ^ FILEKEY;
	}
	free(psrc);
}

bool COption::Load() {
	BackImage.Load("Image/Option/BackImage");
	BGMText.Load("Image/Option/BGMText");
	SEText.Load("Image/Option/SEText");
	Slider.Load("Image/Option/Slider");
	Slider_Fill.Load("Image/Option/Slider_Fill");
	CreditIllust.Load("Image/Option/Credit");
	BackButton.Load("Image/Option/BackButton");
	return true;
}

void COption::Initialize() {
	//テクスチャの読み込み
	Load();

	
	FILE* fp;
	if (fopen_s(&fp, "ScreenData.dat", "rb") != NULL)
	{
		fdecread(&BGMVolumeMeter, sizeof(int), fp);
		fdecread(&SEVolumeMeter, sizeof(int), fp);
		fdecread(&ScreenScaleMeter, sizeof(int), fp);
		fdecread(&FullScreenFlg, sizeof(bool), fp);
		fclose(fp);
	}
	
	TextureAlpha = 0;
}

void COption::Update() {
	//（仮）Nキーでゲームシーンへ移行
	if (g_pInput->IsPush(u22::input::KeyCode::N))
	{
		bEnd = true;
		NextScene = SCENENO_GAME;
	}

	switch (O_ScenePhase)
	{
	case PHASE_START:
		//導入処理
		FeedIn();
		if (FeedInEndCheck())
		{
			O_ScenePhase++;
		}
		break;
	case PHASE_UNDER:
		//操作中処理
		//マウス操作
		MouseControl();
		break;
	case PHASE_NEXT:
		//次の画面への処理
		FeedOut();
		if (FeedOutEndCheck())
		{

		}
		break;
	default:
		break;
	}
}

void COption::Render(CCamera* _camera) {
}

void COption::RenderDebug(CCamera* _camera) {
	std::string text = "オプション画面\nNキーで次の画面へすっとばせるよ";
	::GraphicsUtilities::RenderString(Vector2(10, 10), color::rgba::kWhite, text, *_camera);
}

void COption::Release() {
}

void COption::FeedIn() {
	//フェードイン処理
	TextureAlpha = MaxOrMinAdjust(TextureAlpha, OPTION_TEXTUREALPHAINC, 1, 0);
}
void COption::FeedOut() {
	//フェードアウト処理
	TextureAlpha = MaxOrMinAdjust(TextureAlpha, -OPTION_TEXTUREALPHAINC, 1, 0);
}

bool COption::FeedInEndCheck() {
	if (TextureAlpha < 1)
	{
		return false;
	}
	return true;
}
bool COption::FeedOutEndCheck() {
	if (TextureAlpha > 0)
	{
		return false;
	}
	return true;
}
void COption::MouseControl() {

}
float COption::MaxOrMinAdjust(float value, float IorDvalue, float max, float min) {
	value += IorDvalue;
	if (value > max)
		value = max;
	if (value < min)
		value = min;

	return value;
}

void COption::SlideBGMBar() {

}

void COption::SlideSEBar() {

}

void COption::SlideScreenScaleBar() {

}

#include "GameApplicaion.h"
#include "StageSelect.h"


CStageSelect::CStageSelect() :
	CSceneBase(),
	S_BackGroundBGM(),
	S_SelectSound(),
	S_DecideSound(),
	S_ExitSound(),
	S_BackImage(),
	S_StageImage(),
	S_SelectButtonImage(),
	S_BackButtonImage(),
	S_ScenePhase(0),
	S_StageSelectNo(-1),
	S_DefaultAlpha(0)
{
}

CStageSelect::~CStageSelect()
{};

bool CStageSelect::Load() {
	S_BackGroundBGM.Load("BGM/0_Title.wav");
	S_SelectSound.Load("SE/0_Select.wav");
	S_DecideSound.Load("SE/0_Decide.wav");
	S_ExitSound.Load("SE/0_Back.wav");

	S_BackImage.Load("Image/StageSelect/BackImage.png");
	for (int i = 0; i < STSELECT_STAGE_COUNT; i++)
	{
		S_StageImage[i].Load(StageImageName[i]);
		S_FeedInPopAlpha[i] = 0;
		S_FeedInOffsetY[i] = STSELECT_FEEDSPACEY;
	}
	S_SelectButtonImage.Load("Image/StageSelect/SelectButton.png");
	S_SelectButtonImage_Select.Load("Image/StageSelect/SelectButton_Select.png");
	S_BackButtonImage.Load("Image/StageSelect/BackButton.png");
	return true;
}

void CStageSelect::Initialize() {
	Load();
	S_BackGroundBGM.SetLoop(true);
	S_BackGroundBGM.Play();
	S_ScenePhase = S_PHASE_START;
	S_StageSelectNo = -1;

	S_DefaultAlpha = 0;
	S_FeedOutPopAlpha = 1;
	S_FeedPopNow = 0;
}

void CStageSelect::Update() {
	//（仮）Nキーでゲームシーンへ移行
	if (g_pInput->IsPush(u22::input::KeyCode::N))
	{
		bEnd = true;
		NextScene = SCENENO_GAME;
	}

	switch (S_ScenePhase)
	{
	case S_PHASE_START:
		//導入処理
		FeedIn();
		if (FeedInEndCheck())
		{
			S_ScenePhase++;
		}
		break;
	case S_PHASE_UNDER:
		//操作中処理
		//マウス操作
		MouseControl();
		break;
	case S_PHASE_NEXT:
		//次の画面への処理
		FeedOut();
		if (FeedOutEndCheck())
		{
			switch (S_StageSelectNo)
			{
			case S_POP_SELECT:
				S_BackGroundBGM.Stop();
				bEnd = true;
				NextScene = SCENENO_GAME;
				break;

			case S_POP_OPTION:
				bEnd = true;
				BeforeScene = SCENENO_STAGESELECT;
				NextScene = SCENENO_OPTION;
				break;

			case S_POP_BACK:				
				bEnd = true;
				NextScene = SCENENO_TITLE;
				break;

			default:
				break;
			}
		}
		break;
	default:
		break;
	}
}

void CStageSelect::Render(CCamera* _camera) {
	float width = g_pFramework->GetWindow()->GetWidth();
	float height = g_pFramework->GetWindow()->GetHeight();

	//背景描画
	S_BackImage.Render(Vector2(0, 0), Vector4(1, 1, 1, S_DefaultAlpha), *_camera);

	//バックボタン描画
	S_BackButtonImage.Render(Vector2(10, height - S_BackButtonImage.GetHeight() - 10),
		Vector4(1, 1, 1, S_DefaultAlpha), *_camera);

	//左端のステージ画像位置
	float StageImageRightSpace = STSELECT_STAGE_ANKERX + S_StageImage[0].GetWidth();
	//ステージ画像間のスペース
	float StageImageSpace
		= (width - (STSELECT_STAGE_ANKERX + StageImageRightSpace)) / (float)(STSELECT_STAGE_COUNT - 1);

	if (S_ScenePhase == S_PHASE_NEXT)
	{
		//ポップ描画
		for (int i = 0; i < STSELECT_STAGE_COUNT; i++)
		{
			//ステージ画像用
			auto PS1_Pos = Vector2(
				STSELECT_STAGE_ANKERX + (float)i * StageImageSpace,
				STSELECT_STAGE_ANKERY + S_FeedInOffsetY[i]);

			//ステージ選択ボタン用
			auto PB1_Pos = PS1_Pos;
			PB1_Pos.x += STSELECT_STAGEBUTTON_ANKERX;
			PB1_Pos.y += STSELECT_STAGEBUTTON_ANKERY;

			Vector4 PS1_Color;

			//選択時
			if (i == S_StageSelectNo)
			{
				PS1_Color = Vector4(1.0f, 1.0f, 1.0f, S_DefaultAlpha);
				S_StageImage[i].Render(PS1_Pos, PS1_Color, *_camera);
				S_SelectButtonImage_Select.Render(PS1_Pos, PS1_Color, *_camera);


			}
			//非選択時
			else
			{
				PS1_Color = Vector4(1.0f, 1.0f, 1.0f, S_FeedOutPopAlpha);
				S_StageImage[i].Render(PS1_Pos, PS1_Color, *_camera);
				S_SelectButtonImage.Render(PB1_Pos, PS1_Color, *_camera);
			}

		}
	}
	else
	{
		//ポップ描画
		for (int i = 0; i < STSELECT_STAGE_COUNT; i++)
		{
			//ステージ画像用
			auto PS1_Pos = Vector2(
				STSELECT_STAGE_ANKERX + (float)i * StageImageSpace,
				STSELECT_STAGE_ANKERY + S_FeedInOffsetY[i]);
			auto PS1_Color = Vector4(1.0f, 1.0f, 1.0f, S_FeedInPopAlpha[i]);
			S_StageImage[i].Render(PS1_Pos, PS1_Color, *_camera);

			//ステージ選択ボタン用
			auto PB1_Pos = PS1_Pos;
			PB1_Pos.x += STSELECT_STAGEBUTTON_ANKERX;
			PB1_Pos.y += STSELECT_STAGEBUTTON_ANKERY;
			//選択時
			if (i == S_StageSelectNo)
			{
				S_SelectButtonImage_Select.Render(PB1_Pos, PS1_Color, *_camera);
			}
			//非選択時
			else
			{
				S_SelectButtonImage.Render(PB1_Pos, PS1_Color, *_camera);
			}
		}
	}
}

void CStageSelect::RenderDebug(CCamera* _camera) {
	std::string text = "ステージ選択画面\nNキーで次の画面へすっとばせるよ";
	::GraphicsUtilities::RenderString(Vector2(10, 10), color::rgba::kWhite, text, *_camera);
}

void CStageSelect::Release() {
}

void CStageSelect::MouseControl() {

}

void CStageSelect::FeedIn() {
	//フェードイン処理
	//背景
	if (S_DefaultAlpha < 1)
	{
		S_DefaultAlpha = MaxOrMinAdjust(S_DefaultAlpha, 1.0f / STSELECT_FEEDTIME, 1, 0);
	}

	for (int i = 0; i < STSELECT_STAGE_COUNT; i++)
	{
		//現在のフェードを実行しているポップまでを処理する
		if (S_FeedPopNow >= i)
		{
			//アルファ値の増加
			S_FeedInPopAlpha[i] = MaxOrMinAdjust(S_FeedInPopAlpha[i], 1.0f / STSELECT_FEEDTIME, 1, 0);
			//特定のアルファ値に達すると、次のポップへと切り替わる
			if (S_FeedInPopAlpha[i] >= STSELECT_FEEDTIMINGALPHA &&
				i == S_FeedPopNow && i != STSELECT_STAGE_COUNT - 1)
			{
				S_FeedPopNow++;
			}
			S_FeedInOffsetY[i] = MaxOrMinAdjust(S_FeedInOffsetY[i], -STSELECT_FEEDSPACEY / STSELECT_FEEDTIME, STSELECT_FEEDSPACEY, 0);
		}
	}
	

}
void CStageSelect::FeedOut() {
	//フェードアウト処理
	S_DefaultAlpha = MaxOrMinAdjust(S_DefaultAlpha, -1.0f / STSELECT_FEEDTIME, 1, 0);
}

bool CStageSelect::FeedInEndCheck() {
	if (S_FeedInPopAlpha[STSELECT_STAGE_COUNT - 1] < 1)
	{
		return false;
	}
	return true;
}
bool CStageSelect::FeedOutEndCheck() {
	if (S_DefaultAlpha > 0)
	{
		return false;
	}
	return true;
}

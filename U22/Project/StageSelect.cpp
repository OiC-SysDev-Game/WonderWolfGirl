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
	S_MenuCommandNo(S_POP_SELECT),
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
	S_MenuCommandNo = S_POP_SELECT;
	S_StageSelectNo = -1;

	S_DefaultAlpha = 0;
	S_FeedOutPopAlpha = 1;
	S_FeedPopNow = 0;
}

void CStageSelect::Update() {
	//�i���jN�L�[�ŃQ�[���V�[���ֈڍs
	if (g_pInput->IsPush(u22::input::KeyCode::N))
	{
		bEnd = true;
		NextScene = SCENENO_GAME;
	}

	switch (S_ScenePhase)
	{
	case S_PHASE_START:
		//��������
		FeedIn();
		if (FeedInEndCheck())
		{
			S_ScenePhase++;
		}
		break;
	case S_PHASE_UNDER:
		//���쒆����
		//�}�E�X����
		MouseControl();
		break;
	case S_PHASE_NEXT:
		//���̉�ʂւ̏���
		FeedOut();
		if (FeedOutEndCheck())
		{
			switch (S_MenuCommandNo)
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

	//�w�i�`��
	S_BackImage.Render(Vector2(0, 0), Vector4(1, 1, 1, S_DefaultAlpha), *_camera);

	::GraphicsUtilities::RenderFillRectangle(CRectangle(100, 100, 200, 200), color::rgba::kRed, *_camera);

	//�o�b�N�{�^���`��
	S_BackButtonImage.Render(Vector2(10, height - S_BackButtonImage.GetHeight() - 10),
		Vector4(1, 1, 1, S_DefaultAlpha), *_camera);

	//���[�̃X�e�[�W�摜�ʒu
	float StageImageRightSpace = STSELECT_STAGE_ANKERX + S_StageImage[0].GetWidth();
	//�X�e�[�W�摜�Ԃ̃X�y�[�X
	float StageImageSpace
		= (width - (STSELECT_STAGE_ANKERX + StageImageRightSpace)) / (float)(STSELECT_STAGE_COUNT - 1);

	if (S_ScenePhase == S_PHASE_NEXT)
	{
		//�|�b�v�`��
		for (int i = 0; i < STSELECT_STAGE_COUNT; i++)
		{
			//�X�e�[�W�摜�p
			auto PS1_Pos = Vector2(
				STSELECT_STAGE_ANKERX + (float)i * StageImageSpace,
				STSELECT_STAGE_ANKERY);

			//�X�e�[�W�I���{�^���p
			auto PB1_Pos = PS1_Pos;
			PB1_Pos.x += STSELECT_STAGEBUTTON_ANKERX;
			PB1_Pos.y += STSELECT_STAGEBUTTON_ANKERY;

			Vector4 PS1_Color;

			//�I����
			if (i == S_StageSelectNo)
			{
				PS1_Color = Vector4(1.0f, 1.0f, 1.0f, S_DefaultAlpha);
				S_StageImage[i].Render(PS1_Pos, PS1_Color, *_camera);
				S_SelectButtonImage_Select.Render(PB1_Pos, PS1_Color, *_camera);
			}
			//��I����
			else
			{
				PS1_Pos.y += S_FeedInOffsetY[i];
				PB1_Pos.y += S_FeedInOffsetY[i];
				PS1_Color = Vector4(1.0f, 1.0f, 1.0f, S_FeedOutPopAlpha);
				S_StageImage[i].Render(PS1_Pos, PS1_Color, *_camera);
				S_SelectButtonImage.Render(PB1_Pos, PS1_Color, *_camera);
			}
		}
	}
	else
	{
		//�|�b�v�`��
		for (int i = 0; i < STSELECT_STAGE_COUNT; i++)
		{
			//�X�e�[�W�摜�p
			auto PS1_Pos = Vector2(
				STSELECT_STAGE_ANKERX + (float)i * StageImageSpace,
				STSELECT_STAGE_ANKERY + S_FeedInOffsetY[i]);
			auto PS1_Color = Vector4(1.0f, 1.0f, 1.0f, S_FeedInPopAlpha[i]);
			S_StageImage[i].Render(PS1_Pos, PS1_Color, *_camera);

			//�X�e�[�W�I���{�^���p
			auto PB1_Pos = PS1_Pos;
			PB1_Pos.x += STSELECT_STAGEBUTTON_ANKERX;
			PB1_Pos.y += STSELECT_STAGEBUTTON_ANKERY;
			//�I����
			if (i == S_StageSelectNo)
			{
				S_SelectButtonImage_Select.Render(PB1_Pos, PS1_Color, *_camera);
			}
			//��I����
			else
			{
				S_SelectButtonImage.Render(PB1_Pos, PS1_Color, *_camera);
			}
		}
	}
}

void CStageSelect::RenderDebug(CCamera* _camera) {
	std::string text = "�X�e�[�W�I�����\nN�L�[�Ŏ��̉�ʂւ����Ƃ΂����";
	::GraphicsUtilities::RenderString(Vector2(10, 10), color::rgba::kWhite, text, *_camera);
}

void CStageSelect::Release() {
}

void CStageSelect::MouseControl() {
	float width = g_pFramework->GetWindow()->GetWidth();
	float height = g_pFramework->GetWindow()->GetHeight();
	//�}�E�X���W���L�^
	CRectangle MousePos = CRectangle(g_pInput->GetMouseX(), g_pInput->GetMouseY(), g_pInput->GetMouseX() + 1, g_pInput->GetMouseY() + 1);

	//���[�̃X�e�[�W�摜�ʒu
	float StageImageRightSpace = STSELECT_STAGE_ANKERX + S_StageImage[0].GetWidth();
	//�X�e�[�W�摜�Ԃ̃X�y�[�X
	float StageImageSpace
		= (width - (STSELECT_STAGE_ANKERX + StageImageRightSpace)) / (float)(STSELECT_STAGE_COUNT - 1);
	bool NotSelectFlg = false;
	for (int i = 0; i < STSELECT_STAGE_COUNT; i++)
	{
		CRectangle rect;
		rect = CRectangle(STSELECT_STAGE_ANKERX + (float)i * StageImageSpace,
			STSELECT_STAGE_ANKERY,
			STSELECT_STAGE_ANKERX + (float)i * StageImageSpace + S_StageImage[i].GetWidth(),
			STSELECT_STAGE_ANKERY + S_StageImage[i].GetHeight());

		if (rect.CollisionRectangle(MousePos))
		{
			S_StageSelectNo = i;
			NotSelectFlg = true;
			if (g_pInput->IsPush(MouseButton::Left))
			{
				S_DecideSound.Play();
				S_ScenePhase++;
				S_MenuCommandNo = S_POP_SELECT;
			}
		}
	}
	if (!NotSelectFlg)
	{
		S_StageSelectNo = -1;
	}
}

void CStageSelect::FeedIn() {
	//�t�F�[�h�C������
	//�w�i
	if (S_DefaultAlpha < 1)
	{
		S_DefaultAlpha = MaxOrMinAdjust(S_DefaultAlpha, 1.0f / STSELECT_FEEDTIME, 1, 0);
	}

	for (int i = 0; i < STSELECT_STAGE_COUNT; i++)
	{
		//���݂̃t�F�[�h�����s���Ă���|�b�v�܂ł���������
		if (S_FeedPopNow >= i)
		{
			//�A���t�@�l�̑���
			S_FeedInPopAlpha[i] = MaxOrMinAdjust(S_FeedInPopAlpha[i], 1.0f / STSELECT_FEEDTIME, 1, 0);
			//����̃A���t�@�l�ɒB����ƁA���̃|�b�v�ւƐ؂�ւ��
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
	//�t�F�[�h�A�E�g����	
	//�I�������|�b�v�ȊO�̃A���t�@�l��������
	if (S_FeedOutPopAlpha > 0)
	{
		S_FeedOutPopAlpha = MaxOrMinAdjust(S_FeedOutPopAlpha, -1.0f / STSELECT_FEEDTIME, 1, 0);
	}
	//���̑�
	else
	{
		S_DefaultAlpha = MaxOrMinAdjust(S_DefaultAlpha, -1.0f / STSELECT_FEEDTIME, 1, 0);
	}
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
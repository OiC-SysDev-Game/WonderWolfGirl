#include "GameApplicaion.h"
#include "Title.h"

CTitle::CTitle() :
	CSceneBase(),
	T_BackGroundBGM(),
	T_SelectSound(),
	T_DecideSound(),
	T_ExitSound(),
	T_BackImage(),
	T_Title(),
	T_Pop(),
	T_PopSelect(),
	T_ScenePhase(0),
	T_MenuSelectNo(-1),
	T_DefaultAlpha(0),
	T_FeedInPopAlpha(),
	T_FeedOutPopAlpha(1),
	T_FeedInOffsetX(),
	T_FeedPopNow(0) {
}

CTitle::~CTitle()
{};

bool CTitle::Load() {
	return true;
	//BBB
}

void CTitle::Initialize() {
	//�T�E���h(������)
	T_BackGroundBGM.Load("BGM/0_Title.wav");
	T_SelectSound.Load("SE/0_Select.wav");
	T_DecideSound.Load("SE/0_Decide.wav");
	T_ExitSound.Load("SE/0_Back.wav");

	T_BackGroundBGM.SetLoop(true);
	T_BackGroundBGM.Play();

	//�w�i
	T_BackImage.Load("Image/Title/BackImage.png");
	//�^�C�g��
	T_Title.Load("Image/Title/Title.png");

	//�|�b�v�C���X�g
	for (int i = 0; i < TITLE_MENUCOUNT; i++)
	{
		T_Pop[i].Load(T_PopNames[i]);
		T_PopSelect[i].Load(T_PopSelectNames[i]);

		T_FeedInPopAlpha[i] = 0;
		T_FeedInOffsetX[i] = TITLE_FEEDSPACEX;
	}
	T_ScenePhase = PHASE_START;
	T_MenuSelectNo = -1;

	T_DefaultAlpha = 0;
	T_FeedOutPopAlpha = 1;
	T_FeedPopNow = 0;
}

void CTitle::Update() {
	//�i���jN�L�[�ŃX�e�[�W�I���V�[���ֈڍs
	if (g_pInput->IsPush(u22::input::KeyCode::N))
	{
		T_BackGroundBGM.Stop();
		bEnd = true;
		NextScene = SCENENO_STAGESELECT;
	}

	switch (T_ScenePhase)
	{
	case PHASE_START:
		//��������
		FeedIn();
		if (FeedInEndCheck())
		{
			T_ScenePhase++;
		}
		break;
	case PHASE_UNDER:
		//���쒆����
		//�}�E�X����
		MouseControl();
		break;
	case PHASE_NEXT:
		//���̉�ʂւ̏���
		FeedOut();
		if (FeedOutEndCheck())
		{
			switch (T_MenuSelectNo)
			{
			case POP_SELECT:
				T_BackGroundBGM.Stop();
				bEnd = true;
				NextScene = SCENENO_STAGESELECT;
				break;

			case POP_OPTION:
				bEnd = true;
				BeforeScene = SCENENO_TITLE;
				NextScene = SCENENO_OPTION;
				break;

			case POP_END:
				::PostQuitMessage(0);
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

void CTitle::Render(CCamera* _camera) {
	float width = g_pFramework->GetWindow()->GetWidth();
	float height = g_pFramework->GetWindow()->GetHeight();

	//�w�i�`��
	T_BackImage.Render(Vector2(0, 0), Vector4(1, 1, 1, T_DefaultAlpha), *_camera);

	//�^�C�g���`��
	T_Title.Render(Vector2((width - T_Title.GetWidth()) / 2, TITLE_TITLETOPSPACE),
		Vector4(1, 1, 1, T_DefaultAlpha), *_camera);

	if (T_ScenePhase == PHASE_NEXT)
	{
		//�|�b�v�`��
		for (int i = 0; i < TITLE_MENUCOUNT; i++)
		{
			//�I����
			if (i == T_MenuSelectNo)
			{
				auto PS1P = Vector3((width - T_PopSelect[i].GetWidth()) / 2 + T_FeedInOffsetX[i],
					(height - T_PopSelect[i].GetHeight()) / 2 + i * TITLE_POPSPACE + TITLE_POPTOPSPACE, 0);
				auto PS1C = Vector4(1.0f, 1.0f, 1.0f, T_DefaultAlpha);
				T_PopSelect[i].Render(PS1P, PS1C, *_camera);
			}
			//��I����
			else
			{
				auto PP = Vector3((width - T_Pop[i].GetWidth()) / 2 + T_FeedInOffsetX[i],
					(height - T_Pop[i].GetHeight()) / 2 + i * TITLE_POPSPACE + TITLE_POPTOPSPACE, 0);
				auto PC = Vector4(1.0f, 1.0f, 1.0f, T_FeedOutPopAlpha);
				T_Pop[i].Render(PP, PC, *_camera);
			}
		}
	}
	else
	{
		//�|�b�v�`��
		for (int i = 0; i < TITLE_MENUCOUNT; i++)
		{
			//�I����
			if (i == T_MenuSelectNo)
			{
				auto PS1P = Vector3((width - T_PopSelect[i].GetWidth()) / 2 + T_FeedInOffsetX[i],
					(height - T_PopSelect[i].GetHeight()) / 2 + i * TITLE_POPSPACE + TITLE_POPTOPSPACE, 0);
				auto PS1C = Vector4(1.0f, 1.0f, 1.0f, T_FeedInPopAlpha[i]);
				T_PopSelect[i].Render(PS1P, PS1C, *_camera);
			}
			//��I����
			else
			{
				auto PP = Vector3((width - T_Pop[i].GetWidth()) / 2 + T_FeedInOffsetX[i],
					(height - T_Pop[i].GetHeight()) / 2 + i * TITLE_POPSPACE + TITLE_POPTOPSPACE, 0);
				auto PC = Vector4(1.0f, 1.0f, 1.0f, T_FeedInPopAlpha[i]);
				T_Pop[i].Render(PP, PC, *_camera);
			}
		}
	}
}

void CTitle::RenderDebug(CCamera* _camera) {
	float width = g_pFramework->GetWindow()->GetWidth();
	float height = g_pFramework->GetWindow()->GetHeight();

	std::string text = "�^�C�g�����\nN�L�[�Ŏ��̉�ʂւ����Ƃ΂����";
	::GraphicsUtilities::RenderString(Vector2(10, 10), color::rgba::kWhite, text, *_camera);
}

void CTitle::Release() {
	T_BackGroundBGM.Release();
	T_SelectSound.Release();
	T_DecideSound.Release();
	T_ExitSound.Release();

	T_BackImage.Release();
	T_Title.Release();
	for (int i = 0; i < TITLE_MENUCOUNT; i++)
	{
		T_Pop[i].Release();
		T_PopSelect[i].Release();
	}
}

void CTitle::FeedIn() {
	//�t�F�[�h�C������
	//�w�i
	if (T_DefaultAlpha < 1)
	{
		T_DefaultAlpha = MaxOrMinAdjust(T_DefaultAlpha, 1.0f / TITLE_FEEDTIME, 1, 0);
	}
	//���j���[�|�b�v
	else if (T_FeedInPopAlpha[TITLE_MENUCOUNT - 1] < 1 || T_FeedInOffsetX[TITLE_MENUCOUNT - 1] < 0)
	{
		for (int i = 0; i < TITLE_MENUCOUNT; i++)
		{
			//���݂̃t�F�[�h�����s���Ă���|�b�v�܂ł���������
			if (T_FeedPopNow >= i)
			{
				//�A���t�@�l�̑���
				T_FeedInPopAlpha[i] = MaxOrMinAdjust(T_FeedInPopAlpha[i], 1.0f / TITLE_FEEDTIME, 1, 0);
				//����̃A���t�@�l�ɒB����ƁA���̃|�b�v�ւƐ؂�ւ��
				if (T_FeedInPopAlpha[i] >= TITLE_FEEDTIMINGALPHA && i == T_FeedPopNow && i != TITLE_MENUCOUNT - 1)
				{
					T_FeedPopNow++;
				}
				T_FeedInOffsetX[i] = MaxOrMinAdjust(T_FeedInOffsetX[i], -TITLE_FEEDSPACEX / TITLE_FEEDTIME, 0, TITLE_FEEDSPACEX);
			}
		}
	}
}
void CTitle::FeedOut() {
	//�I�������|�b�v�ȊO�̃A���t�@�l��������
	if (T_FeedOutPopAlpha > 0)
	{
		T_FeedOutPopAlpha = MaxOrMinAdjust(T_FeedOutPopAlpha, -1.0f / TITLE_FEEDTIME, 1, 0);
	}
	//���̑�
	else if (T_DefaultAlpha > 0)
	{
		T_DefaultAlpha = MaxOrMinAdjust(T_DefaultAlpha, -1.0f / TITLE_FEEDTIME, 1, 0);
	}
}
bool CTitle::FeedInEndCheck() {
	//���j���[�|�b�v���������A�܂��̓X���C�h���؂�Ă��Ȃ����A������󂯕t���Ȃ�
	if (T_FeedInPopAlpha[TITLE_MENUCOUNT - 1] < 1 || T_FeedInOffsetX[TITLE_MENUCOUNT - 1] < 0)
	{
		return false;
	}
	return true;
}
bool CTitle::FeedOutEndCheck() {
	if (T_DefaultAlpha > 0)
	{
		return false;
	}
	return true;
}

void CTitle::MouseControl() {
	float width = g_pFramework->GetWindow()->GetWidth();
	float height = g_pFramework->GetWindow()->GetHeight();
	//�}�E�X���W���L�^
	CRectangle MousePos = CRectangle(g_pInput->GetMouseX(), g_pInput->GetMouseY(), g_pInput->GetMouseX() + 1, g_pInput->GetMouseY() + 1);
	bool NotSelectFlg = false;
	for (int i = 0; i < TITLE_MENUCOUNT; i++)
	{
		CRectangle rect;
		if (i == T_MenuSelectNo)
		{
			rect = CRectangle((width - T_PopSelect[i].GetWidth()) / 2 + T_FeedInOffsetX[i],
				(height - T_PopSelect[i].GetHeight()) / 2 + i * TITLE_POPSPACE + TITLE_POPTOPSPACE,
				(width + T_PopSelect[i].GetWidth()) / 2 + T_FeedInOffsetX[i],
				(height + T_PopSelect[i].GetHeight()) / 2 + i * TITLE_POPSPACE + TITLE_POPTOPSPACE);
		}
		else
		{
			rect = CRectangle((width - T_Pop[i].GetWidth()) / 2 + T_FeedInOffsetX[i],
				(height - T_Pop[i].GetHeight()) / 2 + i * TITLE_POPSPACE + TITLE_POPTOPSPACE,
				(width + T_Pop[i].GetWidth()) / 2 + T_FeedInOffsetX[i],
				(height + T_Pop[i].GetHeight()) / 2 + i * TITLE_POPSPACE + TITLE_POPTOPSPACE);
		}

		if (rect.CollisionRectangle(MousePos))
		{
			T_MenuSelectNo = i;
			NotSelectFlg = true;
			if (g_pInput->IsPush(MouseButton::Left))
			{
				T_ScenePhase++;
				switch (T_MenuSelectNo)
				{
				case POP_SELECT:
					T_DecideSound.Play();
					break;
				case POP_OPTION:
					T_DecideSound.Play();
					break;
				case POP_END:
					T_ExitSound.Play();
					break;
				}
			}
		}
	}
	if (!NotSelectFlg)
	{
		T_MenuSelectNo = -1;
	}
}
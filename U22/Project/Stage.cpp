#define _CRT_SECURE_NO_WARNINGS

#include "Stage.h"
#include <string.h>

CStage::CStage(){
}

CStage::~CStage()
{};

bool CStage::Load(int path) {
	//�t�@�C���p�X
	char Filepass[40] = "Image/Game/";
	char NameAddFilepass[120] = "";
	strcpy(NameAddFilepass, Filepass);
	strcat(NameAddFilepass, "Stage1.txt");
	//�e�L�X�g�t�@�C�����J��
	FILE* fp;
	fopen_s(&fp, NameAddFilepass, "rt");
	if (fp == NULL)
	{
		return false;
	}

	//�t�@�C���̑S�e�ʂ𒲂ׂ�
	fseek(fp, 0, SEEK_END);
	long fSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	//�t�@�C���T�C�Y�������̃��������m�ۂ���
	char* pBuffer = (char*)malloc(fSize + 1);
	//�t�@�C����S�ăo�b�t�@�ɓǂݍ���
	fSize = fread(pBuffer, 1, fSize, fp);
	pBuffer[fSize] = '\0';
	char* pstr;

	//�Â��f�[�^��j��
	//ReleaseMapData();

	//�e�N�X�`���̓ǂݍ���
	pstr = strtok(pBuffer, ",");
	strcpy(NameAddFilepass, Filepass);
	strcat(NameAddFilepass, pstr);
	m_BackTexture.Load(NameAddFilepass);
	pstr = strtok(NULL, ",");
	strcpy(NameAddFilepass, Filepass);
	strcat(NameAddFilepass, pstr);
	m_ChipTexture.Load(NameAddFilepass);

	//�v���C���[�����ʒu
	pstr = strtok(NULL, ",");
	m_PlayerPosX = atoi(pstr);
	pstr = strtok(NULL, ",");
	m_PlayerPosY = atoi(pstr);
	pstr = strtok(NULL, ",");
	m_PlayerSize = atoi(pstr);

	//�`�b�v�T�C�Y
	pstr = strtok(NULL, ",");
	m_XChipSize = atoi(pstr);
	pstr = strtok(NULL, ",");
	m_YChipSize = atoi(pstr);
	pstr = strtok(NULL, ",");
	m_XChipEditorSize = atoi(pstr);
	pstr = strtok(NULL, ",");
	m_YChipEditorSize = atoi(pstr);

	//�}�b�v�`�b�v��
	pstr = strtok(NULL, ",");
	m_XChipCount = atoi(pstr);
	pstr = strtok(NULL, ",");
	m_YChipCount = atoi(pstr);
	pstr = strtok(NULL, ",");
	m_LayerCount = atoi(pstr);

	//�}�b�v�̃`�b�v������ (��*�s��)
	int totalChips = m_XChipCount * m_YChipCount * m_LayerCount;

	//�}�b�v�`�b�v�������m��
	m_pChipData = (int*)malloc(sizeof(int) * totalChips);
	m_pObjectData = (int*)malloc(sizeof(int) * totalChips);
	m_pEnemyData = (int*)malloc(sizeof(int) * totalChips);
	m_pItemData = (int*)malloc(sizeof(int) * totalChips);

	//�`�b�v�f�[�^�̓ǂݍ���
	for (int l = 0; l < m_LayerCount; l++)
	{
		for (int y = 0; y < m_YChipCount; y++)
		{
			for (int x = 0; x < m_XChipCount; x++)
			{
				pstr = strtok(NULL, ",");
				m_pChipData[l * m_XChipCount * m_YChipCount + y * m_XChipCount + x] = atoi(pstr);
			}
		}
	}

	
	//�I�u�W�F�N�g�̃e�N�X�`���ǂݍ���
	pstr = strtok(NULL, ",");
	m_ObjectTextureCount = atoi(pstr);
	for (int i = 0; i < m_ObjectTextureCount; i++)
	{
		pstr = strtok(NULL, ",");
		//�ꎞ�ǂݍ��݃e�N�X�`��
		CTexture* tmp = new CTexture();
		//�I�񂾃t�@�C�����J��
		if (!tmp->Load(pstr))
		{
			return false;
		}
		//�e�N�X�`����z��ɒǉ�����
		//m_ObjectTextureArray.a(&tmp);
		
	}
	
	m_ObjectCount = 0;
	for (int l = 0; l < m_LayerCount; l++)
	{
		for (int y = 0; y < m_YChipCount; y++)
		{
			for (int x = 0; x < m_XChipCount; x++)
			{
				pstr = strtok(NULL, ",");
				m_pObjectData[l * m_XChipCount * m_YChipCount + y * m_XChipCount + x] = atoi(pstr);
				if (m_pObjectData[l * m_XChipCount * m_YChipCount + y * m_XChipCount + x] > 0)
				{
					m_ObjectCount++;
				}
			}
		}
	}

	//�G�z�u���
	m_EnemyCount = 0;
	for (int l = 0; l < m_LayerCount; l++)
	{
		for (int y = 0; y < m_YChipCount; y++)
		{
			for (int x = 0; x < m_XChipCount; x++)
			{
				pstr = strtok(NULL, ",");
				m_pEnemyData[l * m_XChipCount * m_YChipCount + y * m_XChipCount + x] = atoi(pstr);
				if (m_pEnemyData[l * m_XChipCount * m_YChipCount + y * m_XChipCount + x] > 0)
				{
					m_EnemyCount++;
				}
			}
		}
	}

	//�A�C�e���z�u���
	m_ItemCount = 0;
	for (int l = 0; l < m_LayerCount; l++)
	{
		for (int y = 0; y < m_YChipCount; y++)
		{
			for (int x = 0; x < m_XChipCount; x++)
			{
				pstr = strtok(NULL, ",");
				m_pItemData[l * m_XChipCount * m_YChipCount + y * m_XChipCount + x] = atoi(pstr);
				if (m_pEnemyData[l * m_XChipCount * m_YChipCount + y * m_XChipCount + x] > 0)
				{
					m_ItemCount++;
				}
			}
		}
	}

	//�t�@�C�������
	fclose(fp);
	free(pBuffer);
	return true;
}

void CStage::Initialize() {
	m_ScrollX = 0;
	m_ScrollY = 0;

	Load(1);
}

void CStage::Update() {
}

void CStage::Render(CCamera* _camera) {
	//���i�̕`��
	int scw = g_pFramework->GetWindow()->GetWidth();
	int sch = g_pFramework->GetWindow()->GetWidth();
	int wn = m_BackTexture.GetWidth();
	int hn = m_BackTexture.GetHeight();

	for (float y = ((int)-m_ScrollY % hn) - hn; y < sch; y += hn)
	{
		for (float x = ((int)-m_ScrollX % wn) - wn; x < scw; x += wn)
		{
			m_BackTexture.Render(Vector2(x, y), *_camera);
		}
	}

	// �e�N�X�`���̉�������}�b�v�`�b�v�̏c�I�t�Z�b�g�����߂�
	int tcx = m_ChipTexture.GetWidth() / m_XChipSize;
	// �}�b�v�`�b�v�̕`��
	for (int y = 0; y < m_YChipCount; y++)
	{
		for (int x = 0; x < m_XChipCount; x++)
		{
			// �`�悷��`�b�v�ԍ�
			// �`�b�v�ԍ�0�͕`�悵�Ȃ�
			char cn = m_pChipData[y * m_XChipCount + x] - 1;
			if (cn < 0 || cn == 16)
			{
				continue;
			}
			// �}�b�v�`�b�v�̋�`
			CRectangle cr(m_XChipSize * (cn % tcx), m_YChipSize * (cn / tcx), m_XChipSize * (cn % tcx + 1), m_YChipSize * (cn / tcx + 1));
			// �}�b�v�`�b�v�̕`��
			Vector2 posMC = Vector2(-m_ScrollX + x * m_XChipSize, -m_ScrollY + y * m_YChipSize);
			m_ChipTexture.Render(posMC, cr, *_camera);
		}
	}
	
	//X,Y���̃X�N���[���l�i�[
	char SX[40];
	char SY[40];
	sprintf(SX, "ScrollX : %0.2f", m_ScrollX);
	sprintf(SY, "ScrollY : %0.2f", m_ScrollY);
	GraphicsUtilities::RenderString(Vector2(10, 70), Vector4(0, 0, 0, 1), SX, *_camera);
	GraphicsUtilities::RenderString(Vector2(10, 100), Vector4(0, 0, 0, 1), SY, *_camera);
}

void CStage::RenderDebug(CCamera* _camera) {
	GraphicsUtilities::RenderString(Vector2(10, 10), Vector4(0, 0, 0, 1), "ScrollX : " + (char)m_ScrollX, *_camera);
	GraphicsUtilities::RenderString(Vector2(10, 40), Vector4(0, 0, 0, 1), "ScrollY : " + (char)m_ScrollY, *_camera);

	for (int y = 0; y < m_YChipCount; y++)
	{
		for (int x = 0; x < m_XChipCount; x++)
		{
			// �`�悷��`�b�v�ԍ�
			// �`�b�v�ԍ�0�͕`�悵�Ȃ�
			char cn = m_pChipData[y * m_XChipCount + x] - 1;
			if (cn < 0)
			{
				continue;
			}
			// �}�b�v�`�b�v�̋�`
			CRectangle cr = GetStageRect(cn, x, y, GetScroll());
			// �}�b�v�`�b�v�̕`��
			GraphicsUtilities::RenderLineRectangle(cr, Vector4(0, 0, 0, 1), *_camera);
		}
	}
}

void CStage::Release() {
	ReleaseMapData();
}

void CStage::ReleaseMapData() {
	// �m�ۂ����f�[�^�̉��
	m_ChipTexture.Release();
	m_BackTexture.Release();
	if (m_pChipData)
	{
		free(m_pChipData);
		m_pChipData = NULL;
	}
	if (m_pObjectData)
	{
		free(m_pObjectData);
		m_pObjectData = NULL;
	}
	if (m_pEnemyData)
	{
		free(m_pEnemyData);
		m_pEnemyData = NULL;
	}
	if (m_pItemData)
	{
		free(m_pItemData);
		m_pItemData = NULL;
	}
}

bool CStage::CollisionWolf(CWolf& wolf) {
	bool re = false;
	CRectangle C_CurRec = wolf.GetRect();
	CRectangle C_BackRec = wolf.GetBackRect();

	//�����蔻�肷���`�̍���ƉE���̃`�b�v�ʒu�����߂�
	int lc = C_CurRec.left / m_XChipSize;
	int rc = C_CurRec.right / m_XChipSize;
	int tc = C_CurRec.top / m_YChipSize;
	int bc = C_CurRec.bottom / m_YChipSize;
	//�X�e�[�W�͈̔͊O�ɂ͂Ȃ�Ȃ��悤�ɂ���
	if (lc < 0)
	{
		lc = 0;
	}
	if (tc < 0)
	{
		tc = 0;
	}
	if (rc >= m_XChipCount)
	{
		rc = m_XChipCount - 1;
	}
	if (bc >= m_YChipCount)
	{
		bc = m_YChipCount - 1;
	}

	//�L�����N�^�[�̌��ݒnX���W���}�C�i�X�l�ł���Ƃ��A0�ɖ߂�
	if (C_CurRec.left <= 0)
	{
		float ox = -C_CurRec.left;
		wolf.CollisionObject(ox, 0);
	}
	//�L�����N�^�[�̌��ݒnX���W���}�b�v�͈͊O�ł���Ƃ��A�ő�X���W�l�ɖ߂�
	else if (C_CurRec.right >= m_XChipCount * m_XChipSize)
	{
		float ox = m_XChipCount * m_XChipSize - C_CurRec.right;
		wolf.CollisionObject(ox, 0);
	}

	//�v���C���[�̈ʒu�𒲐�
	C_CurRec = wolf.GetRect();

	//X���AY���̈ړ��ʂ̐�Βl���v�Z
	float xmove = abs(C_CurRec.left - C_BackRec.left);
	float ymove = abs(C_CurRec.top - C_BackRec.top);

	//�����蔻��������`�̍��ォ��E���͈̔͂̂ݓ����蔻��������Ȃ�
	//����ȊO�̔ԍ��͓����邱�Ƃ͂Ȃ��̂Ŕ��肪�K�v�Ȃ�
	for (int y = tc; y <= bc; y++)
	{
		for (int x = lc; x <= rc; x++)
		{
			//�`�悷��`�b�v�ԍ�
			//�`�b�v�ԍ��O�͓����蔻�肵�Ȃ�
			char cn = m_pChipData[y * m_XChipCount + x] - 1;
			if (cn + 1 == 0) { continue; }

			//�X�e�[�W�̒Z�a
			CRectangle ObjRec = GetStageRect(cn, x, y);
			float ox, oy = 0;
			if (ymove >= xmove)
			{
				if (CollisionHorizontal(ObjRec, wolf.GetRect(), C_BackRec, oy))
				{
					wolf.CollisionObject(0, oy);
				}
				if (CollisionVertical(ObjRec, wolf.GetRect(), C_BackRec, ox))
				{
					wolf.CollisionObject(ox, 0);
				}
			}
			else
			{
				
				if (CollisionVertical(ObjRec, wolf.GetRect(), C_BackRec, ox))
				{
					wolf.CollisionObject(ox, 0);
				}
				if (CollisionHorizontal(ObjRec, wolf.GetRect(), C_BackRec, oy))
				{
					wolf.CollisionObject(0, oy);
				}
			}
		}
	}
	return re;
}

bool CStage::CollisionHorizontal(CRectangle objectRec, CRectangle charaCurRec, CRectangle charaBackRec, float& oy) {
	//�L�����̌��ݒn�̒Z�a
	CRectangle CurRec = charaCurRec;
	//�L������1�t���[���O�̈ʒu�̒Z�a
	CRectangle BackRec = charaBackRec;
	//�ڐG����X�e�[�W�I�u�W�F�N�g�̒Z�a
	CRectangle ObjRec = objectRec;

	Line lineStage;
	Line linePlayer_Right;
	Line linePlayer_Left;
	//�������Ɉړ���
	if (CurRec.top >= BackRec.top)
	{
		//�����蔻��p�̃L�����N�^��`
		//���Ŕ͈͂����肵����p�̋�`���쐬����B
		CRectangle CBotRec = CurRec;
		CBotRec.top = CBotRec.bottom;	//��`�͏㑤�����Ɠ����l�ɂ���
		CBotRec.left += 6;				//���͈̔͂��������߂�
		CBotRec.right -= 6;

		CRectangle BBotRec = BackRec;
		BBotRec.top = BBotRec.bottom;	//��`�͏㑤�����Ɠ����l�ɂ���
		BBotRec.left += 6;			//���͈̔͂��������߂�
		BBotRec.right -= 6;
		//�L�����N�^�[�̉��Ɠ����蔻��
		//�I�u�W�F�N�g�Əd�Ȃ��Ă���ꍇ
		if (ObjRec.CollisionRectangle(CBotRec))
		{
			//���̖��܂�Ȃ̂Ń`�b�v�̏�[�����`�̉��[�̒l���������l�����܂�̒l�ɂȂ�
			oy = ObjRec.top - CurRec.bottom;
			return true;
		}

		//�I�u�W�F�N�g��ʂ�߂��Ă���ꍇ
		//�I�u�W�F�N�g�̏㕔���̓����蔻��
		lineStage.StartPos = Vector2(ObjRec.left, ObjRec.top);
		lineStage.EndPos = Vector2(ObjRec.right, ObjRec.top);
		//�L�����N�^�[�E���̓����蔻��
		linePlayer_Right.StartPos = Vector2(CBotRec.right, CBotRec.bottom);
		linePlayer_Right.EndPos = Vector2(BBotRec.right, BBotRec.bottom);
		//�L�����N�^�[�����̓����蔻��
		linePlayer_Left.StartPos = Vector2(CBotRec.left, CBotRec.bottom);
		linePlayer_Left.EndPos = Vector2(BBotRec.left, BBotRec.bottom);
		if (CollisionLine(lineStage, linePlayer_Right) ||
			CollisionLine(lineStage, linePlayer_Left))
		{
			oy = ObjRec.top - CurRec.bottom;
			return true;
		}
	}
	//������Ɉړ���
	else
	{
		//�����蔻��p�̃L�����N�^��`
		//��Ŕ͈͂����肵����p�̋�`���쐬����B
		CRectangle CTopRec = CurRec;
		CTopRec.bottom = CTopRec.top;	//��`�͉�������Ɠ����l�ɂ���
		CTopRec.left += 6;				//���͈̔͂��������߂�
		CTopRec.right -= 6;

		CRectangle BTopRec = BackRec;
		BTopRec.bottom = BTopRec.top;	//��`�͉�������Ɠ����l�ɂ���
		BTopRec.left += 6;				//���͈̔͂��������߂�
		BTopRec.right -= 6;
		//�L�����N�^�[�̏�Ɠ����蔻��
		//�I�u�W�F�N�g�Əd�Ȃ��Ă���ꍇ
		if (ObjRec.CollisionRectangle(CTopRec))
		{
			//��̖��܂�Ȃ̂Ń`�b�v�̉��[�����`�̏�[�̒l���������l�����܂�̒l�ɂȂ�
			oy = ObjRec.bottom - CurRec.top;
			return true;
		}

		//�I�u�W�F�N�g��ʂ�߂��Ă���ꍇ
		//�I�u�W�F�N�g�̉������̓����蔻��
		lineStage.StartPos = Vector2(ObjRec.left, ObjRec.bottom);
		lineStage.EndPos = Vector2(ObjRec.right, ObjRec.bottom);
		//�L�����N�^�[�E��̓����蔻��
		linePlayer_Right.StartPos = Vector2(CTopRec.right, CTopRec.top);
		linePlayer_Right.EndPos = Vector2(BTopRec.right, BTopRec.top);
		//�L�����N�^�[����̓����蔻��
		linePlayer_Left.StartPos = Vector2(CTopRec.left, CTopRec.top);
		linePlayer_Left.EndPos = Vector2(BTopRec.left, BTopRec.top);
		if (CollisionLine(lineStage, linePlayer_Right) ||
			CollisionLine(lineStage, linePlayer_Left))
		{
			oy = ObjRec.bottom - CurRec.top;
			return true;
		}
	}
	return false;
}

bool CStage::CollisionVertical(CRectangle objectRec, CRectangle charaCurRec, CRectangle charaBackRec, float& ox) {
	//�L�����̌��ݒn�̒Z�a
	CRectangle CurRec = charaCurRec;
	//�L������1�t���[���O�̈ʒu�̒Z�a
	CRectangle BackRec = charaBackRec;
	//�ڐG����X�e�[�W�I�u�W�F�N�g�̒Z�a
	CRectangle ObjRec = objectRec;

	Line lineStage;
	Line linePlayer_Top;
	Line linePlayer_Bottom;

	//�������Ɉړ���
	if (CurRec.left <= BackRec.left)
	{
		//�����蔻��p�̃L�����N�^��`
		//���Ŕ͈͂����肵����p�̋�`���쐬����B
		CRectangle CLeftRec = CurRec;
		CLeftRec.right = CLeftRec.left;	//��`�͉E�������Ɠ����l�ɂ���
		CLeftRec.bottom -= 6;			//�c�͈̔͂��������߂�
		CLeftRec.top += 6;

		CRectangle BLeftRec = BackRec;
		BLeftRec.right = BLeftRec.left;	//��`�͉E�������Ɠ����l�ɂ���
		BLeftRec.bottom -= 6;			//�c�͈̔͂��������߂�
		BLeftRec.top += 6;

		//�L�����N�^�[�̍��Ɠ����蔻��
		//�I�u�W�F�N�g�Əd�Ȃ��Ă���ꍇ
		if (ObjRec.CollisionRectangle(CLeftRec))
		{
			//���̖��܂�Ȃ̂Ń`�b�v�̉E�[�����`�̍��[�̒l���������l�����܂�̒l�ɂȂ�
			ox = ObjRec.right - CurRec.left;
			return true;
		}

		//�I�u�W�F�N�g��ʂ�߂��Ă���ꍇ
		//�I�u�W�F�N�g�̉E�����̓����蔻��
		lineStage.StartPos = Vector2(ObjRec.right, ObjRec.top);
		lineStage.EndPos = Vector2(ObjRec.right, ObjRec.bottom);
		//�L�����N�^�[����̓����蔻��
		linePlayer_Top.StartPos = Vector2(CLeftRec.left, CLeftRec.top);
		linePlayer_Top.EndPos = Vector2(BLeftRec.left, BLeftRec.top);
		//�L�����N�^�[�����̓����蔻��
		linePlayer_Bottom.StartPos = Vector2(CLeftRec.left, CLeftRec.bottom);
		linePlayer_Bottom.EndPos = Vector2(BLeftRec.left, BLeftRec.bottom);
		if (CollisionLine(lineStage, linePlayer_Top) ||
			CollisionLine(lineStage, linePlayer_Bottom))
		{
			ox = ObjRec.right - CurRec.left;
			return true;
		}
	}
	//�E�����Ɉړ���
	else
	{
		//�����蔻��p�̃L�����N�^��`
		//�E�Ŕ͈͂����肵����p�̋�`���쐬����B
		CRectangle CRightRec = CurRec;
		CRightRec.left = CRightRec.right;	//��`�͍������E�Ɠ����l�ɂ���
		CRightRec.bottom -= 6;			//�c�͈̔͂��������߂�
		CRightRec.top += 6;

		CRectangle BRightRec = BackRec;
		BRightRec.left = BRightRec.right;	//��`�͍������E�Ɠ����l�ɂ���
		BRightRec.bottom -= 6;			//�c�͈̔͂��������߂�
		BRightRec.top += 6;

		//�L�����N�^�[�̉E�Ɠ����蔻��
		//�I�u�W�F�N�g�Əd�Ȃ��Ă���ꍇ
		if (ObjRec.CollisionRectangle(CRightRec))
		{
			//�E�̖��܂�Ȃ̂Ń`�b�v�̍��[�����`�̉E�[�̒l���������l�����܂�̒l�ɂȂ�
			ox = ObjRec.left - CurRec.right;
			return true;
		}

		//�I�u�W�F�N�g��ʂ�߂��Ă���ꍇ
		//�I�u�W�F�N�g�̍������̓����蔻��
		lineStage.StartPos = Vector2(ObjRec.left, ObjRec.top);
		lineStage.EndPos = Vector2(ObjRec.left, ObjRec.bottom);
		//�L�����N�^�[�E��̓����蔻��
		linePlayer_Top.StartPos = Vector2(CRightRec.right, CRightRec.top);
		linePlayer_Top.EndPos = Vector2(BRightRec.right, BRightRec.top);
		//�L�����N�^�[�E���̓����蔻��
		linePlayer_Bottom.StartPos = Vector2(CRightRec.right, CRightRec.bottom);
		linePlayer_Bottom.EndPos = Vector2(BRightRec.right, BRightRec.bottom);
		if (CollisionLine(lineStage, linePlayer_Top) ||
			CollisionLine(lineStage, linePlayer_Bottom))
		{
     			ox = ObjRec.left - CurRec.right;
			return true;
		}
	}
	return false;
}

bool CStage::CollisionLine(Line line1, Line line2) {
	float s, t;
	s = (line1.StartPos.x - line1.EndPos.x) * (line2.StartPos.y - line1.StartPos.y) - (line1.StartPos.y - line1.EndPos.y) * (line2.StartPos.x - line1.StartPos.x);
	t = (line1.StartPos.x - line1.EndPos.x) * (line2.EndPos.y - line1.StartPos.y) - (line1.StartPos.y - line1.EndPos.y) * (line2.EndPos.x - line1.StartPos.x);
	if (s * t > 0)
		return false;

	s = (line2.StartPos.x - line2.EndPos.x) * (line1.StartPos.y - line2.StartPos.y) - (line2.StartPos.y - line2.EndPos.y) * (line1.StartPos.x - line2.StartPos.x);
	t = (line2.StartPos.x - line2.EndPos.x) * (line1.EndPos.y - line2.StartPos.y) - (line2.StartPos.y - line2.EndPos.y) * (line1.EndPos.x - line2.StartPos.x);
	if (s * t > 0)
		return false;
	return true;
}

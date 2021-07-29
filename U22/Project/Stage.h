#pragma once
#include "U22.h"

typedef struct tag_Line {
	Vector2 StartPos;
	Vector2 EndPos;

	tag_Line() {
		StartPos = Vector2(0, 0);
		EndPos = Vector2(0, 0);
	};
}Line;

class CStage
{
private:
	CTexture				m_ChipTexture;
	CTexture				m_BackTexture;

	int m_PlayerPosX = -1;
	int m_PlayerPosY = -1;
	int m_PlayerSize = 256;

	int			m_XChipCount = 200;					//�}�b�v���`�b�v��
	int			m_YChipCount = 25;						//�}�b�v�c�`�b�v��
	int			m_LayerCount = 25;

	int			m_XChipSize = 32;						//�`�b�v�T�C�Y
	int			m_YChipSize = 32;						//�`�b�v�T�C�Y

	int			m_XChipEditorSize = 32;						//�`�b�v�T�C�Y
	int			m_YChipEditorSize = 32;						//�`�b�v�T�C�Y

	int						m_Wait;

	float					m_ScrollX;
	float					m_ScrollY;

	int* m_pChipData = NULL;
	int* m_pObjectData = NULL;
	int* m_pEnemyData = NULL;
	int* m_pItemData = NULL;
	int	m_ObjectCount;
	int	m_EnemyCount;
	int	m_ItemCount;

	std::vector<CTexture*> m_ObjectTextureArray;			// �I�u�W�F�N�g�摜�z�u
	std::vector<CTexture*> m_EnemyTextureArray;				// �G�摜�z�u
	std::vector<CTexture*> m_ItemTextureArray;				// �A�C�e���摜�z�u

	int m_ObjectTextureCount;
	int m_EnemyTextureCount;
	int m_ItemTextureCount;

	void ReleaseMapData();

	bool CollisionHorizontal(CRectangle objectRec, CRectangle charaCurRec, CRectangle charaBackRec, float& oy);
	bool CollisionVertical(CRectangle objectRec, CRectangle charaCurRec, CRectangle charaBackRec, float& ox);
	bool CollisionLine(Line line1, Line line2);
public:
	CStage();
	~CStage();
	bool Load(int path);
	void Initialize();
	void Update();
	void Render(CCamera* _camera);
	void RenderDebug(CCamera* _camera);
	void Release();
	float GetScrollX() { return m_ScrollX; }
	float GetScrollY() { return m_ScrollY; }
	Vector2 GetScroll() { return Vector2(m_ScrollX, m_ScrollY); }
	Vector2 GetPlayerPos() { return Vector2(m_PlayerPosX * m_XChipEditorSize, m_PlayerPosY * m_YChipEditorSize); }
	bool Collision(CRectangle charaCurRec, CRectangle charaBackRec, float& ox, float& oy);
	CRectangle GetStageRect(int cn, int x, int y, Vector2 scroll = Vector2(0, 0)) {
		switch (cn + 1)
		{
		case 0:
		default:
			return CRectangle(x * m_XChipSize - scroll.x, y * m_YChipSize - scroll.y, x * m_XChipSize + m_XChipSize - scroll.x, y * m_YChipSize + m_YChipSize - scroll.y);
			break;
		}
	}
	int GetEnemyCount(void) { return m_EnemyCount; }
	int GetItemCount() { return m_ItemCount; }
};


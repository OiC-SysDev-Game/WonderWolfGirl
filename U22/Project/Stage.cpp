#define _CRT_SECURE_NO_WARNINGS

#include "Stage.h"
#include <string.h>

CStage::CStage(){
}

CStage::~CStage()
{};

bool CStage::Load(int path) {
	//ファイルパス
	char Filepass[40] = "Image/Game/";
	char NameAddFilepass[120] = "";
	strcpy(NameAddFilepass, Filepass);
	strcat(NameAddFilepass, "Stage1.txt");
	//テキストファイルを開く
	FILE* fp;
	fopen_s(&fp, NameAddFilepass, "rt");
	if (fp == NULL)
	{
		return false;
	}

	//ファイルの全容量を調べる
	fseek(fp, 0, SEEK_END);
	long fSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	//ファイルサイズ分だけのメモリを確保する
	char* pBuffer = (char*)malloc(fSize + 1);
	//ファイルを全てバッファに読み込む
	fSize = fread(pBuffer, 1, fSize, fp);
	pBuffer[fSize] = '\0';
	char* pstr;

	//古いデータを破棄
	//ReleaseMapData();

	//テクスチャの読み込み
	pstr = strtok(pBuffer, ",");
	strcpy(NameAddFilepass, Filepass);
	strcat(NameAddFilepass, pstr);
	m_BackTexture.Load(NameAddFilepass);
	pstr = strtok(NULL, ",");
	strcpy(NameAddFilepass, Filepass);
	strcat(NameAddFilepass, pstr);
	m_ChipTexture.Load(NameAddFilepass);

	//プレイヤー初期位置
	pstr = strtok(NULL, ",");
	m_PlayerPosX = atoi(pstr);
	pstr = strtok(NULL, ",");
	m_PlayerPosY = atoi(pstr);
	pstr = strtok(NULL, ",");
	m_PlayerSize = atoi(pstr);

	//チップサイズ
	pstr = strtok(NULL, ",");
	m_XChipSize = atoi(pstr);
	pstr = strtok(NULL, ",");
	m_YChipSize = atoi(pstr);
	pstr = strtok(NULL, ",");
	m_XChipEditorSize = atoi(pstr);
	pstr = strtok(NULL, ",");
	m_YChipEditorSize = atoi(pstr);

	//マップチップ数
	pstr = strtok(NULL, ",");
	m_XChipCount = atoi(pstr);
	pstr = strtok(NULL, ",");
	m_YChipCount = atoi(pstr);
	pstr = strtok(NULL, ",");
	m_LayerCount = atoi(pstr);

	//マップのチップ数総数 (列数*行数)
	int totalChips = m_XChipCount * m_YChipCount * m_LayerCount;

	//マップチップメモリ確保
	m_pChipData = (int*)malloc(sizeof(int) * totalChips);
	m_pObjectData = (int*)malloc(sizeof(int) * totalChips);
	m_pEnemyData = (int*)malloc(sizeof(int) * totalChips);
	m_pItemData = (int*)malloc(sizeof(int) * totalChips);

	//チップデータの読み込み
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

	
	//オブジェクトのテクスチャ読み込み
	pstr = strtok(NULL, ",");
	m_ObjectTextureCount = atoi(pstr);
	for (int i = 0; i < m_ObjectTextureCount; i++)
	{
		pstr = strtok(NULL, ",");
		//一時読み込みテクスチャ
		CTexture* tmp = new CTexture();
		//選んだファイルを開く
		if (!tmp->Load(pstr))
		{
			return false;
		}
		//テクスチャを配列に追加する
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

	//敵配置情報
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

	//アイテム配置情報
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

	//ファイルを閉じる
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
	//遠景の描画
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

	// テクスチャの横幅からマップチップの縦オフセットを求める
	int tcx = m_ChipTexture.GetWidth() / m_XChipSize;
	// マップチップの描画
	for (int y = 0; y < m_YChipCount; y++)
	{
		for (int x = 0; x < m_XChipCount; x++)
		{
			// 描画するチップ番号
			// チップ番号0は描画しない
			char cn = m_pChipData[y * m_XChipCount + x] - 1;
			if (cn < 0 || cn == 16)
			{
				continue;
			}
			// マップチップの矩形
			CRectangle cr(m_XChipSize * (cn % tcx), m_YChipSize * (cn / tcx), m_XChipSize * (cn % tcx + 1), m_YChipSize * (cn / tcx + 1));
			// マップチップの描画
			Vector2 posMC = Vector2(-m_ScrollX + x * m_XChipSize, -m_ScrollY + y * m_YChipSize);
			m_ChipTexture.Render(posMC, cr, *_camera);
		}
	}
	
	//X,Y軸のスクロール値格納
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
			// 描画するチップ番号
			// チップ番号0は描画しない
			char cn = m_pChipData[y * m_XChipCount + x] - 1;
			if (cn < 0)
			{
				continue;
			}
			// マップチップの矩形
			CRectangle cr = GetStageRect(cn, x, y, GetScroll());
			// マップチップの描画
			GraphicsUtilities::RenderLineRectangle(cr, Vector4(0, 0, 0, 1), *_camera);
		}
	}
}

void CStage::Release() {
	ReleaseMapData();
}

void CStage::ReleaseMapData() {
	// 確保したデータの解放
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

	//当たり判定する矩形の左上と右下のチップ位置を求める
	int lc = C_CurRec.left / m_XChipSize;
	int rc = C_CurRec.right / m_XChipSize;
	int tc = C_CurRec.top / m_YChipSize;
	int bc = C_CurRec.bottom / m_YChipSize;
	//ステージの範囲外にはならないようにする
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

	//キャラクターの現在地X座標がマイナス値であるとき、0に戻す
	if (C_CurRec.left <= 0)
	{
		float ox = -C_CurRec.left;
		wolf.CollisionObject(ox, 0);
	}
	//キャラクターの現在地X座標がマップ範囲外であるとき、最大X座標値に戻す
	else if (C_CurRec.right >= m_XChipCount * m_XChipSize)
	{
		float ox = m_XChipCount * m_XChipSize - C_CurRec.right;
		wolf.CollisionObject(ox, 0);
	}

	//プレイヤーの位置を調整
	C_CurRec = wolf.GetRect();

	//X軸、Y軸の移動量の絶対値を計算
	float xmove = abs(C_CurRec.left - C_BackRec.left);
	float ymove = abs(C_CurRec.top - C_BackRec.top);

	//当たり判定をする矩形の左上から右下の範囲のみ当たり判定をおこなう
	//それ以外の番号は当たることはないので判定が必要ない
	for (int y = tc; y <= bc; y++)
	{
		for (int x = lc; x <= rc; x++)
		{
			//描画するチップ番号
			//チップ番号０は当たり判定しない
			char cn = m_pChipData[y * m_XChipCount + x] - 1;
			if (cn + 1 == 0) { continue; }

			//ステージの短径
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
	//キャラの現在地の短径
	CRectangle CurRec = charaCurRec;
	//キャラの1フレーム前の位置の短径
	CRectangle BackRec = charaBackRec;
	//接触するステージオブジェクトの短径
	CRectangle ObjRec = objectRec;

	Line lineStage;
	Line linePlayer_Right;
	Line linePlayer_Left;
	//下方向に移動時
	if (CurRec.top >= BackRec.top)
	{
		//当たり判定用のキャラクタ矩形
		//下で範囲を限定した専用の矩形を作成する。
		CRectangle CBotRec = CurRec;
		CBotRec.top = CBotRec.bottom;	//矩形は上側を下と同じ値にする
		CBotRec.left += 6;				//横の範囲を少し狭める
		CBotRec.right -= 6;

		CRectangle BBotRec = BackRec;
		BBotRec.top = BBotRec.bottom;	//矩形は上側を下と同じ値にする
		BBotRec.left += 6;			//横の範囲を少し狭める
		BBotRec.right -= 6;
		//キャラクターの下と当たり判定
		//オブジェクトと重なっている場合
		if (ObjRec.CollisionRectangle(CBotRec))
		{
			//下の埋まりなのでチップの上端から矩形の下端の値を引いた値が埋まりの値になる
			oy = ObjRec.top - CurRec.bottom;
			return true;
		}

		//オブジェクトを通り過ぎている場合
		//オブジェクトの上部分の当たり判定
		lineStage.StartPos = Vector2(ObjRec.left, ObjRec.top);
		lineStage.EndPos = Vector2(ObjRec.right, ObjRec.top);
		//キャラクター右下の当たり判定
		linePlayer_Right.StartPos = Vector2(CBotRec.right, CBotRec.bottom);
		linePlayer_Right.EndPos = Vector2(BBotRec.right, BBotRec.bottom);
		//キャラクター左下の当たり判定
		linePlayer_Left.StartPos = Vector2(CBotRec.left, CBotRec.bottom);
		linePlayer_Left.EndPos = Vector2(BBotRec.left, BBotRec.bottom);
		if (CollisionLine(lineStage, linePlayer_Right) ||
			CollisionLine(lineStage, linePlayer_Left))
		{
			oy = ObjRec.top - CurRec.bottom;
			return true;
		}
	}
	//上方向に移動時
	else
	{
		//当たり判定用のキャラクタ矩形
		//上で範囲を限定した専用の矩形を作成する。
		CRectangle CTopRec = CurRec;
		CTopRec.bottom = CTopRec.top;	//矩形は下側を上と同じ値にする
		CTopRec.left += 6;				//横の範囲を少し狭める
		CTopRec.right -= 6;

		CRectangle BTopRec = BackRec;
		BTopRec.bottom = BTopRec.top;	//矩形は下側を上と同じ値にする
		BTopRec.left += 6;				//横の範囲を少し狭める
		BTopRec.right -= 6;
		//キャラクターの上と当たり判定
		//オブジェクトと重なっている場合
		if (ObjRec.CollisionRectangle(CTopRec))
		{
			//上の埋まりなのでチップの下端から矩形の上端の値を引いた値が埋まりの値になる
			oy = ObjRec.bottom - CurRec.top;
			return true;
		}

		//オブジェクトを通り過ぎている場合
		//オブジェクトの下部分の当たり判定
		lineStage.StartPos = Vector2(ObjRec.left, ObjRec.bottom);
		lineStage.EndPos = Vector2(ObjRec.right, ObjRec.bottom);
		//キャラクター右上の当たり判定
		linePlayer_Right.StartPos = Vector2(CTopRec.right, CTopRec.top);
		linePlayer_Right.EndPos = Vector2(BTopRec.right, BTopRec.top);
		//キャラクター左上の当たり判定
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
	//キャラの現在地の短径
	CRectangle CurRec = charaCurRec;
	//キャラの1フレーム前の位置の短径
	CRectangle BackRec = charaBackRec;
	//接触するステージオブジェクトの短径
	CRectangle ObjRec = objectRec;

	Line lineStage;
	Line linePlayer_Top;
	Line linePlayer_Bottom;

	//左方向に移動時
	if (CurRec.left <= BackRec.left)
	{
		//当たり判定用のキャラクタ矩形
		//左で範囲を限定した専用の矩形を作成する。
		CRectangle CLeftRec = CurRec;
		CLeftRec.right = CLeftRec.left;	//矩形は右側を左と同じ値にする
		CLeftRec.bottom -= 6;			//縦の範囲を少し狭める
		CLeftRec.top += 6;

		CRectangle BLeftRec = BackRec;
		BLeftRec.right = BLeftRec.left;	//矩形は右側を左と同じ値にする
		BLeftRec.bottom -= 6;			//縦の範囲を少し狭める
		BLeftRec.top += 6;

		//キャラクターの左と当たり判定
		//オブジェクトと重なっている場合
		if (ObjRec.CollisionRectangle(CLeftRec))
		{
			//左の埋まりなのでチップの右端から矩形の左端の値を引いた値が埋まりの値になる
			ox = ObjRec.right - CurRec.left;
			return true;
		}

		//オブジェクトを通り過ぎている場合
		//オブジェクトの右部分の当たり判定
		lineStage.StartPos = Vector2(ObjRec.right, ObjRec.top);
		lineStage.EndPos = Vector2(ObjRec.right, ObjRec.bottom);
		//キャラクター左上の当たり判定
		linePlayer_Top.StartPos = Vector2(CLeftRec.left, CLeftRec.top);
		linePlayer_Top.EndPos = Vector2(BLeftRec.left, BLeftRec.top);
		//キャラクター左下の当たり判定
		linePlayer_Bottom.StartPos = Vector2(CLeftRec.left, CLeftRec.bottom);
		linePlayer_Bottom.EndPos = Vector2(BLeftRec.left, BLeftRec.bottom);
		if (CollisionLine(lineStage, linePlayer_Top) ||
			CollisionLine(lineStage, linePlayer_Bottom))
		{
			ox = ObjRec.right - CurRec.left;
			return true;
		}
	}
	//右方向に移動時
	else
	{
		//当たり判定用のキャラクタ矩形
		//右で範囲を限定した専用の矩形を作成する。
		CRectangle CRightRec = CurRec;
		CRightRec.left = CRightRec.right;	//矩形は左側を右と同じ値にする
		CRightRec.bottom -= 6;			//縦の範囲を少し狭める
		CRightRec.top += 6;

		CRectangle BRightRec = BackRec;
		BRightRec.left = BRightRec.right;	//矩形は左側を右と同じ値にする
		BRightRec.bottom -= 6;			//縦の範囲を少し狭める
		BRightRec.top += 6;

		//キャラクターの右と当たり判定
		//オブジェクトと重なっている場合
		if (ObjRec.CollisionRectangle(CRightRec))
		{
			//右の埋まりなのでチップの左端から矩形の右端の値を引いた値が埋まりの値になる
			ox = ObjRec.left - CurRec.right;
			return true;
		}

		//オブジェクトを通り過ぎている場合
		//オブジェクトの左部分の当たり判定
		lineStage.StartPos = Vector2(ObjRec.left, ObjRec.top);
		lineStage.EndPos = Vector2(ObjRec.left, ObjRec.bottom);
		//キャラクター右上の当たり判定
		linePlayer_Top.StartPos = Vector2(CRightRec.right, CRightRec.top);
		linePlayer_Top.EndPos = Vector2(BRightRec.right, BRightRec.top);
		//キャラクター右下の当たり判定
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

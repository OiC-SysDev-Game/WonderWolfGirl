#pragma once
#include "U22.h"

class CSceneBase
{
protected:
	bool			bEnd;
	bool			bDebug;
	int				NextScene;
	int				m_StageNo;

public:
	CSceneBase() :
		bEnd(false),
		bDebug(false),
		NextScene(0),
		m_StageNo(0){
	}
	virtual ~CSceneBase() {};
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Render(CCamera* _camera) = 0;
	virtual void RenderDebug(CCamera* _camera) = 0;
	virtual void Release() = 0;
	int GetNextScene() { return NextScene; }
	bool IsEnd() { return bEnd; }
	int GetNo() { return m_StageNo; }
	void SetNo(int no) { m_StageNo = no; }
};


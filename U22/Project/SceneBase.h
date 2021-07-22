#pragma once
#include "U22.h"

class CSceneBase
{
protected:
	bool			bEnd;
	bool			bDebug;
	int				BeforeScene;
	int				NextScene;
	int				m_StageNo;

	virtual void FeedIn() = 0;
	virtual bool FeedInEndCheck() = 0;
	virtual void FeedOut() = 0;
	virtual bool FeedOutEndCheck() = 0;

public:
	CSceneBase() :
		bEnd(false),
		bDebug(false),
		BeforeScene(0),
		NextScene(0),
		m_StageNo(0){
	}
	virtual ~CSceneBase() {};
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Render(CCamera* _camera) = 0;
	virtual void RenderDebug(CCamera* _camera) = 0;
	virtual void Release() = 0;
	int GetBeforeScene() { return BeforeScene; }
	void SetBeforeScene(int bs) { BeforeScene = bs; }
	int GetNextScene() { return NextScene; }
	bool IsEnd() { return bEnd; }
	int GetNo() { return m_StageNo; }
	void SetNo(int no) { m_StageNo = no; }
	float MaxOrMinAdjust(float value, float IorDvalue, float max, float min) {
		value += IorDvalue;
		if (value > max)
			value = max;
		if (value < min)
			value = min;

		return value;
	}
};


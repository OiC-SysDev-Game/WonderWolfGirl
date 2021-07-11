#pragma once
#include "U22.h"
class CStageObject
{
private:
public:
	CStageObject();
	~CStageObject();
	bool Load();
	void Initialize();
	void Update();
	void Render(CCamera* _camera);
	void RenderDebug(CCamera* _camera);
	void Release();
};


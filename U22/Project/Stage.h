#pragma once
#include "U22.h"
class CStage
{
private:
public:
	CStage();
	~CStage();
	bool Load();
	void Initialize();
	void Update();
	void Render(CCamera* _camera);
	void RenderDebug(CCamera* _camera);
	void Release();
};

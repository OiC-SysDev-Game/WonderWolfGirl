#pragma once
#include "U22.h"
class CWolf
{
private:
public:
	CWolf();
	~CWolf();
	bool Load();
	void Initialize();
	void Update();
	void Render(CCamera* _camera);
	void RenderDebug(CCamera* _camera);
	void Release();
};


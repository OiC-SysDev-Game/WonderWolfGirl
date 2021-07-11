#pragma once
#include "U22.h"
class CGirl
{
private:
public:
	CGirl();
	~CGirl();
	bool Load();
	void Initialize();
	void Update();
	void Render(CCamera* _camera);
	void RenderDebug(CCamera* _camera);
	void Release();
};


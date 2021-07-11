#pragma once
#include "U22.h"
class CEnemy
{
private:
public:
	CEnemy();
	~CEnemy();
	bool Load();
	void Initialize();
	void Update();
	void Render(CCamera* _camera);
	void RenderDebug(CCamera* _camera);
	void Release();
};


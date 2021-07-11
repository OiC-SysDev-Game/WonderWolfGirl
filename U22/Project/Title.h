#pragma once
#include "SceneBase.h"

class CTitle : public CSceneBase
{
private:
public:
	CTitle();
	~CTitle();
	bool Load();
	void Initialize();
	void Update();
	void Render(CCamera* _camera);
	void RenderDebug(CCamera* _camera);
	void Release();
};


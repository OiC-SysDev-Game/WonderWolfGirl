#pragma once
#include "SceneBase.h" 
class CGame : public CSceneBase
{
private:
	u22::graphics::Camera _camera;
public:
	CGame();
	~CGame();
	bool Load();
	void Initialize();
	void Update();
	void Render(CCamera* _camera);
	void RenderDebug(CCamera* _camera);
	void Release();
};


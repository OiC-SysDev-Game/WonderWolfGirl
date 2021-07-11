#pragma once
#include "SceneBase.h" 
class CStageSelect : public CSceneBase
{
private:
public:
	CStageSelect();
	~CStageSelect();
	bool Load();
	void Initialize();
	void Update();
	void Render(CCamera* _camera);
	void RenderDebug(CCamera* _camera);
	void Release();
};


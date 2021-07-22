#pragma once
#include "SceneBase.h" 
class CGame : public CSceneBase
{
private:

protected:
	void FeedIn();
	bool FeedInEndCheck();
	void FeedOut();
	bool FeedOutEndCheck();

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


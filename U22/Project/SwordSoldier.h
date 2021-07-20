#pragma once
#include "U22.h"
#include "Enemy.h"

class CSwordSoldier : public CEnemy
{
private:
	bool isMove = false;
	float height = 240;
	float width = 130;

	float search_Range = 300;
	float invicible_Time = 1;
	float attack_Rate = 3;

public:
	bool Load();
	void Initialize();
	void Update();
	void Render(CCamera* _camera);
	void RenderDebug(CCamera* _camera);
	void Release();

void Acceleration(void);
void Neutral(void);
void Move(void);
void Attack(void);

};
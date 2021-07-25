#include "Enemy.h"

CEnemy::CEnemy() {
}

CEnemy::~CEnemy()
{};

bool CEnemy::Load() {
	return true;
}

void CEnemy::Initialize() {
}

void CEnemy::Update() {
}

void CEnemy::Render(CCamera* _camera) {
}

void CEnemy::RenderDebug(CCamera* _camera) {
}

void CEnemy::Release() {
}

bool CEnemy::TakeDamage() {
	health--;
	return health > 0;
}
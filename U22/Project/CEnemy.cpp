#include "Enemy.h"

void CEnemy::RenderDebug(CCamera* _camera) {

}

bool CEnemy::TakeDamage() {
	health--;
	return health > 0;
}

#include "Stage.h"

CStage::CStage(){
}

CStage::~CStage()
{};

bool CStage::Load() {
	return true;
}

void CStage::Initialize() {
}

void CStage::Update() {
}

void CStage::Render(CCamera* _camera) {
}

void CStage::RenderDebug(CCamera* _camera) {
}

void CStage::Release() {
}
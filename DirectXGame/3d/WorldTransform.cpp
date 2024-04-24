#include "WorldTransform.h"
#include "MyFunc.h"

void WorldTransform::UpdateMatrix() { 
	matWorld_ = AffineMatrix(scale_, rotation_, translation_); 
	TransferMatrix();
}
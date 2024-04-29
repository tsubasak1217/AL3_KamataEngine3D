#include "WorldTransform.h"
#include "MyFunc.h"

void WorldTransform::UpdateMatrix() { 
	matWorld_ = AffineMatrix(scale_, rotation_, translation_); 

	if(parent_){
		matWorld_ = Multiply(matWorld_, parent_->matWorld_);
	}

	TransferMatrix();
}
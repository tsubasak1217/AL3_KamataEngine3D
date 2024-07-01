#include "Camera.h"
#include "MyFunc.h"

Camera::Camera()
{
	wt_.Initialize();
	vp_.Initialize();
	UpdateCamera();
}

Camera::~Camera()
{
}

void Camera::UpdateCamera()
{
	wt_.UpdateMatrix();
	vp_.matView = InverseMatrix(wt_.matWorld_);
	vp_.TransferMatrix();
}

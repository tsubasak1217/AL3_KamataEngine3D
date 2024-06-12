#include "Object.h"

Object::Object() {}

Object::~Object() {
	delete model_;
	model_ = nullptr;
}

void Object::Init() {}

void Object::Update() {}

void Object::Draw() {}

void Object::Fin() {}

void Object::OnCollision(){}

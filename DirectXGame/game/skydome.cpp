#include "skydome.h"
#include "ViewProjection.h"

Skydome::Skydome(){
	Init();
}

Skydome::~Skydome(){
	Fin();
}

void Skydome::Init(){
	wt_.Initialize();
	wt_.scale_ = { 100.0f,100.0f,100.0f };
	wt_.rotation_ = { 0.0f,0.0f,0.0f };
	wt_.translation_ = { 0.0f,0.0f,0.0f };
	wt_.UpdateMatrix();
	model_.reset(Model::CreateFromOBJ("skydome_fukushima", true));
}

void Skydome::Update(){
	wt_.UpdateMatrix();
}

void Skydome::Draw(const ViewProjection& vp){
	model_->Draw(wt_, vp);
}

void Skydome::Fin(){
	model_.reset();
}

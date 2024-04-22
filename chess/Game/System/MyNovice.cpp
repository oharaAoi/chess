#include "MyNovice.h"

InputManager* MyNovice::input_ = new InputManager();
Camera* MyNovice::camera_ = new Camera();

MyNovice::~MyNovice() {
	delete input_;
	delete camera_;
}

void MyNovice::Updata(){
	input_->Update();
	camera_->Update();
}

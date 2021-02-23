#include "Controller/Controller.h"

#include "GameObject.h"

Controller::Controller() {

}

Controller::~Controller() {

}

void Controller::OnDestory() {
	this->~Controller();
}

void Controller::Start() {
	pawn = gameObject->transform;
}

float Controller::GetMovementSpeed() const {
	return movement_speed;
}

void Controller::SetMovementSpeed(float speed) {
	movement_speed = speed;
}
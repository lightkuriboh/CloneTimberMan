#include "Character.h"


void Character::setSideCharacter(Side _side) {
	this->side = _side;
	if (this->side == Side::Right) {
		this->setScaleX(-1.0f);
	}
	else {
		this->setScaleX(+1.0f);
	}
}

Side Character::getSideCharacter() {
	return this->side;
}

bool Character::init() {
	if (!Node::init()) {
		return false;
	}
	this->side = Side::Left;
	this->timeline = cocos2d::CSLoader::createTimeline("Character.csb");
	this->timeline->retain();

	return true;
}

void Character::onExit() {
	this->timeline->release();
	Node::onExit();
}

void Character::runChopAnimation() {
	this->stopAllActions();
	this->runAction(this->timeline);
	timeline->play("chop", false);
}


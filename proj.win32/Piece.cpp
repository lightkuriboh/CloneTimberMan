#include "Piece.h"
using namespace cocos2d;

float Piece::getSpriteHeight() {
	return this->getChildByName<Sprite*>("roll")->getContentSize().height;
}

float Piece::getSpriteWidth() {
	return this->getChildByName<Sprite*>("roll")->getContentSize().width;
}

Side Piece::getStickSide() {
	return this->stickSide;
}

void Piece::setStickSide(Side _side) {
	this->stickSide = _side;

	auto roll = this->getChildByName<Sprite*>("roll");
	auto rightStick = roll->getChildByName<Sprite*>("rightStick");
	auto leftStick = roll->getChildByName<Sprite*>("leftStick");

	switch (this->stickSide) {
		case Side::Right:
			rightStick->setVisible(true);
			leftStick->setVisible(false);
			break;
		case Side::Left:
			leftStick->setVisible(true);
			rightStick->setVisible(false);
			break;
		case Side::None:
			leftStick->setVisible(false);
			rightStick->setVisible(false);
	}
}
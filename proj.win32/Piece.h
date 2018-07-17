#pragma once
#include "cocos2d.h"
#include "Constants.h"

class Piece : public cocos2d::Node {
	public:
		CREATE_FUNC(Piece);
		float getSpriteHeight();
		float getSpriteWidth();
		void setStickSide(Side side);
		Side getStickSide();
	protected:
		Side stickSide;		
};


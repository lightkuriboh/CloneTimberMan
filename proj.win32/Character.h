#pragma once
#ifndef __SushiNeko__Character__
#define __SushiNeko__Character__

#include "cocos2d.h"
#include "Constants.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"


class Character : public cocos2d::Node {
	public:
		CREATE_FUNC(Character);
		void setSideCharacter(Side _side);
		Side getSideCharacter();
		void runChopAnimation();
	protected:
		Side side;
		bool init() override;
		void onExit() override;		
		cocostudio::timeline::ActionTimeline* timeline;
		
};

#endif
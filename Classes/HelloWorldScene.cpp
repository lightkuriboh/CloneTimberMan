#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>

USING_NS_CC;

using namespace cocos2d;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    /**  you can create scene with following comment code instead of using csb file.
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    **/
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	CSLoader* instance = CSLoader::getInstance();
	instance->registReaderObject("CharacterReader", (ObjectFactory::Instance) CharacterReader::getInstance);
	instance->registReaderObject("PieceReader", (ObjectFactory::Instance) PieceReader::getInstance);
    
    auto rootNode = CSLoader::createNode("MainScene.csb");
	Size size = Director::getInstance()->getVisibleSize();
	rootNode->setContentSize(size);
	ui::Helper::doLayout(rootNode);

	this->pieceNode = rootNode->getChildByName("pieceNode");
	this->character = rootNode->getChildByName<Character*>("character");
	this->scoreLabel = rootNode->getChildByName<cocos2d::ui::Text*>("scoreLabel");
	auto lifeBG = rootNode->getChildByName<Sprite*>("lifeBG");
	this->timeBar = lifeBG->getChildByName<Sprite*>("lifeBar");	
	this->timeLeft = 5.0f;
		
	createPieceNode();

	//rootNode->addChild(this->pieceNode);
    addChild(rootNode);		

    return true;
}


void HelloWorld::setStickSide(const int first, Piece* piece) {

	int lr = rand() % 20;

	if (first == 0) {
		piece->setStickSide(Side::None);
	}
	if (lr < 6 && this->lastSide != Side::Right) {
		piece->setStickSide(Side::Left);
		this->lastSide = Side::Left;
	} else
		if (lr < 12 && this->lastSide != Side::Left) {
			piece->setStickSide(Side::Right);
			this->lastSide = Side::Right;
		}
		else {
			piece->setStickSide(Side::None);
			this->lastSide = Side::None;
		}			

}

void HelloWorld::createPieceNode() {	

	srand(time(NULL));

	this->currentIndex = 0;
	this->lastSide = Side::Right;
	this->setScore(0);

	for (int i = 0; i < (this->maxPiece); i++) {
		Piece* piece = dynamic_cast<Piece*>(CSLoader::createNode("Piece.csb"));		
		float rollHeight = piece->getSpriteHeight();
		piece->setPosition(Vec2(0.0f, float(i) * rollHeight / 2.0f));

		this->pieceNode->addChild(piece);

		this->setStickSide(i, piece);

		pieces.pushBack(piece);
	}
	
}

void HelloWorld::onEnter() {
	Layer::onEnter();
	
	this->triggerTitle();
	
	
	setupTouchHandling();
	setupKeyPress();

	this->flyingPiecePosition = this->pieceNode->getPosition();

	this->scheduleUpdate();

}

void HelloWorld::setupKeyPress() {
	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event* event) {
		switch (this->gameState) {
			case GameState::Ready: {
				this->startPlaying();
			}
			case GameState::Playing: {

				if (int(keyCode) == 26) {
					this->character->setSideCharacter(Side::Left);
				}
				else if (int(keyCode) == 27) {
					this->character->setSideCharacter(Side::Right);
				}

				if (this->gameOver()) {
					this->triggerGameOver();
					return true;
				}

				this->character->runChopAnimation();

				this->step();

				if (this->gameOver()) {
					this->triggerGameOver();
					return true;
				}



				this->increaseScore();

				break;
			}
			case GameState::Over: {
				this->resetGame();
				this->triggerReady();
				break;
			}
			case GameState::Title: {
				this->triggerReady();
				break;
			}
		}

		return true;
	};
	keyListener->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event* event) {
		return true;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, this);
}

void HelloWorld::setupTouchHandling() {	

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = [&](Touch* touch, Event* event) {
		switch (this->gameState) {
			case GameState::Ready: {
				this->startPlaying();
			}
			case GameState::Playing: {

				Vec2 touchLocation = this->convertTouchToNodeSpace(touch);

				if (touchLocation.x < this->getContentSize().width / 2.0f) {
					this->character->setSideCharacter(Side::Left);
				}
				else {
					this->character->setSideCharacter(Side::Right);
				}

				if (this->gameOver()) {
					this->triggerGameOver();
					return true;
				}

				this->character->runChopAnimation();

				this->step();

				if (this->gameOver()) {
					this->triggerGameOver();
					return true;
				}

				

				this->increaseScore();

				break;
			}
			case GameState::Over: {
				this->resetGame();
				this->triggerReady();
				break;
			}
			case GameState::Title: {
				this->triggerReady();
				break;
			}
		} 

		return true;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void HelloWorld::step() {
	Piece* currentPiece = this->pieces.at(this->currentIndex);

	this->animateHitPiece(currentPiece->getStickSide());

	currentPiece->setPosition(currentPiece->getPosition() + 
								Vec2(0.0f, float(this->maxPiece) * currentPiece->getSpriteHeight() / 2.0f));


	currentPiece->setLocalZOrder(currentPiece->getLocalZOrder() + 1);

	this->setStickSide(1, currentPiece);

	//this->pieceNode->setPosition(this->pieceNode->getPosition() + 
		//Vec2(0.0f, -1.0f * currentPiece->getSpriteHeight() / 2.0f));

	cocos2d::MoveBy* moveBy = cocos2d::MoveBy::create(0.5f, 
														Vec2(0.0f, -1.0f * currentPiece->getSpriteHeight() / 2.0f));
	this->pieceNode->runAction(moveBy);

	this->currentIndex = (this->currentIndex + 1) % (this->maxPiece);
}

bool HelloWorld::gameOver() {
	Piece* piece = this->pieces.at(this->currentIndex);
	if (piece->getStickSide() == this->character->getSideCharacter()) {
		return true;
	}
	return false;
}

void HelloWorld::triggerGameOver() {
	this->gameState = GameState::Over;

	auto scene = this->getChildByName("Scene");
	auto mat = scene->getChildByName<Sprite*>("mat");

	cocos2d::ui::Text* score = mat->getChildByName<cocos2d::ui::Text*>("finalScore");
	cocos2d::ui::Text* highestScore = mat->getChildByName<cocos2d::ui::Text*>("highestScore");

	cocostudio::timeline::ActionTimeline* overTimeLife = CSLoader::createTimeline("MainScene.csb");

	this->stopAllActions();
	this->runAction(overTimeLife);
	
	if (this->achievedBetterScore()) {
		overTimeLife->play("highScore", false);
	}
	else {
		overTimeLife->play("gameOver", false);
	}
	

	this->updateHighScore();

	score->setString(std::to_string(this->score));
	highestScore->setString(std::to_string(this->getHighScore()));

}

bool HelloWorld::achievedBetterScore() {
	return this->score > this->getHighScore();
}

int HelloWorld::getHighScore() {
	const char* KEY_HIGH_SCORE = "score";
	return UserDefault::getInstance()->getIntegerForKey(KEY_HIGH_SCORE);
}

void HelloWorld::setHighScore(int _score) {
	const char* KEY_HIGH_SCORE = "score";
	UserDefault::getInstance()->setIntegerForKey(KEY_HIGH_SCORE, _score);
	UserDefault::getInstance()->flush();
}

void HelloWorld::updateHighScore() {

	if (this->achievedBetterScore()) {
		this->setHighScore(this->score);
	}
	
}

void HelloWorld::resetGame() {
	
	this->character->setSideCharacter(Side::Left);
	this->lastSide = Side::Right;
	this->setScore(0);
	this->timeLeft = 5.0f;
	for (int i = 0; i < this->maxPiece; i++) {
		this->setStickSide(i, pieces.at((this->currentIndex + i) % this->maxPiece));
	}
	
}

void HelloWorld::startPlaying() {
	
	this->gameState = GameState::Playing;

	this->visibleButton(false);

	auto scene = this->getChildByName("Scene");
	cocos2d::Sprite* tapLeft = scene->getChildByName<cocos2d::Sprite*>("tapLeft");
	cocos2d::Sprite* tapRight = scene->getChildByName<cocos2d::Sprite*>("tapRight");

	cocos2d::FadeOut* leftFade = cocos2d::FadeOut::create(0.35f);
	cocos2d::FadeOut* rightFade = cocos2d::FadeOut::create(0.35f);

	tapLeft->runAction(leftFade);
	tapRight->runAction(rightFade);	

}

void HelloWorld::setScore(int _score) {
	this->score = _score;
	this->scoreLabel->setString(std::to_string(this->score));
}

int HelloWorld::getScore() {
	return this->score;
}

void HelloWorld::increaseScore() {
	this->setScore(this->getScore() + 1);
	this->timeLeft += 1.0f / 6.0f;
}

void HelloWorld::setTimeLeft(float _timeLeft) {	
	this->timeLeft = clampf(_timeLeft, 0.0f, 10.0f);
	this->timeBar->setScaleX(this->timeLeft / 10.0f);
}

void HelloWorld::update(float dt) {
	Layer::update(dt);
	if (this->gameState == GameState::Playing) {
		this->setTimeLeft(this->timeLeft - dt);
		if (this->timeLeft <= 0.0f) {
			this->triggerGameOver();
		}
	}
}

void HelloWorld::triggerTitle() {
	this->gameState = GameState::Title;
	cocostudio::timeline::ActionTimeline* titleTimeLife = CSLoader::createTimeline("MainScene.csb");
	this->stopAllActions();
	this->runAction(titleTimeLife);
	titleTimeLife->play("title", false);
}

void HelloWorld::triggerReady() {
	this->gameState = GameState::Ready;
	cocostudio::timeline::ActionTimeline* readyTimeLife = CSLoader::createTimeline("MainScene.csb");
	this->stopAllActions();
	this->runAction(readyTimeLife);
	readyTimeLife->play("ready", false);
	this->visibleButton(true);
	
}

void HelloWorld::visibleButton(bool _visible) {
	auto scene = this->getChildByName("Scene");
	auto playButton = scene->getChildByName<cocos2d::ui::Button*>("play");
	playButton->setVisible(_visible);
}

void HelloWorld::animateHitPiece(Side obstacleSide) {

	Piece* flyingPiece = dynamic_cast<Piece*>(CSLoader::createNode("Piece.csb"));
	flyingPiece->setStickSide(obstacleSide);
	flyingPiece->setPosition(this->flyingPiecePosition);


	cocostudio::timeline::ActionTimeline* pieceTimeline = CSLoader::createTimeline("Piece.csb");

	this->addChild(flyingPiece);

	Side characterSide = this->character->getSideCharacter();

	
	std::string animationName = (characterSide == Side::Left) ? std::string("moveRight") : std::string("moveLeft");

	flyingPiece->stopAllActions();
	flyingPiece->runAction(pieceTimeline);
	
	pieceTimeline->play(animationName, false);

	pieceTimeline->setLastFrameCallFunc([this, &flyingPiece]() {
		this->removeChild(flyingPiece);
	});

}
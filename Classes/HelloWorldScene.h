#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "../proj.win32/CharacterReader.h"
#include "../proj.win32/Character.h"
#include "../proj.win32/PieceReader.h"
#include "../proj.win32/Piece.h"
#include "../proj.win32/Constants.h"

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
protected:
	int currentIndex;
	int score;
	float timeLeft;
	cocos2d::Sprite* timeBar;
	cocos2d::Node* pieceNode;
	cocos2d::Vector <Piece*> pieces;
	Character* character;
	Side lastSide;
	GameState gameState;
	cocos2d::ui::Text* scoreLabel;

	const int maxPiece = 10;

	void onEnter() override;
	void setupTouchHandling();
	void setupKeyPress();
	void createPieceNode();
	void setStickSide(const int first, Piece* piece);
	void step();
	bool gameOver();
	void triggerGameOver();
	void resetGame();
	void startPlaying();
	void setScore(int _score);
	int getScore();
	void increaseScore();
	void setTimeLeft(float _timeLeft);
	void update(float dt) override;
	void triggerTitle();
	void triggerReady();
	void visibleButton(bool _visible);
	cocos2d::Vec2 flyingPiecePosition;
	void animateHitPiece(Side obstacleSide);
	void updateHighScore();
	int getHighScore();
	void setHighScore(int _score);
	bool achievedBetterScore();
};

#endif // __HELLOWORLD_SCENE_H__

//
//  SelectLayer.h
//  NinjaDart
//
//  Created by 彭芮 on 2019/5/9.
//

#ifndef _GameLayer_H
#define _GameLayer_H

#include "cocos2d.h"
#include "../Box2DHelper/PhyObject.h"
#include <vector>
#include <list>
#include "Vector"
#include <math.h>
#include "GameSceneManager.h"

using namespace cocos2d;

#define SPEED 6
#define PI 3.141592

class GameLayer : public Layer
{
public:
	virtual bool init();
    
	void updateStreakPosition(float time);
	void step();
	void update(float time);
	void initLevelData();
	void init3DBoomerang();
    
    CREATE_FUNC(GameLayer);
    
	bool touchBegan(Touch *touch,Event *event);
	void touchEnded(Touch *touch, Event *event);
	void touchMoved(Touch *touch, Event *event);
	void touchCancelled(Touch *touch, Event *event);
	
    void createBoomerang();
	void initStartPopupWindow();
	void updateDelete();
	void initSpriteFrameCache();
	void initCageOpenAnimate(float x,float y);
	void deleteStreak();
	void initBody();
	void ninjaShootBoomerangAnimate();
	void addScore(int score,float xPosition,float yPosition);
	void delScoreSp();
	void weaponSpriteRunAction();
	void deleteWeapon();
	void deleteCageOpenSprite();
	void pauseMenuCallback(Object *pSender);
	void gameOver(float time);
	void evaluationStar();
	void addYanWuSound();
	void addMenuClickSound();
	void onMyKeyPressed(EventKeyboard::KeyCode keyCode,Event* event);
	void initExplodeAnimate(float x,float y);
	void deleteTntSprite();
	void drawLine(b2Vec2 v1,b2Vec2 v2,Sprite *sprite);
	void tntExplode(float xlocation,float ylocation);
    
public:
    b2World *world;
    std::string *ids;
    float *data;
    PhyObject *po;
    GameSceneManager *gsm;
    std::map<std::string,PhyObject*> pom;
    std::vector<std::string> listForDel;
    std::vector<std::string> listForExplodeDel;
    std::list<Sprite *> listForScoreSpriteDel;
    std::list<Sprite3D *> listForWeaponSpriteDel;
    std::list<Sprite *> listForCageOpenSpriteDel;
    std::list<Sprite *> listForTntSpriteDel;
    Sprite *eyeLineSprite;
    Sprite *crossHairSprite;
    Sprite *explodeAnimateSprite;
    Sprite *shootBoomerangSprite;
    Sprite *weaponSprite;
    SpriteFrameCache *gameSpriteCache;
    SpriteFrameCache *uiSpriteCache;
    LabelAtlas *scoreLabel;
    LabelAtlas *levelLabel;
    Vector<SpriteFrame*> frameVector;
    Point fromPoint;
    Point toPoint;µ„
    CCMotionStreak *streak;
    b2Rot r;
    b2Vec2 velocityDirection;
    int contactCount=0;
    int index;
    int Score=0;
    int totalScole=2;
    int weaponCount=3;
    int cageNumber=0;
    float xPosition=0;
    float xPosition2=1200;
    float lastXPosition;
    float rate=0;
    float XPOSITION;
    float YPOSITION;
    bool shootFlag=true;
    bool streakMoveFlag=false;
    bool flippedFlag=true;
    bool gameOverFlag=false;
    bool touchEndFlag=true;
    static bool WINFLAG;
};
#endif

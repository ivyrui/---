//
//  SelectLayer.h
//  NinjaDart
//
//  Created by 彭芮 on 2019/5/9.
//

#include "GameLayer.h"
#include "MainLayer.h"
#include "SelectLayer.h"
#include <string>
#include <algorithm>
#define  LOG_TAG    "main"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

using namespace std;
USING_NS_CC;

bool GameLayer::WINFLAG=false;

bool GameLayer::init()
{
	if(!Layer::init()){
		return false;
	}
	GameLayer::WINFLAG=false;
	auto listener=EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan=CC_CALLBACK_2(GameLayer::touchBegan,this);
	listener->onTouchMoved=CC_CALLBACK_2(GameLayer::touchMoved,this);
	listener->onTouchEnded=CC_CALLBACK_2(GameLayer::touchEnded,this);
	listener->onTouchCancelled=CC_CALLBACK_2(GameLayer::touchCancelled,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
	auto listener2 = EventListenerKeyboard::create();
	listener2->onKeyPressed = CC_CALLBACK_2(GameLayer::onMyKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, this);
	float gravityY = -9.8f / 6.0f;
	b2Vec2 gravity(0, gravityY);
	world = new b2World(gravity);
	world->SetAllowSleeping(true);
	world->SetContactListener(new MyContactListener(this));
    
	initSpriteFrameCache();
	initBody();
	initLevelData();
	init3DBoomerang();
	initStartPopupWindow();
	schedule(schedule_selector(GameLayer::update),0.001f);
	schedule(schedule_selector(GameLayer::updateStreakPosition),0.001f);
	schedule(schedule_selector(GameLayer::gameOver),2.0f);
	return true;
}
void GameLayer::initSpriteFrameCache()
{
    gameSpriteCache=SpriteFrameCache::getInstance();
	gameSpriteCache->addSpriteFramesWithFile("game_collage.plist", Director::getInstance()->getTextureCache()->addImage(
					"picture/game_collage.png"));
	uiSpriteCache=SpriteFrameCache::getInstance();
	uiSpriteCache->addSpriteFramesWithFile("picture/ui_collage_images.plist",
		Director::getInstance()->getTextureCache()->addImage(
					"picture/ui_collage_images.png"));
}
void GameLayer::initBody()
{
	auto size=Director::sharedDirector()->getVisibleSize();
	auto origin=Director::getInstance()->getVisibleOrigin();
	SpriteFrame *topWallFrame = gameSpriteCache->getSpriteFrameByName(
			"wall_top.png");
	Sprite *sprite = Sprite::createWithSpriteFrame(topWallFrame);
	sprite->setGlobalZOrder(-4);
	index ++;
	data = new float[4] { size.width / 2, size.height - 3, size.width / 2, 20 };
	ids = new std::string(StringUtils::format("%d", index));
	po = new RectPhyObject(ids, true, this, world, sprite, data, 0, 0.8, 0.2f);
	pom[*ids] = po;
	sprite = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("picture/bigdimian1.png"));
	sprite->setGlobalZOrder(-3);
	index ++;
	data = new float[4] { size.width / 2, sprite->getContentSize().height,
			size.width / 2, sprite->getContentSize().height };
	ids = new std::string(StringUtils::format("%d", index));
	po = new RectPhyObject(ids, true, this, world, sprite, data, 0, 0.8, 0.2f);
	pom[*ids] = po;
	SpriteFrame *lWall  gameSpriteCache->getSpriteFrameByName("wall_left.png");
	sprite = Sprite::createWithSpriteFrame(lWall);
	sprite->setGlobalZOrder(-2);
	index ++;
	data = new float[4] { 30, 360,90, 328 };
	ids = new std::string(StringUtils::format("%d", index));
	po = new RectPhyObject(ids, true, this, world, sprite, data, 0, 0.8, 0.2f);
	pom[*ids] = po;
	SpriteFrame *rWall = gameSpriteCache->getSpriteFrameByName("wall_right.png");
	sprite = Sprite::createWithSpriteFrame(rWall);
	sprite->setGlobalZOrder(-1);
	index ++;
	data = new float[4] { size.width - 38, 360,sprite->getContentSize().width, 328 };
	ids = new std::string(StringUtils::format("%d", index));
	po = new RectPhyObject(ids, true, this, world, sprite, data, 0, 0.8, 0.2f);
	pom[*ids] = po;
	sprite=Sprite::createWithSpriteFrame(gameSpriteCache->getSpriteFrameByName("game_bar.png"));
	sprite->setGlobalZOrder(-0.5f);
	sprite->setPosition(ccp(size.width/2,50));
	sprite->setScale(2.2f);
	this->addChild(sprite);
	sprite = Sprite::create("picture/Score.png");
	sprite->setPosition(ccp(size.width / 2 - 100, 50));
	this->addChild(sprite);
	sprite = Sprite::create("picture/Level.png");
	sprite->setPosition(ccp(size.width / 2 + 130, 50));
	this->addChild(sprite);
	scoreLabel=LabelAtlas::create("0","picture/Num.png",20,32,'0');
	scoreLabel->setPosition(ccp(size.width/2-60,35));
	this->addChild(scoreLabel);
	string levelStr=StringUtils::format("%d",(SelectLayer::CURRENT_LEVEL+1));
	levelLabel=LabelAtlas::create(levelStr,"picture/Num.png",20,32,'0');
	levelLabel->setPosition(ccp(size.width/2+170,35));
	this->addChild(levelLabel);
	Sprite *spriteItem1 = Sprite::createWithSpriteFrame(
			gameSpriteCache->getSpriteFrameByName("game_pause1.png"));
	Sprite *spriteItem2 = Sprite::createWithSpriteFrame(
			gameSpriteCache->getSpriteFrameByName("game_pause2.png"));
	MenuItemSprite *pauseItem = MenuItemSprite::create(
			spriteItem1,
			spriteItem2,
			CC_CALLBACK_1(GameLayer::pauseMenuCallback, this)
			);
	pauseItem->setPosition(ccp(size.width-190,50));
	pauseItem->setScale(2.0f);
	Menu *menu=Menu::create(pauseItem,NULL);
	menu->setPosition(CCPointZero);
	this->addChild(menu);
	sprite = Sprite::createWithTexture(
			Director::getInstance()->getTextureCache()->addImage(
					"picture/bg0.png"));
	sprite->setPosition(
			ccp(origin.x + size.width / 2, origin.y + size.height / 2 + 40));
	sprite->setScaleX(2.2f);
	sprite->setScaleY(2.0f);
	sprite->setGlobalZOrder(-5);
	this->addChild(sprite, -1);
}
void GameLayer::initLevelData()
{
	string levelStr=StringUtils::format("%d",SelectLayer::CURRENT_LEVEL);
	string plistPath;
	if(SelectLayer::CURRENT_LEVEL<10){
		plistPath="guanData/level00"+levelStr+".plist";
	}else{
		plistPath="guanData/level0"+levelStr+".plist";
	}
    CCLOG("-------------------------2");
	ValueMap homeMap=FileUtils::getInstance()->getValueMapFromFile(plistPath);
	ValueVector homeVector=homeMap.at("element").asValueVector();
    CCLOG("size====%l", homeVector.size());
	for(int i=0;i<homeVector.size();i++){
        CCLOG("-------------------------3");
		ValueMap map=homeVector.at(i).asValueMap();
		string picName=map.at("picpath").asString();
		string id=map.at("id").asString();
		string src=map.at("src").asString();
		int x=map.at("px").asInt();
		int y=map.at("py").asInt();
		string vertex=map.at("vertex").asString();
		string flip=map.at("flip").asString();
        CCLOG("-------------------------4");
		
		SpriteFrame *frame=NULL;
		if(src==string("ui")){
			frame=uiSpriteCache->getSpriteFrameByName(picName);
		}else if(src==string("game")){
			frame=gameSpriteCache->getSpriteFrameByName(picName);
		}
		Sprite *sprite=Sprite::createWithSpriteFrame(frame);
		if(flip==string("true")){
			sprite->setFlippedX(true);
		}
		
		const char *str=id.c_str();
		char preFix=*str;
		if (preFix == 'M') {
			data = new float[4] { (float)x, (float)y, sprite->getContentSize().width,
					sprite->getContentSize().height / 7 * 6 };
			ids = new std::string(str);
			po = new RectPhyObject(ids, false, this, world, sprite, data, 0.05f,
					0.75f, 0.65f);
		} else if (preFix == 'E') {
			totalScole = totalScole + 3;
			data = new float[4] { (float)x, (float)y, sprite->getContentSize().width,
					sprite->getContentSize().height / 7 * 6 };
			ids = new std::string(str);
			po = new RectPhyObject(ids, false, this, world, sprite, data, 0.05f,
					0.75f, 0.65f);
		} else if (preFix == 'T') {
			data = new float[4] { (float)x, (float)y, sprite->getContentSize().width,
					sprite->getContentSize().height };
			ids = new std::string(str);
			po = new RectPhyObject(ids, true, this, world, sprite, data, 0,
					0.2f, 0.8f);
		} else if (preFix == 'C') {
			totalScole = totalScole + 2;
			cageNumber++;
			data = new float[4] { (float)x, (float)y, sprite->getContentSize().width,
					sprite->getContentSize().height };
			ids = new std::string(str);
			po = new RectPhyObject(ids, true, this, world, sprite, data, 0,
					0.2f, 0.8f);
		} else if (preFix == 'P') {
			sprite->setScale(2.0f);
			int j = 0;
			data = new float[11];
			data[0] = x;
			data[1] = y;
			data[2] = 4;
			string vertexStr = vertex;
			char s[28];
			strcpy(s, vertexStr.c_str());
			const char *d = ",";
			char *p;
			p = strtok(s, d);
			while (p) {
				String *numberStr = String::createWithFormat("%s", p);
				float vertexPoint = numberStr->floatValue();
				data[3 + j] = vertexPoint;
				j++;
				p = strtok(NULL, d);
			}
			ids = new std::string(str);
			po = new PolygonPhyObject(ids, true, this, world, sprite, data, 0,
					0.8f, 0.2f);
		} else if (preFix == 'N')
        {
            
		}

	}
}

void GameLayer::init3DBoomerang()
{
	
}

void GameLayer::step()
{
	
}

void GameLayer::updateStreakPosition(float time)
{
	
}

void GameLayer::createBoomerang()
{

	
}

void GameLayer::deleteWeapon()
{
	
}

bool GameLayer::touchBegan(Touch *touch,Event *event)
{
	
}

void GameLayer::touchMoved(Touch *touch, Event *event)
{

}

void GameLayer::touchEnded(Touch *touch, Event *event)
{
	
}

void GameLayer::touchCancelled(Touch *touch, Event *event)
{
}

void GameLayer::initCageOpenAnimate(float x,float y)
{
	
}

void GameLayer::initExplodeAnimate(float x,float y)
{
	
}

void GameLayer::ninjaShootBoomerangAnimate()
{
	
}

void GameLayer::updateDelete()
{
	
}

void GameLayer::tntExplode(float xlocation, float ylocation)
{
    
}

void GameLayer::addScore(int score,float xPosition,float yPosition)
{
    
}
void GameLayer::delScoreSp()
{
    
}
void GameLayer::pauseMenuCallback(Object *pSender)
{
    
	
}

void GameLayer::addMenuClickSound()
{
    
}

void GameLayer::onMyKeyPressed(EventKeyboard::KeyCode keyCode,Event* event)
{
    
}

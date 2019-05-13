//
//  SelectLayer.cpp
//  NinjaDart
//
//  Created by 彭芮 on 2019/5/6.
//

#include "SelectLayer.h"
#include "MainLayer.h"
#include "Vector"

#define  LOG_TAG    "main"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

int SelectLayer::CURRENT_LEVEL=1;

USING_NS_CC;

bool SelectLayer::init(){
	if(!Layer::init()){
		return false;
	}
	auto listener=EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(SelectLayer::exitCallback, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
	auto size = Director::sharedDirector()->getVisibleSize();
	spriteFrameCache = SpriteFrameCache::getInstance();
	spriteFrameCache->addSpriteFramesWithFile("ui_collage_images.plist", Director::getInstance()->getTextureCache()->addImage("ui_collage_images.png"));
    
	MenuItemImage *backItem=MenuItemImage::create(
			"picture/return.png",
			"picture/return2.png",
			CC_CALLBACK_1(SelectLayer::menuCallback,this));
    
	Menu *menu=Menu::create(backItem,NULL);
	menu->setPosition(ccp(size.width-100,100));
	this->addChild(menu);
	parentSprite=Sprite::create();
	parentSprite->setPosition(CCPointZero);
	this->addChild(parentSprite);
    
	initLevel();
    
	return true;
}
void SelectLayer::initLevel(){
	Vector<MenuItem*> itemVector;
	int startLevel=(currentPage-1)*LEVELNUMBER;
	int endLevel=currentPage*LEVELNUMBER;
    
	for(int i=startLevel;i<endLevel;i++)
    {
		int xOfset = (i - startLevel) % 3;
        int yOfset = (i - startLevel) / 3;
        
		std::string numberStr = StringUtils::format("%d",
		int starNum = UserDefault::getInstance()->getIntegerForKey(numberStr.c_str(), 0);
		std::string picthStr = "picture/level" + numberStr + ".png";
		Sprite *sprite = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage(picthStr));
                                                    
		MenuItem *item = MenuItemSprite::create(
				sprite,
				sprite,
				CC_CALLBACK_1(SelectLayer::menuSelectCallback, this)
				);
		item->setPosition(ccp(350+xOfset*280,440-yOfset*220));
		item->setTag(i);
		itemVector.pushBack(item);
		std::string number1 = StringUtils::format("%d", (i + 1));
		LabelAtlas *levelNum= LabelAtlas::create(number1,
				"picture/number_time_red.png", 36, 39, '0');
		levelNum->setPosition(ccp(340+xOfset*280,530-yOfset*220));
        parentSprite->addChild(levelNum,1);
                                                    
		if (preLevelStar == 0)
        {
			Sprite *lockSp = Sprite::createWithSpriteFrame(spriteFrameCache->getSpriteFrameByName("xiaosuozi.png"));
			lockSp->setPosition(ccp(350+xOfset*280,440-yOfset*220));
			lockSp->setScale(2.0f);
			this->addChild(lockSp);
			item->setEnabled(false);
		}
		preLevelStar = starNum;
	}
                                                    
	Menu *menu=Menu::createWithArray(itemVector);
	menu->setPosition(CCPointZero);
	parentSprite->addChild(menu);
}
void SelectLayer::menuSelectCallback(Object *pSender)
{

}
void SelectLayer::menuCallback(Object *pSender)
{
	addMenuClickSound();
	gsm->goMainLayer();
}
void SelectLayer::exitCallback(EventKeyboard::KeyCode keyCode,Event *event)
{
    
}
                               
void SelectLayer::addMenuClickSound()
        {
	if (MainLayer::IsSoundOn) {
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(
				"anniujihuo2.wav");
	}
}

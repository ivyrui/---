//
//  SelectLayer.h
//  NinjaDart
//
//  Created by 彭芮 on 2019/5/6.
//

#ifndef _SelectLayer_H
#define _SelectLayer_H

#include "GameSceneManager.h"
#include "cocos2d.h"

using namespace cocos2d;

#define LEVELNUMBER 6

class SelectLayer : public Layer{
public:
    
    CREATE_FUNC(SelectLayer);
	virtual bool init();
    
	void menuCallback(Object *pSender);
	void initLevel();
	void menuSelectCallback(Object *pSender);
	void exitCallback(EventKeyboard::KeyCode keyCode,Event *event);
	void addMenuClickSound();
    
public:
	GameSceneManager *gsm;
    Sprite *parentSprite;
    SpriteFrameCache *spriteFrameCache;
    int preLevelStar=1;             //记录上一关卡的星数
    int currentPage=1;              //表示当前的页数
    static int CURRENT_LEVEL;       //表示当前关卡
};
#endif
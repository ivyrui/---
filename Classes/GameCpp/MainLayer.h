//
//  MainLayer.h
//  NinjaDart
//
//  Created by 彭芮 on 2019/4/25.
//

#ifndef __MainLayer_H_
#define __MainLayer_H_

#include "cocos2d.h"
#include "GameSceneManager.h"

using namespace cocos2d;
using namespace std;

class MainLayer : public Layer
{
public:
    MainLayer();
    ~MainLayer();
    
    virtual bool init();
    CREATE_FUNC(MainLayer);
    
    void loadingImageAsync();
    void loadingCallback(Texture2D *texture);
    void loadMusic();
    
    void startGame(Ref *pSender);
    void lookRank(Ref *pSender);
    void lookAbout(Ref *pSender);
    void lookHelp(Ref *pSender);
    
    void controlMusic(Ref *pSender);
    void controlSound(Ref *pSender);
    void onMyKeyPressed(EventKeyboard::KeyCode keyCode, Event *event);
    void addMenuClickSound();
    
public:
    GameSceneManager *gsm;              //场景管理
    Menu *musicOnMenu;
    Menu *musicOffMenu;
    MenuItemImage *musicOnItem;
    MenuItemImage *musicOffItem;
    MenuItemImage *soundOnItem;
    MenuItemImage *soundOffItem;
    
    static bool IsMusicOn;
    static bool IsSoundOn;
    
    int jd;                             //图片资源加载累加器
    int loadCount;                      //记录加载图片的整型变量
    
};

#endif /* MainLayer_hpp */

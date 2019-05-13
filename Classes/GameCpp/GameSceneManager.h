//
//  GameSceneManager.h
//  NinjaDart
//
//  Created by 彭芮 on 2019/4/24.
//

#ifndef __GameSceneManager_H_
#define __GameSceneManager_H_

#include "cocos2d.h"

using namespace cocos2d;

class GameSceneManager
{
public:
    GameSceneManager();
    ~GameSceneManager();
    
    void createScene();  //创建场景
    
    //界面跳转
    void goSelectLayer();
    void goMainLayer();
    void goGameLayer();
    void goRankLayer();
    void goAboutLayer();
    void goHelpLayer();
    
public:
    Scene *mainScene;
    Scene *selectScene;
    Scene *gameScene;
    Scene *rankScene;
    Scene *aboutScene;
    Scene *helpScene;
    
};

#endif /* GameSceneManager_hpp */

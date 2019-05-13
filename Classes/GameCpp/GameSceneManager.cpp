//
//  GameSceneManager.cpp
//  NinjaDart
//
//  Created by 彭芮 on 2019/4/24.
//

#include "GameSceneManager.h"
#include "MainLayer.h"

GameSceneManager::GameSceneManager()
:mainScene(NULL)
,gameScene(NULL)
,rankScene(NULL)
,aboutScene(NULL)
,helpScene(NULL)
{
    
}

GameSceneManager::~GameSceneManager()
{
  //  CC_SAFE_DELETE(NULL);
}

void GameSceneManager::createScene()
{
    auto layer = MainLayer::create();
    layer->gsm = this;
    mainScene = Scene::create();
    mainScene->addChild(layer);
}

void GameSceneManager::goMainLayer()
{
    Director::getInstance()->setDepthTest(true);
    auto layer=MainLayer::create();
    layer->gsm=this;
    mainScene=Scene::create();
    mainScene->addChild(layer);
    TransitionScene *ts=TransitionFade::create(1.0f,mainScene);
    Director::getInstance()->replaceScene(ts);
}

void GameSceneManager::goSelectLayer()
{
    auto layer=SelectLayer::create();
    layer->gsm=this;
    selectScene=Scene::create();
    selectScene->addChild(layer);
    TransitionScene *ts=TransitionFade::create(1.0f,selectScene);
    Director::getInstance()->replaceScene(ts);
}

void GameSceneManager::goGameLayer()
{
    
}

void GameSceneManager::goRankLayer()
{
    
}

void GameSceneManager::goHelpLayer()
{
    
}

void GameSceneManager::goAboutLayer()
{
    
}



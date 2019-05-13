//
//  MainLayer.cpp
//  NinjaDart
//
//  Created by 彭芮 on 2019/4/25.
//

#include "MainLayer.h"
#include "audio/include/SimpleAudioEngine.h"

MainLayer::MainLayer()
{
    
}

MainLayer::~MainLayer()
{
    
}

bool MainLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    auto size = Director::getInstance()->getVisibleSize();
    
    Sprite *loadSprite = Sprite::create("loding.png");
    loadSprite->setPosition(Vec2(size.width / 2, size.height / 2));
    loadSprite->setTag(1);
    this->addChild(loadSprite);
    
    Sprite *boomSprite = Sprite::create("boom_weapon.png");
    boomSprite->setPosition(Vec2(size.width / 2 - 290, size.height / 2));
    boomSprite->setScale(2.0f);
    boomSprite->runAction(RepeatForever::create(RotateBy::create(0.5, 360)));
    boomSprite->setTag(2);
    this->addChild(boomSprite);
    
    //创建键盘触摸监听器
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(MainLayer::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    loadMusic();
    
    loadingImageAsync();
    
    return true;
}

void MainLayer::loadMusic()
{
    string mc[9] = {"anniujihuo2.wav", "bg_lose.mp3", "bg_win1.mp3", "feibiaofantan1.wav", "yanwudanbaozha1.wav", "direncanjiao1.mp3", "xingjitishi.wav", "tielongjisui.wav", "zhayaotongbaozha.mp3"};
    for (int i = 0; i < 9; i++) {
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(mc[i].c_str());
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("bg_home.mp3");
    }
}

void MainLayer::loadingImageAsync()
{
    std::string sa[23] = {"game_collage.png", "ui_collage_images.png",
    "bigdimian1.png", "level0.png",
    "level1.png", "level2.png", "level3.png",
    "level4.png", "level5.png", "AboutUs.png",
    "Exita.png", "bg0.png", "bg1.png",
    "bg2.png", "help0.png", "picture/help1.png",
    "help2.png", "help3.png", "About.png",
    "Help.png", "HistoryScore.png",
    "SelectLevel.png", "HelpBar.png" };
    for(int i =0;i<23;i++)
    {
        Director::getInstance()->getTextureCache()->addImageAsync(sa[i], CC_CALLBACK_1(MainLayer::loadingCallback, this));
    }
}

void MainLayer::loadingCallback(Texture2D *texture)
{
    auto size = Director::getInstance()->getVisibleSize();
    jd ++;
    
    if (jd == 23) {
        this->removeChildByTag(1, true);
        this->removeChildByTag(2, true);
        Sprite * titleSp = Sprite::create("title.png");
        titleSp->setPosition(Vec2(size.width / 2, size.height - 100));
        this->addChild(titleSp);
        
        MenuItemImage * startItem = MenuItemImage::create("Startc1.png", "Startc1.png", LBACK_1(MainLayer::startGame, this));
        MenuItemImage *helpItem = MenuItemImage::create("Helpc1.png","Helpc1.png", CC_CALLBACK_1(MainLayer::lookHelp, this));
        MenuItemImage *rankItem = MenuItemImage::create("Rankc1.png","Rankc1.png",CC_CALLBACK_1(MainLayer::lookRank, this));
        MenuItemImage *aboutItem= MenuItemImage::create("picture/Aboutc1.png","picture/Aboutc1.png",CC_CALLBACK_1(MainLayer::lookAbout, this));
        
        Menu * menu = Menu::create(startItem,helpItem,rankItem,aboutItem,NULL);
        menu->alignItemsVerticallyWithPadding(30);
        menu->setPosition(ccp(size.width / 2, size.height / 2-100));
        this->addChild(menu,2);
        
        musicOnItem = MenuItemImage::create("menu_option_button_music_on.png", "menu_option_button_music_on.png",CC_CALLBACK_1(MainLayer::controlMusic, this));
        soundOnItem = MenuItemImage::create("menu_option_button_sound_on.png", "menu_option_button_sound_on.png", ,CC_CALLBACK_1(MainLayer::controlSound, this));
        
        Menu *msOnMenu = Menu::create(musicOnItem, soundOnItem,NULL);
        //设置菜单中的菜单项按照竖直方式排列，菜单项间距50个像素
        msOnMenu->alignItemsHorizontallyWithPadding(50);
        msOnMenu->setPosition(ccp(200,100));
        this->addChild(msOnMenu,2);
        
        musicOffItem = MenuItemImage::create("menu_option_button_music_off.png", "menu_option_button_music_off.png", CC_CALLBACK_1(MainLayer::controlMusic, this));
        soundOffItem = MenuItemImage::create("menu_option_button_sound_off.png", "menu_option_button_sound_off.png", CC_CALLBACK_1(MainLayer::controlSound, this));
        
        Menu *msOffMenu = Menu::create(musicOffItem, soundOffItem, NULL);
        msOffMenu->alignItemsHorizontallyWithPadding(50);
        msOffMenu->setPosition(ccp(200, 100));
        this->addChild(msOffMenu,2);
        
        //当背景音乐标志为true时
        if(IsMusicOn){
            musicOnItem->setVisible(true);                            //设置关音乐菜单项可见
            musicOffItem->setVisible(false);                        //设置开音乐菜单项不可见
        if(!CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()) {
            CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/bg_home.mp3", true);
            }
        }else{
            musicOnItem->setVisible(false);
            musicOffItem->setVisible(true);
        }
        
        //当及时音效标志位为true时
        if (IsSoundOn) {
            soundOnItem->setVisible(true);
            soundOffItem->setVisible(false);
        } else {
            soundOnItem->setVisible(false);
            soundOffItem->setVisible(true);
        }
    }
}

void MainLayer::startGame(Object *pSender)
{
    addMenuClickSound();
    gsm->goSelectLayer();
}

void MainLayer::lookRank(Object *pSender)
{
    addMenuClickSound();
    gsm->goRankLayer();
}

void MainLayer::lookAbout(Object *pSender)
{
    addMenuClickSound();
    gsm->goAboutLayer();
}

void MainLayer::lookHelp(Object *pSender)
{
    addMenuClickSound();
    gsm->goHelpLayer();
}

void MainLayer::controlMusic(Object *pSender)
{
    addMenuClickSound();
    IsMusicOn=!IsMusicOn;
    if(IsMusicOn)
    {
        musicOnItem->setVisible(true);
        musicOffItem->setVisible(false);
        //继续播放背景音乐
        CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    }else
    {
        musicOnItem->setVisible(false);
        musicOffItem->setVisible(true);
        //暂停播放背景音乐
        CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    }
}

void MainLayer::controlSound(Object *pSender)
{
    addMenuClickSound();
    IsSoundOn=!IsSoundOn;
    if (IsSoundOn)
    {
        soundOnItem->setVisible(true);
        soundOffItem->setVisible(false);
    } else
    {
        soundOnItem->setVisible(false);
        soundOffItem->setVisible(true);
    }
}

void MainLayer::onMyKeyPressed(EventKeyboard::KeyCode keyCode,Event *event)
{
    //点击手机返回键时，调用该方法
    Node *node=this->getChildByTag(100);
    if (node != NULL)
    {
        this->removeChild(node);
    }else
    {
        ExitPopupWindow* popWindow = ExitPopupWindow::create();
        //如果节点不存在，创建一个节点
        popWindow->setTag(100);
        this->addChild(popWindow,2);
    }
}

void MainLayer::addMenuClickSound()
{
    if (MainLayer::IsSoundOn)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/anniujihuo2.wav");
    }
}



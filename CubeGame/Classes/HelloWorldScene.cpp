/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "Nivel1.h"
#include "Nivel2.h"
#include "Nivel3.h"
#include <AudioEngine.h>

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //Crear escena
        crearEscena();

    //Musica
        _musicaFondoMenu = AudioEngine::play2d("Audios/MusicaFondoMenu.mp3", true, _volumenMusica);

    return true;
}

void HelloWorld::crearEscena() 
{
    auto visibleSize = Director::getInstance()->getVisibleSize();

    //Sprite del fondo
        auto spriteFondo = Sprite::create("ImagenesMenu/MenuCompleto.png");
        spriteFondo->setScale(0.5, 0.5);
        spriteFondo->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
        this->addChild(spriteFondo, 0);

    //Botones
        auto botonJugar = MenuItemImage::create("ImagenesMenu/PlayBoton.png", "ImagenesMenu/PlayBotonS.png", CC_CALLBACK_1(HelloWorld::PlayButton, this));
        auto botonHighScores = MenuItemImage::create("ImagenesMenu/HighScoreBoton.png", "ImagenesMenu/HighScoreBotonS.png", CC_CALLBACK_1(HelloWorld::HighScoresButton, this));
        auto botonCerrar = MenuItemImage::create("ImagenesMenu/CloseBoton.png", "ImagenesMenu/CloseBotonS.png", CC_CALLBACK_1(HelloWorld::CloseButton, this));

        botonJugar->setScale(0.45, 0.45);
        botonHighScores->setScale(0.45, 0.45);
        botonCerrar->setScale(0.45, 0.45);

        botonJugar->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 40) * 10));
        botonHighScores->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 40) * 7));
        botonCerrar->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 40) * 4));

    auto* menu = Menu::create(botonJugar, botonHighScores, botonCerrar, NULL);
    menu->setPosition(Point(0, 0));
    this->addChild(menu);
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

//Botones
void HelloWorld::PlayButton(HelloWorld::Ref* pSender) {
    CCLOG("Play");
    _efectoSeleccionar = AudioEngine::play2d("Audios/EfectoSeleccionar.mp3", false, _volumenSeleccionar);
    AudioEngine::stop(_musicaFondoMenu);
    
    auto scene = Nivel1::createScene();
    Director::getInstance()->replaceScene(TransitionCrossFade::create(2, scene));
}
void HelloWorld::HighScoresButton(HelloWorld::Ref* pSender) {
    _efectoSeleccionar = AudioEngine::play2d("Audios/EfectoSeleccionar.mp3", false, _volumenSeleccionar);
    this->removeAllChildren();

    auto visibleSize = Director::getInstance()->getVisibleSize();
    CCLOG("HighScore");

    //Desplegar pantalla de menu
        _highScoreMenu = Sprite::create("ImagenesMenu/HighScoreMenuMenu.png");
        _highScoreMenu->setScale(0.52, 0.52);
        _highScoreMenu->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
        this->addChild(_highScoreMenu, 100000);

    //Boton
        botonCloseHigh = MenuItemImage::create("ImagenesMenu/CloseBoton.png", "ImagenesMenu/CloseBotonS.png", CC_CALLBACK_1(HelloWorld::CloseButtonHigh, this));
        botonCloseHigh->setScale(0.5, 0.5);
        botonCloseHigh->setPosition(Point(visibleSize.width / 2, 200));

        menuHighScore = Menu::create(botonCloseHigh, NULL);
        menuHighScore->setPosition(Point(0, 0));
        this->addChild(menuHighScore, 100000);

    //Label
        def = UserDefault::getInstance();
        highPuntuation = def->getIntegerForKey("HIGHSCORE", 0);
        def->flush();

        std::stringstream ss;
        ss << highPuntuation;
        scoreLabelHigh = Label::createWithTTF(ss.str(), "fonts/Minecrafter.ttf", 60);
        scoreLabelHigh->setColor(Color3B::WHITE);
        scoreLabelHigh->setPosition(Point(visibleSize.width / 2, 375));
        this->addChild(scoreLabelHigh, 100000);
}

void HelloWorld::CloseButton(HelloWorld::Ref* pSender) {
    CCLOG("Close");
    _efectoSeleccionar = AudioEngine::play2d("Audios/EfectoSeleccionar.mp3", false, _volumenSeleccionar);
    Director::getInstance()->end();
}

void HelloWorld::CloseButtonHigh(Nivel1::Ref* pSender) {
    this->removeAllChildren();
    _efectoSeleccionar = AudioEngine::play2d("Audios/EfectoSeleccionar.mp3", false, _volumenSeleccionar);
    auto visibleSize = Director::getInstance()->getVisibleSize();
    CCLOG("CloseHighScores");

    crearEscena();
}

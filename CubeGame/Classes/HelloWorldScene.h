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

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
private:
    //Botones
        void PlayButton(Ref* pSender);
        void SettingsButton(Ref* pSender);
        void CloseButton(Ref* pSender);

        void HelloWorld::HighScoresButton(Ref* pSender);
        cocos2d::MenuItemImage* botonHighsScore;
        cocos2d::Menu* menuHighScore;

        void HelloWorld::CloseButtonHigh(Ref* pSender);
        cocos2d::MenuItemImage* botonCloseHigh;
        cocos2d::Menu* menuPauseHigh;

    //Label
        cocos2d::Label* scoreLabelHigh;

    //onTouch
        bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
        bool onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
        bool onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

    //Musica
        int _musicaFondoMenu;

    //Volumen
        float _volumenMusica = 0.5;
        float _volumenSeleccionar = 0.9;

    //Efectos
        int _efectoSeleccionar;

    //UserDefault
        cocos2d::UserDefault* def;
        int highPuntuation;

    //Sprite
        cocos2d::Sprite* _highScoreMenu;

    //Escena
        void HelloWorld::crearEscena();
};

#endif // __HELLOWORLD_SCENE_H__

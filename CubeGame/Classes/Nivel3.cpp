#include "HelloWorldScene.h"
#include "Nivel1.h"
#include "Nivel2.h"
#include "Nivel3.h"
#include <AudioEngine.h>

USING_NS_CC;

Scene* Nivel3::createScene()
{
    return Nivel3::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Nivel3::init()
{
    //////////////////////////////
    // 1. super init first
    /*if ( !Scene::init() )
    {
        return false;
    }*/

    if (!Scene::initWithPhysics())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    def1 = UserDefault::getInstance();
    score = def1->getIntegerForKey("SCOREACTUAL", 0);
    def1->flush();

    def2 = UserDefault::getInstance();
    vida = def2->getIntegerForKey("VIDA", 0);
    def2->flush();

    crearEscenaIntermedia();


    return true;
}

void Nivel3::crearEscenaIntermedia() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //Sprite del fondo
    _spriteFondoIntermedio = Sprite::create("PantallasIntermedias/Nivel3.png");
    _spriteFondoIntermedio->setScale(0.52, 0.52);
    _spriteFondoIntermedio->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(_spriteFondoIntermedio, 0);

    //Enemigo
        //Circulo
    auto cacher1 = SpriteFrameCache::getInstance();
    cacher1->addSpriteFramesWithFile("Cache3.plist");

    // load all the animation frames into an array
    Vector<SpriteFrame*> frames;
    for (int i = 1; i <= 6; i++)
    {
        std::stringstream ss;
        ss << "Circulo" << i << ".png";
        frames.pushBack(cacher1->getSpriteFrameByName(ss.str()));
    }
    circuloIntermedio = Sprite::createWithSpriteFrameName("Circulo1.png");
    circuloIntermedio->setPosition(Point((visibleSize.width / 2) - 40, 295));
    circuloIntermedio->setScale(0.1, 0.1);
    this->addChild(circuloIntermedio, 1);

    // play the animation
    Animation* anim = Animation::createWithSpriteFrames(frames, 0.10);
    circuloIntermedio->runAction(RepeatForever::create(Animate::create(anim)));

    //Triangulo
        // load all the animation frames into an array
    Vector<SpriteFrame*> frames1;
    for (int i = 1; i <= 6; i++)
    {
        std::stringstream ss;
        ss << "Triangulo" << i << ".png";
        frames1.pushBack(cacher1->getSpriteFrameByName(ss.str()));
    }
    trianguloIntermedio = Sprite::createWithSpriteFrameName("Triangulo1.png");
    trianguloIntermedio->setPosition(Point((visibleSize.width / 2) - 40, 255));
    trianguloIntermedio->setScale(0.1, 0.1);
    this->addChild(trianguloIntermedio, 1);

    // play the animation
    Animation* anim1 = Animation::createWithSpriteFrames(frames1, 0.10);
    trianguloIntermedio->runAction(RepeatForever::create(Animate::create(anim1)));


    //Boton PlayIntermedio
    botonPlayIntermedio = MenuItemImage::create("ImagenesMenu/PlayBoton.png", "ImagenesMenu/PlayBotonS.png", CC_CALLBACK_1(Nivel3::PlayIntermedio, this));
    botonPlayIntermedio->setScale(0.4, 0.4);
    botonPlayIntermedio->setPosition(Point(visibleSize.width / 2, 100));
    menuPlayIntermedio = Menu::create(botonPlayIntermedio, NULL);
    menuPlayIntermedio->setPosition(Point(0, 0));
    this->addChild(menuPlayIntermedio, 1000);
}

void Nivel3::crearEscenaIntermediaFinal() {
    this->removeAllChildren();
    this->unscheduleAllCallbacks();
    this->removeAllComponents();
    _eventDispatcher->removeAllEventListeners();

    auto visibleSize = Director::getInstance()->getVisibleSize();
    AudioEngine::stop(_musicaFondoNivel1);
    _efectoVictoria = AudioEngine::play2d("Audios/EfectoVictoria.mp3", false, _volumenMusica);

    //Sprite del fondo
    _spriteFondoIntermedio = Sprite::create("PantallasIntermedias/Win2.png");
    _spriteFondoIntermedio->setScale(0.52, 0.52);
    _spriteFondoIntermedio->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(_spriteFondoIntermedio, 0);

    //Animacion
    auto cacher1 = SpriteFrameCache::getInstance();
    //cacher1->init();
    cacher1->addSpriteFramesWithFile("Cache4.plist");

    // load all the animation frames into an array
    Vector<SpriteFrame*> frames;
    for (int i = 1; i <= 5; i++)
    {
        std::stringstream ss;
        ss << "Victoria" << i << ".png";
        frames.pushBack(cacher1->getSpriteFrameByName(ss.str()));
    }
    circuloIntermedio = Sprite::createWithSpriteFrameName("Victoria1.png");
    circuloIntermedio->setPosition(Point(visibleSize.width / 2, 150));
    circuloIntermedio->setScale(0.3, 0.3);
    this->addChild(circuloIntermedio, 1);

    // play the animation
    Animation* anim = Animation::createWithSpriteFrames(frames, 0.10);
    circuloIntermedio->runAction(RepeatForever::create(Animate::create(anim)));


    //Boton PlayIntermedioFinal
    botonPlayIntermedioFinal = MenuItemImage::create("ImagenesMenu/PlayBoton.png", "ImagenesMenu/PlayBotonS.png", CC_CALLBACK_1(Nivel3::PlayIntermedioFinal, this));
    botonPlayIntermedioFinal->setScale(0.4, 0.4);
    botonPlayIntermedioFinal->setPosition(Point(visibleSize.width / 2, 50));
    menuPlayIntermedioFinal = Menu::create(botonPlayIntermedioFinal, NULL);
    menuPlayIntermedioFinal->setPosition(Point(0, 0));
    this->addChild(menuPlayIntermedioFinal, 1000);

    //Label
    std::stringstream ss;
    ss << score;
    scoreLabel = Label::createWithTTF(ss.str(), "fonts/Minecrafter.ttf", 40);
    scoreLabel->setColor(Color3B::WHITE);
    scoreLabel->setPosition(Point(visibleSize.width / 2, 240));
    this->addChild(scoreLabel, 100);

    def1 = UserDefault::getInstance();
    def1->setIntegerForKey("SCOREACTUAL", 0);
    def1->flush();

    //Vida
    def2 = UserDefault::getInstance();
    def2->setIntegerForKey("VIDA", 3);
    def2->flush();
}

void Nivel3::crearEscenaDerrota() {
    this->removeAllChildren();
    this->unscheduleAllCallbacks();
    this->removeAllComponents();
    _eventDispatcher->removeAllEventListeners();

    auto visibleSize = Director::getInstance()->getVisibleSize();
    AudioEngine::stop(_musicaFondoNivel1);
    _efectoDerrota = AudioEngine::play2d("Audios/EfectoDerrota.mp3", false, _volumenMusica);

    //Sprite del fondo
    _spriteFondoIntermedio = Sprite::create("PantallasIntermedias/GameOver.png");
    _spriteFondoIntermedio->setScale(0.52, 0.52);
    _spriteFondoIntermedio->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(_spriteFondoIntermedio, 0);

    //Animacion
    auto cacher1 = SpriteFrameCache::getInstance();
    //cacher1->init();
    cacher1->addSpriteFramesWithFile("Cache4.plist");

    // load all the animation frames into an array
    Vector<SpriteFrame*> frames;
    for (int i = 1; i <= 12; i++)
    {
        std::stringstream ss;
        ss << "Final" << i << ".png";
        frames.pushBack(cacher1->getSpriteFrameByName(ss.str()));
    }
    circuloIntermedio = Sprite::createWithSpriteFrameName("Final1.png");
    circuloIntermedio->setPosition(Point(visibleSize.width / 2, 285));
    circuloIntermedio->setScale(0.5, 0.5);
    this->addChild(circuloIntermedio, 1);

    // play the animation
    Animation* anim = Animation::createWithSpriteFrames(frames, 0.20);
    circuloIntermedio->runAction(RepeatForever::create(Animate::create(anim)));


    //Boton Derrota
    botonMenuDerrota = MenuItemImage::create("ImagenesMenu/BackMenu.png", "ImagenesMenu/BackMenuS.png", CC_CALLBACK_1(Nivel3::MenuDerrota, this));
    botonMenuDerrota->setScale(0.4, 0.4);
    botonMenuDerrota->setPosition(Point(visibleSize.width / 2, 100));
    menuMenuDerrota = Menu::create(botonMenuDerrota, NULL);
    menuMenuDerrota->setPosition(Point(0, 0));
    this->addChild(menuMenuDerrota, 1000);

    //Label
    std::stringstream ss;
    ss << score;
    scoreLabel = Label::createWithTTF(ss.str(), "fonts/Minecrafter.ttf", 40);
    scoreLabel->setColor(Color3B::WHITE);
    scoreLabel->setPosition(Point(visibleSize.width / 2, 450));
    this->addChild(scoreLabel, 100);

    def1 = UserDefault::getInstance();
    def1->setIntegerForKey("SCOREACTUAL", 0);
    def1->flush();

    //Vida
    def2 = UserDefault::getInstance();
    def2->setIntegerForKey("VIDA", 3);
    def2->flush();
}

void Nivel3::crearEscena() {
    auto visibleSize = Director::getInstance()->getVisibleSize();

    //Boton Configuracion
    botonConfiguracion = MenuItemImage::create("HUD/Tuerca.png", "HUD/TuercaPush.png", CC_CALLBACK_1(Nivel3::ConfigurationButton, this));
    botonConfiguracion->setScale(0.3, 0.3);
    botonConfiguracion->setPosition(Point(440, 760));
    menuConfiguracion = Menu::create(botonConfiguracion, NULL);
    menuConfiguracion->setPosition(Point(0, 0));
    this->addChild(menuConfiguracion, 1000);


    //Sprite del fondo
    auto spriteFondo = Sprite::create("Nivel3/Montanas3.png");
    spriteFondo->setScale(0.5, 0.5);
    spriteFondo->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(spriteFondo, 0);

    //Sprite del HUD
    mySprite = Sprite::create("HUD/HUD.png");
    mySprite->setScale(0.5, 0.5);
    mySprite->setPosition(Point(visibleSize.width / 2, 51));
    this->addChild(mySprite, 100);

    //Barreras
    agregarBarrerasContension();

    //Score
    agregarScore();

    //Nivel
    auto estrellaNivel = Sprite::create("EstrellasNivel/EstrellaBronce.png");
    estrellaNivel->setScale(0.2, 0.2);
    estrellaNivel->setPosition(Point(366, 69));
    this->addChild(estrellaNivel, 100);

    auto estrellaNivel2 = Sprite::create("EstrellasNivel/EstrellaPlata.png");
    estrellaNivel2->setScale(0.2, 0.2);
    estrellaNivel2->setPosition(Point(399, 69));
    this->addChild(estrellaNivel2, 100);

    auto estrellaNivel3 = Sprite::create("EstrellasNivel/EstrellaOro.png");
    estrellaNivel3->setScale(0.2, 0.2);
    estrellaNivel3->setPosition(Point(432, 69));
    this->addChild(estrellaNivel3, 100);

    //Vida
    agregarVida();

    //Cubito
    agregarCubitoNormal();

    //Sol
    agregarLuna();

    //Enemigos
    this->schedule(SEL_SCHEDULE(&Nivel3::agregarEnemigos), 2);

    //Nubes
    this->schedule(SEL_SCHEDULE(&Nivel3::agregarNubes), 1);

    //Punto Score
    agregarPuntoScore();

    //Moviento
    iniciarTouch();

    //Tiempo
    agregarTimer();
    //time = 90.0f;

//Audio
    _musicaFondoNivel1 = AudioEngine::play2d("Audios/MusicaFondoNivel3.mp3", true, _volumenMusica);

    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(Nivel3::onContactBegin, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

    this->scheduleUpdate();
}

void Nivel3::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);

}

void Nivel3::agregarBarrerasContension() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    _barreras[0] = Sprite::create("BarrerasContension/Vertical.png");
    _barreras[1] = Sprite::create("BarrerasContension/Vertical.png");
    _barreras[2] = Sprite::create("BarrerasContension/Horizontal.png");
    _barreras[3] = Sprite::create("BarrerasContension/Horizontal.png");

    _barreras[0]->setScale(0.50, 0.51);
    _barreras[1]->setScale(0.50, 0.51);
    _barreras[2]->setScale(0.51, 0.50);
    _barreras[3]->setScale(0.51, 0.50);



    _barreras[0]->setPosition(Point(-15, (visibleSize.height / 2) + 7));
    _barreras[1]->setPosition(Point(495, (visibleSize.height / 2) + 7));
    _barreras[2]->setPosition(Point((visibleSize.width / 2), -60));
    _barreras[3]->setPosition(Point((visibleSize.width / 2), 900));
    this->addChild(_barreras[0], 10000);
    this->addChild(_barreras[1], 10000);
    this->addChild(_barreras[2], 10000);
    this->addChild(_barreras[3], 10000);

    for (int i = 0; i < 2; i++) {
        _barrerasBody[i] = PhysicsBody::createBox(Size(_barreras[i]->getContentSize()), PhysicsMaterial(1.0f, 1.0f, 1.0f));
        _barrerasBody[i]->setCollisionBitmask(BARRERAS_LATERALES_COLLISION_BITMASK);
        _barrerasBody[i]->setContactTestBitmask(true);
        _barrerasBody[i]->setDynamic(false);
        _barrerasBody[i]->setGravityEnable(false);
        _barreras[i]->addComponent(_barrerasBody[i]);
    }

    for (int i = 2; i < 4; i++) {
        int n;
        if (i == 2) {
            n = BARRERAS_ABAJO_COLLISION_BITMASK;
        }
        else {
            n = BARRERAS_ARRIBA_COLLISION_BITMASK;
        }
        _barrerasBody[i] = PhysicsBody::createBox(Size(_barreras[i]->getContentSize()), PhysicsMaterial(1.0f, 1.0f, 1.0f));
        _barrerasBody[i]->setCollisionBitmask(n);
        _barrerasBody[i]->setContactTestBitmask(true);
        _barrerasBody[i]->setDynamic(false);
        _barrerasBody[i]->setGravityEnable(false);
        _barreras[i]->addComponent(_barrerasBody[i]);
    }
}

void Nivel3::agregarScore() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    std::stringstream ss;
    ss << score;
    scoreLabel = Label::createWithTTF(ss.str(), "fonts/Minecrafter.ttf", 40);
    scoreLabel->setColor(Color3B::BLACK);
    scoreLabel->setPosition(Point(visibleSize.width / 2, 62));
    this->addChild(scoreLabel, 100);

    def = UserDefault::getInstance();
    highPuntuation = def->getIntegerForKey("HIGHSCORE", 0);
    def->flush();

}

void Nivel3::actualizarScore() {
    this->removeChild(scoreLabel);
    auto visibleSize = Director::getInstance()->getVisibleSize();
    std::stringstream ss;
    ss << score;
    scoreLabel = Label::createWithTTF(ss.str(), "fonts/Minecrafter.ttf", 40);
    scoreLabel->setColor(Color3B::BLACK);
    scoreLabel->setPosition(Point(visibleSize.width / 2, 62));
    this->addChild(scoreLabel, 100);

    def = UserDefault::getInstance();
    if (score > highPuntuation) {
        highPuntuation = score;
        def->setIntegerForKey("HIGHSCORE", highPuntuation);
    }
    def->flush();
}

void Nivel3::agregarTimer() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    _timer = Sprite::create("Timer/Timer.png");
    _timer->setScale(0.3, 0.3);
    _timer->setPosition(Point(76, 747));
    this->addChild(_timer, 1000);

    std::stringstream ss;
    time = 180.0f;
    /*ss << int(time);
    timerLabel = Label::createWithTTF(ss.str(), "fonts/Minecrafter.ttf", 40);
    timerLabel->setColor(Color3B::BLACK);
    timerLabel->setPosition(Point(77, 718));
    this->addChild(timerLabel, 1000);*/
}

void Nivel3::actualizarTimer() {
    this->removeChild(timerLabel);
    auto visibleSize = Director::getInstance()->getVisibleSize();
    std::stringstream ss;
    ss << int(time);
    timerLabel = Label::createWithTTF(ss.str(), "fonts/Minecrafter.ttf", 40);
    timerLabel->setColor(Color3B::BLACK);
    timerLabel->setPosition(Point(77, 718));
    this->addChild(timerLabel, 1000);
}

void Nivel3::iniciarFisicaCubito(Sprite* sprite, int n) {
    _cuboBody = PhysicsBody::createCircle(sprite->getContentSize().width / 2, PhysicsMaterial(1.0f, 1.0f, 1.0f));
    //_cuboBody = PhysicsBody::createBox(Size(sprite->getContentSize()), PhysicsMaterial(1.0f, 1.0f, 1.0f));
    _cuboBody->setTag(n);
    _cuboBody->setCollisionBitmask(CUBITO_COLLISION_BITMASK);
    _cuboBody->setContactTestBitmask(true);
    _cuboBody->setDynamic(false);
    _cuboBody->setGravityEnable(false);
    sprite->addComponent(_cuboBody);
}

void Nivel3::iniciarFisicaCirculos(Sprite* sprite, int n) {
    _enemigosBody[contEnemigosBody] = PhysicsBody::createCircle(sprite->getContentSize().width / 2, PhysicsMaterial(1.0f, 1.0f, 1.0f));
    _enemigosBody[contEnemigosBody]->setTag(n);
    _enemigosBody[contEnemigosBody]->setCollisionBitmask(ENEMIGOS_COLLISION_BITMASK);
    _enemigosBody[contEnemigosBody]->setContactTestBitmask(true);

    _enemigosBody[contEnemigosBody]->setContactTestBitmask(true);

    _enemigosBody[contEnemigosBody]->setDynamic(true);
    _enemigosBody[contEnemigosBody]->setGravityEnable(true);
    _enemigosBody[contEnemigosBody]->setVelocity(Vec2(cocos2d::random(0, 0),
        cocos2d::random(-150, -100)));
    sprite->addComponent(_enemigosBody[contEnemigosBody]);
    contEnemigosBody += 1;

}

void Nivel3::iniciarFisicaTriangulos(Sprite* sprite, int n) {
    auto dn = new Vec2[3]();
    dn[0] = Vec2(0 - (sprite->getContentSize().width / 2), 0 - (sprite->getContentSize().height / 2));
    dn[1] = Vec2(0, 0 + (sprite->getContentSize().height / 2));
    dn[2] = Vec2(0 + (sprite->getContentSize().width / 2), 0 - (sprite->getContentSize().height / 2));

    _enemigosBody[contEnemigosBody] = PhysicsBody::createPolygon(dn, 3, PhysicsMaterial(1.0f, 1.0f, 1.0f));
    _enemigosBody[contEnemigosBody]->setTag(n);
    _enemigosBody[contEnemigosBody]->setCollisionBitmask(ENEMIGOS_COLLISION_BITMASK);
    _enemigosBody[contEnemigosBody]->setContactTestBitmask(true);

    _enemigosBody[contEnemigosBody]->setContactTestBitmask(true);

    _enemigosBody[contEnemigosBody]->setDynamic(true);
    _enemigosBody[contEnemigosBody]->setGravityEnable(true);
    _enemigosBody[contEnemigosBody]->setVelocity(Vec2(cocos2d::random(0, 0),
        cocos2d::random(-150, -100)));
    sprite->addComponent(_enemigosBody[contEnemigosBody]);
    contEnemigosBody += 1;

}

void Nivel3::agregarPuntoScore() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto cacher1 = SpriteFrameCache::getInstance();
    cacher1->addSpriteFramesWithFile("Cache3.plist");


    // load all the animation frames into an array
    Vector<SpriteFrame*> frames;
    for (int i = 1; i <= 8; i++)
    {
        std::stringstream ss;
        ss << "AgujeroNegro" << i << ".png";
        frames.pushBack(cacher1->getSpriteFrameByName(ss.str()));
    }
    _agujeroNegro = Sprite::createWithSpriteFrameName("AgujeroNegro1.png");
    _agujeroNegro->setScale(0.3, 0.3);

    // play the animation
    Animation* anim = Animation::createWithSpriteFrames(frames, 0.10);
    _agujeroNegro->runAction(RepeatForever::create(Animate::create(anim)));

    auto pointBody = PhysicsBody::createBox(Size(_agujeroNegro->getContentSize()), PhysicsMaterial(0.0f, 0.0f, 0.0f));

    pointBody->setDynamic(false);
    pointBody->setCollisionBitmask(PUNTO_SCORE_BITMASK);
    pointBody->setContactTestBitmask(true);


    _agujeroNegro->setPhysicsBody(pointBody);
    _agujeroNegro->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 10) * 7));

    this->addChild(_agujeroNegro, 1);
}

void Nivel3::iniciarTouch() {
    auto escuchador = EventListenerTouchOneByOne::create();
    escuchador->onTouchBegan = [](Touch* touch, Event* event) { return true; };
    escuchador->onTouchMoved = CC_CALLBACK_2(Nivel3::moverJugador, this);
    escuchador->onTouchEnded = [=](Touch* touch, Event* event) {};
    _eventDispatcher->addEventListenerWithSceneGraphPriority(escuchador, this);
}

void Nivel3::moverJugador(Touch* toque, Event* evento) {
    auto posicionToque = toque->getLocation();
    if (_cubito->getBoundingBox().containsPoint(posicionToque)) {
        if (posicionToque.x <= 490 && posicionToque.x >= -10) {
            _cubito->setPositionX(posicionToque.x);
        }
        if (posicionToque.y <= 210 && posicionToque.y >= 100) {
            _cubito->setPositionY(posicionToque.y);
        }
    }

}

void Nivel3::agregarVida() {
    Sprite* corazones[3];
    for (int i = 0; i < vida; i++) {
        corazones[i] = Sprite::create("Vida/CorazonLleno.png");
        corazones[i]->setScale(0.8, 0.8);
        corazones[i]->setPosition(Point(48 + (i * 33), 69));
        _corazones.push(corazones[i]);
        this->addChild(corazones[i], 150);
    }
}

void Nivel3::agregarCubitoNormal() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto cacher = SpriteFrameCache::getInstance();
    cacher->addSpriteFramesWithFile("Cache3.plist");

    // load all the animation frames into an array
    Vector<SpriteFrame*> frames;
    for (int i = 1; i <= 6; i++)
    {
        std::stringstream ss;
        ss << "PersonajeNormal" << i << ".png";
        frames.pushBack(cacher->getSpriteFrameByName(ss.str()));
    }

    _cubito = Sprite::createWithSpriteFrameName("PersonajeNormal1.png");
    _cubito->setTag(tagNum);
    _cubito->setScale(0.25, 0.25);
    _cubito->setPosition(Point(visibleSize.width / 2, 185));
    iniciarFisicaCubito(_cubito, tagNum);
    tagNum += 1;
    this->addChild(_cubito, 2);

    // play the animation
    Animation* anim = Animation::createWithSpriteFrames(frames, 0.10);
    _cubito->runAction(RepeatForever::create(Animate::create(anim)));
}

void Nivel3::agregarLuna() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto cacher = SpriteFrameCache::getInstance();
    cacher->addSpriteFramesWithFile("Cache3.plist");

    // load all the animation frames into an array
    Vector<SpriteFrame*> frames;
    for (int i = 1; i <= 8; i++)
    {
        std::stringstream ss;
        ss << "LunaSangre" << i << ".png";
        frames.pushBack(cacher->getSpriteFrameByName(ss.str()));
    }

    _luna = Sprite::createWithSpriteFrameName("LunaSangre1.png");
    _luna->setScale(0.40, 0.40);
    _luna->setPosition(Point((visibleSize.width / 10) * 7, (visibleSize.height / 20) * 17));
    this->addChild(_luna, 1);

    // play the animation
    Animation* anim = Animation::createWithSpriteFrames(frames, 0.3);
    _luna->runAction(RepeatForever::create(Animate::create(anim)));
}

void Nivel3::agregarNubes(float dt) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    int n = CCRANDOM_0_1() * 10000;
    n %= 4;
    //CCLOG("%d", n);

    if (n == 0) {
        agregarNube1();
    }
    else if (n == 1) {
        agregarNube2();
    }
    else if (n == 2) {
        agregarNube3();
    }
    else if (n == 3) {
        agregarNube4();
    }

    n = CCRANDOM_0_1() * 1000;
    n = (n / 3) + 400;
    //CCLOG("%d", n);
    CCLOG("NUBE %d", tagNum);
    _nubes[contNubes]->setScale(0.25, 0.25);
    _nubes[contNubes]->setPosition(Point(-200, n));
    moverNubes(_nubes[contNubes]);
    contNubes += 1;
}

void Nivel3::moverNubes(Sprite* sprite) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    sprite->runAction(
        Sequence::create(
            MoveTo::create(15, Point(700, sprite->getPositionY())),
            RemoveSelf::create(true),
            nullptr));

}

void Nivel3::agregarNube1() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto cacher1 = SpriteFrameCache::getInstance();
    cacher1->addSpriteFramesWithFile("Cache3.plist");

    // load all the animation frames into an array
    Vector<SpriteFrame*> frames;
    for (int i = 1; i <= 4; i++)
    {
        std::stringstream ss;
        ss << "NubesSangreA" << i << ".png";
        frames.pushBack(cacher1->getSpriteFrameByName(ss.str()));
    }

    _nubes[contNubes] = Sprite::createWithSpriteFrameName("NubesSangreA1.png");
    _nubes[contNubes]->setTag(tagNum);
    tagNum += 1;
    this->addChild(_nubes[contNubes], 3);

    // play the animation
    Animation* anim = Animation::createWithSpriteFrames(frames, 0.10);
    _nubes[contNubes]->runAction(RepeatForever::create(Animate::create(anim)));
}
void Nivel3::agregarNube2() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto cacher = SpriteFrameCache::getInstance();
    cacher->addSpriteFramesWithFile("Cache3.plist");

    // load all the animation frames into an array
    Vector<SpriteFrame*> frames;
    for (int i = 1; i <= 4; i++)
    {
        std::stringstream ss;
        ss << "NubesSangreB" << i << ".png";
        frames.pushBack(cacher->getSpriteFrameByName(ss.str()));
    }

    _nubes[contNubes] = Sprite::createWithSpriteFrameName("NubesSangreB1.png");
    _nubes[contNubes]->setTag(tagNum);
    tagNum += 1;
    this->addChild(_nubes[contNubes], 3);

    // play the animation
    Animation* anim = Animation::createWithSpriteFrames(frames, 0.10);
    _nubes[contNubes]->runAction(RepeatForever::create(Animate::create(anim)));
}
void Nivel3::agregarNube3() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto cacher = SpriteFrameCache::getInstance();
    cacher->addSpriteFramesWithFile("Cache3.plist");

    // load all the animation frames into an array
    Vector<SpriteFrame*> frames;
    for (int i = 1; i <= 4; i++)
    {
        std::stringstream ss;
        ss << "NubesSangreC" << i << ".png";
        frames.pushBack(cacher->getSpriteFrameByName(ss.str()));
    }

    _nubes[contNubes] = Sprite::createWithSpriteFrameName("NubesSangreC1.png");
    _nubes[contNubes]->setTag(tagNum);
    tagNum += 1;
    this->addChild(_nubes[contNubes], 3);

    // play the animation
    Animation* anim = Animation::createWithSpriteFrames(frames, 0.10);
    _nubes[contNubes]->runAction(RepeatForever::create(Animate::create(anim)));
}
void Nivel3::agregarNube4() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto cacher = SpriteFrameCache::getInstance();
    cacher->addSpriteFramesWithFile("Cache3.plist");

    // load all the animation frames into an array
    Vector<SpriteFrame*> frames;
    for (int i = 1; i <= 4; i++)
    {
        std::stringstream ss;
        ss << "NubesSangreD" << i << ".png";
        frames.pushBack(cacher->getSpriteFrameByName(ss.str()));
    }

    _nubes[contNubes] = Sprite::createWithSpriteFrameName("NubesSangreD1.png");
    _nubes[contNubes]->setTag(tagNum);
    tagNum += 1;
    this->addChild(_nubes[contNubes], 3);

    // play the animation
    Animation* anim = Animation::createWithSpriteFrames(frames, 0.10);
    _nubes[contNubes]->runAction(RepeatForever::create(Animate::create(anim)));
}

void Nivel3::agregarEnemigos(float dt) {
    auto visibleSize = Director::getInstance()->getVisibleSize();

    int m = CCRANDOM_0_1() * 100000;
    m %= 5;


    int n = random(45, 435);
    CCLOG("X ---> %d", m);

    if (m < 4) {
        agregarCirculito();
        _circulos[contCirculos]->setScale(0.25, 0.25);
        _circulos[contCirculos]->setPosition(Point(n, 850));
        contCirculos += 1;
    }
    else if (m == 4) {
        agregarTriangulito();
        _triangulos[contTriangulos]->setScale(0.25, 0.25);
        _triangulos[contTriangulos]->setPosition(Point(n, 850));
        contTriangulos += 1;
    }

    tagNum += 1;
}

void Nivel3::agregarCirculito() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto cacher1 = SpriteFrameCache::getInstance();
    cacher1->addSpriteFramesWithFile("Cache3.plist");

    // load all the animation frames into an array
    Vector<SpriteFrame*> frames;
    for (int i = 1; i <= 6; i++)
    {
        std::stringstream ss;
        ss << "Circulo" << i << ".png";
        frames.pushBack(cacher1->getSpriteFrameByName(ss.str()));
    }
    _circulos[contCirculos] = Sprite::createWithSpriteFrameName("Circulo1.png");

    _circulos[contCirculos]->setTag(tagNum);
    iniciarFisicaCirculos(_circulos[contCirculos], tagNum);
    this->addChild(_circulos[contCirculos], 2);
    _efectoBurbuja = AudioEngine::play2d("Audios/EfectoBurbuja.mp3", false, _volumenBurbuja);

    // play the animation
    Animation* anim = Animation::createWithSpriteFrames(frames, 0.10);
    _circulos[contCirculos]->runAction(RepeatForever::create(Animate::create(anim)));
}

void Nivel3::agregarTriangulito() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto cacher1 = SpriteFrameCache::getInstance();
    cacher1->addSpriteFramesWithFile("Cache3.plist");

    // load all the animation frames into an array
    Vector<SpriteFrame*> frames;
    for (int i = 1; i <= 6; i++)
    {
        std::stringstream ss;
        ss << "Triangulo" << i << ".png";
        frames.pushBack(cacher1->getSpriteFrameByName(ss.str()));
    }
    _triangulos[contTriangulos] = Sprite::createWithSpriteFrameName("Triangulo1.png");

    _triangulos[contTriangulos]->setTag(tagNum);
    iniciarFisicaTriangulos(_triangulos[contTriangulos], tagNum);
    this->addChild(_triangulos[contTriangulos], 2);
    _efectoBurbuja = AudioEngine::play2d("Audios/EfectoBurbuja.mp3", false, _volumenBurbuja);

    // play the animation
    Animation* anim = Animation::createWithSpriteFrames(frames, 0.10);
    _triangulos[contTriangulos]->runAction(RepeatForever::create(Animate::create(anim)));
}

bool Nivel3::onContactBegin(cocos2d::PhysicsContact& contact) {
    PhysicsBody* a = contact.getShapeA()->getBody();
    PhysicsBody* b = contact.getShapeB()->getBody();

    if ((CUBITO_COLLISION_BITMASK == a->getCollisionBitmask() && ENEMIGOS_COLLISION_BITMASK == b->getCollisionBitmask()) || (CUBITO_COLLISION_BITMASK == b->getCollisionBitmask() && ENEMIGOS_COLLISION_BITMASK == a->getCollisionBitmask())) {
        _efectoChoque = AudioEngine::play2d("Audios/EfectoChoque.mp3", false, _volumenChoque);
        if (a->getCollisionBitmask() == ENEMIGOS_COLLISION_BITMASK) {
            a->setCollisionBitmask(ENEMIGOS_AFTER_PUNCH_COLLISION_BITMASK);
        }
        else if (b->getCollisionBitmask() == ENEMIGOS_COLLISION_BITMASK) {
            b->setCollisionBitmask(ENEMIGOS_AFTER_PUNCH_COLLISION_BITMASK);
        }

    }

    else if ((ENEMIGOS_COLLISION_BITMASK == a->getCollisionBitmask() && ENEMIGOS_COLLISION_BITMASK == b->getCollisionBitmask()) || (ENEMIGOS_COLLISION_BITMASK == b->getCollisionBitmask() && ENEMIGOS_COLLISION_BITMASK == a->getCollisionBitmask())) {
        _efectoChoque = AudioEngine::play2d("Audios/EfectoChoque.mp3", false, _volumenChoque);
    }
    else if ((ENEMIGOS_AFTER_PUNCH_COLLISION_BITMASK == a->getCollisionBitmask() && ENEMIGOS_COLLISION_BITMASK == b->getCollisionBitmask()) || (ENEMIGOS_AFTER_PUNCH_COLLISION_BITMASK == b->getCollisionBitmask() && ENEMIGOS_COLLISION_BITMASK == a->getCollisionBitmask())) {
        _efectoChoque = AudioEngine::play2d("Audios/EfectoChoque.mp3", false, _volumenChoque);
        if (a->getCollisionBitmask() == ENEMIGOS_COLLISION_BITMASK) {
            a->setCollisionBitmask(ENEMIGOS_AFTER_PUNCH_COLLISION_BITMASK);
        }
        else if (b->getCollisionBitmask() == ENEMIGOS_COLLISION_BITMASK) {
            b->setCollisionBitmask(ENEMIGOS_AFTER_PUNCH_COLLISION_BITMASK);
        }
    }
    else if ((ENEMIGOS_AFTER_PUNCH_COLLISION_BITMASK == a->getCollisionBitmask() && CUBITO_COLLISION_BITMASK == b->getCollisionBitmask()) || (ENEMIGOS_AFTER_PUNCH_COLLISION_BITMASK == b->getCollisionBitmask() && CUBITO_COLLISION_BITMASK == a->getCollisionBitmask())) {
        _efectoChoque = AudioEngine::play2d("Audios/EfectoChoque.mp3", false, _volumenChoque);
    }

    else if ((BARRERAS_LATERALES_COLLISION_BITMASK == a->getCollisionBitmask() && ENEMIGOS_COLLISION_BITMASK == b->getCollisionBitmask()) || (BARRERAS_LATERALES_COLLISION_BITMASK == b->getCollisionBitmask() && ENEMIGOS_COLLISION_BITMASK == a->getCollisionBitmask())) {
        _efectoChoque = AudioEngine::play2d("Audios/EfectoChoque.mp3", false, _volumenChoque);
    }
    else if ((ENEMIGOS_AFTER_PUNCH_COLLISION_BITMASK == a->getCollisionBitmask() && BARRERAS_LATERALES_COLLISION_BITMASK == b->getCollisionBitmask()) || (ENEMIGOS_AFTER_PUNCH_COLLISION_BITMASK == b->getCollisionBitmask() && BARRERAS_LATERALES_COLLISION_BITMASK == a->getCollisionBitmask())) {
        _efectoChoque = AudioEngine::play2d("Audios/EfectoChoque.mp3", false, _volumenChoque);
    }


    else if ((PUNTO_SCORE_BITMASK == a->getCollisionBitmask() && ENEMIGOS_AFTER_PUNCH_COLLISION_BITMASK == b->getCollisionBitmask()) || (PUNTO_SCORE_BITMASK == b->getCollisionBitmask() && ENEMIGOS_AFTER_PUNCH_COLLISION_BITMASK == a->getCollisionBitmask())) {
        _efectoPunto = AudioEngine::play2d("Audios/EfectoPunto.mp3", false, _volumenPunto);
        score += 1;
        actualizarScore();
        if (a->getCollisionBitmask() == ENEMIGOS_AFTER_PUNCH_COLLISION_BITMASK) {
            this->removeChildByTag(a->getTag());
        }
        else if (b->getCollisionBitmask() == ENEMIGOS_AFTER_PUNCH_COLLISION_BITMASK) {
            this->removeChildByTag(b->getTag());
        }
    }

    else if (((BARRERAS_ARRIBA_COLLISION_BITMASK == a->getCollisionBitmask() && ENEMIGOS_COLLISION_BITMASK == b->getCollisionBitmask()) || (BARRERAS_ARRIBA_COLLISION_BITMASK == b->getCollisionBitmask() && ENEMIGOS_COLLISION_BITMASK == a->getCollisionBitmask())) ||
        ((BARRERAS_ARRIBA_COLLISION_BITMASK == a->getCollisionBitmask() && ENEMIGOS_AFTER_PUNCH_COLLISION_BITMASK == b->getCollisionBitmask()) || (BARRERAS_ARRIBA_COLLISION_BITMASK == b->getCollisionBitmask() && ENEMIGOS_AFTER_PUNCH_COLLISION_BITMASK == a->getCollisionBitmask()))) {
        _efectoBurbuja = AudioEngine::play2d("Audios/EfectoBurbuja.mp3", false, _volumenBurbuja);
        if (a->getCollisionBitmask() == ENEMIGOS_AFTER_PUNCH_COLLISION_BITMASK) {
            this->removeChildByTag(a->getTag());
        }
        else if (b->getCollisionBitmask() == ENEMIGOS_AFTER_PUNCH_COLLISION_BITMASK) {
            this->removeChildByTag(b->getTag());
        }
    }

    else if (((BARRERAS_ABAJO_COLLISION_BITMASK == a->getCollisionBitmask() && ENEMIGOS_COLLISION_BITMASK == b->getCollisionBitmask()) || (BARRERAS_ABAJO_COLLISION_BITMASK == b->getCollisionBitmask() && ENEMIGOS_COLLISION_BITMASK == a->getCollisionBitmask())) ||
        ((BARRERAS_ABAJO_COLLISION_BITMASK == a->getCollisionBitmask() && ENEMIGOS_AFTER_PUNCH_COLLISION_BITMASK == b->getCollisionBitmask()) || (BARRERAS_ABAJO_COLLISION_BITMASK == b->getCollisionBitmask() && ENEMIGOS_AFTER_PUNCH_COLLISION_BITMASK == a->getCollisionBitmask()))) {

        _efectoDannio = AudioEngine::play2d("Audios/EfectoDannio.mp3", false, _volumenDannio);
        vida -= 1;
        if (_corazones.empty() != true) {
            this->removeChild(_corazones.top());
            _corazones.pop();
            if (a->getCollisionBitmask() == ENEMIGOS_COLLISION_BITMASK || a->getCollisionBitmask() == ENEMIGOS_AFTER_PUNCH_COLLISION_BITMASK) {
                this->removeChildByTag(a->getTag());
            }
            else if (b->getCollisionBitmask() == ENEMIGOS_COLLISION_BITMASK || b->getCollisionBitmask() == ENEMIGOS_AFTER_PUNCH_COLLISION_BITMASK) {
                this->removeChildByTag(b->getTag());
            }
        }
        if (vida == 0) {
            crearEscenaDerrota();
        }
    }
    return true;
}

void Nivel3::update(float dt) {
    //Time
    if (time <= 0) {
        time = 0;
        crearEscenaIntermediaFinal();
    }
    else {
        time -= dt;
        actualizarTimer();
    }


}



void Nivel3::ConfigurationButton(Nivel3::Ref* pSender) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    CCLOG("Configuracion");
    _efectoSeleccionar = AudioEngine::play2d("Audios/EfectoSeleccionar.mp3", false, _volumenSeleccionar);
    Director::getInstance()->pause();


    //DesplegarPantallaPausa
    _menuPausa = Sprite::create("ImagenesMenu/PantallaPausa.png");
    _menuPausa->setScale(0.52, 0.52);
    _menuPausa->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(_menuPausa, 100000);

    //AgregarBotones
    botonContinue = MenuItemImage::create("ImagenesMenu/ContinueBoton.png", "ImagenesMenu/ContinueBotonS.png", CC_CALLBACK_1(Nivel3::ContinueButton, this));
    botonHighsScore = MenuItemImage::create("ImagenesMenu/HighScoreBoton.png", "ImagenesMenu/HighScoreBotonS.png", CC_CALLBACK_1(Nivel3::HighsScoreButton, this));
    botonMenu = MenuItemImage::create("ImagenesMenu/BackMenu.png", "ImagenesMenu/BackMenuS.png", CC_CALLBACK_1(Nivel3::MenuButton, this));
    botonClose = MenuItemImage::create("ImagenesMenu/CloseBoton.png", "ImagenesMenu/CloseBotonS.png", CC_CALLBACK_1(Nivel3::CloseButton, this));

    botonContinue->setScale(0.5, 0.5);
    botonHighsScore->setScale(0.5, 0.5);
    botonMenu->setScale(0.5, 0.5);
    botonClose->setScale(0.5, 0.5);

    botonContinue->setPosition(Point(visibleSize.width / 2, 400));
    botonHighsScore->setPosition(Point(visibleSize.width / 2, 330));
    botonMenu->setPosition(Point(visibleSize.width / 2, 260));
    botonClose->setPosition(Point(visibleSize.width / 2, 190));


    menuPause = Menu::create(botonContinue, botonHighsScore, botonMenu, botonClose, NULL);
    menuPause->setPosition(Point(0, 0));
    this->addChild(menuPause, 100000);


}

void Nivel3::ContinueButton(Nivel3::Ref* pSender) {
    Director::getInstance()->resume();
    _efectoSeleccionar = AudioEngine::play2d("Audios/EfectoSeleccionar.mp3", false, _volumenSeleccionar);
    this->removeChild(_menuPausa);
    this->removeChild(botonContinue);
    this->removeChild(botonHighsScore);
    this->removeChild(botonMenu);
    this->removeChild(botonClose);
    this->removeChild(menuPause);
    CCLOG("Continue");

}

void Nivel3::HighsScoreButton(Nivel3::Ref* pSender) {
    _efectoSeleccionar = AudioEngine::play2d("Audios/EfectoSeleccionar.mp3", false, _volumenSeleccionar);
    this->removeChild(_menuPausa);
    this->removeChild(botonContinue);
    this->removeChild(botonHighsScore);
    this->removeChild(botonMenu);
    this->removeChild(botonClose);
    this->removeChild(menuPause);
    auto visibleSize = Director::getInstance()->getVisibleSize();
    CCLOG("HighScore");

    //Desplegar pantalla de menu
    _highScoreMenuPause = Sprite::create("ImagenesMenu/HighScoreMenuPause.png");
    _highScoreMenuPause->setScale(0.52, 0.52);
    _highScoreMenuPause->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(_highScoreMenuPause, 100000);

    //Boton
    botonCloseHigh = MenuItemImage::create("ImagenesMenu/CloseBoton.png", "ImagenesMenu/CloseBotonS.png", CC_CALLBACK_1(Nivel3::CloseButtonHigh, this));
    botonCloseHigh->setScale(0.5, 0.5);
    botonCloseHigh->setPosition(Point(visibleSize.width / 2, 200));

    menuPauseHigh = Menu::create(botonCloseHigh, NULL);
    menuPauseHigh->setPosition(Point(0, 0));
    this->addChild(menuPauseHigh, 100000);

    //Label
    std::stringstream ss;
    ss << highPuntuation;
    scoreLabelHigh = Label::createWithTTF(ss.str(), "fonts/Minecrafter.ttf", 60);
    scoreLabelHigh->setColor(Color3B::WHITE);
    scoreLabelHigh->setPosition(Point(visibleSize.width / 2, 375));
    this->addChild(scoreLabelHigh, 100000);

}

void Nivel3::MenuButton(Nivel3::Ref* pSender) {
    Director::getInstance()->resume();
    _efectoSeleccionar = AudioEngine::play2d("Audios/EfectoSeleccionar.mp3", false, _volumenSeleccionar);
    auto visibleSize = Director::getInstance()->getVisibleSize();
    CCLOG("Menu");
    AudioEngine::stop(_musicaFondoNivel1);
    def1 = UserDefault::getInstance();
    def1->setIntegerForKey("SCOREACTUAL", 0);
    def1->flush();

    //Vida
    def2 = UserDefault::getInstance();
    def2->setIntegerForKey("VIDA", 3);
    def2->flush();
    auto menuPrincipal = HelloWorld::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, menuPrincipal));

}

void Nivel3::CloseButton(Nivel3::Ref* pSender) {
    Director::getInstance()->resume();
    _efectoSeleccionar = AudioEngine::play2d("Audios/EfectoSeleccionar.mp3", false, _volumenSeleccionar);
    auto visibleSize = Director::getInstance()->getVisibleSize();
    CCLOG("Close");
    def1 = UserDefault::getInstance();
    def1->setIntegerForKey("SCOREACTUAL", 0);
    def1->flush();

    //Vida
    def2 = UserDefault::getInstance();
    def2->setIntegerForKey("VIDA", 3);
    def2->flush();
    Director::getInstance()->end();
}

void Nivel3::CloseButtonHigh(Nivel3::Ref* pSender) {
    Director::getInstance()->resume();
    _efectoSeleccionar = AudioEngine::play2d("Audios/EfectoSeleccionar.mp3", false, _volumenSeleccionar);
    auto visibleSize = Director::getInstance()->getVisibleSize();
    CCLOG("CloseHighScores");

    this->removeChild(_highScoreMenuPause);
    this->removeChild(botonCloseHigh);
    this->removeChild(menuPauseHigh);
    this->removeChild(scoreLabelHigh);
    ConfigurationButton(this);
}

void Nivel3::PlayIntermedio(Nivel3::Ref* pSender) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    CCLOG("PlayIntermedio");
    _efectoSeleccionar = AudioEngine::play2d("Audios/EfectoSeleccionar.mp3", false, _volumenSeleccionar);

    this->removeAllChildren();
    crearEscena();
}

void Nivel3::PlayIntermedioFinal(Nivel3::Ref* pSender) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    CCLOG("PlayIntermedioFinal");
    _efectoSeleccionar = AudioEngine::play2d("Audios/EfectoSeleccionar.mp3", false, _volumenSeleccionar);
    this->removeAllChildren();
    auto menuPrincipal = HelloWorld::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, menuPrincipal));
}

void Nivel3::MenuDerrota(Nivel3::Ref* pSender) {
    _efectoSeleccionar = AudioEngine::play2d("Audios/EfectoSeleccionar.mp3", false, _volumenSeleccionar);
    auto visibleSize = Director::getInstance()->getVisibleSize();
    CCLOG("MenuDerrota");
    AudioEngine::stop(_musicaFondoNivel1);
    auto menuPrincipal = HelloWorld::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, menuPrincipal));
}
#ifndef __NIVEL_3_H__
#define __NIVEL_3_H__

#define CUBITO_COLLISION_BITMASK 0x000001
#define ENEMIGOS_COLLISION_BITMASK 0x000002
#define ENEMIGOS_AFTER_PUNCH_COLLISION_BITMASK 0x000003
#define BARRERAS_LATERALES_COLLISION_BITMASK 0x000004
#define BARRERAS_ABAJO_COLLISION_BITMASK 0x000005
#define BARRERAS_ARRIBA_COLLISION_BITMASK 0x000006
#define PUNTO_SCORE_BITMASK 0x000000

#include "cocos2d.h"

class Nivel3 : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(Nivel3);


    float time = 0.0f;
    int score = 0;
    int vida = 3;
    int tagNum = 1;
    int contCirculos = 0;
    int contTriangulos = 0;
    int contNubes = 0;
    int contEnemigosBody = 0;
    bool crear = false;

    //Escena
    void Nivel3::crearEscena();
    void Nivel3::crearEscenaIntermedia();
    void Nivel3::crearEscenaIntermediaFinal();
    void Nivel3::crearEscenaDerrota();

    //Botones
    void ConfigurationButton(Ref* pSender);
    cocos2d::MenuItemImage* botonConfiguracion;
    cocos2d::Menu* menuConfiguracion;

    void ContinueButton(Ref* pSender);
    cocos2d::MenuItemImage* botonContinue;

    void HighsScoreButton(Ref* pSender);
    cocos2d::MenuItemImage* botonHighsScore;

    void MenuButton(Ref* pSender);
    cocos2d::MenuItemImage* botonMenu;

    void CloseButton(Ref* pSender);
    cocos2d::MenuItemImage* botonClose;

    cocos2d::Menu* menuPause;


    void Nivel3::CloseButtonHigh(Ref* pSender);
    cocos2d::MenuItemImage* botonCloseHigh;
    cocos2d::Menu* menuPauseHigh;

    void Nivel3::PlayIntermedio(Ref* pSender);
    cocos2d::MenuItemImage* botonPlayIntermedio;
    cocos2d::Menu* menuPlayIntermedio;

    void Nivel3::PlayIntermedioFinal(Ref* pSender);
    cocos2d::MenuItemImage* botonPlayIntermedioFinal;
    cocos2d::Menu* menuPlayIntermedioFinal;

    void Nivel3::MenuDerrota(Ref* pSender);
    cocos2d::MenuItemImage* botonMenuDerrota;
    cocos2d::Menu* menuMenuDerrota;

    //Musica
    int _musicaFondoNivel1;

    //Efectos
    int _efectoChoque;
    int _efectoDannio;
    int _efectoPunto;
    int _efectoSeleccionar;
    int _efectoDerrota;
    int _efectoVictoria;
    int _efectoBurbuja;

    //Volumen
    float _volumenChoque = 0.7;
    float _volumenPunto = 0.5;
    float _volumenMusica = 0.5;
    float _volumenDannio = 0.7;
    float _volumenSeleccionar = 0.9;
    float _volumenBurbuja = 0.8;

    //Score
    cocos2d::Label* scoreLabelHigh;
    cocos2d::Label* scoreLabel;
    cocos2d::Label* timerLabel;

    //Sprites
    cocos2d::Sprite* _spriteFondoIntermedio;
    cocos2d::Sprite* _highScoreMenuPause;
    cocos2d::Sprite* _settingsMenuPause;
    cocos2d::Sprite* _menuPausa;
    cocos2d::Sprite* _timer;
    cocos2d::Sprite* _barreras[4];
    cocos2d::Sprite* _agujeroNegro;
    cocos2d::Sprite* mySprite;
    cocos2d::Sprite* _cubito;
    cocos2d::Sprite* _luna;
    cocos2d::Sprite* circuloIntermedio;
    cocos2d::Sprite* trianguloIntermedio;
    std::stack<cocos2d::Sprite*> _corazones;
    cocos2d::Sprite* _circulos[10000];
    cocos2d::Sprite* _triangulos[10000];
    cocos2d::Sprite* _nubes[10000];

    //Funciones de agregar
    void Nivel3::agregarConfiguracion();
    void Nivel3::agregarTimer();
    void Nivel3::agregarScore();
    void Nivel3::agregarVida();
    void Nivel3::agregarBarrerasContension();
    void Nivel3::agregarCubitoNormal();
    void Nivel3::agregarLuna();
    void Nivel3::agregarNubes(float dt);
    void Nivel3::agregarNube1();
    void Nivel3::agregarNube2();
    void Nivel3::agregarNube3();
    void Nivel3::agregarNube4();
    void Nivel3::agregarEnemigos(float dt);
    void Nivel3::agregarCirculito();
    void Nivel3::agregarTriangulito();

    //Funciones Mover
    void Nivel3::moverNubes(cocos2d::Sprite* sprite);
    void Nivel3::moverJugador(cocos2d::Touch* toque, cocos2d::Event* evento);


    //Funciones de movimiento de jugador
    void Nivel3::iniciarTouch();


    //Cuerpos
    cocos2d::PhysicsBody* _cuboBody;
    cocos2d::PhysicsBody* _enemigosBody[10000];
    cocos2d::PhysicsBody* _barrerasBody[4];

    //Funciones de físicas
    void Nivel3::agregarPuntoScore();
    void Nivel3::iniciarFisicaCubito(cocos2d::Sprite* sprite, int n);
    void Nivel3::iniciarFisicaCirculos(cocos2d::Sprite* sprite, int n);
    void Nivel3::iniciarFisicaTriangulos(cocos2d::Sprite* sprite, int n);
    bool Nivel3::onContactBegin(cocos2d::PhysicsContact& contact);

    //Update
    void Nivel3::update(float dt);
    void Nivel3::actualizarScore();
    void Nivel3::actualizarTimer();

    //Pasar de nivel
        //void nextLevel(Ref* pSender);

    //Datos
    void Nivel3::agregarDatos();

    //UserDefault
    cocos2d::UserDefault* def;
    cocos2d::UserDefault* def1;
    cocos2d::UserDefault* def2;
    int highPuntuation;


};

#endif // __NIVEL_3_H__

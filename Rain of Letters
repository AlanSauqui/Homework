import ddf.minim.*;

//Variables iniciales
Minim minim;
AudioPlayer musicaFondo;
AudioSample efecto;
AudioSample dano;
AudioSample nivelUp;
PImage corazon;
PImage gameOver;
PImage fondoComienzo;
PImage fondoJuego;
PImage fondoPausa;
PImage fondoFinal;
PFont minecraft;
int x[]=new int[10];
int y[]=new int[10];
int alturaArriba=35;
int contador=0;
int nivel=0;
int vida=3;
int repetido=0;
int limiteArrojador=20;
int arrojador=1;
int velocidad=2;
int tiempo=millis();
String abecedario="abcdefghijklmnopqrstuvwxyz";
char abc[]=new char[10];

boolean pausa=false;
boolean inicio=false;

void setup()
{
  size(1000,600);
  //background(0);
  //Texto de Score y puntuación
  //Texto de vida restante
  for(int i=0;i<10;i++)
  {
    abc[i]=' ';
  }
  //Imágenes
  corazon=loadImage("Corazonmine.png");
  fondoJuego=loadImage("fondoJuego.png");
  fondoComienzo=loadImage("fondoInicioOpcional.png");
  fondoJuego=loadImage("fondoJuego.png");
  fondoPausa=loadImage("fondoPausa.png");
  fondoFinal=loadImage("fondoFinal.png");
  
  //Fuente
  minecraft=loadFont("Minecrafter-48.vlw");
  
  //Audio
  minim=new Minim(this);
  musicaFondo=minim.loadFile("minecraft.mp3");
  efecto=minim.loadSample("burbuja.mp3");
  nivelUp=minim.loadSample("nivelUp.mp3");
  dano=minim.loadSample("daño.mp3");
  musicaFondo.setGain(-4);
  musicaFondo.loop();
  y[0]=alturaArriba;
}

void draw()
{
  textFont(minecraft);
  //Inicio
  if((inicio==false)&&(vida==3))
  {
    background(0);
    image(fondoComienzo,0,0,width,height);
    image(corazon,797,318,40,40);
    image(corazon,854,318,40,40);
    image(corazon,911,318,40,40);
  }
  //Muerte
  else if((inicio==false)&&(vida==0))
  {
    //Fondos durante la muerte
    background(0);
      image(fondoFinal,0,0,width,height);
      
      //Contador y nivel
        fill(0);
        textSize(40);
        textAlign(CENTER);
        text(contador,874,150);
        text(nivel,874,560);
        fill(255);
        text(contador,226,355);
        text(nivel,535,355);
  }
  //Juego
  else if((inicio==true)&&(vida>0))
  {
    if(pausa==true)
    {
      //Fondos durante la pausa
      image(fondoPausa,0,0,width,height);
      
      //Contador y nivel
        fill(0);
        textSize(40);
        textAlign(CENTER);
        text(contador,874,150);
        text(nivel,874,560);
        //Vida
        if(vida==3)
        {
          image(corazon,797,318,40,40);
          image(corazon,854,318,40,40);
          image(corazon,911,318,40,40);
        }
        else if(vida==2)
        {
          image(corazon,797,318,40,40);
          image(corazon,854,318,40,40);
        }
        else if(vida==1)
        {
          image(corazon,797,318,40,40);
        }
    }
    else
    {
      //Rellenado de posición aleatoria
      for(int i=0;i<10;i++)
      {
        if(x[i]==0)
        {
          x[i]=(int)(Math.random()*660)+45;
        }
      }
      
      //Rellenado de letras
      for(int i=0;i<10;i++)
      {
        if(abc[i]==' ')
        {
          abc[i]=abecedario.charAt((int)random(26));
          //Filtro de repetición
          repetido=1;
          while(repetido>0)
          {
            repetido=0;
            for(int j=0;j<10;j++)
            {
              if(j!=i)
              {
                if(abc[i]==abc[j])
                {
                  repetido++;
                  abc[i]=abecedario.charAt((int)random(26));
                }
              }
            }
          }
        }
      }
      
      
      
      //Fondo principal
      //background(0);
              //Lluvia de letras
              fill(0,0,0,60);
              rect(0,0,width,height);
              fill(255);
              textSize(40);
              //text(abc.charAt(0),x[0],y[0]);
              for(int i=0;i<arrojador;i++)
              {
                text(abc[i],x[i],y[i]);
              }
                //Aumento en Y
                for(int i=0;i<arrojador;i++)
                {
                  if(y[i]<=567)
                  {
                    y[i]+=velocidad;
                  }
                  else
                  {
                    y[i]=alturaArriba;
                    abc[i]=abecedario.charAt((int)random(26));
                    vida--;
                    dano.setGain(-1);
                    dano.trigger();
                  }
                }
                //Arrojador de letras
                if((contador==limiteArrojador)&&(limiteArrojador<200))
                {
                  arrojador++;
                  limiteArrojador+=20;
                  nivel++;
                  nivelUp.setGain(-4);
                  nivelUp.trigger();
                    
                  //Velocidades incrementándose
                  if(contador==100)
                  {
                    velocidad=2;
                  }
                }
                //Modo Dios
                if((contador==200)&&(nivel==9))
                {
                  nivel=10;
                  velocidad=3;
                  nivelUp.setGain(-10);
                  nivelUp.trigger();
                }
                
      //Fondos durante el juego
      image(fondoJuego,0,0,width,height);
        //Contador y nivel
        fill(0);
        textSize(40);
        textAlign(CENTER);
        text(contador,874,150);
        text(nivel,874,560);
        //Vida
        if(vida<=0)
        {
           inicio=false;
        }
        else if(vida==3)
        {
          image(corazon,797,318,40,40);
          image(corazon,854,318,40,40);
          image(corazon,911,318,40,40);
        }
        else if(vida==2)
        {
          image(corazon,797,318,40,40);
          image(corazon,854,318,40,40);
        }
        else if(vida==1)
        {
          image(corazon,797,318,40,40);
        }
    }
  }
}

void keyPressed()
{
  if((pausa==false)&&(inicio==true))
  {
    for(int i=0;i<arrojador;i++)
    {
      if(key==abc[i])
      {
        abc[i]=' ';
        contador++;
        y[i]=alturaArriba;
        x[i]=0;
        efecto.trigger();
      }
    }
  }
  
  if((keyCode==ENTER)&&(vida==3))
   {
     inicio=true;
   }
   else if((keyCode==ENTER)&&(vida==0))
   {
     inicio=true;
     vida=3;
     nivel=0;
     contador=0;
     arrojador=1;
     velocidad=2;
     for(int i=0;i<10;i++)
     {
       y[i]=alturaArriba;
     }
   }
   
   if((keyCode==SHIFT)&&(pausa==false)&&(inicio==true))
   {
     pausa=true;
   }
   else if((keyCode==SHIFT)&&(pausa==true)&&(inicio==true))
   {
     pausa=false;
   }
}

void mouseClicked()
{
  int ratonX,ratonY;
  ratonX=mouseX;
  ratonY=mouseY;
  System.out.println(ratonX+","+ratonY);
}

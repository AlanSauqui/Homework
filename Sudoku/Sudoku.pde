//Variables controladoras generales

int resolver=0;
int borrar=1;

//Imágenes
PImage fondo;

//Variables globales
int tamanoTexto=100;
int relleno=0;
int numDeCasillas=9;
int contador=-1;
int contador1=-1;
int[][] casillas=/*{{0,0,0,1,0,0,0,0,0},
                 {0,0,0,3,0,0,0,0,0},
                 {0,0,0,6,0,0,0,0,0},
                 {0,0,0,0,0,0,0,0,6},
                 {0,0,0,0,0,0,0,0,0},
                 {0,0,5,0,0,0,0,0,0},
                 {0,0,0,0,0,0,0,0,0},
                 {0,0,0,0,0,0,0,0,0},
                 {0,4,0,0,0,0,9,0,0}};*/

              /* {{0,4,7,0,0,0,5,3,0},
                 {5,0,0,8,0,7,0,0,9},
                 {3,0,0,0,5,0,0,0,2},
                 {2,0,6,0,0,0,4,0,7},
                 {1,0,0,6,0,2,0,0,5},
                 {0,9,0,0,8,0,0,6,0},
                 {0,0,4,0,0,0,1,0,0},
                 {0,0,0,5,0,8,0,0,0},
                 {0,0,0,0,6,0,0,0,0}};*/
                 
                {{9,6,0,1,0,4,0,5,8},
                 {0,7,8,3,2,5,6,0,9},
                 {2,5,0,6,0,0,7,0,1},
                 {8,0,1,4,0,7,5,0,6},
                 {0,9,6,0,0,2,3,0,7},
                 {7,0,5,9,6,1,0,2,4},
                 {5,0,0,7,1,0,4,6,2},
                 {3,1,7,2,0,6,9,0,0},
                 {0,4,0,5,0,8,0,7,3}};
int[][] casillas1=new int[numDeCasillas][numDeCasillas];
int[] rectangulosFila=new int[10000];
int[] rectangulosColumna=new int[10000];
int[][][] movimientos=new int[100000][numDeCasillas][numDeCasillas];
                 
void setup()
{
  size(1280,720);
  background(0);
  //Rellenado de Casillas1
  for(int i=0;i<numDeCasillas;i++)
  {
    for(int j=0;j<numDeCasillas;j++)
    {
      casillas1[i][j]=casillas[i][j];
    }
  }
  
  //Imágenes
  fondo=loadImage("Sudoku1.PNG");
  image(fondo,0,0,width,height);
  tablero();
}

void draw()
{
  background(0);
  tablero();
  
  //Iniciar
  if((resolver==0)&&(borrar==1))
  {
    tablero();
    numeroMov();
    texto();
  }
  
  //Resolver
  if((resolver==1)&&(borrar==0))
    {
      backtracking();
    //texto();
    if(contador1<contador)
    {
      tablero();
      numeroMov();
      contador1++;
      //print_array();
      
      //Casillas
      for(int i=0,recX=60;i<numDeCasillas;i++,recX+=70)
      {
        if((i==3)|(i==6))
        {
          recX+=20;
        }
        for(int j=0,recY=80;j<numDeCasillas;j++,recY+=68)
        {
          if((j==3)|(j==6))
          {
            recY+=27;
          }
          if(movimientos[contador1][i][j]>0)
          {
            fill(255);
            textAlign(CENTER);
            textSize(50);
            text(movimientos[contador1][i][j],recX,recY);
          }
        }
      }
      delay(0);
    }
    else
    {
      tablero();
      numeroMov();
      texto();
    }
  }
}

boolean backtracking()
{
  for(int i=0;i<numDeCasillas;i++)
  {
    for(int j=0;j<numDeCasillas;j++)
    {
      if(casillas[i][j]==0)
      {
        for(int k=1;k<10;k++)
        {
          if(validaciones(i,j,k))
          {
            contador++;
        for(int m=0;m<numDeCasillas;m++)
              {
                for(int n=0;n<numDeCasillas;n++)
                {
                  movimientos[contador][n][m]=casillas[m][n];
                }
              }
                
            casillas[i][j]=k;
            if(backtracking()==true)
            {
              return true;
            }
            else
            {
              casillas[i][j]=0;
            }
          }
        }
        return false;
      }
    }
  }
  return true;
}

boolean validaciones(int fila,int columna,int evaluar)
{
  //Movimientos reales
  /*contador++;
        for(int m=0;m<numDeCasillas;m++)
              {
                for(int n=0;n<numDeCasillas;n++)
                {
                  movimientos[contador][n][m]=casillas[m][n];
                }
              }*/         
  //Columnas y filas
  for(int i=0;i<9;i++)
  {
    if((casillas[i][columna]==evaluar)||(casillas[fila][i]==evaluar)||(gruposNueve(fila,columna,evaluar)))
    {
      return false;
    }
  }
  return true;
}

boolean gruposNueve(int fila,int columna,int evaluar)
{
  fila=fila-(fila%3);
  columna=columna-(columna%3);
  for(int i=fila;i<fila+3;i++)
  {
    for(int j=columna;j<columna+3;j++)
    {
      if(casillas[i][j]==evaluar)
      {
        return true;
      }
    }
  }
  return false;
}

void print_array()
{
  print(contador1+1);
  print("[ ");
  for(int i=0;i<numDeCasillas;i++)
  {
    for(int j=0;j<numDeCasillas;j++)
    {
      print(movimientos[contador1][j][i]);
      print(" ");
    }
    println();
  }
  println("]");
}

void tablero()
{
  image(fondo,0,0,width,height);
}

void texto()
{
  if((resolver==0)&&(borrar==1))
  {
    for(int i=0,recX=60;i<numDeCasillas;i++,recX+=70)
      {
        if((i==3)|(i==6))
        {
          recX+=20;
        }
        for(int j=0,recY=80;j<numDeCasillas;j++,recY+=68)
        {
          if((j==3)|(j==6))
          {
            recY+=27;
          }
          if(casillas1[j][i]>0)
          {
            fill(255);
            textAlign(CENTER);
            textSize(50);
            text(casillas1[j][i],recX,recY);
          }
        }
      }
    delay(0);
  }
  else
  {
    for(int i=0,recX=60;i<numDeCasillas;i++,recX+=70)
      {
        if((i==3)|(i==6))
        {
          recX+=20;
        }
        for(int j=0,recY=80;j<numDeCasillas;j++,recY+=68)
        {
          if((j==3)|(j==6))
          {
            recY+=27;
          }
          fill(255);
          textAlign(CENTER);
          textSize(50);
          text(casillas[j][i],recX,recY);
        }
      }
    delay(0);
  }
}

void numeroMov()
{
  textAlign(CENTER);
  textSize(60);
  text(contador1+1,987,210);
}

void mouseClicked()
{
  int ratonX,ratonY;
  ratonX=mouseX;
  ratonY=mouseY;
  System.out.printf(ratonX+","+ratonY+"\n");
  
  if((mouseX>=730)&&(mouseX<=1244)&&(mouseY>=486)&&(mouseY<=590))
  {
    borrar=1; 
    resolver=0;
    //Vaciado del arreglo original
    for(int i=0;i<numDeCasillas;i++)
    {
      for(int j=0;j<numDeCasillas;j++)
      {
        casillas[i][j]=casillas1[i][j];
      }
    }
    //Vaciado del arreglo soluciones
    for(int o=0;o<contador;o++)
    {
      for(int m=0;m<numDeCasillas;m++)
      {
        for(int n=0;n<numDeCasillas;n++)
        {
          movimientos[o][n][m]=0;
         }
      }
    }          
    //Reinicio contador1
    contador1=-1;
    contador=-1;   
  }
  if((mouseX>=730)&&(mouseX<=1244)&&(mouseY>=594)&&(mouseY<=698))
  {
    resolver=1; 
    borrar=0;
  }
}

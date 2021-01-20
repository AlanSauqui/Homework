int relleno=255;
int contadorSoluciones=-1;
int contadorSoluciones1=-1;
int numDeReinas=8; //Cambiar el número de reinas:D
int tamano=100;
int[] tablero=new int[numDeReinas];
int[][] soluciones=new int[50000][numDeReinas];


void setup()
{
  size(900,900);
  background(0);
  //Tablero
  relleno=255;
  for(int i=0,recY=0;i<numDeReinas;i++,recY+=tamano)
  {
    for(int j=0,recX=0;j<numDeReinas;j++,recX+=tamano)
    {
      fill(relleno);
      stroke(255);
      rect(recX,recY,tamano,tamano);
      if(relleno==255)
      {
        relleno=0;
      }
      else if(relleno==0)
      {
        relleno=255;
      }
    }
    if(numDeReinas%2==0)
    {
      if(relleno==255)
      {
        relleno=0;
      }
      else if(relleno==0)
      {
        relleno=255;
      }
    }
  }
  
  //Rellenando el arreglo
  for(int i=0;i<numDeReinas;i++)
  {
    tablero[i]=-1;
  }
  backtracking(0);
}

void draw()
{ 
  background(0);
  delay(200);
  if(contadorSoluciones<contadorSoluciones1)
  {
  contadorSoluciones++;
  System.out.printf("Solución número: ");
  print(contadorSoluciones+1);
  print(" [ ");
  for(int j=0;j<numDeReinas;j++)
  {
    print(soluciones[contadorSoluciones][j]);
    print(" ");
  }
  println("]");
  }
  //contadorSoluciones++;
  //Tablero
  relleno=255;
  for(int i=0,recY=0;i<numDeReinas;i++,recY+=tamano)
  {
    for(int j=0,recX=0;j<numDeReinas;j++,recX+=tamano)
    {
      fill(relleno);
      stroke(255);
      rect(recX,recY,tamano,tamano);
      //Cuadro de solución
      if(soluciones[contadorSoluciones][j]==i)
      {
        fill(250,0,0);
        rect(recX,recY,tamano,tamano);
      }
      
      if(relleno==255)
      {
        relleno=0;
      }
      else if(relleno==0)
      {
        relleno=255;
      }
    }
    if(numDeReinas%2==0)
    {
      if(relleno==255)
      {
        relleno=0;
      }
      else if(relleno==0)
      {
        relleno=255;
      }
    }
  }
  //Texto
  for(int i=0,xText=50;i<numDeReinas;i++,xText+=100)
  {
    textAlign(CENTER);
    textSize(50);
    text(soluciones[contadorSoluciones][i],xText,870);
  }
  //Texto de soluciones
  textSize(20);
  text("Solucion\n no.",850,50);
  textSize(50);
  text(contadorSoluciones+1,850,150);
}

void backtracking(int cebo1)
{
  if(cebo1>=tablero.length)
  {
    contadorSoluciones1++;
    for(int i=0;i<numDeReinas;i++)
    {
      soluciones[contadorSoluciones1][i]=tablero[i];
    }
    return;
  }
  else
  {
    for(int i=0;i<tablero.length;i++)
    {
      tablero[cebo1]=i;
      if(validarRenglones(tablero,cebo1))
      {
        backtracking(cebo1+1);
      }
    }
    tablero[cebo1]=-1;
  }
}

//Validaciones
boolean validarRenglones(int[] tablero,int r)
{
  for(int i=0;i<r;i++)
  {
    if(tablero[i]==tablero[r])
    {
      return false;
    }
  }
  //Diagonales a la derecha
  for(int i=0;i<r;i++)
  {
    if((tablero[i]+i)==(tablero[r]+r))
    {
      return false;
    }
  }
  //Diagonales a la izquierda
  for(int i=0;i<r;i++)
  {
    if((tablero[i]-i)==(tablero[r]-r))
    {
      return false;
    }
  }
  return true;
}

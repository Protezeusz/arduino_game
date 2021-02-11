
#include <LiquidCrystal.h> //Dołączenie bilbioteki

LiquidCrystal lcd(2, 3, 4, 5, 6, 7); //Informacja o podłączeniu nowego wyświetlacza


int board[2][16] = {
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  
 };

int kaktus = 1; 
int kaktusy = 0; 
int dinorzaur = 2;
int up = 0;
int timer = 900;
int punkty = 1;
int game_over = 1;
int r=0;

void jump()
{
      if ((up==0)&((digitalRead(13) == LOW)||(digitalRead(9) == LOW)||(digitalRead(8) == LOW)))
      {
          up=3;
          board[0][1]+=dinorzaur;
          board[1][1]-=dinorzaur;  
      }
}

void setup() {

  pinMode(13, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  lcd.begin(16, 2);
  board[1][1]=dinorzaur; 
  
}
 
void loop() {

    if(game_over)
    {
     jump();  
    //wyswietlacz
    for(int i=0;i<2;i++)
    {
      for(int j=0;j<16;j++)
      {
        switch (board[i][j]) 
        {
           case 1: /* instrukcje, jeśli wyrażenie == wartość1 */
             lcd.setCursor(j, i); //Ustawienie kursora
             lcd.print((board[j][i]+48));
             break;
           case 2: /* instrukcje, jeśli wyrażenie == wartość2 */
             lcd.setCursor(j,i); //Ustawienie kursora
             lcd.print(" ");
             break;
           default: /* instrukcje, jeśli żaden z wcześniejszych warunków nie został spełniony */
              lcd.setCursor(j, i); //Ustawienie kursora
              lcd.print(" ");
             break;
         }
      }
    }
      jump();
      
      if(up!=0)
      {
        up-=1;
        if(up==0)
        {
          board[0][1]-=dinorzaur;
          board[1][1]+=dinorzaur;
        }
      }
    
    //gra
jump();
 
      for(int i=0; i<16; i+=1) //przesun kaktus
      {
        if(board[1][i]==kaktus)
        {
          if(i!=0)
          {
            board[1][i-1]=+kaktus;
          }
          board[1][i]-=kaktus;
        }
      }
  jump();
  
      if(board[1][0]==kaktus) //punkty
      {
        punkty+=1;
        kaktusy-=1;
      }
      
    jump();
      if((punkty%10)==0)      //poziom trudnosci     
      {
        timer=(timer/2);
      }
    jump();
      if(board[1][1]==3)   //die
      {
        game_over = 0;
      }
      
      jump();
      //kaktusy
    
      if(kaktusy!=2)  
      {
        r = random(0,2);
        kaktusy+=r;
      }
        jump();
      if(r!=0)
      {
        board[1][15]=kaktus;
        r-=1;  
      }
jump();
     
      delay(timer);
    }
    else
    {
      lcd.clear();
      lcd.setCursor(0, 0); //Ustawienie kursora
      lcd.print("Game over!!!"); //Wyświetlenie tekstu
      lcd.setCursor(0, 1); //Ustawienie kursora
      lcd.print("any key to restart"); //Wyświetlenie tekstu
      int k=1;
      while(k)
      {
        if ((digitalRead(13) == LOW)||(digitalRead(9) == LOW)||(digitalRead(8) == LOW))
        {
            for(int i=0;i<2;i++)
            {
              for(int j=0;j<16;j++)
              {
                board[i][j] = 0;
              }
            }
            
            kaktus = 1; 
            kaktusy = 0; 
            dinorzaur = 2;
            up = 0;
            timer = 900;
            punkty = 0;
            game_over = 1;
            r=0;
            k=0;
            board[1][1]=dinorzaur;
        }
      }
    }
    
    
}

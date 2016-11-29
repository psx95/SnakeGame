#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <graphics.h>
#include <stdlib.h>
#include <process.h>
//NOTE: movesnake() function's prototype might be needed to chnage

void startup(int);//will draw the logo of the project & main screen
void drawline(int , int ,int ,int, int, int);//to draw lines using putpixel
void playgame();//the snake game code
void level1();
void level2();
void contribution();//shows the contribution of the group members
void displaygraphic_1(void);//diplay the graphic prior to level 1
void about();//to display about this project
void highscores();//display high scores from the .txt file
void addhighscore();//add ann entry to the high scores if it is among the top 5
void congrats();//display a graphic if the score is highest of all entries
void settings ();// change settings like speed & color,level,game type
void drawlogo ();//to draw the logo of this game;
void progexit ();//function to exit the program & display a thank you note
void level1_layout();//function to draw the layout of level 1
void level2_layout();
void updatescore(int, int);//function to display the updated score on the screen
// functions required to make the snake mobile in the game
void touchsnake (struct snake *,struct food *);//function to check if the snake hs touched itself
void gameplay (struct snake *,struct food*);//function that actually controls the movement of snake and displays it by using plot function
void gameplay2 (struct snake *,struct food*);
void plot (struct snake *,struct food *);//function to plot the snake and its food at a specified position
void gameover (void);//function to display a graphic when the game is over by any means
void choice (void);//function to display 2 choices after the game is over
//choice also displays the final score after the game is over
//structures required in the gameplay
struct loc
 {
  int x;
  int y;
 };
struct snake
 {
  struct loc snakeloc;
  struct snake *next;
  char dir;//direction of each node of the snake
 };
struct food
 {
  struct loc foodloc;
  int n;//to calculate no of food hits
 };
struct score_record
{
  long s;
  char name[20];
}arr[6],temp;
//global variables
char getkey;//variable to record the keystroke as pressed by the user
long score=0,prevscore=0;//variable to keep the track of the current score
int count=0,bye=0;
int lifelost=0;//flag value to check if the snake has lost a life
int level=1,speed=1,color=1,lives=1;//attributes for the snake
int prevlives;
int putscoretozero=0;//flag variable to check if the score of the player has been reseted befor starting a new game
int records;//to maintain the number of highscores in the game
FILE *fp;//File pointer for storing the highscores in a txt file
void main ()
 {
   int gd=DETECT,gm;
   initgraph (&gd,&gm,"C:\\tc\\bgi");
   drawlogo();
   cleardevice();
   startup(2);
//  highscores();
// choice ();
// about();
  //  gameover ();
//  settings();
 // level1_layout();
   cleardevice ();
 //  printf ("%d",count);// to check if the keyboard selection is working or not
   getch();
   fflush (stdin);
   closegraph();
 }// main
  //THE DRAW LOGO FUNCTION
void drawlogo()
{
int x,y,i;
for(i=0;i<500;i++)
{
putpixel(rand()%640,rand()%480,rand()%15);
delay(1);
}
sound(240);
delay(50);
nosound();
for(x=100;x<=550;x++)
{
//setlinestyle(0,SOLID_LINE,4);
putpixel(x,150,15);
delay(3);
}
for(y=150;y<=300;y++)
{putpixel(550,y,14);
delay(3);
}
for(x=550;x>=100;x--)
{putpixel(x,300,13);
delay(3);}
for(y=300;y>=150;y--)
{putpixel(100,y,12);
delay(3);
}
setcolor(RED);
settextstyle(BOLD_FONT,0,5);
outtextxy(115,170,"SNAKE");
setcolor(GREEN);
outtextxy(350,170,"GAME");
delay(3000);
}//END OF DRAW LOGO
void drawline (int x, int y, int x2, int y2, int color,int d)
 {
  int i;
  int w=x2-x;
  int h=y2-y;
  double m=h/(double)w;
  double j=y;
  for (i=x;i<=x2;i++)
   {
    putpixel (i,(int)j,color);
    delay (d);
    j+=m;
   }
 }//drawline
void about ()  //working
 {           // the content in about needs to be aligned
  a:
  cleardevice ();
  settextstyle (GOTHIC_FONT,0,5);
  setcolor (LIGHTGREEN);
  outtextxy (280,20, "ABOUT");
  settextstyle (DEFAULT_FONT,0,1);
  setcolor (WHITE);
  outtextxy (20,80, "This is a basic snake game created using linked list data structure in c.");
  outtextxy (20,100, "INSTRUCTIONS: Use the w-a-s-d keys to control the snake in the game and make ");
  outtextxy (20,120, "              it hit the target. ");
  outtextxy (20,140, "              The snake starts with 1 life, if you hit the wall or the snake ");
  outtextxy (20,160, "              touches itself, it looses a life. Once it looses a life, press ");
  outtextxy (20,180, "              any key to continue with remaining lives (if any). ");
  outtextxy (20,200, "              As the score increases, the snake's length also increases. ");
  outtextxy (20,220, "              The speed of the snake however, remains constant throughout.");
  outtextxy (20,240, "              You can also pause the game by pressing and holding any key ");
  outtextxy (20,260, "              except the w-a-s-d keys. To resume the game simply release the ");
  outtextxy (20,280, "              pressed key. ");
  outtextxy (20,300, "              Customizing options are available under the settings option ");
  outtextxy (20,320, "              here, you can change snake's speed, game levels, snake's color ");
  outtextxy (20,340, "              and the number of lives the snake has. ");
  setcolor (RED);
  outtextxy (20,360, "SCORE CALCULATION:");
  setcolor (15);
  outtextxy (20,380, "              HIGHER THE SPEED, GREATER THE SCORE PER HIT. ");
  outtextxy (20,400, "              Speed 1: 20 points per hit. ");
  outtextxy (20,420, "              Speed 2: 40 points per hit. ");
  outtextxy (20,440, "              Speed 3: 60 points per hit. ");
  //enjoy
  settextstyle (SANS_SERIF_FONT,0,2);
  setcolor (YELLOW);
  outtextxy (30,400,"ENJOY..!!");
  settextstyle (DEFAULT_FONT,0,2);
  setcolor (LIGHTRED);
  outtextxy (480,400, "Snake v1.0");
  rectangle (550,430,630,460);
  settextstyle (DEFAULT_FONT,0,2);
  setcolor (LIGHTGRAY);
  outtextxy (560,440, "BACK");
  outtextxy (520,440,">>");
  if (getch()==13)
  {
   sound (400);
   delay (50);
   nosound ();
   cleardevice();
   return;
  }
  else
  goto a;
 }//about
void displaygraphic_1 ()
{
    char x;
  if (level==1)
  {
    cleardevice();
    setbkcolor(WHITE);
    settextstyle (DEFAULT_FONT,0,4);
    setcolor (BLUE);
    rectangle (100,100,540,380);
    outtextxy (220,120,"LEVEL 1 ");
    setcolor (RED);
    outtextxy (230,200,"READY ?? ");
    setcolor (BROWN);
    settextstyle (TRIPLEX_FONT,0,1);
    outtextxy (500,440,"press enter ");
      while (getch()!=13)
      {
      }
      sound (400);
      delay (50);
      nosound ();
      setcolor (WHITE);
      outtextxy (500,440,"press enter ");
      delay (1000);
    setcolor (LIGHTGREEN);
    settextstyle (DEFAULT_FONT,0,4);
    outtextxy (230,280, "BEGIN !! ");
    delay (1000);
   // getch();
   // progexit();
   cleardevice();
  }//if level==1
  else if(level==2)
  {
    cleardevice();
    setbkcolor(WHITE);
    settextstyle (DEFAULT_FONT,0,4);
    setcolor (BLUE);
    rectangle (100,100,540,380);
    outtextxy (220,120,"LEVEL 2");
    setcolor (RED);
    outtextxy (230,200,"READY ?? ");
    setcolor (BROWN);
    settextstyle (TRIPLEX_FONT,0,1);
    outtextxy (500,440,"press enter ");
      while (getch()!=13)
      {
      }
      sound (400);
      delay (50);
      nosound ();
      setcolor (WHITE);
      outtextxy (500,440,"press enter ");
      delay (1000);
    setcolor (LIGHTGREEN);
    settextstyle (DEFAULT_FONT,0,4);
    outtextxy (230,280, "BEGIN !! ");
    delay (1000);
   // getch();
   // progexit();
   cleardevice();
     }
  return;
}
void playgame () ///working
 {

  displaygraphic_1();
  cleardevice ();
  if (level==1)
  level1_layout();
  else
  {
  level2_layout();
  }
  return;
 }//playgame
void highscores ()//will display all the highscores in hscore.txt
 {  //working as it should
  int i,d=0;
  long score;
  char name[10],buffer_score[100],buffer_name[10];
  cleardevice ();
  //pixelated bckground
  fp=fopen ("hscore.txt","r");
  setviewport (0,0,640,480,0);
  for (i=0;i<1000;i++)
  {
   putpixel (rand()%640,rand()%480,rand()%15);
  }
  settextstyle (EUROPEAN_FONT,0,4);
  setcolor (LIGHTGREEN);
  outtextxy (200,50,"HIGHSCORES");
  setcolor (WHITE);
  line (195,50,500,50);
  line (195,120,500,120);
  settextstyle (1,0,3);
  setcolor (LIGHTGRAY);
  outtextxy (200,170,"NAME");
  outtextxy (450,170,"SCORE");
  //code to read and display the highscores from the file
  settextstyle (DEFAULT_FONT,0,1);
  setcolor (WHITE);
  rewind (fp);
  while (fscanf (fp,"%s %ld",name,&score)!=EOF)
  {
   sprintf (buffer_score,"%ld",score);
   sprintf (buffer_name,"%s",name);
   if (score>0)
   {
   outtextxy (200,210+d,buffer_name);
   outtextxy (450,210+d,buffer_score);
   d+=40;
   }
   //i+=1;
  }
  fclose (fp);
  getch();
  clearviewport();
  return;
 }//highscores
void settings ()
 {
  int arrow_y=100,co=0;
  char x;
  cleardevice();
  setbkcolor (WHITE);
 // printf ("\n in settings ");
//  getch ();
  q:
  settextstyle (SANS_SERIF_FONT,0,4);
  setcolor (LIGHTGRAY);
  outtextxy (280,20,"SETTINGS ");
  setlinestyle(3,1,1);
  line  (40,60,600,60);
  line  (40,75,600,75);
  settextstyle (TRIPLEX_FONT,0,3);
  setcolor (DARKGRAY);
  if (level==1)
  outtextxy (50,100," Level :<< 1 >>");
  else if (level==2)
  outtextxy (50,100," Level :<< 2 >>");
  else if (level==3)
  outtextxy (50,100," Level :<< 3 >>");
  if (speed==1)
  outtextxy (50,140," Speed :<< 1 >> ");
  else if (speed==2)
  outtextxy (50,140," Speed :<< 2 >> ");
  else if (speed==3)
  outtextxy (50,140," Speed :<< 3 >> ");
  if (color==1)
  {
  setcolor (BLUE);
  outtextxy (50,180," Color :<< BLUE >> ");
  }
  else if (color==2)
  {
  setcolor (GREEN);
  outtextxy (50,180," Color :<< GREEN >> ");
  }
  else if (color==3)
  {
  setcolor (CYAN);
  outtextxy (50,180," Color :<< CYAN >> ");
  }
  else if (color==4)
  {
  setcolor (RED);
  outtextxy (50,180," Color :<< RED >> ");
  }
  setcolor (DARKGRAY);
  if (lives==1)
  outtextxy (50,220," Lives :<< 1 >> ");
  else if (lives==2)
  outtextxy (50,220," Lives :<< 2 >> ");
  else if  (lives==3)
  outtextxy (50,220," Lives :<< 3 >> ");
  setlinestyle (2,1,1);
  rectangle (40,255,120,290);
  outtextxy (50,260,"BACK" );
 // setcolor (RED);                       linestyle
  outtextxy (10,arrow_y,">>");

  while (arrow_y<=260)
  {
    x=getch();
    if (arrow_y==260&&x==13)
    break;
    if (x==80 && arrow_y<260)  //arrow up down selection process
     {
       sound (400);
       delay (50);
       nosound ();
       cleardevice ();
       arrow_y+=40;
       co++;
       goto q;
     }
     else if (x==72 && arrow_y>100)
      {
	sound (400);
	delay (50);
	nosound ();
	cleardevice ();
	arrow_y-=40;
	co--;
	goto q;
      }
     else if (x==75 &&  arrow_y<260)//left
       {
	sound (400);
	delay (50);
	nosound ();
	switch (arrow_y)      //decrement value of attribute at arrow_y
	 {
	  case 100:
		    if (level>1)
		    {
		      level--;
		      cleardevice ();
		      goto q;
		    }
		    break;
	 case 140:
		   if (speed>1)
		   {
		    speed--;
		    cleardevice ();
		    goto q;
		   }
		   break;
	 case 180:
		   if  (color>1)
		   {
		    color--;
		    cleardevice ();
		    goto q;
		   }
		   break;
	 case 220:
		  if (lives>1)
		  {
		   lives--;
		   cleardevice();
		   goto q;
		  }
		  break;

	 }//switch case
       }//else if for x==75
      else if (x==77 && arrow_y<260)
       {
	 sound (400);
	 delay (50);
	 nosound ();
	 switch (arrow_y)      //increment value of attribute at arrow_y
	 {
	  case 100:
		    if (level<3)
		    {
		      level++;
		      cleardevice ();
		      goto q;
		    }
		    break;
	 case 140:
		   if (speed<3)
		   {
		    speed++;
		    cleardevice ();
		    goto q;
		   }
		   break;
	 case 180:
		   if  (color<4)
		   {
		    color++;
		    cleardevice ();
		    goto q;
		   }
		   break;
	 case 220:
		  if (lives<3)
		  {
		   lives++;
		   cleardevice();
		   goto q;
		  }
		  break;

	 }//switch case
       }//else if for x=77
   }//if (kbhit())
  cleardevice();
  setlinestyle (SOLID_LINE,0,1);
  startup (0);
 }//settings
  void contribution()
 {
 cleardevice();
  settextstyle(GOTHIC_FONT,0,6);
  outtextxy(220,10,"CREDITS");
  settextstyle(EUROPEAN_FONT,0,1);
  setcolor(11);
  outtextxy(10,190,"Made by PSX95");
  getch();
    return;
 }
void progexit ()
 {
   contribution();
 // delay(17000);
  cleardevice ();
  bye=1;// flag variable
  closegraph();
  exit(1);
 }//progexit
void startup(int x) // function working as it should
 {
 int i,j,d=20;
 char b;
 count=1;
// setlinestyle (0,1,3); //linestyle
 setviewport (0,0,640,480,1);
 setbkcolor (BLACK);
  q:
  //pixelated background
  for (i=0;i<1000;i++)
  {
   putpixel (rand()%640,rand()%480,rand()%15);
  }
  for (i=150;i>=50;i--)
  {
   putpixel (i,50,RED);
   delay(x);
  }
  for (i=50;i<=120;i++)
  {
   putpixel (50,i,WHITE);
   delay(x);
  }
  for (i=50;i<=150;i++)
  {
   putpixel (i,120,RED);
   delay(x);
  }
  for (i=120;i<=190;i++)
  {
   putpixel (150,i,WHITE);
   delay(x);
  }
  for (i=150;i>=50;i--)
  {
   putpixel (i,190,RED);
   delay(x);
  }
	  // S
  for (i=190;i>=50;i--)
  {
   putpixel (180,i,YELLOW);
   delay(x);
  }
  setcolor (RED);
  drawline (180,50,280,190,3,x);//try using putpixel instead
  for (i=190;i>=50;i--)
  {
   putpixel (280,i,GREEN);
   delay(x);
  }
  //N
  drawline (310,190,360,50,15,x);
  drawline (360,50,410,190,4,x);
  drawline (330,140,390,140,14,x);
  //A
 // drawline (430,190,430,50,15,x);   (not working)
  for (i=190;i>=50;i--)
  {
   putpixel (440,i,14);
   delay (x);
  }
  drawline (440,120,510,190,15,x);
  drawline (440,120,510,50,4,x);
  //K
  for (i=600;i>=540;i--)
  {
   putpixel (i,190,1);
   delay(x);
  }
  for (i=190;i>=50;i--)
  {
   putpixel (540,i,5);
   delay (x);
  }
  for (i=540;i<=580;i++)
  {
   putpixel (i,120,6);
   delay (x);
  }
  for (i=540;i<=600;i++)
  {
   putpixel (i,50,15);
   delay (x);
  }
  //E
  // Writing snake on the logo screen complete
  // Displaying the options
  setcolor (LIGHTGRAY);
  rectangle (getmaxx()/2-100,getmaxy()/2+10,getmaxx()/2+100,getmaxy()/2+40);
  settextstyle (DEFAULT_FONT,0,2);
  setcolor (GREEN);
  outtextxy (getmaxx()/2-90,getmaxy()/2+20,"PLAY GAME !!");
  rectangle (getmaxx()/2-100,getmaxy()/2+60,getmaxx()/2+100,getmaxy()/2+90);
  setcolor (YELLOW);
  outtextxy (getmaxx()/2-90,getmaxy()/2+70,"HIGH SCORES");
  rectangle (getmaxx()/2-100,getmaxy()/2+110,getmaxx()/2+100,getmaxy()/2+140);
  setcolor (LIGHTMAGENTA);
  outtextxy (getmaxx()/2-90,getmaxy()/2+120," SETTINGS ");
  rectangle (getmaxx()/2-100,getmaxy()/2+160,getmaxx()/2+100,getmaxy()/2+190);
  setcolor (RED);
  outtextxy (getmaxx()/2-90,getmaxy()/2+170,"   ABOUT");
  rectangle (getmaxx()/2-100,getmaxy()/2+210,getmaxx()/2+100,getmaxy()/2+240);
  setcolor (LIGHTGRAY);
  outtextxy (getmaxx()/2-90,getmaxy()/2+220,"    EXIT");
  setcolor (LIGHTRED);
  outtextxy (getmaxx()/2-129,getmaxy()/2+d, ">>             <<");
  while (b!=13)  //arrow moving and selection process through keyboard
  {
  b=getch();
  if (b==80)
   {
    sound (400);
    delay (50);
    nosound();
    while (d>=20&&d<210) //displaying arrow mve on pressing down arrow
     {
      cleardevice();
      x=0;
      d+=50;
      count++;
      goto q;
     }
   }
   else
    {
     if (b==72)  //displaying arrrow move on pressing up arrow
      {
       sound (400);
       delay(50);
       nosound();
       while (d>20&&d<=220)
       {
	 cleardevice();
	 x=0;
	 d-=50;
	 count--;
	 goto q;
       }///while
      }//if
    }//else
  }//while
  b='\0';
  // Starting to call other functions from this function
  // Control has to be returned to this function after exiting from the other functions
  switch (count)
  {
   case 1:
	   playgame();
	   break;
   case 2:
	   highscores();
	   break;
   case 3:
	   settings();
	   break;
   case 4:
	   about();
	   break;
   case 5:
	   progexit ();
	   break;
  }//switch case
  if (bye==1)
  return;
  else
  goto q;
 }//drawlogo_program
//plot- function to plot the snake at a specified x-y co ordinate
//function will also plot the food location at a specified x-y co-ordinate
//NOTE: setviewport coordinates needs to be changed
void plot (struct snake *head, struct food *f)
 {
  struct snake *temp;			 // will draw the target and
  temp=head;                                  //the snake at the specified
  setfillstyle (9,15);	    		     //x-y co ordinates
//  settextstyle ("TRIPLEX_FONT",0,2);
  setviewport (35,80,610,438,1);
//  bar (temp->snakeloc.x-5,temp->snakeloc.y-5,temp->snakeloc.x+5,temp->snakeloc.y+5);
  setcolor (5);
   if(level==2)
  {
   setfillstyle(9,12);
   bar (150,165,420,185);
   setfillstyle(9,14);
   bar(50,40,70,320);
   setfillstyle(9,13);
   bar(490,40,510,320);
  }

  circle (temp->snakeloc.x,temp->snakeloc.y,5);
  temp=temp->next;//updating pointer to be started from
  setfillstyle (9,3);
  setcolor (color);
  while (temp!=NULL)
  {
  //  bar (temp->snakeloc.x-4,temp->snakeloc.y-4,temp->snakeloc.x+4,temp->snakeloc.y+4);
    circle (temp->snakeloc.x,temp->snakeloc.y,4);
    temp=temp->next;
  }//while
  //now to draw the food
  setcolor (14);

  circle (f->foodloc.x,f->foodloc.y,3);
  circle (f->foodloc.x,f->foodloc.y,2);
  circle (f->foodloc.x,f->foodloc.y,1);
  if (speed==1)
  delay (40);//controlling speed of the snake (working)
  else if (speed==2)
  delay (30);
  else if (speed==3)
  delay (20);
  while (!kbhit())//untill any key on the keyboard is pressed
  {
   goto q;
  }
  getkey=getch();
//  touchsnake (head);
  q:
   clearviewport();
 }
//touchsnake- function to check if the snake has touch its own body
void touchsnake (struct snake *head,struct food *f)//touchsnake
 {
   struct snake *temp,*temp1;
   temp=head->next;
   //head should be preserved in a seperate variable
   //logic applied: chek if the head's x-y co-ordinates matches any
   //node's x-y coordinte
   while (temp!=NULL)
   {
    if (temp->dir!=head->dir) //snake's head cannot hit the nodes which
    {                         //have the same direction as the snake's head
      if (head->dir=='a')
      {
	if (temp->dir!='d')
	{
	  if (head->snakeloc.x==temp->snakeloc.x&&head->snakeloc.y==temp->snakeloc.y)
	  {
	   if (lives==0)
	   {
	    clearviewport();
	    gameover();
	   }
	   else
	   {
	      prevlives=lives;
	      --lives;
	      lifelost=1;
	      //to display the update life on the screen
	      updatescore(score,prevscore);
	     // setting the snake's position back to intial
	     head->snakeloc.x=250;
	     head->snakeloc.y=250;
	     plot (head,f);
	     getch();
	   }
	  // return 1;
	  } //if 3
	}//if 2
      }//if 1
     else
     if (head->dir=='d')
     {
      if (temp->dir!='a')
      {
       if (head->snakeloc.x==temp->snakeloc.x&&head->snakeloc.y==temp->snakeloc.y)
	  {
	   if (lives==0)
	   {
	    clearviewport();
	    gameover();
	   }
	   else
	   {
	      prevlives=lives;
	     --lives;
	     lifelost=1;
	    //to display the update life on the screen
	     updatescore(score,prevscore);
	    // setting the snake's position back to intial
	    head->snakeloc.x=250;
	    head->snakeloc.y=250;
	    plot (head,f);
	    getch();
	   }
	  // return 1;
	  } //if 2
      }//if 1
     }// if 'd'
     else
     if (head->dir=='w')
     {
      if (temp->dir!='s')
      {
	if (head->snakeloc.y==temp->snakeloc.y&&head->snakeloc.x==temp->snakeloc.x)
	{
	 if (lives==0)
	 {
	  clearviewport();
	  gameover ();
	 }
	 else
	  {
	    prevlives=lives;
	    --lives;
	    lifelost=1;
	    //to display the update life on the screen
	    updatescore(score,prevscore);
	   // setting the snake's position back to intial
	    head->snakeloc.x=250;
	    head->snakeloc.y=250;
	    plot (head,f);
	    getch();
	  }
	} //if 1
      }//if 2
     }//if 'w'
     else
     if (head->dir=='s')
     {
      if (temp->dir!='w')
      {
       if (head->snakeloc.y==temp->snakeloc.y&&head->snakeloc.x==temp->snakeloc.x)
       {
	if (lives==0)
	{
		clearviewport();
		gameover();
	}
	else
	 {
	    prevlives=lives;
	    --lives;
	    lifelost=1;
	   //to display the update life on the screen
	     updatescore(score,prevscore);
	  // setting the snake's position back to intial
	    head->snakeloc.x=250;
	    head->snakeloc.y=250;
	    plot (head,f);
	    getch();
	 }
       } //if 1
      } //if 2
     }// if 's'
   }//if temp!=head->dir
   temp=temp->next;
  }//while
   return ;
 }
void gameplay (struct snake *head, struct food *f)
 {
  int fx,fy;
  char buffer[10];
  struct snake *temp,pre,nxt;
  temp=head;//so that head remains unchanged
  // to check if the snake touches the boundry
 while  (1)
  {
  if (head->snakeloc.x<=5||head->snakeloc.y<=0||head->snakeloc.x>=570||head->snakeloc.y>=355)
  {//this needs to be fixed
   if (lives==0)
   {
     clearviewport();
     gameover();//gameover condition
   }
   else
   {
    //updating value of lives
    prevlives=lives;
    --lives;
    lifelost=1;
    //to display the update life on the screen
    updatescore(score,prevscore);
    // setting the snake's position back to intial
    head->snakeloc.x=250;
    head->snakeloc.y=250;
    plot (head,f);
    getch();
   }
  }
//  touchsnake (head);
  //now to check if the snake's "head" actually hits the target (the food)
  if(head->snakeloc.x>=f->foodloc.x-5&&head->snakeloc.x<=f->foodloc.x+5&&head->snakeloc.y>=f->foodloc.y-5&&head->snakeloc.y<=f->foodloc.y+5)
   {

   // change the food loaction and update the score
   sound (420);
   delay (20);
   nosound();
   temp=head;
   prevscore=score;
   score=(score+20*speed);
   updatescore (score,prevscore);
   fx=random(450);
   while (fx<=50)
     fx=random(470);
   f->foodloc.x=fx;
   fy=random(300);
   while (fy<=90)
     fy=random(320);
     f->foodloc.y=fy;
   f->n+=1;
   // since the snake has hit the target, so now snake's length needs to be updated
   // to update length
  while (temp->next!=NULL)
  {
   temp=temp->next;
  }//to reach the end of linked list
  //adding a new node for increasing snake's length
  temp->next=(struct snake *)malloc (sizeof (struct snake));
  temp->next->next=NULL;
  temp->next->snakeloc.x=temp->snakeloc.x;
  temp->next->snakeloc.y=temp->snakeloc.y;
  temp->next->dir=temp->dir;
  }
  //now to check if the diretion of the snake has been changed or not
  switch (getkey)
  {
   case 'a': if (head->dir!='d')
	     {
		head->dir='a';
		head->snakeloc.x-=3;
	     }
	     else
	     {
	      getkey=head->dir;
	     }
	     break;
   case 'd': if (head->dir!='a')
	     {
	       head->dir='d';
	       head->snakeloc.x+=3;
	     }
	     else
	     {
	      getkey=head->dir;
	     }
	     break;
   case 'w':
	    if (head->dir!='s')
	    {
	     head->dir='w';
	     head->snakeloc.y-=3;
	    }
	    else
	    {
	     getkey=head->dir;
	    }
	    break;
   case 's':
	    if (head->dir!='w')
	    {
	     head->dir='s';
	     head->snakeloc.y+=3;
	    }
	    else
	    {
	     getkey=head->dir;
	    }
	    break;
   default:
	    getkey=head->dir;
	    break;
  }//switch case
 // updatescore (score,prevscore);
  plot (head,f);//to plot the current location of snake and the food
  //now to swap previous and the next nodes of the linked list
  // to make it appear as a moving snake
  temp=head;
  pre=*temp;
  while (temp->next!=NULL)        //swapping adjecent nodes
  {
		nxt.snakeloc.x=temp->next->snakeloc.x; // assigning the temp->link node to nxt
		nxt.snakeloc.y=temp->next->snakeloc.y;  //nxt=temp->link
		nxt.dir=temp->next->dir;
		temp->next->snakeloc.x=pre.snakeloc.x;//temp->link=pre
		temp->next->snakeloc.y=pre.snakeloc.y;
		temp->next->dir=pre.dir;
		temp=temp->next;
		pre=nxt;
  }
  //updated node (in case of direction change will now be added to the end
  //of the linked list to make it look like a moving snake
  touchsnake (head,f);
 }//while
 }//gameplay
//level 1 of the game
//code has been integrated from trysnake.c
//the function below will control all the gameplay of level 2
//seperate function has been made to avoid confusion
void gameplay2 (struct snake *head, struct food *f)
 {
  int fx,fy;
  char buffer[10];
  struct snake *temp,pre,nxt;
  temp=head;//so that head remains unchanged
  // to check if the snake touches the boundry
 while  (1)
  {
  if (head->snakeloc.x<=5||head->snakeloc.y<=0||head->snakeloc.x>=570||head->snakeloc.y>=355)
  {//this needs to be fixed
   if (lives==0)
   {
     clearviewport();
     gameover();//gameover condition
   }
   else
   {
    //updating value of lives
    prevlives=lives;
    --lives;
    lifelost=1;
    //to display the update life on the screen
    updatescore(score,prevscore);
    // setting the snake's position back to intial
    head->snakeloc.x=250;
    head->snakeloc.y=250;
    plot (head,f);
    getch();
   }
  }
  else if((head->snakeloc.x>=150&&head->snakeloc.x<=420)&&(head->snakeloc.y>=165&&head->snakeloc.y<=185))
  {
  if (lives==0)
   {
     clearviewport();
     gameover();//gameover condition
   }
   else
   {
    //updating value of lives
    prevlives=lives;
    --lives;
    lifelost=1;
    //to display the update life on the screen
    updatescore(score,prevscore);
    // setting the snake's position back to intial
    head->snakeloc.x=250;
    head->snakeloc.y=250;
    plot (head,f);
    getch();
   }
  }
  else if((head->snakeloc.x>=50&&head->snakeloc.x<=70)&&(head->snakeloc.y>=40&&head->snakeloc.y<=320))
  {
    if (lives==0)
   {
     clearviewport();
     gameover();//gameover condition
   }
   else
   {
    //updating value of lives
    prevlives=lives;
    --lives;
    lifelost=1;
    //to display the update life on the screen
    updatescore(score,prevscore);
    // setting the snake's position back to intial
    head->snakeloc.x=250;
    head->snakeloc.y=250;
    plot (head,f);
    getch();
   }
  }
  else if((head->snakeloc.x>=490&&head->snakeloc.x<=510)&&(head->snakeloc.y>=40&&head->snakeloc.y<=320))
  {
     if (lives==0)
   {
     clearviewport();
     gameover();//gameover condition
   }
   else
   {
    //updating value of lives
    prevlives=lives;
    --lives;
    lifelost=1;
    //to display the update life on the screen
    updatescore(score,prevscore);
    // setting the snake's position back to intial
    head->snakeloc.x=250;
    head->snakeloc.y=250;
    plot (head,f);
    getch();
   }
    }

//  touchsnake (head);
  //now to check if the snake's "head" actually hits the target (the food)
  if(head->snakeloc.x>=f->foodloc.x-5&&head->snakeloc.x<=f->foodloc.x+5&&head->snakeloc.y>=f->foodloc.y-5&&head->snakeloc.y<=f->foodloc.y+5)
   {

   // change the food loaction and update the score
   sound (420);
   delay (20);
   nosound();
   temp=head;
   prevscore=score;
   score=(score+20*speed);
   updatescore (score,prevscore);
   d:
   fx=random(450);
   while (fx<=50)
     fx=random(470);
   f->foodloc.x=fx;
   fy=random(300);
   while (fy<=90)
     fy=random(320);
     f->foodloc.y=fy;
   if (fx>=147&&fx<=423&&fy>=162&&fy<=189)
   goto d;
   else
   if (fx>=47&&fx<=73&&fy>=37&&fy<=323)
   goto d;
   else if (fx>=487&&fx<=513&&fy>=37&&fy<=323)
   goto d;
   f->n+=1;
   // since the snake has hit the target, so now snake's length needs to be updated
   // to update length
  while (temp->next!=NULL)
  {
   temp=temp->next;
  }//to reach the end of linked list
  //adding a new node for increasing snake's length
  temp->next=(struct snake *)malloc (sizeof (struct snake));
  temp->next->next=NULL;
  temp->next->snakeloc.x=temp->snakeloc.x;
  temp->next->snakeloc.y=temp->snakeloc.y;
  temp->next->dir=temp->dir;
  }
  //now to check if the diretion of the snake has been changed or not
  switch (getkey)
  {
   case 'a': if (head->dir!='d')
	     {
		head->dir='a';
		head->snakeloc.x-=3;
	     }
	     else
	     {
	      getkey=head->dir;
	     }
	     break;
   case 'd': if (head->dir!='a')
	     {
	       head->dir='d';
	       head->snakeloc.x+=3;
	     }
	     else
	     {
	      getkey=head->dir;
	     }
	     break;
   case 'w':
	    if (head->dir!='s')
	    {
	     head->dir='w';
	     head->snakeloc.y-=3;
	    }
	    else
	    {
	     getkey=head->dir;
	    }
	    break;
   case 's':
	    if (head->dir!='w')
	    {
	     head->dir='s';
	     head->snakeloc.y+=3;
	    }
	    else
	    {
	     getkey=head->dir;
	    }
	    break;
   default:
	    getkey=head->dir;
	    break;
  }//switch case
 // updatescore (score,prevscore);
  plot (head,f);//to plot the current location of snake and the food
  //now to swap previous and the next nodes of the linked list
  // to make it appear as a moving snake
  temp=head;
  pre=*temp;
  while (temp->next!=NULL)        //swapping adjecent nodes
  {
	nxt.snakeloc.x=temp->next->snakeloc.x; // assigning the temp->link node to nxt
		nxt.snakeloc.y=temp->next->snakeloc.y;  //nxt=temp->link
		nxt.dir=temp->next->dir;
		temp->next->snakeloc.x=pre.snakeloc.x;//temp->link=pre
		temp->next->snakeloc.y=pre.snakeloc.y;
		temp->next->dir=pre.dir;
		temp=temp->next;
		pre=nxt;
  }
  //updated node (in case of direction change will now be added to the end
  //of the linked list to make it look like a moving snake
  touchsnake (head,f);
 }//while
 }//gameplay
//level 1 of the game
//code has been integrated from trysnake.c
void addhighscore()
{
int i,j,k=0;
char a[20];char n[20];
long sc;
   fp=fopen ("hscore.txt","a");//append mode so that records can be added
   printf("Enter Your Name-");
   scanf("%s",a);
   fclose(fp);
  // fprintf(fp,"%s ",a);
  // fprintf(fp,"%ld\n",score);
   //re open the file to copy data into an array of structures
   fp=fopen ("hscore.txt","r");
   while (!feof(fp))
    {
    fscanf (fp,"%s %ld",n,&sc);
      if (sc>0){
      strcpy (arr[k].name,n);
      arr[k].s=sc;
      k++;      }
    }//while
    arr[k].s=score;         //entering the current data
    strcpy (arr[k].name,a);
  /*  for (i=0;i<=k;i++)
    {
      printf ("%s\n",arr[i].name);
      printf ("%ld\n",arr[i].s);
    }*/
  fclose (fp);
  //sorting the structures
  k++;
  for (i=0;i<k;i++)
  {
    for (j=0;j<k-1-i;j++)
    {
      if (arr[j].s<=arr[j+1].s)
	 {
	   temp=arr[j];
	   arr[j]=arr[j+1];
	   arr[j+1]=temp;
	 }
    }
  } //outer for
  //now write the new sorted content in hscore.txt
  fp=fopen ("hscore.txt","w");
  for (i=0;i<5;i++)
  {
    fprintf (fp,"%s %ld\n",arr[i].name,arr[i].s);
  }//writing in the file complete
  fclose (fp);

  //open in write mode=> previous data in the file will be overwritten

}
void gameover ()// code made by tanmay
{
int i;
cleardevice();
//records+=1;
setviewport (0,0,640,480,1);
settextstyle(EUROPEAN_FONT,0,5);
for (i=0;i<4;i++)
{
  sound (600);
  setcolor (YELLOW);
  outtextxy(100,150,"GAME OVER");
  delay (500);
  nosound ();
  sound (500);
  setcolor (0);
  outtextxy(100,150,"GAME OVER");
  delay(500);
  nosound();
}
//delay(1000);
 clearviewport ();
//setting the attributes of the snake back to original values
 cleardevice ();
 lives=1;color=1;speed=1;level=1;
 addhighscore();
 cleardevice();
 putscoretozero=1; //flag to set sore back to zero
 choice ();
}
void level1_layout ()
 {
    char buffer[80];
   cleardevice();
   setbkcolor (BLACK);
   settextstyle (3,0,1);
   setcolor (LIGHTGRAY);
   outtextxy (70,30,"Score :");
//   printf ("%d",score);
   outtextxy (285,30,"Speed :");
  // printf ("%d",speed);
   outtextxy(540,30,"Lives :");
   setfillstyle (7,7);
   bar (10,60,630,80);
   bar (10,60,30,460);
   bar (10,440,630,460);
   bar (630,60,610,460);
   sprintf (buffer,"%d",speed); //this will work co ordinates needs to be set up
   outtextxy (350,30,buffer);
   level1 ();// level 1 starts here
  // getch ();
   cleardevice();
   return;
}
void level2_layout()
 {
    char buffer[80];
   cleardevice();
   setbkcolor (BLACK);
   settextstyle (3,0,1);
   setcolor (LIGHTGRAY);
   outtextxy (70,30,"Score :");
//   printf ("%d",score);
   outtextxy (285,30,"Speed :");
  // printf ("%d",speed);
   outtextxy(540,30,"Lives :");
   setfillstyle (7,7);
   bar (10,60,630,80);
   bar (10,60,30,460);
   bar (10,440,630,460);
   bar (630,60,610,460);
   // if(level==2)
 // {
   //setfillstyle(7,7);
 // }
     sprintf (buffer,"%d",speed); //this will work co ordinates needs to be set up
   outtextxy (350,30,buffer);
   level2 ();// level 2 starts here
  // getch ();
   cleardevice();
   startup(0);
}
void level1 ()
{
 struct snake *s;
 struct food f;
 s=(struct snake *)malloc (sizeof (struct snake ));
 s->next=NULL;
 s->dir='w';
 s->snakeloc.x=250;
 s->snakeloc.y=250;
 f.foodloc.x=0;
 f.foodloc.y=0;
 updatescore (score,prevscore);
 randomize();//initialise random() with a random value
 //so that the food doesn't lies within the boundry walls
 while (f.foodloc.x<=39)
 f.foodloc.x=random(470);
 while (f.foodloc.y<=85)
 f.foodloc.y=random(320);
 plot (s,&f);
 getkey='r';
 gameplay (s,&f);
 cleardevice ();
 return;
}
void level2 ()
{
 struct snake *s;
 struct food f;
 s=(struct snake *)malloc (sizeof (struct snake ));
 s->next=NULL;
 s->dir='w';
 s->snakeloc.x=250;
 s->snakeloc.y=250;
 f.foodloc.x=0;
 f.foodloc.y=0;
 updatescore (score,prevscore);
 randomize();//initialise random() with a random value
 //so that the food doesn't lies within the boundry walls
 while (f.foodloc.x<=39)
 f.foodloc.x=random(470);
 while (f.foodloc.y<=85)
 f.foodloc.y=random(320);
 plot (s,&f);
 getkey='r';
 gameplay2 (s,&f);
 cleardevice ();
 return;
}
void updatescore (int sc,int prevsc)
 {
   char buf [10], buff[10],bufferlife[10];
 /*  if (lives==0)
   {
     clearviewport();
     setviewport (0,0,640,480,1);
   } */
   setviewport (0,0,630,70,1);
   setcolor (0); // to overshadow the score previously displayed
   sprintf (buf,"%d",prevsc);
   outtextxy (140,30,buf);
   setcolor (15);
   sprintf (buff,"%d",sc);
   outtextxy (140,30,buff);
   setcolor (0);
   sprintf (bufferlife,"%d",prevlives);
   outtextxy (600,30,bufferlife);
   setcolor (15);
   sprintf (bufferlife,"%d",lives);
   outtextxy (600,30,bufferlife);
   if (lifelost==1)
   {
     lifelost=0;
     setcolor (BLACK);
     sprintf (bufferlife,"%d",prevlives);
     outtextxy (600,30,bufferlife);
     setcolor (15);
     sprintf (bufferlife,"%d",lives);
     outtextxy (600,30,bufferlife);
   }
   return;
 }
void choice ()
 {
   int x=70,i;
   char c,bufsc[10];
   cleardevice ();
   q:
   //here a setviewport is very important
   //to overshadow the previuos setviewport that was initialised in updatescore()
   setviewport (0,0,620,460,0);
   sprintf (bufsc,"%d",score);
   setcolor (WHITE);
   settextstyle (TRIPLEX_FONT,0,3);
   outtextxy (250,105,"Final Score:");
   outtextxy (400,105,bufsc);
   for (i=0;i<1000;i++)
   {
    putpixel (rand()%640,rand()%480,rand()%15);
   }
   setcolor (WHITE);
   rectangle (100,200,290,250);
   settextstyle (TRIPLEX_FONT,0,3);
   setcolor (GREEN);
   outtextxy (130,205,"MAIN MENU");
   setcolor (WHITE);
   rectangle (450,200,550,250);
   setcolor (LIGHTRED);
   outtextxy (480,205,"EXIT");
   settextstyle (DEFAULT_FONT,0,2);
   setcolor (CYAN);
   outtextxy (x,210,">>");
   if (putscoretozero==1)
   score=0;
   putscoretozero=0;
   c=getch();
   while (c!=13)
   {
     c=getch();
     if (c==75)
     {
       sound (400);
       delay (50);
       nosound();
       cleardevice();
       x=70;
       goto q;
     }
     else if (c==77)
     {
       sound (500);
       delay (50);
       nosound();
       cleardevice ();
       x=420;
       goto q;
     }
   }//while
   cleardevice();
   if  (x==420)
   exit (1);
   else
   if (x==70)   //this needs to be fixed
   startup (0); //UPDATE :Fixed
 }
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include<time.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>
#include <process.h>
#include "std.h"
#include <string.h>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

int score;
int length;
int bend_no;
int len;
char key;
int life;

struct coordinate{
    int x;
    int y;
    int direction;
};
typedef struct coordinate coordinate;

coordinate head, bend[500],food,body[30];

void GotoXY(int x, int y)
{
    HANDLE a;
    COORD b;
    fflush(stdout);
    b.X = x;
    b.Y = y;
    a = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(a,b);
 }
void load(){
    int row,col,r,c,q;
    gotoxy(78,18);
    printf("loading...");
    gotoxy(72,20);
    for(r=1;r<=20;r++){
    for(q=0;q<=100000000;q++);
    printf("%c",177);}
    getch();
}

void Delay(long double k)
{
    Score();
    long double i;
    for(i=0;i<=(10000000);i++);
}

void Boarder()
{
   clear_ular();
   int i;
   GotoXY(food.x,food.y);
   		printfColor(0,0," ");
   for(i=30;i<131;i++)
   {
       GotoXY(i,10);
    		printfColor(2, 12, " ");
       GotoXY(i,42);
       		printfColor(2, 12, " ");
   }
   for(i=10;i<43;i++)
   {
       GotoXY(30,i);
       		printfColor(2, 12, " ");
       GotoXY(130,i);
    	printfColor(2, 12, " ");
   }
}

void Bend()
{
    int i,j,diff;
    for(i=bend_no;i>=0&&len<length;i--)
    {
            if(bend[i].x==bend[i-1].x)
            {
                diff=bend[i].y-bend[i-1].y;
                if(diff<0)
                    for(j=1;j<=(-diff);j++)
                    {
                        body[len].x=bend[i].x;
                        body[len].y=bend[i].y+j;
                        GotoXY(body[len].x,body[len].y);
                        printfColor(4,10," ");
                        len++;
                        if(len==length)
                            break;
                    }
                else if(diff>0)
                    for(j=1;j<=diff;j++)
                    {
                        body[len].x=bend[i].x;
                        body[len].y=bend[i].y-j;
                        GotoXY(body[len].x,body[len].y);
                        printfColor(4,10," ");
                        len++;
                        if(len==length)
                            break;
                    }
            }
        else if(bend[i].y==bend[i-1].y)
        {
            diff=bend[i].x-bend[i-1].x;
            if(diff<0)
                for(j=1;j<=(-diff)&&len<length;j++)
                {
                    body[len].x=bend[i].x+j;
                    body[len].y=bend[i].y;
                    GotoXY(body[len].x,body[len].y);
                    	printfColor(4,10," ");
                   len++;
                   if(len==length)
                           break;
               }
           else if(diff>0)
               for(j=1;j<=diff&&len<length;j++)
               {
                   body[len].x=bend[i].x-j;
                   body[len].y=bend[i].y;
                   GotoXY(body[len].x,body[len].y);
                		printfColor(4,10," ");
                   len++;
                   if(len==length)
                       break;
               }
       }
   }
}

void Food()
{
    if(head.x==food.x&&head.y==food.y)
    {
        length++;
        time_t a;
        a=time(0);
        srand(a);
        food.x=rand()%70;
        if(food.x<=30)
            food.x+=31;
        food.y=rand()%30;
        if(food.y<=10)
            food.y+=11;
    }
    else if(food.x==0)//makanan pertama kali
    {
        food.x=rand()%70;
        if(food.x<=30)
            food.x+=31;
        food.y=rand()%30;
        if(food.y<=10)
            food.y+=11;
    }
}
void ExitGame()
{
    int i,check=0;
    for(i=4;i<length;i++)   //starts with 4 because it needs minimum 4 element to touch its own body
    {
        if(body[0].x==body[i].x&&body[0].y==body[i].y)
        {
            check++;    //check's value increases as the coordinates of head is equal to any other body coordinate
        }
        if(i==length||check!=0)
            break;
    }
    if(head.x<=30||head.x>=130||head.y<=10||head.y>=42||check!=0)
    {
        life--;
        if(life>=0)
        {
            head.x=25;
            head.y=20;
            bend_no=0;
            head.direction=RIGHT;
            Move();
        }
        else //fungsi KALO MATI
        {
            window_meninggal();
            system("cls");
            start();
        }
    }
}

int Score()
{
   GotoXY(60,8);
   score=(length-5);
   printf("SCORE : %d",(length-5)*10);
   score=(length-5)*10;
   GotoXY(50,8);
   printf("Life : %d",life);
   gotoxy(0,0);
   return score;
}

void input_score(char hiscore[]){
	char username_temp[10];
	char comma[10] = ",";
	printf("MASUKAN USERNAME: ");
	scanf("%s", &username_temp);
	strcat(username_temp, comma);
	strcat(hiscore, comma);
	
	FILE *fappendusername = fopen("USERNAME.txt", "a");
	fputs(username_temp, fappendusername);
	fclose(fappendusername);
	
	FILE *fappendscore = fopen("HIGHSCORE.txt", "a");
	fputs(hiscore, fappendscore);
	fclose(fappendscore);
}


//FUNGSI PERGERAKAN ULER
void Down()
{
    int i;
    for(i=0;i<=(head.y-bend[bend_no].y)&&len<length;i++)
    {
        GotoXY(head.x,head.y-i);
        {
            if(len==0)
                //printf("v");
                printfColor(4,10," ");
            else
                //printf("*");
                printfColor(4,10," ");
        }
        body[len].x=head.x;
        body[len].y=head.y-i;
        len++;
    }
    Bend();
    if(!kbhit())
        head.y++;
}

void Up()
{
   int i;
   for(i=0;i<=(bend[bend_no].y-head.y)&&len<length;i++)
   {
       GotoXY(head.x,head.y+i);
       {
           if(len==0)
           		printfColor(3,4," ");
               //printf("^");
           else
           		printfColor(4,10," ");
               //printf("*");
       }
       body[len].x=head.x;
       body[len].y=head.y+i;
       len++;
   }
   Bend();
   if(!kbhit())
       head.y--;
}

void Right()
{
    int i;
    for(i=0;i<=(head.x-bend[bend_no].x)&&len<length;i++)
    {
        body[len].x=head.x-i;
        body[len].y=head.y;
        GotoXY(body[len].x,body[len].y);
        {
            if(len==0)
            	printfColor(3,4," ");
            else
            	printfColor(4,10," ");
        }
        len++;
    }
    Bend();
    if(!kbhit())
        head.x++;
}

void Left()
{
    int i;
    for(i=0;i<=(bend[bend_no].x-head.x)&&len<length;i++)
    {
        GotoXY((head.x+i),head.y);
       {
                if(len==0)
                	printfColor(3,4," ");
                else
                	printfColor(4,10," ");
        }
        body[len].x=head.x+i;
        body[len].y=head.y;
        len++;
    }
    Bend();
    if(!kbhit())
        head.x--;
}

void Move()
{
    int a,i;
    do{
        Food();
        fflush(stdin);
        len=0;
        for(i=0;i<30;i++)
        {
            body[i].x=0;
            body[i].y=0;
            if(i==length)
            break;
        }
        Delay(length);
        Boarder();
        if(head.direction==RIGHT)
            Right();
        else if(head.direction==LEFT)
            Left();
        else if(head.direction==DOWN)
            Down();
        else if(head.direction==UP)
            Up();
        ExitGame();
    }while(!kbhit());
    a=getch();
    if(a==27)
    {
        system("cls");
        exit(0);
    }
    key=getch();
    if((key==RIGHT&&head.direction!=LEFT&&head.direction!=RIGHT)||(key==LEFT&&head.direction!=RIGHT&&head.direction!=LEFT)||(key==UP&&head.direction!=DOWN&&head.direction!=UP)||(key==DOWN&&head.direction!=UP&&head.direction!=DOWN))
    {
        bend_no++;
        bend[bend_no]=head;
        head.direction=key;
        if(key==UP)
            head.y--;
        if(key==DOWN)
            head.y++;
        if(key==RIGHT)
            head.x++;
        if(key==LEFT)
            head.x--;
        Move();
    }
    else if(key==27)
    {
        system("cls");
        exit(0);
    }
    else
    {
        printf("\a");
        Move();
    }
}


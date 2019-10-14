#include "header_ular.h"

void window_HS(){
	int x=0,y=0,ch1,ch2,counter=1;
	char hscore[10][10];
	char username[10][10];
	gotoxy(0,3);
	
	FILE *fptr; 
	char filename[100], c; 
	fptr = fopen("judul skor.txt", "r"); 
	if (fptr == NULL) 
	{ 
		printf("Cannot open file \n"); 
		exit(0); 
	}  
	c = fgetc(fptr); 
	while (c != EOF) 
	{ 
		printf ("%c", c); 
		c = fgetc(fptr); 
	} 
	fclose(fptr);
	boxBorder(59,10,27,5,12,2,1);
	boxBorder(84,10,27,5,12,2,1);
	boxBorder(59,14,27,25,12,2,1);
	boxBorder(84,14,27,25,12,2,1);
	
	gotoxy(68,12);
	printf("USERNAME");
	gotoxy(95,12);
	printf("SCORES");
	
	boxBorder(66,40,14,3,4,2,1);
	boxBorder(90,40,14,3,12,2,1);
	gotoxy(70,41);
	printfColor(1,15,"RETURN");
	gotoxy(95,41);
	printfColor(0,15,"CLEAR");
	gotoxy(1,1);	
		
	FILE *fp = fopen("USERNAME.txt", "r");
	int i=0;
	while(1){
		char r = (char)fgetc(fp);
		int k = 0;
		while(r!=44 && !feof(fp)){
			username[i][k++] = r;
			r = (char)fgetc(fp);
		}
		username[i][k]=0;
		if(feof(fp)){
			break;
		}
		i++;
	}
	FILE *fp1 = fopen("HIGHSCORE.txt", "r");
	int j=0;
	while(1){
		char r = (char)fgetc(fp1);
		int k = 0;
		while(r!=44 && !feof(fp1)){
			hscore[j][k++] = r;
			r = (char)fgetc(fp1);
		}
		hscore[j][k]=0;
		if(feof(fp1)){
			break;
		}
		j++;
	}
	for(j=0;j<strlen(username);j++){
		gotoxy(63,16+x);
		printf("%s", username[j]);
		x+=2;
	}
	for(j=0;j<strlen(hscore);j++){
		gotoxy(96,16+y);		
		printf("%s\n", hscore[j]);
		y+=2;
	}	
	
	while(1){
		ch1 = getch();
    	ch2 = 0;
		if(ch1 == 0xE0 || ch1 == 0xD){
			ch2 = getch();
			switch(ch2){
				case 77://kanan
					if(counter==2) continue;
					else counter += 1;
					break;
				case 75://kiri
					if(counter==1) continue;
					else counter -= 1;
					break;
				case 13:
					if(counter==1){
						system("cls");
						start();
					}
					else if(counter==2){
						fclose(fopen("USERNAME.txt","w"));
						fclose(fopen("HIGHSCORE.txt","w"));
						system("cls");
						window_HS();
					}
			}
    		if(counter==1){
				boxBorder(66,40,14,3,4,2,1);
				boxBorder(90,40,14,3,12,2,1);
				gotoxy(70,41);
				printfColor(1,15,"RETURN");
				gotoxy(95,41);
				printfColor(0,15,"CLEAR");
				gotoxy(1,1);
			}
			else if(counter==2){
				boxBorder(66,40,14,3,12,2,1);
				boxBorder(90,40,14,3,4,2,1);
				gotoxy(70,41);
				printfColor(0,15,"RETURN");
				gotoxy(95,41);
				printfColor(1,15,"CLEAR");
				gotoxy(1,1);
			}
		}
	}
}

void window_Play(){
	char key;
    load();
    length=15;
    head.x=55;
    head.y=20;
    head.direction=RIGHT;
    Boarder();
    Food(); 
    life=0; //jumlah nyawa
    bend[0]=head;
    Move();
    return 0;
}

int window_main(){
	int counter = 1, ch1,ch2;
	system("COLOR F2");
	gotoxy(0,18);
	
	FILE *fptr; 
	char filename[100], c; 
	fptr = fopen("judul.txt", "r"); 
	if (fptr == NULL) 
	{ 
		printf("Cannot open file \n"); 
		exit(0); 
	}  
	c = fgetc(fptr); 
	while (c != EOF) 
	{ 
		printf ("%c", c); 
		c = fgetc(fptr); 
	} 
	fclose(fptr);  
	
	boxBorder(75,27,21,5,4,2,1);
	gotoxy(81,29);
	printfColor(1,15,"PLAY GAME");
	
	boxBorder(75,33,21,5,12,2,1);
	gotoxy(81,35);
	printfColor(0,15,"HIGH SCORE");
	gotoxy(1,1);
	
	while(1){
		ch1 = getch();
    	ch2 = 0;
		if(ch1 == 0xE0 || ch1 == 0xD){
			ch2 = getch();
			switch(ch2){
				case 80://bawah
					if(counter==2) continue;
					else counter += 1;
					break;
				case 72://atas
					if(counter==1) continue;
					else counter -= 1;
					break;
				case 13:
					if(counter==1){
						system("cls");
						return 2;
					}
					else if(counter==2){
						system("cls");
						return 3;
					}
			}
    		if(counter==1){
    			boxBorder(75,27,21,5,4,2,1);
				gotoxy(81,29);
				printfColor(1,15,"PLAY GAME");
	
				boxBorder(75,33,21,5,12,2,1);
				gotoxy(81,35);
				printfColor(0,15,"HIGH SCORE");
				gotoxy(1,1);
			}
			else if(counter==2){
    			boxBorder(75,27,21,5,12,2,1);
				gotoxy(81,29);
				printfColor(0,15,"PLAY GAME");
	
				boxBorder(75,33,21,5,4,2,1);
				gotoxy(81,35);
				printfColor(1,15,"HIGH SCORE");
				gotoxy(1,1);
			}
		}
	}
}

void window_meninggal(){
	char string_score[10];
	itoa(score, string_score, 10);
	system("cls");
	gotoxy(0,15);
	
	FILE *fptr; 
	char filename[100], c; 
	fptr = fopen("gameover.txt", "r"); 
	if (fptr == NULL) 
	{ 
		printf("Cannot open file \n"); 
		exit(0); 
	}  
	c = fgetc(fptr); 
	while (c != EOF) 
	{ 
		printf ("%c", c); 
		c = fgetc(fptr); 
	} 
	fclose(fptr);
	gotoxy(75,24);
	printf("SCORE: %d", score);
	gotoxy(75,23);
	input_score(string_score);
}

///NAMA : MUHAMMAD DAFFA ABIYYU RAHMAN
///NRP  : 2916100010
///GAME : SNAKE SURVIVAL

#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <wincon.h>
#define STRMAX 50
#define TotShopItem 4

void Reset();

int Diff, Player, xS, yS, xB[999], yB[999], xLH=1, yLV=1, xLB[999], yLB[999], sLB[999], TotBul=-1, DelayVer, DelayHor, sLH=0, sLV=0, len=0;
int Score=0, GRate=0, menu, GType=0, GMode=0, Life=0, DelayLas=28, DelayApply=15, LaserCD=0, LaserState=0;
int xLaser[68], yLaser[68],Reveal=0,Pts,ItemPrice[TotShopItem],LifeCost=200;
char PurchaseStat[TotShopItem], ItemName[TotShopItem][STRMAX];
COORD coord = {0,0};
short n;

void gotoxy(int x, int y){
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Colorize(unsigned short c){
    HANDLE Color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(Color , c);
}


void Load(){
    FILE *fp;
    char data[255];

    fp = fopen("/SSS.txt", "r+");
    fgets(data,255,fp);
    fclose(fp);
    Pts = atoi(data);
}

void Save(){
    FILE *fp;
    char data[255];

    sprintf(data, "%d", Pts);
    fp = fopen("/SSS.snk", "w");
    fputs(data, fp);
    fclose(fp);
}

void ItemEffect(int x){
    switch (x){
        case 0:printf("Impossible Mode Unlocked!");break;
        case 1:LifeCost = LifeCost-25;break;
        case 2:printf("Your snake is now Green!");break;
        case 3:printf("Time Attack Ultimate Challenge Mode Unlocked!");break;
    }
}

void SnakeMove(){
    int i, tX, tY;

    tX = xB[0];
    tY = yB[0];

    xB[0] = xS;
    yB[0] = yS;

    for (i=len;i>0;i--){
        if (i>1){
            xB[i] = xB[i-1];
            yB[i] = yB[i-1];
        }else{
            xB[i] = tX;
            yB[i] = tY;
        }
    }
}

void LaserMoveHor()
{
    if (sLH==0 && xLH==68){
        sLH = 1;///LEFT
    }else if (sLH==1 && xLH==1){
        sLH = 0;///RIGHT
    }

    if (sLH==0){
        xLH++;
    }else{xLH--;}
    gotoxy(xLH,0);
}

void LaserMoveVer()
{
    if (sLV==0 && yLV==28){
        sLV = 1;///UP
    }else if (sLV==1 && yLV==1){
        sLV = 0;///DOWN
    }

    if (sLV==0){
        yLV++;
    }else{yLV--;}
}

void BulletHorizontal(){
    TotBul++;
    xLB[TotBul] = xLH;
    yLB[TotBul] = 1;
    sLB[TotBul] = 0; ///VERTICAL BULLET
}
void BulletVertical(){
    TotBul++;
    xLB[TotBul] = 1;
    yLB[TotBul] = yLV;
    sLB[TotBul] = 1; ///HORIZONTAL BULLET
}
void LaserPrep(){
    int i;
    for (i=0;i<68;i++){
        xLaser[i]=i+1;
        yLaser[i]=yLV;
    }
}

void LaserView(){
    int i;
    for (i=0;i<68;i++){
        if (GMode<5 || Reveal==1)
            gotoxy(xLaser[i],yLaser[i]);printf(".");
    }
}

int LaserFire(){
    int i,j,x=0;
    Colorize(04);
    for (i=0;i<68;i++){
        if(GMode<5 || Reveal==1)
            gotoxy(xLaser[i],yLaser[i]);printf("-");

        for(j=0;j<=len;j++){
            if (xLaser[i]==xB[j] && yLaser[i]==yB[j] ){
                x++;
                break;
            }
        }
        xLaser[i]=0;
        yLaser[i]=0;
    }
    Colorize(07);
    return x;
}

void BulletMove()
{
    int i,j;
    Colorize(15);
    for (i=0;i<=TotBul;i++){
        if (sLB[i]==1){///HORIZONTAL
            xLB[i]++;
            if (xLB[i]==68){
                for (j=i;j<=TotBul;j++){
                    xLB[j]=xLB[j+1];
                    yLB[j]=yLB[j+1];
                    sLB[j]=sLB[j+1];
                }
            }else{
                if (GMode<5 || Reveal==1)
                {gotoxy(xLB[i], yLB[i]);printf(">");}
            }
        }else{///VERTICAL
            yLB[i] = yLB[i]+1;
            if (yLB[i]==68){
                for (j=i;j<=TotBul;j++){
                    xLB[j]=xLB[j+1];
                    yLB[j]=yLB[j+1];
                    sLB[j]=sLB[j+1];
                }
            }else{
                if (GMode<5 || Reveal==1)
                {gotoxy(xLB[i], yLB[i]);printf("V");}
            }
        }
    }
    Colorize(07);
}

int BulletHit()
{
    int i,j,k,x=0;
    for (i=0;i<=len;i++){
        for (j=0;j<=TotBul;j++){
            if(xB[i]==xLB[j] && yB[i]==yLB[j]){
                x=1;
                for (k=j;k<=TotBul;k++){
                    xLB[k]=xLB[k+1];
                    yLB[k]=yLB[k+1];
                    sLB[k]=sLB[k+1];
                }
                break;
            }
        }
        if (x==1){
            break;
        }
    }
    return x;
}

void MainMenu()
{
    printf("WELCOME TO SNAKE SURVIVAL!\n");
    printf("CURRENT POINTS : %d\n", Pts);
    printf("1. PLAY\n");
    printf("2. HOW TO PLAY\n");
    printf("3. SHOP\n");
    printf("4. EXIT\n");
    printf("CHOOSE : ");scanf("%d",&menu);
    system("cls");
}

void DiffMenu()
{
    printf("Choose Difficulty : \n");
    printf("1. Easy\n2. Medium\n3. Hard\n4. Chaos\n5. Impossible (Requires Purchase)\n\n");
    scanf("%d", &Diff);
    switch (Diff){
        case 1 : printf("Easy Difficulty!");Life=3;len = 2;DelayHor=15;DelayVer=14;GRate=1;break;
        case 2 : printf("Medium Difficulty!");Life=3;len = 3;DelayHor=12;DelayVer=13;GRate=2;break;
        case 3 : printf("Hard Difficulty!");Life=2;len = 5;DelayHor=9;DelayVer=8;GRate=3;break;
        case 4 : printf("Chaos Difficulty!");Life=2;len = 7;DelayHor=7;DelayVer=5;GRate=5;break;
        case 5 : if (PurchaseStat[0]=='X'){printf("Impossible Difficulty!");Life=1;len = 10;DelayHor=3;DelayVer=5;GRate=10;break;}
        default : printf("Unknown Difficulty! Set to Medium.");Life=3;len = 3;DelayHor=12;DelayVer=13;GRate=2;break;
    }
    printf("\n\nPRESS ANY KEY TO CONTINUE");getch();
    system("cls");
}

void PlayerMenu(){
    printf("Choose Movement Mode :\n1. Normal\n2. Inverse\n3. Diagonal\n");
    scanf("%d", &Player);
    switch (Player){
        case 1 : printf("Normal Movement Mode!");GType=1;break;
        case 2 : printf("Inverse Movement Mode!");GType=2;break;
        case 3 : printf("Diagonal Movement Mode!");GType=3;break;
        default : printf("Invalid Choice! Set to Default!");GType=1;break;
    }
    printf("\n\nPRESS ANY KEY TO CONTINUE");getch();
    system("cls");
}

void GameMenu(){
    printf("Choose Game Mode :\n1. Normal\n2. Speed Rush\n3. Laser Beams\n4. Speed Laser\n5. Invisible\n6. Invisible Rush");
    printf("\n7. Invisible Laser\n8. Ultimate Challenge\n9. Time Attack Ultimate Challenge (Requires Purchase)\n");
    scanf("%d", &GMode);
    switch (GMode){
        case 1:printf("Normal Game Mode!");break;
        case 2:printf("Speed Rush Mode! 2x Faster!");break;
        case 3:printf("Laser Beam Mode! Random Laser Shots");break;
        case 4:printf("Laser & Speed Mode Combo!");break;
        case 5:printf("Invisible Mode! Walls and Bullets are unseen!");break;
        case 6:printf("Speed Rush & Invisible Combo! Walls and Bullets are unseen");break;
        case 7:printf("Invisible & Laser Combo! Walls, Bullets and Laser are unseen!");break;
        case 8:printf("Ultimate Mode Selected! Walls, Bullets and Laser are unseen!");break;
        case 9:if (PurchaseStat[3]=='X'){printf("Time Attack Ultimate Challenge! Walls, Bullets and Laser are unseen!");break;}
        default : printf("Invalid Game Mode! Setting to Default!");GMode=1;break;
    }
    if (GMode>4){printf("\nThere will be a short reveal, use it wisely.");}
    printf("\n\nPRESS ANY KEY TO CONTINUE");getch();
    system("cls");
}

void Game()
{
    int i, Counter=0, Cont=0, temp=0;
    xB[0]=30;
    yB[0]=15;
    xS=xB[0];
    yS=yB[0];
    int TimeRemaining=1250;
    unsigned char c;
    for (i=1;i<=len;i++){
        xB[i]= xB[i-1]+1;
        yB[i]= yB[i-1];
    }

    while(1){
        if (GMode==2 || GMode==5 || GMode==6 || GMode>=8)
            delay(80);
        else
            delay(160);

        system("cls");
        Reveal = 0;
        Score = Score+(GRate*GType*GMode);
        if (kbhit()){
            c = getch();
            if (c==224){
                c=getch();
            }

            if(c==77){
                if (GType==1)
                    xS=xS+1;///Right
                else if (GType==2)
                    xS=xS-1;
                else if (GType==3){
                    xS=xS+1;
                    yS=yS+1;
                }
            }

            if(c==75){
                if (GType==1)
                    xS=xS-1;///Left
                else if (GType==2)
                    xS=xS+1;
                else if (GType==3){
                    xS=xS-1;
                    yS=yS-1;
                }
            }

            if(c==72){
                if (GType==1)
                    yS=yS-1;///Up
                else if (GType==2)
                    yS=yS+1;
                else if (GType==3){
                    yS=yS-1;
                    xS=xS+1;
                }
            }

            if(c==80){
                if (GType==1)
                yS=yS+1;///Down
                else if (GType==2)
                yS=yS-1;
                else if (GType==3){
                    yS=yS+1;
                    xS=xS-1;
                }
            }
            if (c==27){///Main Menu (Escape)
                system("cls");
                break;
            }
            if (c==32){///Add Life (Space)
                if (Score>(LifeCost*Diff)){
                    Life++;
                    Score = Score-(LifeCost*Diff);
                }
            }
            SnakeMove();
            if (Counter==len){
                Counter = 0;
                len++;
                Score = Score+(GRate*GRate*GType*GMode);
            }else{Counter++;}
        }
        LaserMoveHor();
        LaserMoveVer();
        Cont++;
        if (Cont%DelayHor==0){
            BulletHorizontal();
            Reveal=1;
        }
        if (Cont%DelayVer==0){
            BulletVertical();
            Reveal=1;
        }
        if (Cont%(DelayLas/Diff)==0 && (GMode==3 || GMode==4 || GMode>=7)){
            LaserPrep();
            Reveal=1;
            LaserState = 1;
            LaserView();
        }
        if (LaserState==1){
            if (GMode<5)
                LaserView();
            LaserCD++;
            if (LaserCD == (DelayApply/Diff)){
                Reveal = 1;
                LaserCD = 0;
                LaserState = 0;
                Life = Life-LaserFire();
            }
        }
        if (Cont==30){
            Cont = 0;
        }
        BulletMove();
        if (GMode<5 || Reveal==1){
            for (i=0;i<70;i++){
                gotoxy(i, 0);printf("X");
                gotoxy(i, 29);printf("X");
            }
            for (i=0;i<30;i++){
                gotoxy(0, i);printf("Y");
                gotoxy(69, i);printf("Y");
            }
        }
        gotoxy(75,0);printf("SCORE : %d", Score);
        Colorize(12);gotoxy(75,2);printf("LIFE : %d", Life);
        Colorize(12);gotoxy(75,4);printf("LENGTH : %d", len);
        if (GMode==9){TimeRemaining--;Colorize(15);gotoxy(75,4);printf("TIME REMAINING : %d", TimeRemaining);}
        Colorize(07);
        if (BulletHit()==1){
            Life--;
            Colorize(12);
        }
        for (i=0;i<=len;i++){
            if (PurchaseStat[2]=='X')
                Colorize(02);
            else
                Colorize(07);
            gotoxy(xB[i],yB[i]);
            if (i>0)
                printf("O");
            else
                printf("Q");
        }
        Colorize(07);
        if (xS==0 || yS==0 || xS==69 || yS==29 || Life<=0 || TimeRemaining==0){
            break;
        }
    }
    system("cls");
    printf("GAME OVER! YOUR FINAL SCORE : %d\n\n", Score);
    temp = (Score/100);
    if (GMode==9 && TimeRemaining==0)
        temp = temp+200;
    Pts = Pts + temp;
    printf("YOU EARNED %d POINTS\n", temp);
    getch();
    Reset();
}

void Loading(){
    int x;

    if (menu==1 && GType!=0 && Diff!=0 && GMode!=0){
        for(x=0;x<100;x++){
            delay(35);gotoxy(10+x,20);
            Colorize(55);printf(" ");
            Colorize(07);gotoxy(45,22);
            if (x<30)
                printf("Establishing Data...");
            if (x>=30 && x<65)
                printf("Preparing the Snake...");
            if (x>=65 && x<80)
                printf("Preparing Anti-Snake...");
            if (x>=80)
                printf("Activating Grow Field...");
        }
    }else if (menu==1){
        for(x=0;x<100;x++){
            delay(15);gotoxy(10+x,20);
            Colorize(66);printf(" ");
            Colorize(07);gotoxy(45,22);printf("Preparing Data...");
        }
    }else if (menu==2){
        for(x=0;x<100;x++){
            delay(10);gotoxy(10+x,20);
            Colorize(77);printf(" ");
            Colorize(07);gotoxy(45,22);printf("Acessing Manual...");
        }
    }else if(menu==3){
        for(x=0;x<100;x++){
            delay(20);gotoxy(10+x,20);
            Colorize(33);printf(" ");
            Colorize(07);gotoxy(45,22);
            if (x<65)
                printf("To Pet Shop...");
            else
                printf("Calling Shop Owner...");
        }
    }else if(menu==4){
        for(x=0;x<100;x++){
            delay(15);gotoxy(10+x,20);
            Colorize(44);printf(" ");
            Colorize(07);gotoxy(45,22);printf("Saving Data...");
        }
    }else if(menu==0){
        for(x=0;x<100;x++){
            delay(30);gotoxy(10+x,20);
            Colorize(45);printf(" ");
            Colorize(07);gotoxy(45,22);printf("Loading Data...");
        }
    }
    Colorize(07);
    gotoxy(45,22);printf("PRESS ANY KEY TO CONTINUE");
    getch();
    Colorize(10);
    system("cls");
    Colorize(07);
}

void HowTo()
{
    system("cls");
    printf("HOW TO PLAY\n");
    printf("Control the O Snake using Arrow Keys and prevent any part of the body hit by V and > Bullets.\n");
    printf("The Snake slowly grows because the field is mutated with growing chemicals, be careful!\n");
    printf("At expense of LifeCost*Difficulty Level Score, you can restore 1 life by pressing Spacebar. Use it wisely.\n");
    printf("At end of game, you earn Score/100 Points for items at the shop.\n");
    printf("To end a game prematurely, press ESC.\n");
    printf("THE GAME REQUIRES ADMIN MODE TO UTILIZE SAVE LOAD FEATURE!\n");
    printf("Purchased items at shop aren't kept, so re-purchase is needed everytime the game is restarted.\n");

    gotoxy(35,13);printf("PRESS ANY KEY TO RETURN TO MAIN MENU");
    getch();
    system("cls");
    Reset();
}

void Shop()
{
    printf("WELCOME TO SNAKE SURVIVAL SHOP!\n");
    printf("How may I help you?\n");

    int p;

    strcpy(ItemName[0], "1. Impossible Difficulty (10 Pts)");ItemPrice[0]=10;
    strcpy(ItemName[1], "2. Life Score Cost -25 (5 Pts)");ItemPrice[1]=5;
    strcpy(ItemName[2], "3. Green Colour Snake (3 Pts)");ItemPrice[2]=3;
    strcpy(ItemName[3], "4. Time Attack Ultimate Challenge Game Mode (15 Pts)");ItemPrice[3]=15;

    for (p=0;p<TotShopItem;p++){
        if (PurchaseStat[p]!='X'){
            Colorize(15);
            printf("Purchase : ");
        }else{
            Colorize(12);
            printf("[PURCHASED] ");
        }
        printf("%s\n", ItemName[p]);
    }
    Colorize(15);
    printf("0 TO LEAVE STORE\n");

    printf("CHOOSE ITEM : ");scanf("%d",&p);p--;

    if (p==-1){
        p=0;
        Colorize(15);
        printf("Thanks for coming!");
        getch();
        system("cls");
        Reset();
    }else if (p<-1 || p>=TotShopItem){
        printf("Invalid Item Selected");
    }else if (PurchaseStat[p]=='X'){
        printf("Already Purchased");
    }else if (Pts<ItemPrice[p]){
        printf("Insufficient Points!");
    }else {
        PurchaseStat[p] = 'X';
        ItemEffect(p);
        Pts = Pts-ItemPrice[p];
    }
    if (menu==3 && p!=-1){
        system("cls");
        Shop();
    }
}

int main()
{
    Load();
    MainMenu();
    Loading();
    switch (menu){
        case 1 : DiffMenu();PlayerMenu();GameMenu();Loading();Game();break;
        case 2 : HowTo();break;
        case 3 : Shop();break;
        case 4 : Save();return 0;break;
    }
    return 0;
}

void Reset()
{
    xLH=1;
    yLV=1;
    TotBul=-1;
    sLH=0;
    sLV=0;
    len=0;
    Score=0;
    GRate=0;
    LaserState=0;
    Life=0;
    LaserCD=0;
    LaserState=0;
    menu=0;GType=0;GMode=0;Diff=0;

    int i;

    for (i=0;i<999;i++){
        xB[i] = 0;
        yB[i] = 0;
        xLB[i] = 0;
        yLB[i] = 0;
        if (i<68){
            xLaser[i]=0;
            yLaser[i]=0;
        }
    }
    Save();Loading();main();
}

///MUHAMMAD DAFFA ABIYYU RAHMAN
///2916100010
///TMJ KELAS A

///LIBRARIES
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

///FUNCTIONS
int Menu();
void Colorize(unsigned short c);
int GetMonthCal(int i, int l);
int CMonth(int k, int l);
long CDays(int i, int j);

///GLOBALS
int MIn, YIn;
int order=0;

///PROGRAM

int main()
{
    int Day, i;
    char *str1;

    Colorize(07);
    if (order==0){
        printf("Year : ");scanf("%d", &YIn);
        printf("Month : ");scanf("%d", &MIn);

        if (MIn>12 || MIn<1){
            system("cls");
            Colorize(12);printf("Invalid Month!\n\n");
            main();
        }
        if (YIn<1){
            system("cls");
            Colorize(12);printf("Invalid Year!");
            main();
        }
    }else if (order==1){
        if (MIn==12){
            YIn++;
            MIn=1;
        }else{
            MIn++;
        }
    }else if (order==2){
        if (MIn==1){
            YIn--;
            MIn=12;
        }else{
            MIn--;
        }
    }else if(order==3){
        YIn++;
    }else if(order==4){
        YIn--;
    }

    Day = CDays(YIn, MIn)%7;

    switch (MIn){
        case 1 : str1 = "January";break;
        case 2 : str1 = "February";break;
        case 3 : str1 = "March";break;
        case 4 : str1 = "April";break;
        case 5 : str1 = "May";break;
        case 6 : str1 = "June";break;
        case 7 : str1 = "July";break;
        case 8 : str1 = "August";break;
        case 9 : str1 = "September";break;
        case 10 : str1 = "October";break;
        case 11 : str1 = "November";break;
        case 12 : str1 = "December";break;
    }

    printf("%s %d C\n\n", str1, YIn);
    printf("======================================================\n");
    Colorize(12);printf("MINGGU");
    Colorize(15);printf("\tSENIN\tSELASA\tRABU\tKAMIS\tJUM'AT\t");
    Colorize(02);printf("SABTU\n");
    Colorize(15);printf("======================================================\n");

    for (i=1;i<Day+2;i++){
        if (Day!=6){
            printf("\t");
        }
    }

    for (i=1;i<=GetMonthCal(MIn,YIn);i++){
        if (Day%7==6 && i!=1){
            printf("\n");
        }
        if ((i==10 && MIn==11) || (i==17 && MIn==8)|| (i==1 && MIn==1) || Day%7==6){
            Colorize(12);
        }else if (Day%7==5){
            Colorize(02);
        }else{
            Colorize(15);
        }
        printf("%d",i);
        printf("\t");
        Day++;
    }

    Menu();

    return 0;
}


int Menu(){
    int cho;

    Colorize(07);
    printf("\n\nMenu :\n");
    printf("1. Return to Month and Year Selection\n");
    printf("2. Next Month\n");
    printf("3. Prev Month\n");
    printf("4. Next Year\n");
    printf("5. Prev Year\n");
    printf("0. Close Application\n");
    ///Make Full Year View and Input Mode Switcher next...

    printf("\nInput a number to continue :");scanf("%d", &cho);
    system("cls");
    switch (cho){
        case 0 : return 0;break;
        case 1 : order=0;break;
        case 2 : order=1;break;
        case 3 : order=2;break;
        case 4 : order=3;break;
        case 5 : order=4;break;
        case 6 : order=5;break;
        default : printf("Invalid Choice!"); Menu();break;
    }
    main();
}

void Colorize(unsigned short c){
    HANDLE Color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(Color , c);
}


int GetMonthCal(int i, int l){
    int res=0;
    if (i==2){
        if (l%4==0 && l%100!=0){
            res = 29;
        }else if (l%400==0){
            res = 29;
        }else{
            res = 28;
        }
    }else if((i%2==1 && i<8) || (i%2==0 && i>7)){
        res = 31;
    }else{
        res = 30;
    }
    return res;
}

int CMonth(int k, int l){
    int i, res=0;

    for (i=1;i<k;i++){
        res = res+GetMonthCal(i,l);
    }
    return res;
}

long CDays(int i, int j){
    long res = 0;
    i = i-1;
    res = (i*365)+(i/4)-(i/100)+(i/400);
    i = i+1;
    res = res + CMonth(j,i);
    return res;
}

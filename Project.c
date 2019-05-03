// #Bora Arslan          #383218 #bora-arslan@outlook.com        #Struct Islemleri
// #Huseyin Can Celikkol #383258 #huseyincancelikkol@hotmail.com #Dosya okuma yazma islemleri
#include <stdio.h>
#include <stdlib.h>

typedef unsigned int uint;

typedef struct teams{
    char lname[13];
    char cname[13];
    char sname;
    uint played;
    uint won;
    uint lost;
    uint draw;
    uint pscore;
    uint nscore;
    int difference;
    int points;
    char* mchart;
} Team;

int NumberOfTeams = 10;                                      //Takim sayisini tutan degisken
int *AddressOfNumberOfTeams = &NumberOfTeams;                //Takim sayisinin pointeri
Team *AdressToStartOfTeams;
int* PointArray;
int* AlphabetArray;
int PointsForWin = 2;
int PointsForLose = -1;
int PointsForDraw = 1;

void CopyString(char from[], char to[]){
    uint i = 0;
    for (; from[i] != '\0'; i++){
        to[i] = from[i];
    }
    to[i] = '\0';
}

void CapitalLetter(char smallarray[] , char bigarray[]){
    for(int i = 0 ; smallarray[i] !='\0'; i++){
        if((int)(smallarray[i]) > 96){
            bigarray[i] = smallarray[i] - 32;
        }
        else{
            bigarray[i] = smallarray[i];
        }
        
    }
}

Team *MoveStruct(int shift){
    return (AdressToStartOfTeams + shift);
}

void AllocateMemory(int TeamCount){
    AdressToStartOfTeams = calloc(sizeof(Team), TeamCount);
    for (int i = 0; i <= TeamCount; i++){
        MoveStruct(i)->mchart = (char *)calloc(sizeof(char), TeamCount);
    }
    PointArray = calloc(sizeof(int) , TeamCount);
    AlphabetArray = calloc(sizeof(int) , TeamCount);
}

void ReadTeamNumberFromFile(int *address){                       //Takim sayisi verisini almaak icin ornek fonksiyon
    FILE* fp = fopen("ayarlar.txt", "r");
    if(fp == NULL){
        printf("ayarlar dosyasi bulunamadi.\n");
        return;
    }
    fscanf(fp , "%d" , address);
    fclose(fp);
}


void ReadPointsFromFile(){
    FILE* fp = fopen("ayarlar.txt", "r");
    if(fp == NULL){
        printf("ayarlar dosyasi bulunamadi.\n");
        return;
    }
    fscanf(fp , "%*[^\n]\n" , NULL);
    fscanf(fp , "%d" , &PointsForWin);
    fscanf(fp , "%d" , &PointsForDraw);
    fscanf(fp , "%d" , &PointsForLose);
}


void ReadMatchFromKeyboard(){
    printf("Maclari tek tek girin cikmak icin ! yazin.");
    char HomeTeam = 0;
    int HomeTeamScore = 0;
    char GuestTeam = 0;
    int GuestTeamScore = 0;
    int checkVariable = 0;
    while (1){
        checkVariable++;
        scanf(" %c", &HomeTeam);
        if (HomeTeam == '!'){
            break;
        }

        scanf("%d %c %d", &HomeTeamScore, &GuestTeam, &GuestTeamScore);

        if (((int)(HomeTeam)-65) >= NumberOfTeams || ((int)(GuestTeam)-65) >= NumberOfTeams){
            printf("Lutfen gecerli takim adi girin.\n");
            HomeTeam = 0;
            GuestTeam = 0;
            continue;
        }

        for (int i = 0; i < NumberOfTeams; i++){

            if (HomeTeam == MoveStruct(i)->sname){                                  //Structlar icinden takimi buluyor

                for (int a = 0; a < NumberOfTeams; a++){

                    if (GuestTeam == MoveStruct(a)->sname){                         //Structlar icinden takimi buluyor

                        if (a == i){
                            printf("Ayni takim kendiyle mac yapamaz.\n");
                            break;
                        }

                        if (MoveStruct(i)->mchart[a] == '\0'){
                            printf("Bu ev sahibi takim bu deplasmandaki takimla zaten mac yapmis.\n");
                            break;
                        }

                        MoveStruct(i)->mchart[a] = '\0';

                        MoveStruct(i)->pscore += HomeTeamScore;                     //Kodun bu kisimi atilan ve
                        MoveStruct(i)->nscore += GuestTeamScore;                    //yenilen gollerin structlara
                        MoveStruct(a)->pscore += GuestTeamScore;                    //veri olarak girilmesini sagliyor
                        MoveStruct(a)->nscore += HomeTeamScore;
                        MoveStruct(i)->difference += HomeTeamScore - GuestTeamScore;
                        MoveStruct(a)->difference += GuestTeamScore - HomeTeamScore;
                        MoveStruct(i)->played += 1;
                        MoveStruct(a)->played += 1;

                        if (HomeTeamScore > GuestTeamScore){                        //Ev sahibi kazanirsa
                            MoveStruct(i)->won += 1;
                            MoveStruct(a)->lost += 1;
                            MoveStruct(i)->points += PointsForWin;
                            MoveStruct(a)->points += PointsForLose;
                        }

                        if (HomeTeamScore < GuestTeamScore){                        //Deplasman takimi kazanirsa
                            MoveStruct(a)->won += 1;
                            MoveStruct(i)->lost += 1;
                            MoveStruct(a)->points += PointsForWin;
                            MoveStruct(i)->points += PointsForLose;
                        }

                        if (HomeTeamScore == GuestTeamScore){                       //Berabere kalinirsa
                            MoveStruct(i)->draw += 1;
                            MoveStruct(a)->draw += 1;
                            MoveStruct(i)->points += PointsForDraw;
                            MoveStruct(a)->points += PointsForDraw;
                        }
                    }
                    
                }
            }
            
        }
    }
}


void ReadMatchesFromFile(){
    FILE* fp = fopen("maclar1.txt", "r");
    char HomeTeam = 0;
    int HomeTeamScore = 0;
    char GuestTeam = 0;
    int GuestTeamScore = 0;
    int checkVariable = 0;
    while (fscanf(fp , " %c %d %c %d",&HomeTeam, &HomeTeamScore, &GuestTeam, &GuestTeamScore) != EOF){
        checkVariable++;
        if (((int)(HomeTeam)-65) >= NumberOfTeams || ((int)(GuestTeam)-65) >= NumberOfTeams){
            printf("%d'inci satirdaki mac gecersiz.\n", checkVariable);
            HomeTeam = 0;
            GuestTeam = 0;
            continue;
        }

        for (int i = 0; i < NumberOfTeams; i++){

            if (HomeTeam == MoveStruct(i)->sname){                                  //Structlar icinden takimi buluyor

                for (int a = 0; a < NumberOfTeams; a++){

                    if (GuestTeam == MoveStruct(a)->sname){                         //Structlar icinden takimi buluyor

                        if (a == i){
                            printf("%d'inci satirda hata: Ayni takim kendiyle mac yapamaz.\n" , checkVariable);
                            break;
                        }

                        if (MoveStruct(i)->mchart[a] == '\0'){
                            printf("%d'inci satirda hata: Bu ev sahibi takim bu deplasmandaki takimla zaten mac yapmis.\n" , checkVariable);
                            break;
                        }

                        MoveStruct(i)->mchart[a] = '\0';

                        MoveStruct(i)->pscore += HomeTeamScore;                     //Kodun bu kisimi atilan ve
                        MoveStruct(i)->nscore += GuestTeamScore;                    //yenilen gollerin structlara
                        MoveStruct(a)->pscore += GuestTeamScore;                    //veri olarak girilmesini sagliyor
                        MoveStruct(a)->nscore += HomeTeamScore;
                        MoveStruct(i)->difference += HomeTeamScore - GuestTeamScore;
                        MoveStruct(a)->difference += GuestTeamScore - HomeTeamScore;
                        MoveStruct(i)->played += 1;
                        MoveStruct(a)->played += 1;

                        if (HomeTeamScore > GuestTeamScore){                        //Ev sahibi kazanirsa
                            MoveStruct(i)->won += 1;
                            MoveStruct(a)->lost += 1;
                            MoveStruct(i)->points += PointsForWin;
                            MoveStruct(a)->points += PointsForLose;
                        }

                        if (HomeTeamScore < GuestTeamScore){                        //Deplasman takimi kazanirsa
                            MoveStruct(a)->won += 1;
                            MoveStruct(i)->lost += 1;
                            MoveStruct(a)->points += PointsForWin;
                            MoveStruct(i)->points += PointsForLose;
                        }

                        if (HomeTeamScore == GuestTeamScore){                       //Berabere kalinirsa
                            MoveStruct(i)->draw += 1;
                            MoveStruct(a)->draw += 1;
                            MoveStruct(i)->points += PointsForDraw;
                            MoveStruct(a)->points += PointsForDraw;
                        }
                    }
                }
            }
        }
    }
}

void GetTeamLongName(){
    FILE* fp = fopen("takimlar.txt" , "r+");
    if(fp == NULL){
        printf("takimalr.txt dosyasi bulunamadi!");
        return;
    }
    for(int i = 0; i < NumberOfTeams; i++){
        char array[59];
        fscanf(fp, "%s" , array);
        for(int a = 0; a < 13; a++){
            MoveStruct(i)->lname[a] = array[a];
        }
        MoveStruct(i)->lname[12] = '\0';
    }
}

void BuildTeams(int TeamCount){
    GetTeamLongName();
    for (struct{char i; int a; } fV ={65, 0};
                                fV.a < TeamCount;
                                fV.a++, fV.i++){
        MoveStruct(fV.a)->sname = fV.i;
        CapitalLetter(MoveStruct(fV.a)->lname , MoveStruct(fV.a)->cname);
        MoveStruct(fV.a)->points = 0;
        MoveStruct(fV.a)->played = 0;
        MoveStruct(fV.a)->won = 0;
        MoveStruct(fV.a)->lost = 0;
        MoveStruct(fV.a)->draw = 0;
        MoveStruct(fV.a)->points = 0;
        MoveStruct(fV.a)->pscore = 0;
        MoveStruct(fV.a)->nscore = 0;
        MoveStruct(fV.a)->difference = 0;
        for (int i = 0; i <= TeamCount; i++){
            MoveStruct(fV.a)->mchart[i] = 65 + i;
        }
        MoveStruct(fV.a)->mchart[fV.a] = '\0';
    }
    for(int i = 0; i < NumberOfTeams; i++){
        PointArray[i] = i;
    }
    for(int i = 0; i < NumberOfTeams; i++){
        AlphabetArray[i] = i;
    }
}


void AlphabeticOrder(int integer, int start){
    if(MoveStruct(PointArray[integer])->lname[start] == '\0'){
        int temp = PointArray[integer-1];
        PointArray[integer-1] = PointArray[integer];
        PointArray[integer] = temp;
        return;
    }
    if(MoveStruct(PointArray[integer - 1])->lname[start] == '\0'){
        return;
    }
    if((int)(MoveStruct(PointArray[integer])->lname[start]) < (int)(MoveStruct(PointArray[integer - 1])->lname[start])){
        int temp = PointArray[integer-1];
        PointArray[integer-1] = PointArray[integer];
        PointArray[integer] = temp;
    }
    if((int)(MoveStruct(PointArray[integer])->lname[start]) == (int)(MoveStruct(PointArray[integer - 1])->lname[start])){
        AlphabeticOrder(integer , start+1);
    }
}


void SortTeamsByPoint(){
    for(int i = 0; i < NumberOfTeams; i++){
        for(int a = i; a > 0 ; a--){
            int temp;
            if(MoveStruct(PointArray[a])->points > MoveStruct(PointArray[a-1])->points){
                temp = PointArray[a-1];
                PointArray[a-1] = PointArray[a];
                PointArray[a] = temp;
            }
            if(MoveStruct(PointArray[a])->points == MoveStruct(PointArray[a-1])->points){
                if(MoveStruct(PointArray[a])->difference > MoveStruct(PointArray[a-1])->difference){
                    temp = PointArray[a-1];
                    PointArray[a-1] = PointArray[a];
                    PointArray[a] = temp;
                }
                if(MoveStruct(PointArray[a])->difference == MoveStruct(PointArray[a-1])->difference){
                    AlphabeticOrder(a , 0);
                }
            }
        }
    }
}

void LocalFunc(int temp, int a , int start){
    if(MoveStruct(AlphabetArray[a])->lname[start] == '\0'){
        temp = AlphabetArray[a-1];
        AlphabetArray[a-1] = AlphabetArray[a];
        AlphabetArray[a] = temp;
    }
    if(MoveStruct(AlphabetArray[a-1])->lname[start] == '\0'){
        return;
    }
    if(MoveStruct(AlphabetArray[a])->lname[start] < MoveStruct(AlphabetArray[a-1])->lname[start]){
        temp = AlphabetArray[a-1];
        AlphabetArray[a-1] = AlphabetArray[a];
        AlphabetArray[a] = temp;
    }
    if(MoveStruct(AlphabetArray[a])->lname[start] == MoveStruct(AlphabetArray[a-1])->lname[start]){
        LocalFunc(temp , a , start+1);
    }
}

void SortTeamsByNames(){
    for(int i = 0; i < NumberOfTeams; i++){
        for(int a = i; a > 0 ; a--){
            int temp;
            LocalFunc(temp , a , 0);
        }
    }
}

void ConstructTable(){
    printf("%-5s",  "SH");
    printf("%-30s", "TEAM NAME");
    printf("%-5s",  "P");
    printf("%-5s",  "W");
    printf("%-5s",  "L");
    printf("%-5s",  "D");
    printf("%-5s",  "POS");
    printf("%-5s",  "NEG");
    printf("%-5s",  "DIFF");
    printf("%-5s",  "PTS");
    printf("\n");
}

void ConstructTableFile(FILE* ptr){
    fprintf(ptr ,"%-5s",  "SH");
    fprintf(ptr ,"%-30s", "TEAM NAME");
    fprintf(ptr ,"%-5s",  "P");
    fprintf(ptr ,"%-5s",  "W");
    fprintf(ptr ,"%-5s",  "L");
    fprintf(ptr ,"%-5s",  "D");
    fprintf(ptr ,"%-5s",  "POS");
    fprintf(ptr ,"%-5s",  "NEG");
    fprintf(ptr ,"%-5s",  "DIFF");
    fprintf(ptr ,"%-5s",  "PTS");
    fprintf(ptr ,"\n");
}

void DestructTable(){
    printf("%s", "SH = Short Name, ");
    printf("%s", "P = Played, ");
    printf("%s", "W = Games Won, ");
    printf("%s", "L = Games Lost, ");
    printf("%s", "D = Draw, ");
    printf("%s", "POS = Positive Score, ");
    printf("%s", "NEG = Negative Score, ");
    printf("%s", "DIFF = Difference, \n");
}

void DestructTableFile(FILE* ptr){
    fprintf(ptr ,"%s", "SH = Short Name, ");
    fprintf(ptr ,"%s", "P = Played, ");
    fprintf(ptr ,"%s", "W = Games Won, ");
    fprintf(ptr ,"%s", "L = Games Lost, ");
    fprintf(ptr ,"%s", "D = Draw, ");
    fprintf(ptr ,"%s", "POS = Positive Score, ");
    fprintf(ptr ,"%s", "NEG = Negative Score, ");
    fprintf(ptr ,"%s", "DIFF = Difference, \n");
}

void PrintTableByPointToConsole(int capital){
    ConstructTable();

    if(capital == 2){

        for(int i = 0; i < NumberOfTeams; i++){
            printf("%-5c",  MoveStruct(PointArray[i])->sname);
            printf("%-30s", MoveStruct(PointArray[i])->cname);
            printf("%-5d",  MoveStruct(PointArray[i])->played);
            printf("%-5d",  MoveStruct(PointArray[i])->won);
            printf("%-5d",  MoveStruct(PointArray[i])->lost);
            printf("%-5d",  MoveStruct(PointArray[i])->draw);
            printf("%-5d",  MoveStruct(PointArray[i])->pscore);
            printf("%-5d",  MoveStruct(PointArray[i])->nscore);
            printf("%-5d",  MoveStruct(PointArray[i])->difference);
            printf("%-5d\n",MoveStruct(PointArray[i])->points);
        }

    } else{

        for(int i = 0; i < NumberOfTeams; i++){
            printf("%-5c",  MoveStruct(PointArray[i])->sname);
            printf("%-30s", MoveStruct(PointArray[i])->lname);
            printf("%-5d",  MoveStruct(PointArray[i])->played);
            printf("%-5d",  MoveStruct(PointArray[i])->won);
            printf("%-5d",  MoveStruct(PointArray[i])->lost);
            printf("%-5d",  MoveStruct(PointArray[i])->draw);
            printf("%-5d",  MoveStruct(PointArray[i])->pscore);
            printf("%-5d",  MoveStruct(PointArray[i])->nscore);
            printf("%-5d",  MoveStruct(PointArray[i])->difference);
            printf("%-5d\n",MoveStruct(PointArray[i])->points);

        }
    }

    DestructTable();
}

void PrintTableByPointToFile(int capital){
    FILE* fp = fopen("puan_tablosu.txt","w");
    ConstructTableFile(fp);
    if(capital == 2){

        for(int i = 0; i < NumberOfTeams; i++){
            fprintf(fp , "%-5c",  MoveStruct(PointArray[i])->sname);
            fprintf(fp , "%-30s", MoveStruct(PointArray[i])->cname);
            fprintf(fp , "%-5d",  MoveStruct(PointArray[i])->played);
            fprintf(fp , "%-5d",  MoveStruct(PointArray[i])->won);
            fprintf(fp , "%-5d",  MoveStruct(PointArray[i])->lost);
            fprintf(fp , "%-5d",  MoveStruct(PointArray[i])->draw);
            fprintf(fp , "%-5d",  MoveStruct(PointArray[i])->pscore);
            fprintf(fp , "%-5d",  MoveStruct(PointArray[i])->nscore);
            fprintf(fp , "%-5d",  MoveStruct(PointArray[i])->difference);
            fprintf(fp , "%-5d\n",MoveStruct(PointArray[i])->points);
        }

    } else {
        for(int i = 0; i < NumberOfTeams; i++){
            fprintf(fp , "%-5c",  MoveStruct(PointArray[i])->sname);
            fprintf(fp , "%-30s", MoveStruct(PointArray[i])->lname);
            fprintf(fp , "%-5d",  MoveStruct(PointArray[i])->played);
            fprintf(fp , "%-5d",  MoveStruct(PointArray[i])->won);
            fprintf(fp , "%-5d",  MoveStruct(PointArray[i])->lost);
            fprintf(fp , "%-5d",  MoveStruct(PointArray[i])->draw);
            fprintf(fp , "%-5d",  MoveStruct(PointArray[i])->pscore);
            fprintf(fp , "%-5d",  MoveStruct(PointArray[i])->nscore);
            fprintf(fp , "%-5d",  MoveStruct(PointArray[i])->difference);
            fprintf(fp , "%-5d\n",MoveStruct(PointArray[i])->points);
        }
    }

    DestructTableFile(fp);
    fclose(fp);
}

void PrintTableByAliasToConsole(int capital){
    ConstructTable();

    if(capital == 2){
        for(int i = 0; i < NumberOfTeams; i++){
            printf("%-5c",  MoveStruct(i)->sname);
            printf("%-30s", MoveStruct(i)->cname);
            printf("%-5d",  MoveStruct(i)->played);
            printf("%-5d",  MoveStruct(i)->won);
            printf("%-5d",  MoveStruct(i)->lost);
            printf("%-5d",  MoveStruct(i)->draw);
            printf("%-5d",  MoveStruct(i)->pscore);
            printf("%-5d",  MoveStruct(i)->nscore);
            printf("%-5d",  MoveStruct(i)->difference);
            printf("%-5d\n",MoveStruct(i)->points);
        }
    } else {
        for(int i = 0; i < NumberOfTeams; i++){
            printf("%-5c",  MoveStruct(i)->sname);
            printf("%-30s", MoveStruct(i)->lname);
            printf("%-5d",  MoveStruct(i)->played);
            printf("%-5d",  MoveStruct(i)->won);
            printf("%-5d",  MoveStruct(i)->lost);
            printf("%-5d",  MoveStruct(i)->draw);
            printf("%-5d",  MoveStruct(i)->pscore);
            printf("%-5d",  MoveStruct(i)->nscore);
            printf("%-5d",  MoveStruct(i)->difference);
            printf("%-5d\n",MoveStruct(i)->points);
        }
    }

    DestructTable();
}

void PrintTableByAliasToFile(int capital){
    FILE* fp = fopen("puan_tablosu.txt","w");
    ConstructTableFile(fp);
    if (capital == 2){
        for(int i = 0; i < NumberOfTeams; i++){
            fprintf(fp, "%-5c",  MoveStruct(i)->sname);
            fprintf(fp, "%-30s", MoveStruct(i)->cname);
            fprintf(fp, "%-5d",  MoveStruct(i)->played);
            fprintf(fp, "%-5d",  MoveStruct(i)->won);
            fprintf(fp, "%-5d",  MoveStruct(i)->lost);
            fprintf(fp, "%-5d",  MoveStruct(i)->draw);
            fprintf(fp, "%-5d",  MoveStruct(i)->pscore);
            fprintf(fp, "%-5d",  MoveStruct(i)->nscore);
            fprintf(fp, "%-5d",  MoveStruct(i)->difference);
            fprintf(fp, "%-5d\n",MoveStruct(i)->points);
        }
    } else {
        for(int i = 0; i < NumberOfTeams; i++){
            fprintf(fp, "%-5c",  MoveStruct(i)->sname);
            fprintf(fp, "%-30s", MoveStruct(i)->lname);
            fprintf(fp, "%-5d",  MoveStruct(i)->played);
            fprintf(fp, "%-5d",  MoveStruct(i)->won);
            fprintf(fp, "%-5d",  MoveStruct(i)->lost);
            fprintf(fp, "%-5d",  MoveStruct(i)->draw);
            fprintf(fp, "%-5d",  MoveStruct(i)->pscore);
            fprintf(fp, "%-5d",  MoveStruct(i)->nscore);
            fprintf(fp, "%-5d",  MoveStruct(i)->difference);
            fprintf(fp, "%-5d\n",MoveStruct(i)->points);
        }
    }

    DestructTableFile(fp);
    fclose(fp);
}

void PrintTableByNamesToConsole(int capital){
    ConstructTable();
    if(capital == 2){
        for(int i = 0; i < NumberOfTeams; i++){
            printf("%-5c",  MoveStruct(AlphabetArray[i])->sname);
            printf("%-30s", MoveStruct(AlphabetArray[i])->cname);
            printf("%-5d",  MoveStruct(AlphabetArray[i])->played);
            printf("%-5d",  MoveStruct(AlphabetArray[i])->won);
            printf("%-5d",  MoveStruct(AlphabetArray[i])->lost);
            printf("%-5d",  MoveStruct(AlphabetArray[i])->draw);
            printf("%-5d",  MoveStruct(AlphabetArray[i])->pscore);
            printf("%-5d",  MoveStruct(AlphabetArray[i])->nscore);
            printf("%-5d",  MoveStruct(AlphabetArray[i])->difference);
            printf("%-5d\n",MoveStruct(AlphabetArray[i])->points);
        }
    } else {
        for(int i = 0; i < NumberOfTeams; i++){
            printf("%-5c",  MoveStruct(AlphabetArray[i])->sname);
            printf("%-30s", MoveStruct(AlphabetArray[i])->lname);
            printf("%-5d",  MoveStruct(AlphabetArray[i])->played);
            printf("%-5d",  MoveStruct(AlphabetArray[i])->won);
            printf("%-5d",  MoveStruct(AlphabetArray[i])->lost);
            printf("%-5d",  MoveStruct(AlphabetArray[i])->draw);
            printf("%-5d",  MoveStruct(AlphabetArray[i])->pscore);
            printf("%-5d",  MoveStruct(AlphabetArray[i])->nscore);
            printf("%-5d",  MoveStruct(AlphabetArray[i])->difference);
            printf("%-5d\n",MoveStruct(AlphabetArray[i])->points);
        }
    }
    DestructTable();
}

void PrintTableByNamesToFile(int capital){
    FILE* fp = fopen("puan_tablosu.txt" , "w");
    ConstructTableFile(fp);
    if(capital == 2){
        for(int i = 0; i < NumberOfTeams; i++){
            fprintf(fp , "%-5c",  MoveStruct(AlphabetArray[i])->sname);
            fprintf(fp , "%-30s", MoveStruct(AlphabetArray[i])->cname);
            fprintf(fp , "%-5d",  MoveStruct(AlphabetArray[i])->played);
            fprintf(fp , "%-5d",  MoveStruct(AlphabetArray[i])->won);
            fprintf(fp , "%-5d",  MoveStruct(AlphabetArray[i])->lost);
            fprintf(fp , "%-5d",  MoveStruct(AlphabetArray[i])->draw);
            fprintf(fp , "%-5d",  MoveStruct(AlphabetArray[i])->pscore);
            fprintf(fp , "%-5d",  MoveStruct(AlphabetArray[i])->nscore);
            fprintf(fp , "%-5d",  MoveStruct(AlphabetArray[i])->difference);
            fprintf(fp , "%-5d\n",MoveStruct(AlphabetArray[i])->points);
        }
    } else {
        for(int i = 0; i < NumberOfTeams; i++){
            fprintf(fp , "%-5c",  MoveStruct(AlphabetArray[i])->sname);
            fprintf(fp , "%-30s", MoveStruct(AlphabetArray[i])->lname);
            fprintf(fp , "%-5d",  MoveStruct(AlphabetArray[i])->played);
            fprintf(fp , "%-5d",  MoveStruct(AlphabetArray[i])->won);
            fprintf(fp , "%-5d",  MoveStruct(AlphabetArray[i])->lost);
            fprintf(fp , "%-5d",  MoveStruct(AlphabetArray[i])->draw);
            fprintf(fp , "%-5d",  MoveStruct(AlphabetArray[i])->pscore);
            fprintf(fp , "%-5d",  MoveStruct(AlphabetArray[i])->nscore);
            fprintf(fp , "%-5d",  MoveStruct(AlphabetArray[i])->difference);
            fprintf(fp , "%-5d\n",MoveStruct(AlphabetArray[i])->points);
        }
    }
    DestructTableFile(fp);
    fclose(fp);
}

void PleaseHelpMeGetGoodGrades(){
    int Decision = 0;
    int CheckCapital = 1;
    ReadTeamNumberFromFile(AddressOfNumberOfTeams);
    printf("Takimlarin kazanma, kaybetme, berabere durumlarinda alacagi puanlar: %d %d %d\n", PointsForWin , PointsForLose , PointsForDraw);
    printf("Bu ayari degistirmek istiyor musunuz? (1) Evet , (2) Hayir: ");
    scanf(" %d",&Decision);
    if(Decision == 1){
        ReadPointsFromFile();
    }
    AllocateMemory(NumberOfTeams);
    BuildTeams(NumberOfTeams);
    while(1){
        printf("(1) Maclari dosyadan oku , (2) Maclari klavyeden oku , (3) Puan tablosu yazdirma menusu (4) Cikmak icin\n");
        scanf(" %d", &Decision);
        if(Decision == 4){
            break;
        }
        switch (Decision){
            case 1:
                ReadMatchesFromFile();
                break;

            case 2:
                ReadMatchFromKeyboard();
                break;

            case 3:
                SortTeamsByNames();
                SortTeamsByPoint();

                while(1){
                    printf("(1) Puan tablosunu ekrana yazdir , (2) Puan tablosunu dosyaya yazdir (3) Cikmak icin\n");
                    scanf(" %d",&Decision);
                    if(Decision == 3){
                        break;
                    }
                    switch (Decision){
                        case 1:
                            while(1){
                                printf("(1) Puan sirasina gore , (2) Kisa adlara gore , (3) Alfabetik siraya gore , (4) Cikmak icin\n");
                                scanf("%d",&Decision);
                                printf("(1) Takim isimleri kucuk harf , (2) Takim isimleri buyuk harf\n" );
                                scanf("%d", &CheckCapital);
                                if(Decision == 1){

                                    PrintTableByPointToConsole(CheckCapital);

                                } else if (Decision == 2){

                                    PrintTableByAliasToConsole(CheckCapital);

                                } else if (Decision == 3){

                                    PrintTableByNamesToConsole(CheckCapital);

                                }else if (Decision == 4){

                                    break;

                                } else {
                                    
                                    printf("Hatali giris yaptiniz!\n");
                                    
                                    continue;
                                }
                                break;
                            }
                            break;

                        case 2:
                            while(1){
                                printf("(1) Puan sirasina gore , (2) Kisa adlara gore , (3) Alfabetik siraya gore , (4) Cikmak icin\n");
                                scanf("%d",&Decision);
                                printf("(1) Takim isimleri kucuk harf , (2) Takim isimleri buyuk harf\n" );
                                scanf("%d", &CheckCapital);
                                if(Decision == 1){

                                    PrintTableByPointToFile(CheckCapital);

                                } else if (Decision == 2){

                                    PrintTableByAliasToFile(CheckCapital);

                                } else if (Decision == 3){

                                    PrintTableByNamesToFile(CheckCapital);

                                }else if (Decision == 4){

                                    break;

                                } else {
                                    
                                    printf("Hatali giris yaptiniz!\n");
                                    
                                    continue;
                                }
                                break;
                            }
                            break;

                        default:
                            printf("Lutfen gecerli bir deger giriniz!\n");
                            break;
                        
                    }
                }
                break;

            default:
                printf("Lutfen gecerli bir deger giriniz.\n");
                break;
        }
    }
    
}

int main(){
    PleaseHelpMeGetGoodGrades();
    return 0;
}

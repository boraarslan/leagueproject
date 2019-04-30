#include <stdio.h>
#include <stdlib.h>
typedef unsigned int uint;

struct team{
    char sname;
    char lname[12];
    uint played;
    uint won;
    uint tie;
    uint lost;
    uint pscore;
    uint nscore;
    uint average;
    uint points;
};

void ReadTeamNames()//takimlar.txt icinden takimlarin isimlerini okumayi saglayan fonksiyon.
{
	
	int i;
	int n;
	FILE *fp;
	fp = fopen("C:/takimlar.txt","r");//konum değiştirilecek. ben kolaylık olsun diye c nin içerisine attım.
	
	printf("kac takim okunacak: ");
	scanf("%d",&n);
	struct team teams[n];
	if(n>10){
		printf("Fazla sayi girdiniz.Onun yerine tum takimlar gosteriliyor ve depolaniyor.\n\n");
		for(i=0;i<10;i++){	
			fscanf(fp,"%s",&teams[i].sname);
			printf("%s ",teams[i].sname);	
			fscanf(fp,"%s",&teams[i].lname);
			printf("%s \n",teams[i].lname);
		}
	}
	
	else
	{
		for(i=0;i<n;i++){
			fscanf(fp,"%s",&teams[i].sname);
			printf("%s ",teams[i].sname);	
			fscanf(fp,"%s",&teams[i].lname);
			printf("%s \n",teams[i].lname);
		}
	}
	fclose(fp);
} 

struct match{
	int hscore;	//h = home a = away 
	char hteam;
	int ascore;
	char ateam;
};

void ReadMatches()
{
	int i;
	int m;//mac sayisi
	int n;
	
	FILE *fp;
	fp = fopen("C:/maclar1.txt","r");//KONUM DEĞİŞTİRİLECEK.
	
	printf("Dosyadan Kac mac okunacak?: ");
	scanf("%d",&m);
	struct match matches[m];
	if(fp){
		if(m>12){
			printf("Diger %d maci giriniz(Takim kisaltmalarini buyuk harf giriniz): ",m-12);
			for(i=12;i<m;i++){
				scanf(" %c %d %c %d",&matches[i].hteam,&matches[i].hscore,&matches[i].ateam,&matches[i].ascore);
				printf("Bu maci girdiniz: %c %d %c %d\n",matches[i].hteam,matches[i].hscore,matches[i].ateam,matches[i].ascore);
			}
			
			printf("\n\n-------------------------\n\n");
			
			for(i=0;i<12;i++){
				fscanf(fp,"%c %d %c %d\n",&matches[i].hteam,&matches[i].hscore,&matches[i].ateam,&matches[i].ascore);
				printf("%d. mac:  %c %d %c %d\n",i+1,matches[i].hteam,matches[i].hscore,matches[i].ateam,matches[i].ascore);
			}
			
			printf("\nIlaveten eklenen maclar:\n\n");
			
			for(i=12;i<m;i++){
				printf("%d. mac:  %c %d %c %d\n",i+1,matches[i].hteam,matches[i].hscore,matches[i].ateam,matches[i].ascore);
			}
			
		}
		else if(m<12){
			for(i=0;i<m;i++)
			{	
				fscanf(fp,"%c %d %c %d\n",&matches[i].hteam,&matches[i].hscore,&matches[i].ateam,&matches[i].ascore);
				printf("%d. mac:  %c %d %c %d\n",i+1,matches[i].hteam,matches[i].hscore,matches[i].ateam,matches[i].ascore);
			}
		}
	}
		
	
	else{
		printf("dosya okunamadi!");
	}
fclose(fp);
}

int main(){

    return 0;
}

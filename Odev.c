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
	int n;//bunu global tanimlamamiz gerek. takim sayisini buradan seciyoruz.
	int i;
	FILE *fp;
	fp = fopen("C:/takimlar.txt","r");//konum değiştirilecek. ben kolaylık olsun diye c nin içerisine attım.

	printf("Kac takim olacak? :  ");
	scanf("%d",&n);
	
	struct team teams[n];//n tane takımın verilerini buradan saklıyorum.

	for(i=0;i<n;i++)
	fscanf(fp,"%s %s",teams[i].lname,teams[i].sname);	
	

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
	
	FILE *fp;
	fp = fopen("C:/maclar1.txt","r");//değiştirilecek konum.
	
	printf("Dosyadan Kac mac okunacak?: ");
	scanf("%d",&m);
	
	struct match matches[m];
	
	if(fp){
		if(!feof(fp)){
		
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

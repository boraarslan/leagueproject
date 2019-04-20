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
	int n;
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

void ReadMatches(); //maclar.1txt dosyasindan maclari okumayi saglayan fonksiyon.

int main(){

    return 0;
}

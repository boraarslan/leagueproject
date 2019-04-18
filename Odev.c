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

char ReadTeamNames(); //takimlar.txt icinden takimlarin isimlerini okumayi saglayan fonksiyon.
void ReadMatches(); //maclar.1txt dosyasindan maclari okumayi saglayan fonksiyon.

int main(){

    return 0;
}
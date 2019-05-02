#include <stdlib.h>
#include <stdio.h>
#include "persist.h"

void TestHS(int score){
	FILE * F = NULL;
	F = fopen("top.txt","r"); //ouverture du fichier et stockage des scores
	char hs1[10] = "",hs2[10] = "", hs3[10] = "", hs4[10] = "", hs5[10] = "";
	int s1=0, s2=0, s3=0, s4=0, s5=0;
	fgets(hs1,10,F),fgets(hs2,10,F),fgets(hs3,10,F),fgets(hs4,10,F),fgets(hs5,10,F); //récupération des scores en char
	s1 = transf(hs1); s2 = transf(hs2); s3 = transf(hs3); s4 = transf(hs4); s5 = transf(hs5); //passage en int
	fclose(F);
	F = fopen("top.txt","w"); //réécriture avec comparaison du score actuel et des high score
	if (score >= s1) {s5 = s4; s4 = s3; s3 = s2; s2 = s1; s1 = score;}
	else if (score >= s2) {s5=s4;s4=s3;s3=s2; s2 = score;}
	else if (score >= s3) {s5=s4;s4=s3; s3 = score;}
	else if (score >= s4) {s5=s4; s4 = score;}
	else if (score >= s5) {s5 = score;}
	fprintf(F,"%d\n%d\n%d\n%d\n%d\n",s1,s2,s3,s4,s5);
	fclose(F);
}

int transf(char * t){ //FCT pour passer de char->int (ASCII -48)
	int x = 0,j=0, p =0;
	while (t[j] != '\0' && j<=5){j++;}
	j=j-1;
	for (int i=0;i<j;i++){
		p=pui(10,j-i);
		x = (t[i]-48)*p + x;
	}
	return x;
	}


int pui(int a, int b){ //FCT pour la puissance
        int p =1;
        for (int i=0;i<b-1;i++){
                p=a*p;
        }
        return p;
}


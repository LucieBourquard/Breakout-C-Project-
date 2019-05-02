#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h> // Pour pouvoir utiliser printf()
#include "initialisation.h"


BRK *creermaillon(int x, int y, int lvl){
    BRK *B = (BRK *) malloc(sizeof(BRK));
    B->PositionX=x;
    B->PositionY=y;
    B->lvl=lvl;
	printf("CR Coordonnés: %d %d %d\n", B->PositionX, B->PositionY, B->lvl);
    B->suiv=NULL;
    return B;
}

BRK *insertete(BRK *liste, BRK *maillon){
    maillon->suiv=liste;
    liste=maillon;
    return liste;
}

BRK *listeSOLO1(BRK* liste1,BRK* nv){
	liste1=NULL;
   	for(int ligne=0; ligne<5; ligne ++){
        for(int colonne=0; colonne<14; colonne++){
           	nv = creermaillon(0+57*colonne,525-32*ligne,1);
            	liste1 = insertete(liste1, nv);
		printf("maillon inséré");
		printf("Coordonnés: %d %d %d\n", liste1->PositionX, liste1->PositionY, liste1->lvl);
        }
    }
    return liste1;
}

BRK *listeSOLO2(BRK* liste2, BRK* nv){
    int niveau;
    int ligne=0;
	
    liste2=NULL;
    for(ligne=0; ligne<5; ligne ++){
        if(ligne==0 || ligne==1) niveau=2;
        if(ligne==2 || ligne==3 || ligne ==4) niveau=1;

        for(int colonne=0; colonne<14; colonne++){
            nv = creermaillon(0+57*colonne,525-32*ligne,niveau);
            liste2 = insertete(liste2, nv);
        }
    }
    return liste2;
}

BRK *listeSOLO3(BRK* liste3, BRK* nv){
    int niveau;
    int ligne=0;
    liste3=NULL;
    
    for(ligne=0; ligne<5; ligne ++){
        if(ligne==0 || ligne==1) niveau=3;
        if(ligne==2 || ligne==3) niveau=2;
        if(ligne==4) niveau=1;

        for(int colonne=0; colonne<14; colonne++){
            nv = creermaillon(0+57*colonne,525-32*ligne,niveau);
            liste3 = insertete(liste3, nv);
        }
    }
    return liste3;
}



BRK *listeVS(BRK* listeVS, BRK* nv){
	int niveau;
	int ligne=0;
	listeVS=NULL;
	for(ligne=0; ligne<3; ligne++){
			if(ligne==0 || ligne==2) niveau=1;
			if(ligne==1) niveau=3;
			for(int colonne=0; colonne<3; colonne++){
				nv = creermaillon(50+325*colonne,425-135*ligne,niveau);
				listeVS = insertete(listeVS, nv);}
			}
		for(ligne=3; ligne<5; ligne++){
			niveau=2;
			for(int colonne2=0; colonne2<2; colonne2++){
			nv = creermaillon(212+325*colonne2,358-138*(ligne-3),niveau);
				listeVS = insertete(listeVS, nv);}
			}
    return listeVS;
}


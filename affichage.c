#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h> // Pour pouvoir utiliser printf()
#include <math.h> // Pour pouvoir utiliser sin() et cos()
#include "GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "ESLib.h" // Pour utiliser valeurAleatoire()


#include "affichage.h"




void Menu(){
	effaceFenetre (0, 0, 0);
	couleurCourante(255,255,255);
	epaisseurDeTrait(5);
	afficheChaine("BREAKOUT",30,330,500);

	//Rectangle MODE SOLO
	couleurCourante(0,0,255); 
	rectangle(300,450,500,400);
	couleurCourante(255,255,255);
	epaisseurDeTrait(3);
	afficheChaine("MODE : SOLO",17,330,420);

	//Rectangle MODE 1V1
	couleurCourante(0,0,255); 
	rectangle(300,350,500,300);
	couleurCourante(255,255,255);
	epaisseurDeTrait(3);
	afficheChaine("MODE : 1V1",17,330,320);

	//Rectangle H-S
	couleurCourante(255,255,0); 
	rectangle(100,150,250,100);
	couleurCourante(255,255,255);
	epaisseurDeTrait(4);
	afficheChaine("H-S",17,160,120);

	//Rectangle EXIT
	couleurCourante(255,0,0); 
	rectangle(550,150,700,100);
	couleurCourante(255,255,255);
	epaisseurDeTrait(3);
	afficheChaine("EXIT",17,610,120);
}

void Menu_Solo(){
	//Rectangle NIVEAU 1
	couleurCourante(0,255,0); 
	rectangle(100,250,275,200);
	couleurCourante(255,255,255);
	epaisseurDeTrait(3);
	afficheChaine("Niveau 1",17,140,220);

	//Rectangle NIVEAU 2
	couleurCourante(0,255,0); 
	rectangle(325,250,475,200);
	couleurCourante(255,255,255);
	epaisseurDeTrait(3);
	afficheChaine("Niveau 2",17,360,220);	

	//Rectangle NIVEAU 3
	couleurCourante(0,255,0); 
	rectangle(525,250,700,200);
	couleurCourante(255,255,255);
	epaisseurDeTrait(3);
	afficheChaine("Niveau 3",17,580,220);
}

void Menu_1V1(){
	//Rectangle NIVEAU 1
	couleurCourante(0,255,0); 
	rectangle(300,250,500,200);
	couleurCourante(255,255,255);
	epaisseurDeTrait(3);
	afficheChaine("Niveau 1",17,360,220);
}

void Menu_Reprendre(){
	//Rectangle Lancer Partie
	couleurCourante(0,255,0); 
	rectangle(700,580,780,500);
	couleurCourante(255,255,255);
	epaisseurDeTrait(10);
	afficheChaine("->",17,730,530);
}

void Menu_Quitter(){
	effaceFenetre (0, 0, 0);
	//Rectangle Quitter
	couleurCourante(255,0,0); 
	rectangle(22,580,85,502);
	couleurCourante(255,255,255);
	epaisseurDeTrait(6);
	afficheChaine("x",80,34,520);
}


void Menu_Fleche(){
	couleurCourante(255,255,255);
	epaisseurDeTrait(4);
	afficheChaine("Press UP",23,340,100);
}

void Victoire(){
	//Texte victoire
	couleurCourante(255,255,255);
	epaisseurDeTrait(7);
	afficheChaine("CONGRATULATION !",40,150,330);
	epaisseurDeTrait(4);
	afficheChaine("YOU WIN",25,330,280);
}

void Defaite(){
	//Texte victoire
	couleurCourante(255,255,255);
	epaisseurDeTrait(7);
	afficheChaine("  GAME OVER !   ",38,200,330);
	epaisseurDeTrait(4);
	afficheChaine("YOU LOSE",25,325,280);
}

void VictoireJoueur1(){
	//Texte victoire
	couleurCourante(255,255,255);
	epaisseurDeTrait(7);
	afficheChaine("CONGRATULATION PLAYER 1 ! ",38,75,330);
	epaisseurDeTrait(4);
	afficheChaine("YOU WIN",30,325,250);
}

void VictoireJoueur2(){
	//Texte victoire
	couleurCourante(255,255,255);
	epaisseurDeTrait(7);
	afficheChaine("CONGRATULATION PLAYER 2 ! ",38,75,330);
	epaisseurDeTrait(4);
	afficheChaine("YOU WIN",30,325,250);
}

void MenuScore(){

	FILE *F=NULL;
	F = fopen("top.txt","r");
	char hs1[10] = "",hs2[10] = "",hs3[10] = "",hs4[10] = "",hs5[10] = "";

fgets(hs1,10,F),fgets(hs2,10,F),fgets(hs3,10,F),fgets(hs4,10,F),fgets(hs5,10,F);
	fclose(F);

	couleurCourante(68,114,196);
	epaisseurDeTrait(7);
	afficheChaine("H - S",30,350,470);
	
	couleurCourante(91,155,213);
	epaisseurDeTrait(3);
	afficheChaine(hs1,20,400,350);

	couleurCourante(191,155,213);
	epaisseurDeTrait(3);
	afficheChaine(hs2,20,400,300);

	couleurCourante(254,155,213);
	epaisseurDeTrait(3);
	afficheChaine(hs3,20,400,250);

	couleurCourante(254,81,213);
	epaisseurDeTrait(3);
	afficheChaine(hs4,20,400,200);

	couleurCourante(254,81,161);
	epaisseurDeTrait(3);
	afficheChaine(hs5,20,400,150);
}


void cercle(float centreX, float centreY, float rayon)
{
	const int Pas = 20; // Nombre de secteurs pour tracer le cercle
	const double PasAngulaire = 2.*M_PI/Pas;
	int index;
	
	for (index = 0; index < Pas; ++index) // Pour chaque secteur
	{
		const double angle = 2.*M_PI*index/Pas; // on calcule l'angle de depart du secteur
		triangle(centreX, centreY,
				 centreX+rayon*cos(angle), centreY+rayon*sin(angle),
				 centreX+rayon*cos(angle+PasAngulaire), centreY+rayon*sin(angle+PasAngulaire));
			// On trace le secteur a l'aide d'un triangle => approximation d'un cercle
	}
	
}



void AfficheBarre(int xBarre,int yBarre){
	couleurCourante(255,255,255); 
	rectangle(xBarre,yBarre,xBarre + LargeurBarre,yBarre + (HauteurBarre/2));
}

void Afficher_vies1(int Life){
	static DonneesImageRGB *imagevie1 = NULL;
	static DonneesImageRGB *imagevie2 = NULL;
	static DonneesImageRGB *imagevie3 = NULL;
	if(Life==1 || Life==2 || Life==3){
		imagevie1 = lisBMPRGB("Vie.bmp");
		if (imagevie1 != NULL){
			ecrisImage((largeurFenetre()-imagevie1->largeurImage)/23, (hauteurFenetre()-imagevie1->hauteurImage)/40, imagevie1->largeurImage, imagevie1->hauteurImage, imagevie1->donneesRGB);
		}
	}
	if(Life==2 || Life==3){
		imagevie2 = lisBMPRGB("Vie.bmp");
		if (imagevie2 != NULL){
			ecrisImage((largeurFenetre()-imagevie2->largeurImage)/15, (hauteurFenetre()-imagevie2->hauteurImage)/40, imagevie2->largeurImage, imagevie2->hauteurImage, imagevie2->donneesRGB);
		}
	}
	if(Life==3){
		imagevie3 = lisBMPRGB("Vie.bmp");
		if (imagevie3 != NULL){
			ecrisImage((largeurFenetre()-imagevie3->largeurImage)/11.2, (hauteurFenetre()-imagevie3->hauteurImage)/40, imagevie3->largeurImage, imagevie3->hauteurImage, imagevie3->donneesRGB);
		}
	}
}

void Afficher_vies2(int Life2){
	static DonneesImageRGB *imagevie1 = NULL;
	static DonneesImageRGB *imagevie2 = NULL;
	static DonneesImageRGB *imagevie3 = NULL;
	if(Life2==1 || Life2==2 || Life2==3){
		imagevie1 = lisBMPRGB("Vie.bmp");
		if (imagevie1 != NULL){
			ecrisImage((largeurFenetre()-imagevie1->largeurImage)/23, (hauteurFenetre()-imagevie1->hauteurImage)/1.02, imagevie1->largeurImage, imagevie1->hauteurImage, imagevie1->donneesRGB);
		}
	}
	if(Life2==2 || Life2==3){
		imagevie2 = lisBMPRGB("Vie.bmp");
		if (imagevie2 != NULL){
			ecrisImage((largeurFenetre()-imagevie2->largeurImage)/15, (hauteurFenetre()-imagevie2->hauteurImage)/1.02, imagevie2->largeurImage, imagevie2->hauteurImage, imagevie2->donneesRGB);
		}
	}
	if(Life2==3){
		imagevie3 = lisBMPRGB("Vie.bmp");
		if (imagevie3 != NULL){
			ecrisImage((largeurFenetre()-imagevie3->largeurImage)/11.2, (hauteurFenetre()-imagevie3->hauteurImage)/1.02, imagevie3->largeurImage, imagevie3->hauteurImage, imagevie3->donneesRGB);
		}
	}
}

void AfficheScore(int score, char valscore[4]){
	couleurCourante(255,255,255);
	epaisseurDeTrait(4);
	afficheChaine("SCORE :",20,610,12);
	sprintf(valscore,"%d",score);
	couleurCourante(255,255,255);
	epaisseurDeTrait(4);
	afficheChaine(valscore,20,730,12);	
}

void AfficheBalle(int xBalle, int yBalle){
	couleurCourante(255, 0, 0);
	cercle(xBalle, yBalle, 10);
}




#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h> // Pour pouvoir utiliser printf()

#include "GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "ESLib.h" // Pour utiliser valeurAleatoire()


#include "initialisation.h"
#include "affichage.h"
#include "persist.h"

# define LargeurFenetre 800
# define HauteurFenetre 600
# define RayonBalle 10

# define LargeurBrique 50
# define HauteurBrique 25
# define vBarre 9
# include <math.h>



/* La fonction de gestion des evenements, appelee automatiquement par le systeme
des qu'une evenement survient */
void gestionEvenement(EvenementGfx evenement);

void AppuiBouton();

void limiteBrique();
void limiteFenetre();
void limiteBarre1();
void limiteBarre2();
BRK* supprimemaillon(BRK*liste, BRK* Prec, BRK* Asup);

//------PB MODULES:
void Afficher_Brique(BRK* liste);

int xBalle=0;
int yBalle=0;
int Life=0;
int Life2=0;
char valscore[4] = "0";
int score = 0;



double Vitesse=7;
double pi=3.14;//acos(-1);
double alpha=0;
double angle=0;
double vxBalle=0;
double vyBalle=0;

int Pause=0;

static int Etat_Menu=1;
static int Etat_Pause=0;
static int Etat_Prec;
static int i=1;
static int Niveau=0;
static int z=0;
static int x=0;
static int Debut_Partie=0;

static int xBrique=0;
static int yBrique=0;

static int Gauche1 = 0;
static int Gauche2 = 0;
static int Droite1 = 0;
static int Droite2 = 0;
static int xBarre1 = 0;
static int xBarre2 = 0;
static int yBarre1 = 0;
static int yBarre2 = 0;
static int Etat_Partie=0;


BRK * liste = NULL;
BRK* nv =NULL;




int main(int argc, char **argv)
{
	initialiseGfx(argc, argv);
	
	prepareFenetreGraphique("GfxLib", LargeurFenetre, HauteurFenetre);
	
	/* Lance la boucle qui aiguille les evenements sur la fonction gestionEvenement ci-apres,
		qui elle-meme utilise fonctionAffichage ci-dessous */
	lanceBoucleEvenements();
	
	return 0;
}




/* La fonction de gestion des evenements, appelee automatiquement par le systeme
des qu'une evenement survient */
void gestionEvenement(EvenementGfx evenement)
{

	/* On va aussi animer une balle traversant l'ecran */
	
	switch (evenement)
	{
		case Initialisation:
			//liste = (BRK*)malloc(sizeof(BRK));
            nv = (BRK*)malloc(sizeof(BRK));
			xBalle = 400;
			yBalle = 65;
			xBarre1 = 375;
			xBarre2 = 375;
			yBarre1 = 40;
			yBarre2 = 545; 	
			/* Le message "Initialisation" est envoye une seule fois, au debut du
			programme : il permet de fixer "image" a la valeur qu'il devra conserver
			jusqu'a la fin du programme : soit "image" reste a NULL si l'image n'a
			pas pu etre lue, soit "image" pointera sur une structure contenant
			les caracteristiques de l'image "imageNB.bmp" */

			// Configure le systeme pour generer un message Temporisation
			// toutes les 20 millisecondes
			demandeTemporisation(20);
			break;
		
		case Temporisation:
			

			if((i==5) && (Life==3)){
				if((Niveau == 1) && (x==0)){
					liste = listeSOLO1(liste,nv);
					x++;
				}
				if((Niveau == 2) && (x==0)){
					liste = listeSOLO2(liste,nv);
					x++;
				}
				if((Niveau == 3) && (x==0)){
					liste = listeSOLO3(liste,nv);
					x++;
				}
			}
			if((i==6) && (x==0) && (Life==3) && (Life2==3)){
				liste = listeVS(liste,nv);
				x++;
			}
			if(Debut_Partie==0){
				vyBalle=7;
				vxBalle=0;
				xBalle=425;
				yBalle=65;
				xBarre1=375;
				xBarre2=375;
				if(Etat_Pause==2){
					xBarre1=270;
					xBarre2=430;
					xBalle=320;
				}
			}
			if(Debut_Partie==1){
				if(i==5){
					if((Etat_Partie!=0) && (Pause==1)){
						xBalle += vxBalle;
						yBalle += vyBalle;
						if(Gauche1==1)
							if(xBarre1 > 10)
								xBarre1 -= vBarre;
						if(Droite1==1)
							if(xBarre1 <= 689)
								xBarre1 += vBarre;
						limiteFenetre();
						limiteBrique(liste);
						limiteBarre1();
					}
				}
				if(i==6){
					if((Etat_Partie!=0) && (Pause==1)){
						xBalle += vxBalle;
						yBalle += vyBalle;
						if(Gauche1==1)
							if(xBarre1 > 10)
								xBarre1 -= vBarre;
						if(Gauche2==1)
							if(xBarre2 > 10)
								xBarre2 -= vBarre;
						if(Droite1==1)
							if(xBarre1 <= 689)
								xBarre1 += vBarre;
						if(Droite2==1)
							if(xBarre1 <= 689)
								xBarre2 += vBarre;
						limiteFenetre();
						limiteBrique(liste);
						limiteBarre1();
						limiteBarre2();
					}
				}
			}
			rafraichisFenetre();
		break;
			
		case Affichage:
			switch(i){
				case 1:
				Menu();
				if(Etat_Pause!=0){
					Menu_Reprendre();
				}
				Etat_Menu=1;
				break;
				case 2:
				Menu();
				Menu_Solo();
				if(Etat_Pause!=0){
					Menu_Reprendre();
				}
				Etat_Menu=2;
				break;
				case 3:
				Menu();
				Menu_1V1();
				if(Etat_Pause!=0){
					Menu_Reprendre();
				}
				Etat_Menu=3;
				break;
/* MENU H-S */			case 4:
				Menu_Quitter();
				MenuScore();
				if(z==0){
					Etat_Prec=Etat_Menu;
					z++;
				}
				Etat_Menu=4;
				break;
				case 5:
				Afficher_Brique(liste);
				AfficheBalle(xBalle,yBalle);
				AfficheBarre(xBarre1,yBarre1);
				AfficheScore(score, valscore);
				Afficher_vies1(Life);
				if(Debut_Partie==0){
					Menu_Fleche();
				}	
				Etat_Pause=1;
				Etat_Partie=1;
				Etat_Menu=5;
				break;
				case 6:
				Afficher_Brique(liste);
				AfficheBalle(xBalle,yBalle);
				AfficheBarre(xBarre1,yBarre1);
				AfficheBarre(xBarre2,yBarre2);
				Afficher_vies1(Life);
				Afficher_vies2(Life2);
				if(Debut_Partie==0){
					Menu_Fleche();
				}
				Etat_Pause=2;
				Etat_Partie=1;
				Etat_Menu=5;
				break;
				case 7:
				Afficher_Brique(liste);
				AfficheBalle(xBalle,yBalle);
				AfficheBarre(xBarre1,yBarre1);
				AfficheScore(score, valscore);
				Afficher_vies1(Life);
				x=0;
				if(Life==0)
					Defaite();
				if(Life!=0)
					Victoire();
				TestHS(score);
				Menu_Fleche();
				break;
				case 8:
				Afficher_Brique(liste);
				AfficheBalle(xBalle,yBalle);
				AfficheBarre(xBarre1,yBarre1);
				AfficheBarre(xBarre2,yBarre2);
				Afficher_vies1(Life);
				Afficher_vies2(Life2);
				x=0;
				if(Life==0)
					VictoireJoueur2();
				if(Life2==0)
					VictoireJoueur1();
				TestHS(score);
				Menu_Fleche();
				break;
				default:
				break;

			}
		break;
			
		case Clavier:
			printf("%c : ASCII %d\n", caractereClavier(), caractereClavier());

			switch (caractereClavier())
			{
				case 'Q':
				case 'q':
					termineBoucleEvenements();
					break;
				case 'P': 
				case 'p':
					if((i!=7) && (i!=8)){
						i=1;
						Etat_Partie=0;
					}
				break;


			}
		break;
			
		case ClavierSpecial:
			printf("ASCII %d\n", toucheClavier());
			switch(toucheClavier()){
				case ToucheFlecheGauche:
					Gauche1=1;
					Droite1=0;
				break;
				case ToucheFlecheDroite:
					Gauche1=0;
					Droite1=1;
				break;
				case ToucheFlecheHaut:
					if((i==5) || (i==6)){
						Debut_Partie=1;
						Pause=1;
					}
					if((i==7) || (i==8)){
						i=1;
						Etat_Pause=0;
					}
				break;
				default :
					Gauche1=0;
					Droite1=0;
				break;
			}
		break;

		case BoutonSouris:
			switch(etatBoutonSouris()){
				case GaucheAppuye:
					if((i!=5) && (i!=6) && (i!=7) && (i!=8))
						AppuiBouton();
					if(i==6){
						Gauche2=1;
						Droite2=0;
					}
					printf("Bouton gauche appuye en : (%d, %d)\n", abscisseSouris(), ordonneeSouris());
				break;

				case DroiteAppuye:
					if((i!=5) || (i!=6) || (i!=7) || (i!=8))
						AppuiBouton();
					if(i==6){
						Gauche2=0;
						Droite2=1;
					}
					printf("Bouton droite appuye en : (%d, %d)\n", abscisseSouris(), ordonneeSouris());
				break;

				default:
					Gauche2=0;
					Droite2=0;
				break;
			}
		break;

		case Inactivite: // Quand aucun message n'est disponible
		break;
		
		case Souris:
		break;
		case Redimensionnement: // La taille de la fenetre a ete modifie ou on est passe en plein ecran
			// Donc le systeme nous en informe
			if (xBalle >= largeurFenetre())
				xBalle = largeurFenetre()-1;
			if (yBalle >= hauteurFenetre())
				yBalle = hauteurFenetre()-1;
			printf("Largeur : %d\t", largeurFenetre());
			printf("Hauteur : %d\n", hauteurFenetre());
		break;
	}
}

void AppuiBouton(){
		switch(Etat_Menu){
		case 1:
/* SOLO */		if((abscisseSouris()>=300) && (abscisseSouris()<=500) && (ordonneeSouris()<=450) && (ordonneeSouris()>=400))
				i=2;
/* 1V1 */		if((abscisseSouris()>=300) && (abscisseSouris()<=500) && (ordonneeSouris()<=350) && (ordonneeSouris()>=300))
				i=3;
/* EXIT */		if((abscisseSouris()>=550) && (abscisseSouris()<=700) && (ordonneeSouris()<=150) && (ordonneeSouris()>=100))
				termineBoucleEvenements();
/* H-S */		if((abscisseSouris()>=100) && (abscisseSouris()<=250) && (ordonneeSouris()<=150) && (ordonneeSouris()>=100))
				i=4;
/* REPRENDRE */		if(Etat_Pause!=0){
				if((abscisseSouris()>=700) && (abscisseSouris()<=780) && (ordonneeSouris()<=580) && (ordonneeSouris()>=500)){
					if(Etat_Pause==1)
						i=5;
					if(Etat_Pause==2)
						i=6;
					Pause=0;
				}
			}
		break;
/*-------------------------------------------------------------------------------------------------------*/
		case 2:
/* SOLO */		if((abscisseSouris()>=300) && (abscisseSouris()<=500) && (ordonneeSouris()<=450) && (ordonneeSouris()>=400))
				i=2;
/* 1V1 */		if((abscisseSouris()>=300) && (abscisseSouris()<=500) && (ordonneeSouris()<=350) && (ordonneeSouris()>=300))
				i=3;
/* EXIT */		if((abscisseSouris()>=550) && (abscisseSouris()<=700) && (ordonneeSouris()<=150) && (ordonneeSouris()>=100))
				termineBoucleEvenements();
/* H-S */		if((abscisseSouris()>=100) && (abscisseSouris()<=250) && (ordonneeSouris()<=150) && (ordonneeSouris()>=100))
				i=4;
/* NIVEAU 1 */		if((abscisseSouris()>=100) && (abscisseSouris()<=275) && (ordonneeSouris()<=250) && (ordonneeSouris()>=200)){
				Debut_Partie=0;
				effaceFenetre (0,0,0);
				i=5;
				Niveau=1;
				x=0;
				score=0;
				Life=3;
    		}
/* NIVEAU 2 */		if((abscisseSouris()>=325) && (abscisseSouris()<=475) && (ordonneeSouris()<=250) && (ordonneeSouris()>=200)){
				Debut_Partie=0;
				effaceFenetre (0,0,0);
				i=5;
				Niveau=2;
				x=0;
				score=0;
				Life=3;
			}
/* NIVEAU 3 */		if((abscisseSouris()>=525) && (abscisseSouris()<=700) && (ordonneeSouris()<=250) && (ordonneeSouris()>=200)){
				Debut_Partie=0;
				effaceFenetre (0,0,0);
				i=5;
				Niveau=3;
				x=0;
				score=0;
				Life=3;
			}
/* REPRENDRE */		if(Etat_Pause!=0){
				if((abscisseSouris()>=700) && (abscisseSouris()<=780) && (ordonneeSouris()<=580) && (ordonneeSouris()>=500)){
					if(Etat_Pause==1)
						i=5;
					if(Etat_Pause==2)
						i=6;
					Pause=0;
				}
			}
		break;
/*-------------------------------------------------------------------------------------------------------*/
		case 3:
/* SOLO */		if((abscisseSouris()>=300) && (abscisseSouris()<=500) && (ordonneeSouris()<=450) && (ordonneeSouris()>=400))
				i=2;
/* 1V1 */		if((abscisseSouris()>=300) && (abscisseSouris()<=500) && (ordonneeSouris()<=350) && (ordonneeSouris()>=300))
				i=3;
/* EXIT */		if((abscisseSouris()>=550) && (abscisseSouris()<=700) && (ordonneeSouris()<=150) && (ordonneeSouris()>=100))
				termineBoucleEvenements();
/* H-S */		if((abscisseSouris()>=100) && (abscisseSouris()<=250) && (ordonneeSouris()<=150) && (ordonneeSouris()>=100))
				i=4;
/* NIVEAU 1 */		if((abscisseSouris()>=325) && (abscisseSouris()<=475) && (ordonneeSouris()<=250) && (ordonneeSouris()>=200)){
				Debut_Partie=0;
				effaceFenetre (0,0,0);
				i=6;
				Niveau=1;
				x=0;
				score=0;
				Life=3;
				Life2=3;
			}
/* REPRENDRE */		if(Etat_Pause!=0){
				if((abscisseSouris()>=700) && (abscisseSouris()<=780) && (ordonneeSouris()<=580) && (ordonneeSouris()>=500)){
					if(Etat_Pause==1)
						i=5;
					if(Etat_Pause==2)
						i=6;
					Pause=0;
				}
			}
		break;
/*-------------------------------------------------------------------------------------------------------*/
		case 4:			
/* QUITER */			if((abscisseSouris()>=22) && (abscisseSouris()<=85) && (ordonneeSouris()<=580) && (ordonneeSouris()>=502)){
				i=Etat_Prec;
				z=0;
			}
		break;
		case 5:
		break;
		}
	return;
}



void limiteFenetre(){
	if (xBalle < 5){
		vxBalle = -vxBalle;
		xBalle=10;
	}
	if (xBalle >= largeurFenetre()){
		vxBalle = -vxBalle;
		xBalle=770;
	}
	if (yBalle >= hauteurFenetre()-10){
		if(i==5){
			yBalle = 590;
			vyBalle = -vyBalle;
		}
		if(i==6){
			Life2--;
			if(Life2!=0)
				Debut_Partie=0;
			if(Life2==0)
				i=8;
		}
	}
	if (yBalle <= 0){
		Life--;
		if(Life!=0)
			Debut_Partie=0;
		if(Life==0){
			if(Etat_Pause==1)
				i=7;
			if(Etat_Pause==2)
				i=8;
		}
	}
	return;
}


void limiteBrique(BRK * liste){
	BRK * Asup=liste;
	BRK * Prec=NULL;
	while(Asup!=NULL){
		xBrique = Asup->PositionX;
		yBrique = Asup->PositionY;
		if (((xBalle >= xBrique) && (xBalle <= (xBrique+LargeurBrique)) && (yBalle >= yBrique) && (yBalle <= (yBrique+HauteurBrique))) || (((xBalle-RayonBalle) >= xBrique) && ((xBalle-RayonBalle) <= (xBrique+LargeurBrique)) && (yBalle >= yBrique) && (yBalle <= (yBrique+HauteurBrique))) || ((xBalle >= xBrique) && (xBalle <= (xBrique+LargeurBrique)) && ((yBalle+RayonBalle) >= yBrique) && ((yBalle+RayonBalle) <= (yBrique+HauteurBrique))) || ((xBalle >= xBrique) && (xBalle <= (xBrique+LargeurBrique)) && ((yBalle-RayonBalle) >= yBrique) && ((yBalle-RayonBalle) <= (yBrique+HauteurBrique)))){
			if (((xBalle - xBrique) < (LargeurBrique/2)) && ((yBalle - yBrique) < (HauteurBrique/2))){
				if ((xBalle - xBrique) >= (yBalle - yBrique))
					vyBalle = -vyBalle;
				else
					vxBalle = -vxBalle;
			}
			if (((xBalle - xBrique) < (LargeurBrique/2)) && ((yBalle - yBrique) >= (HauteurBrique/2))){
				if ((xBalle - xBrique) >= (HauteurBrique - (yBalle - yBrique)))
					vyBalle = -vyBalle;
				else 
					vxBalle = -vxBalle;
			}
			if (((xBalle - xBrique) >= (LargeurBrique/2)) && ((yBalle - yBrique) < (HauteurBrique/2))){
				if ((LargeurBrique - (xBalle - xBrique)) >= (yBalle - yBrique))
					vyBalle = -vyBalle;
				else 
					vxBalle = -vxBalle;
			}
			if (((xBalle - xBrique) >= (LargeurBrique/2)) && ((yBalle - yBrique) >= (HauteurBrique/2))){
				if ((LargeurBrique - (xBalle - xBrique)) >= (HauteurBrique - (yBalle - yBrique)))
					vyBalle = -vyBalle;
				else
					vxBalle = -vxBalle;
			}
			if(Asup->lvl==1){
				liste=supprimemaillon(liste,Prec,Asup);
			}
			if((Asup->lvl==2) || (Asup->lvl==3))
				Asup->lvl-=1;
			score++;
			return;
		}
		Prec=Asup;
		Asup=Asup->suiv;
	}
	return;
}

void limiteBarre1(){
	if ((yBalle <= yBarre1 + HauteurBarre) && (yBalle >= yBarre1 + HauteurBarre - 7)){
		if ((xBalle >= xBarre1-0.2*LargeurBarre) && (xBalle < (xBarre1 + 0.2*LargeurBarre))){
			yBalle= 66;
			alpha = pi/2;
			angle = pi - acos((vxBalle - Vitesse)/14) + alpha;
			if(angle>(5*pi)/6)
				angle=(5*pi)/6;
			vxBalle = Vitesse*cos(angle);
			vyBalle = Vitesse*sin(angle);	
		}
		if ((xBalle >= (xBarre1 + 0.2*LargeurBarre)) && (xBalle < (xBarre1 + 0.45*LargeurBarre))){
			yBalle= 66;
			alpha = pi/3.5;
			angle = pi - acos((vxBalle - Vitesse)/14) + alpha;
			if(angle>(5*pi)/6)
			vxBalle = Vitesse*cos(angle);
			vyBalle = Vitesse*sin(angle);	
		}
		if ((xBalle >= (xBarre1 + 0.45*LargeurBarre)) && (xBalle < (xBarre1 + 0.55*LargeurBarre))){
			yBalle= 66;
			vyBalle = -vyBalle;	
		}
		if ((xBalle >= (xBarre1 + 0.55*LargeurBarre)) && (xBalle < (xBarre1 + 0.8*LargeurBarre))){
			yBalle= 66;
			alpha = -pi/100;
			angle = pi - acos((vxBalle - Vitesse)/14) + alpha;
		//	if(angle<pi/6)
			//	angle=pi/6;
			vxBalle = Vitesse*cos(angle);
			vyBalle = Vitesse*sin(angle);		
		}
		if ((xBalle >= (xBarre1 + 0.8*LargeurBarre)) && (xBalle < (xBarre1 + 1.2*LargeurBarre))){
			yBalle= 66;
			alpha = -pi/6;
			angle = pi - acos((vxBalle - Vitesse)/14) + alpha;
			if(angle<pi/10)
				angle=pi/10;
			vxBalle = Vitesse*cos(angle);
			vyBalle = Vitesse*sin(angle);		
		}
	}
	return;
}

void limiteBarre2(){
	if ((yBalle >= yBarre2) && (yBalle <= yBarre2 + 7)){
		if ((xBalle >= xBarre2-0.2*LargeurBarre) && (xBalle < (xBarre2 + 0.2*LargeurBarre))){
			yBalle= 525;
			alpha = pi/2;
			angle = pi - acos((vxBalle - Vitesse)/14) + alpha;
			if(angle>(5*pi)/6)
				angle=(5*pi)/6;
			vxBalle = Vitesse*cos(angle);
			vyBalle = Vitesse*sin(angle);
			vyBalle = -vyBalle;	
		}
		if ((xBalle >= (xBarre2 + 0.2*LargeurBarre)) && (xBalle < (xBarre2 + 0.45*LargeurBarre))){
			yBalle= 525;
			alpha = pi/3.5;
			angle = pi - acos((vxBalle - Vitesse)/14) + alpha;
			if(angle>(5*pi)/6)
				angle=(5*pi)/6;
			printf("HELLO");
			vxBalle = Vitesse*cos(angle);
			vyBalle = Vitesse*sin(angle);
			vyBalle = -vyBalle;	
		}
		if ((xBalle >= (xBarre2 + 0.45*LargeurBarre)) && (xBalle < (xBarre2 + 0.55*LargeurBarre))){
			yBalle= 525;
			vyBalle = -vyBalle;
			printf("OLLEH");	
		}
		if ((xBalle >= (xBarre2 + 0.55*LargeurBarre)) && (xBalle < (xBarre2 + 0.8*LargeurBarre))){
			yBalle= 525;
			alpha = -pi/100;
			angle = pi - acos((vxBalle - Vitesse)/14) + alpha;
		//	if(angle<pi/6)
			//	angle=pi/6;
			vxBalle = Vitesse*cos(angle);
			vyBalle = Vitesse*sin(angle);	
			vyBalle = -vyBalle;	
		}
		if ((xBalle >= (xBarre2 + 0.8*LargeurBarre)) && (xBalle < (xBarre2 + 1.2*LargeurBarre))){
			yBalle= 525;
			alpha = -pi/6;
			angle = pi - acos((vxBalle - Vitesse)/14) + alpha;
			if(angle<pi/10)
				angle=pi/10;
			vxBalle = Vitesse*cos(angle);
			vyBalle = Vitesse*sin(angle);	
			vyBalle = -vyBalle;	
		}
	}
	return;
}


BRK* supprimemaillon(BRK*liste, BRK* Prec, BRK* Asup){
    if(Asup==liste){ //On supprime le premier element
        liste=liste->suiv;
        free(Asup);}
    else{        //On supprime un autre element dans la liste
        Asup=Prec->suiv;
        Prec->suiv=Asup->suiv;
        free(Asup);}
    return liste;
}


void Afficher_Brique(BRK* liste){
	int niv;
	//printf("Afficher Briques\n");
    while(liste!=NULL){
		xBrique=liste->PositionX;
		yBrique=liste->PositionY;
		niv=liste->lvl;
        if(niv==1){
			couleurCourante(0,0,230);
		}
		if(niv==2){
			couleurCourante(230,0,230);
		}
		if(niv==3){
			couleurCourante(255,0,0);
		}
		rectangle(xBrique, yBrique, xBrique+LargeurBrique, yBrique+HauteurBrique);
		liste=liste->suiv;
	}
	return;
}


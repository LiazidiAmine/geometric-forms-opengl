/*=================================================================*/
/*= E.Incerti - incerti@upem.fr                                   =*/
/*= Université Paris-Est-Marne-la-Vallée                          =*/
/*= Exemple de fonctionalités de lib. graphique <g3x>             =*/
/*=================================================================*/

#include <g3x.h>

/*Variable globale*/
G3Xpoint *Vrtx;
G3Xvector *Norm;
int *boolean;
int nbv, nbn;
	
/*= FONCTION DE MODELISATION =*/
static void Init(void)
{
	/*Statique : appeler 1 fois
	 * 
	 * allocation memoire ici 
	 * */
	fprintf(stderr,"\nInit\n");	
}

/*= FONCTION D'ANIMATION =*/
static void Anim(void)
{
	/*
	 * Que du calcul
	 * Pas d'affichage*/
	fprintf(stderr,"Anim-");		
}

/*= FONCTION DE DESSIN PRINCIPALE =*/
static void Draw(void)
{
	/*
	 * Que du dessin
	 * appelée dans une boucle infini
	 * la dedans qu'on fait du OPENGL
	 * Pas de calcul
	 * 
	 * */
	glPushMatrix();
	glTranslatef(.5,.5,.5);
	g3x_Material(G3Xr,.25,.25,.25,.25,.25);
	glutSolidSphere(1.,40,40);
	glPopMatrix();
	g3x_Material(G3Xg,.25,.25,.25,.25,.25);
	glutSolidCube(1.6);
}

static void draw2(){
	glPushMatrix();
	g3x_Material(G3Xr,.25,.25,.25,.25,.25);
	glPointSize(1.);
	glBegin(GL_POINTS);
	G3Xpoint *v = Vrtx;
	G3Xvector *n = Norm;
	int *tab = boolean;
	int i=0;
	while(v < Vrtx+nbv){
		
			glNormal3dv(*n); 
		if(tab[i] == 1){
			glVertex3dv(*v);
		}
		n++;
		i++;
		v++;
	}
	glEnd();
	glPopMatrix();	
}

/*=    ACTION A EXECUTER EN SORTIE   =*/
/*= libération de mémoire, nettoyage =*/
/*= -> utilise la pile de <atexit()> =*/
static void Exit(void)
{
	/*
	 * 1 fois : atexit()
	 * et les free
	 * */
  /* rien à faire ici puisqu'il n'y a pas d'allocation dynamique */
	fprintf(stderr,"\nbye !\n");
}


int main(int argc, char** argv)
{ 
  
  /* initialisation de la fenêtre graphique et paramétrage Gl */
  g3x_InitWindow(*argv,768,512);

  /* définition des fonctions */
  g3x_SetInitFunction(Init2);     /* la fonction de sortie */
  g3x_SetExitFunction(Exit);     /* la fonction de sortie */
  g3x_SetDrawFunction(draw2);     /* la fonction de Dessin */
	g3x_SetAnimFunction(Anim);
	
	/* boucle d'exécution principale */
  return g3x_MainStart();
  /* rien après ça */
}
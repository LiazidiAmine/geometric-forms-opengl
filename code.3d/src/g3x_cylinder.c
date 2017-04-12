/*=================================================================*/
/*= E.Incerti - incerti@upem.fr                                   =*/
/*= Université Paris-Est-Marne-la-Vallée                          =*/
/*= Exemple de fonctionalités de lib. graphique <g3x>             =*/
/*=================================================================*/

#include <g3x.h>

/*Variable globale*/
G3Xpoint *Vrtx;
G3Xvector *Norm;
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
static void Init2(){
	
	int nbp = 250;
	int nbm = 250;
	int i,j;
	nbv = nbp*nbm; 
	nbn = nbv;
	
	Vrtx = (G3Xpoint *)calloc(nbv,sizeof(G3Xpoint));
	Norm = (G3Xvector *)calloc(nbn,sizeof(G3Xvector));
	
	double a = 2.*PI/nbv;
	double phi = PI/nbp;
	
	G3Xpoint *v = Vrtx;
	G3Xvector *n = Norm;
	
	/*bande du cilindre*/
	double r = g3x_Rand_Delta(0,1);
	double theta = g3x_Rand_Delta(0,2*PI);
	for(i= 0; i < nbv/3; i++){	
		double t = g3x_Rand_Delta(1,1);
		double k = g3x_Rand_Delta(0,PI);
		(*n)[0]=cos(i*k);
		(*v)[0] = (*n)[0];
		(*n)[1]=sin(i*k);
		(*v)[1] = (*n)[1];
		(*n)[2]= t;
		(*v)[2] = (*n)[2];
		v++;
		n++;
	}
	
	/*disque de base */
	for(i=nbv/3; i < nbv*2/3; i++){
		double r = g3x_Rand_Delta(0,1);
		double theta = g3x_Rand_Delta(0,2*PI);
		(*n)[0]= 0;
		(*v)[0] = r*cos(theta);
		(*n)[1]= 0;
		(*v)[1] = r*sin(theta);
		(*n)[2]= -1;
		(*v)[2] = 0;
		v++;
		n++;
	}

	/*disque du haut*/
	/*TODO*/
	/*disque de base */
	for(i=nbv*2/3; i < nbv; i++){
		double t = g3x_Rand_Delta(1,1);
		double r = g3x_Rand_Delta(0,1);
		double theta = g3x_Rand_Delta(0,2*PI);
		(*n)[0]= 0;
		(*v)[0] = r*cos(theta);
		(*n)[1]= 0;
		(*v)[1] = r*sin(theta);
		(*n)[2]= -1;
		(*v)[2] = 2;
		v++;
		n++;
	}
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
	while(v < Vrtx+nbv){
		glNormal3dv(*n); n++;
		glVertex3dv(*v);v++;
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

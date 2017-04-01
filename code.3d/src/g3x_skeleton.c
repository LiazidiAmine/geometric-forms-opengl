/*=================================================================*/
/*= E.Incerti - incerti@upem.fr                                   =*/
/*= Universit� Paris-Est-Marne-la-Vall�e                          =*/
/*= Exemple de fonctionalit�s de lib. graphique <g3x>             =*/
/*=================================================================*/

#include <g3x.h>

/* des couleurs prédéfinies */
static G3Xcolor rouge  ={1.0,0.0,0.0};
static G3Xcolor jaune  ={1.0,1.0,0.0};
static G3Xcolor vert   ={0.0,1.0,0.0};
static G3Xcolor cyan   ={0.0,1.0,1.0};
static G3Xcolor bleu   ={0.0,0.0,1.0};
static G3Xcolor magenta={1.0,0.0,1.0};
/* paramètres géométriques */
static double angle= 0.00;
static double rayon= 0.66;
/* paramètres de lumière/matière */
static double alpha= 0.5;
static double ambi = 0.2;
static double diff = 0.3;
static double spec = 0.4;
static double shin = 0.5;

#define MAXCOL 25
static G3Xcolor colmap[MAXCOL];

static G3Xvector W={1.,2.,3.};
static double    b=0.1;

/*= FONCTION DE MODELISATION =*/
static void Init(void)
{
	fprintf(stderr,"\nInit\n");
}

/*= FONCTION D'ANIMATION =*/
static void Anim(void)
{
	static double pas=0.1;
	b+=pas;
	W[0]+=pas;
	W[1]-=pas;
	W[2]+=pas;
	if (W[0]<-10. || W[0]>+10.) pas=-pas;
}

/* flag d'affichag/masquage */
static bool FLAG_TERRE  =true;

/*= FONCTION DE DESSIN PRINCIPALE =*/
static void Draw(void)
{
	/* un soleil dans l'axe du plan */
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
			/* une sphere rouge*/
			g3x_Material(rouge,ambi,diff,spec,shin,1.);
			glutSolidSphere(rayon,40,40);
			/* une sphere jaune*/
			g3x_Material(jaune,ambi,diff,spec,shin,alpha);
			glutSolidSphere(rayon,40,45);
	glDisable(GL_BLEND);

	/* les spheres animees autour du centre */
	int i=0;
	double a=360./8;
	glPushMatrix();
		glRotatef(-2.*b,0.,0.,W[2]);
		while (i<MAXCOL)
		{
			g3x_Material(colmap[i],ambi,diff,spec,shin,1.);
			glRotatef(a,0.,0.,1.);
			glPushMatrix();
				/* distance du centre (distance de o,distance de o,hauteur)*/
				glTranslatef(1.,2.,0.);
				glRotatef(i*a,2.,0.,0.);
				glRotatef(10.*b,W[0],W[1],W[2]);
				glutSolidSphere(0.4,40,45);
			glPopMatrix();
			i += 1;
		}
	glPopMatrix();

}

/*=    ACTION A EXECUTER EN SORTIE   =*/
/*= lib�ration de m�moire, nettoyage =*/
/*= -> utilise la pile de <atexit()> =*/
static void Exit(void)
{
  /* rien � faire ici puisqu'il n'y a pas d'allocation dynamique */
	fprintf(stderr,"\nbye !\n");
}


int main(int argc, char** argv)
{

  /* initialisation de la fen�tre graphique et param�trage Gl */
  g3x_InitWindow(*argv,768,512);

	/* paramètres caméra */
  /* param. géométrique de la caméra. cf. gluLookAt(...) */
  g3x_SetPerspective(40.,100.,1.);
  /* position, orientation de la caméra */
  g3x_SetCameraSpheric(0.25*PI,+0.25*PI,6.,(G3Xpoint){0.,0.,0.});

	/* initialisation d'une carte de couleurs */
	g3x_FillColorMap(colmap,MAXCOL);

  /* d�finition des fonctions */
  g3x_SetInitFunction(Init);     /* la fonction de sortie */
  g3x_SetExitFunction(Exit);     /* la fonction de sortie */
  g3x_SetDrawFunction(Draw);     /* la fonction de Dessin */
	g3x_SetAnimFunction(Anim);

	/* boucle d'ex�cution principale */
  return g3x_MainStart();
  /* rien apr�s �a */
}

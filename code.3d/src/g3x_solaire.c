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
static bool FLAG_SOLEIL  = true;
static bool FLAG_PLANETS1 = true;
static bool FLAG_PLANETS2 = true;
static bool FLAG_PLANETS3 = true;

/*= FONCTION DE DESSIN PRINCIPALE =*/
static void Draw(void)
{
	/* un soleil dans l'axe du plan */
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		if(FLAG_SOLEIL)
		{
			/* une sphere rouge*/
			g3x_Material(rouge,ambi,diff,spec,shin,1.);
			glutSolidSphere(rayon,40,40);
			/* une sphere jaune*/
			g3x_Material(jaune,ambi,diff,spec,shin,alpha);
			glutSolidSphere(rayon,40,45);
		}
	glDisable(GL_BLEND);

	/* Les planetes autour du soleil */
	if(FLAG_PLANETS1)
	{
		int i=0;
		double a=360./4;
		glPushMatrix();
			glRotatef(-2.*b,0.,0.,W[2]);
			while (i<MAXCOL)
			{
				g3x_Material(colmap[i],ambi,diff,spec,shin,1.);
				glRotatef(a,0.,0.,1.);
				glPushMatrix();
					/* distance du centre (distance de o,distance de o,hauteur)*/
					glTranslatef(1.,1.,0.);
					glRotatef(i*a+angle,2.,0.,0.);
					glRotatef(10.*b,W[0],W[1],W[2]);
					glutSolidSphere(rayon/6,40,45);
				glPopMatrix();
				i += 1;
			}
		glPopMatrix();
	}

	if(FLAG_PLANETS2)
	{
		/* les spheres animees autour du centre */
		int i=0;
		double a=360./6;
		glPushMatrix();
			glRotatef(-2.*b,0.,0.,W[2]);
			while (i<MAXCOL)
			{
				g3x_Material(colmap[i],ambi,diff,spec,shin,1.);
				glRotatef(a,0.,0.,1.);
				glPushMatrix();
					/* distance du centre (distance de o,distance de o,hauteur)*/
					glTranslatef(0.,2.,0.);
					glRotatef(i*a+angle,2.,0.,0.);
					glRotatef(10.*b,W[0],W[1],W[2]);
					glutSolidSphere(rayon/2,40,45);
				glPopMatrix();
				i += 1;
			}
		glPopMatrix();
	}

	if(FLAG_PLANETS3)
	{
		/* les spheres animees autour du centre */
		int i=0;
		double a=360./3;
		glPushMatrix();
			glRotatef(-2.*b,0.,0.,W[2]);
			while (i<MAXCOL)
			{
				g3x_Material(colmap[i],ambi,diff,spec,shin,1.);
				glRotatef(a,0.,0.,1.);
				glPushMatrix();
					/* distance du centre (distance de o,distance de o,hauteur)*/
					glTranslatef(1.,2.,0.);
					glRotatef(i*a+angle,2.,0.,0.);
					glRotatef(10.*b,W[0],W[1],W[2]);
					glutSolidSphere(rayon/3,40,45);
				glPopMatrix();
				i += 1;
			}
		glPopMatrix();
	}
}

/*=    ACTION A EXECUTER EN SORTIE   =*/
/*= lib�ration de m�moire, nettoyage =*/
/*= -> utilise la pile de <atexit()> =*/
static void Exit(void)
{
  /* rien � faire ici puisqu'il n'y a pas d'allocation dynamique */
	fprintf(stderr,"\nbye !\n");
}

/*= action : variation de couleur =*/
static void action1(void)
{
  rouge[0]-=0.01;  rouge[1]+=0.01;
  vert[1] -=0.01;  vert[2] +=0.01;
  bleu[2] -=0.01;  bleu[0] +=0.01;
}
/*= action : variation de couleur =*/
static void action2(void)
{
  rouge[0]+=0.01;  rouge[1]-=0.01;
  vert[1] +=0.01;  vert[2] -=0.01;
  bleu[2] +=0.01;  bleu[0] -=0.01;
}
/*= action : affiche les parametre camera dans le terminal =*/
static void camera_info(void)
{
	G3Xcamera* cam=g3x_GetCamera();
	fprintf(stderr,"position (x:%lf,y:%lf,z:%lf)\n",(*cam->pos)[0],(*cam->pos)[1],(*cam->pos)[2]);
	fprintf(stderr,"cible    (x:%lf,y:%lf,z:%lf)\n",(*cam->tar)[0],(*cam->tar)[1],(*cam->tar)[2]);
	fprintf(stderr,"coord. spheriques (d:%lf,theta:%lf,phi:%lf)\n",cam->dist,cam->theta,cam->phi);
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

	g3x_CreateSwitch("soleil ",&FLAG_SOLEIL,"affiche/masques le soleil  ");
	g3x_CreateSwitch("planetes 1 ",&FLAG_PLANETS1 ,"affiche/masques les planetes 1     ");
	g3x_CreateSwitch("planetes 2  ",&FLAG_PLANETS2  ,"affiche/masques les planetes 2     ");
	g3x_CreateSwitch("planetes 3  ",&FLAG_PLANETS3  ,"affiche/masques les planetes 3");

	g3x_SetScrollWidth(6);
	g3x_CreateScrollv_d("ray",&rayon,0.1,  2.0,1.0,"rayon sphere     ");
	g3x_CreateScrollv_d("ang",&angle,0.0,360.0,1.0,"angle rotation   ");
	g3x_CreateScrollv_d("alf",&alpha,0.0,  1.0,1.0,"transparence cube");

	g3x_SetScrollWidth(4);
	g3x_CreateScrollh_d("shin",&shin,0.0,1.0,1.0,"intensite lumiere brillance ");
	g3x_CreateScrollh_d("spec",&spec,0.0,1.0,1.0,"intensite lumiere speculaire");
	g3x_CreateScrollh_d("diff",&diff,0.0,1.0,1.0,"intensite lumiere diffuse   ");
	g3x_CreateScrollh_d("ambi",&ambi,0.0,1.0,1.0,"intensite lumiere ambiante  ");

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

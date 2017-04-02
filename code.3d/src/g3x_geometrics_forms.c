#include <g3x.h>

/* quelques couleurs pr�d�finies */
static G3Xcolor marron1={0.30,0.20,0.10};
static G3Xcolor marron2={0.50,0.40,0.20};
static G3Xcolor rouge  ={1.00,0.00,0.00};
static G3Xcolor vert   ={0.00,1.00,0.00};
static G3Xcolor bleu   ={0.00,0.00,1.00};
static G3Xcolor jaune  ={1.00,1.00,0.00};
static G3Xcolor cyan   ={0.00,1.00,1.00};
static G3Xcolor orange ={0.75,0.50,0.00};
static G3Xcolor vert2  ={0.50,0.75,0.00};
static G3Xcolor metal  ={0.60,0.75,0.95};
static G3Xcolor glass  ={0.90,0.90,1.00};
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
/* scale */
static double scalef = 1.;

#define MAXCOL 25
static G3Xcolor colmap[MAXCOL];

static G3Xvector W={1.,2.,3.};
static double    b=0.1;
void Anim(void)
{
	static double pas=0.1;
	b+=pas;
	W[0]+=pas;
	W[1]-=pas;
	W[2]+=pas;
	if (W[0]<-10. || W[0]>+10.) pas=-pas;
}

/* flag d'affichag/masquage */
static bool FLAG_POLYGON=true;
static bool FLAG_CYLINDER=true;

/* mise en forme des paramètre de couleur/matière des objets */
/*	col    : teinte RGB
		ambi   : réaction à la lumière ambiante (blanche par défaut)
		diff   : réaction à la lumière diffuse (blanche par défaut)
		spec   : réaction à la lumière de spéculosité (blanche par défaut)
		shine  : coeff. de spéculosité (max par défaut -- 256.    )
		transp : valeur de transparence (0.: objet totalement transp. / 1.:opaque)
*/
void Material(G3Xcolor col, float ambi, float diff, float spec, float shine, float transp)
{
	float tmp[4];
	tmp[3]=transp;

	tmp[0]=ambi*col[0];
	tmp[1]=ambi*col[1];
	tmp[2]=ambi*col[2];
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT  ,tmp);
	tmp[0]=diff*col[0];
	tmp[1]=diff*col[1];
	tmp[2]=diff*col[2];
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE  ,tmp);
	tmp[0]=spec*col[0];
	tmp[1]=spec*col[1];
	tmp[2]=spec*col[2];
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR ,tmp);
	glMaterialf (GL_FRONT_AND_BACK,GL_SHININESS,shine*256.);
}


/* Cylindre canonique de rayon 1, de hauteur 2, centré en (0.,0.,0.) */
/* n :   nombre de 'côtés'                                         */
void gl_Cylinder(int n)
{
	int i;
	double pas=2*PI/n;
	double a=0.,cosa,sina;
  glBegin(GL_QUAD_STRIP);
  for (i=0;i<=n;i++)
  {
		cosa=cos(a);
		sina=sin(a);
  	a+=pas;
    glNormal3d(cosa, sina, 0.0);
    glVertex3d(cosa, sina,-1.0);
    glVertex3d(cosa, sina,+1.0);
	}
  glEnd();

}

/* Polygone avec n têtes*/
void gl_Polygon(int n)
{
	int i;
	double pas=2*PI/n;
	double cosa,sina;
  glBegin(GL_QUAD_STRIP);
	g3x_Material(rouge,ambi,diff,spec,shin,1.);
	glNormal3d(0.,0.,0.5);
  for (i=0;i<=n;i++)
  {
		cosa=cos(angle);
		sina=sin(angle);
  	angle+=pas;
    glNormal3d(cosa, sina, 0.0);
    glVertex3d(cosa, sina,-1.0);
    glVertex3d(cosa, sina,+1.0);
	}
	angle=0.0;
  glEnd();
}

/*= FONCTION DE DESSIN PRINCIPALE =*/
/*= les objets sont reconstruits  =*/
/*= à  chaque dessin              =*/
static void Dessin(void)
{
	if(FLAG_POLYGON){
		/* polygon */
		glPushMatrix();
			glScalef(scalef,scalef,scalef);
			gl_Polygon(5);
		glPopMatrix();
	}

	if(FLAG_CYLINDER){
		/* polygon */
		glPushMatrix();
			glScalef(scalef,scalef,scalef);
			gl_Cylinder(3);
		glPopMatrix();
	}
}


/*=    ACTION A EXECUTER EN SORTIE   =*/
/*= libération de mémoire, nettoyage =*/
/*= -> utilise la pile de <atexit()> =*/
static void Exit(void)
{
  /*! rien à faire dans cet exemples !*/
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
/*= action : variation du scale =*/
static void action3(void)
{
  scalef-=0.01;  scalef+=0.01;
}



int main(int argc, char** argv)
{
  /* initialisation de la fenêtre graphique et paramétrage Gl */
  g3x_InitWindow(*argv,768,512);

  /* position, orientation de la caméra */
	g3x_SetCameraSpheric(0.,0.25*PI,15.,(G3Xpoint){0.,0.,0.});

	g3x_CreateSwitch("polygon",&FLAG_POLYGON,"affiche/masques le polygon  ");
	g3x_CreateSwitch("cylinder ",&FLAG_CYLINDER ,"affiche/masques la cylindre     ");

  g3x_SetScrollWidth(6);
	g3x_CreateScrollv_d("ray",&rayon,0.1,  2.0,1.0,"rayon sphere     ");
	g3x_CreateScrollv_d("ang",&angle,0.0,360.0,1.0,"angle rotation   ");
	g3x_CreateScrollv_d("alf",&alpha,0.0,  1.0,1.0,"transparence cube");
	g3x_CreateScrollv_d("sca",&scalef,0.0, 1.0,1.0,"scale");

	g3x_SetScrollWidth(4);
	g3x_CreateScrollh_d("shin",&shin,0.0,1.0,1.0,"intensite lumiere brillance ");
	g3x_CreateScrollh_d("spec",&spec,0.0,1.0,1.0,"intensite lumiere speculaire");
	g3x_CreateScrollh_d("diff",&diff,0.0,1.0,1.0,"intensite lumiere diffuse   ");
	g3x_CreateScrollh_d("ambi",&ambi,0.0,1.0,1.0,"intensite lumiere ambiante  ");

	/* initialisation d'une carte de couleurs */
	g3x_FillColorMap(colmap,MAXCOL);


  /* définition des fonctions */
  g3x_SetExitFunction(Exit  );     /* la fonction de sortie */
  g3x_SetDrawFunction(Dessin);     /* la fonction de Dessin */

  /* boucle d'exécution principale */
  return g3x_MainStart();
}

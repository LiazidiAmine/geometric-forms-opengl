#include <g3x.h>
#include "cylinder.h"

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

static double    b=0.1;

void AnimCylinder(G3Xvector W)
{
	static double pas=0.1;
	b+=pas;
	W[0]+=pas;
	W[1]-=pas;
	W[2]+=pas;
	if (W[0]<-10. || W[0]>+10.) pas=-pas;
}

/* Cylindre canonique de rayon 1, de hauteur 2, centré en (0.,0.,0.) */
/* n :   nombre de 'côtés'                                         */
void DrawCylinder(int n)
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

/*= FONCTION DE DESSIN PRINCIPALE =*/
/*= les objets sont reconstruits  =*/
/*= à  chaque dessin              =*/
static void DessinCylinder(void)
{

	/* polygon */
	glPushMatrix();
		glScalef(scalef,scalef,scalef);
		gl_Cylinder(3);
	glPopMatrix();

}

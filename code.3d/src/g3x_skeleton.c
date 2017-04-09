#include <g3x.h>

/* flag d'affichag/masquage */
static bool FLAG_CERCLE =true;
static bool FLAG_CARRE  =true;
static bool FLAG_TRIANGLE  =true;
static bool FLAG_ETOILE =true;

/* des couleurs prédéfinies */
static G3Xcolor marron1={0.30,0.20,0.10};
static G3Xcolor marron2={0.50,0.40,0.20};
static G3Xcolor rouge  ={1.0,0.0,0.0};
static G3Xcolor jaune  ={1.0,1.0,0.0};
static G3Xcolor vert   ={0.0,1.0,0.0};
static G3Xcolor cyan   ={0.0,1.0,1.0};
static G3Xcolor bleu   ={0.0,0.0,1.0};
static G3Xcolor magenta={1.0,0.0,1.0};
static G3Xcolor orange ={0.75,0.50,0.00};
static G3Xcolor vert2  ={0.50,0.75,0.00};
static G3Xcolor metal  ={0.60,0.75,0.95};
static G3Xcolor glass  ={0.90,0.90,1.00};
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
void Anim(void)
{
	static double pas=0.1;
	b+=pas;
	W[0]+=pas;
	W[1]-=pas;
	W[2]+=pas;
	if (W[0]<-10. || W[0]>+10.) pas=-pas;
}
/* mise en forme des param�tre de couleur/mati�re des objets */
/*	col    : teinte RGB
		ambi   : r�action � la lumi�re ambiante (blanche par d�faut)
		diff   : r�action � la lumi�re diffuse (blanche par d�faut)
		spec   : r�action � la lumi�re de sp�culosit� (blanche par d�faut)
		shine  : coeff. de sp�culosit� (max par d�faut -- 256.    )
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
/*= FONCTION DE MODELISATION =*/
static void Init(void)
{
	fprintf(stderr,"\nInit\n");
}

/*
 *	Polygone
 *	n côtés, h hauteur, col color
 */
void polygone(int n,double h, G3Xcolor col)
{
	double h2 = h/2;
	int i;
	double pas=2*PI/n;
	double a=0.,cosa,sina;
	Material(marron1,0.20,0.50,0.,0.,1.);
	glBegin(GL_QUAD_STRIP);
  for (i=0;i<=n;i++)
  {
		cosa=cos(a);
		sina=sin(a);
  	a+=pas;
    glNormal3d(cosa, sina, 0.0);
    glVertex3d(cosa, sina,-h2);
    glVertex3d(cosa, sina,+h2);
	}
  glEnd();
}

/*
 * Etoile
 * c'est un polygone de 5 côtés avec un pas plus grand
 * h hauteur, col color
 */
void etoile(double h, G3Xcolor col)
{
 	double h2 = h/2;
 	int n=5,i;
 	double pas=4*PI/n;
 	double a=0.,cosa,sina;
	Material(col,0.20,0.50,0.,0.,1.);
	glBegin(GL_QUAD_STRIP);
   for (i=0;i<=n;i++)
   {
 		cosa=cos(a);
 		sina=sin(a);
   	a+=pas;
     glNormal3d(cosa, sina, 0.0);
     glVertex3d(cosa, sina,-h2);
     glVertex3d(cosa, sina,+h2);
 	}
   glEnd();
 }

/*
 * Carre
 * c'est un polygone à 4 côtés
 * h hauteur, col color
 */
void carre(double h, G3Xcolor col)
{
	polygone(4,h,col);
}

/*
 * triangle
 * c'est un polygone à 4 côtés
 * h hauteur, col color
 */
void triangle(double h, G3Xcolor col)
{
	polygone(3,h,col);
}

/*
 * cercle
 * c'est un polygone avec énormément de côtés
 * h hauteur, col color
 */
void cercle(double h, G3Xcolor col)
{
	int i,n = 200;;
	double pas=2*PI/n;
	double a=0.,cosa,sina,h2 = h/2;
	Material(col,0.20,0.50,0.,0.,1.);
	glBegin(GL_QUAD_STRIP);
	for (i=0;i<=n;i++)
	{
		cosa=cos(a);
		sina=sin(a);
		a+=pas;
		glNormal3d(cosa, sina, 0.0);
		glVertex3d(cosa, sina,-h2);
		glVertex3d(cosa, sina,+h2);
	}
	glEnd();
}
/*
 * cercle
 * c'est un polygone avec énormément de côtés
 * h hauteur, col color
 */
void drawCrescentTriStrip(double step,double scale,double fullness, G3Xcolor col,double h) {
		Material(col,0.20,0.50,0.,0.,1.);
		glBegin(GL_QUAD_STRIP);
		glVertex3d(0.,scale,h);
    float angle=step;
    while (angle<M_PI) {
        double sinAngle=sinf(angle);
        double cosAngle=cosf(angle);
        glVertex3d(scale*sinAngle,scale*cosAngle,h);
        glVertex3d(-fullness*scale*sinAngle,scale*cosAngle,h);
        angle+=step;
    }
    glVertex3d(0.,-scale,h);
		glEnd();
}

void drawSpecialCircle(){

	double x,y,angle;
	/*All lines lie in the xy plane.*/
	double z=0;
	glBegin(GL_LINES);/* Call only once for all remaining points*/
	Material(bleu,0.20,0.50,0.,0.,1.);
	for(angle = 0.; angle <= PI; angle += (PI/20.))
	  {
		/* Top half of the circle*/
	  x = 50.*sin(angle);
	  y = 50.*cos(angle);
	  glVertex3d(x, y, z);/*First endpoint of line*/

	  x = 50.*sin(angle + PI);
	  y = 50.*cos(angle + PI);
	  glVertex3d(x, y, z);/*Second endpoint of line*/
	  }

	glEnd();/*Done drawing points*/
}

void drawEllipse(){
	glBegin(GL_LINE_STRIP);
	Material(marron2,0.20,0.50,0.,0.,1.);
	double x, y,z,i;
	for(i = 0; i < 360; i=i+0.1)
	{
		x = sin(i);
		y = cos(i);
		z = 0;
		glVertex3d(x,y,z);
	}
	glEnd();
}

void drawCircle(){
	/* Call only once for all remaining points*/
glBegin(GL_LINE_STRIP);
Material(marron2,0.20,0.50,0.,0.,1.);
double angle,x,y,z = -50.;
for(angle = 0.; angle <= (2.*PI)*3.; angle += 0.1)
  {
  x = 50.*rayon*sin(angle);
  y = 50.*rayon*cos(angle);

  /* Specify the point and move the z value up a little*/
  glVertex3d(x, y, z);
  z += 0.1;
  }

/* Done drawing points */
glEnd();
}
void DrawEllipse()
{
  Material(marron2,1,1,1.,1.,1.);
	double x,y,z,t;
	glBegin(GL_POINTS);
	for(t = 0.; t <= 360; t +=1.)
	{
    x = 0.625*rayon*sin(t);
	  y = 0.5*rayon*cos(t);
	  z = 0.;
	  glVertex3d(x,y,z);
	}
  glEnd();
}
/*= FONCTION DE DESSIN PRINCIPALE =*/
static void Draw(void)
{
	/*drawCrescentTriStrip(1.,2.,2.,rouge,2.);*/
	/*drawSpecialCircle();*/
	/*drawLines();*/
	/*drawCircle();*/
	DrawEllipse();
	if(FLAG_ETOILE)
	{
		etoile(3,bleu);
	}
	if (FLAG_CERCLE)
	{
		cercle(2,rouge);
	}
	if (FLAG_CARRE)
	{
		carre(1,magenta);
	}
	if (FLAG_TRIANGLE)
	{
		triangle(1,marron2);
	}

}

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
	/* initialisation de la fenêtre graphique et paramétrage Gl */
  g3x_InitWindow(*argv,768,512);

	/* paramètres caméra */
  /* param. géométrique de la caméra. cf. gluLookAt(...) */
  g3x_SetPerspective(40.,100.,1.);
  /* position, orientation de la caméra */
  g3x_SetCameraSpheric(0.25*PI,+0.25*PI,6.,(G3Xpoint){0.,0.,0.});

  /* fixe les param. colorimétriques du spot lumineux */
	/* lumiere blanche (c'est les valeurs par defaut)   */
  g3x_SetLightAmbient (1.,1.,1.);
  g3x_SetLightDiffuse (1.,1.,1.);
  g3x_SetLightSpecular(1.,1.,1.);

  /* fixe la position et la direction du spot lumineux */
	/* (c'est les valeurs par defaut)                    */
  g3x_SetLightPosition (10.,10.,10.);
  g3x_SetLightDirection( 0., 0., 0.);

	g3x_CreateSwitch("cercle ",&FLAG_CERCLE ,"affiche/masques le cercle     ");
	g3x_CreateSwitch("carre  ",&FLAG_CARRE  ,"affiche/masques le carre     ");
	g3x_CreateSwitch("triangle  ",&FLAG_TRIANGLE  ,"affiche/masques l'triangleahedre");
	g3x_CreateSwitch("etoile  ",&FLAG_ETOILE  ,"affiche/masques la etoile");

  g3x_SetScrollWidth(6);
	g3x_CreateScrollv_d("ray",&rayon,0.1,  2.0,1.0,"rayon etoile     ");
	g3x_CreateScrollv_d("ang",&angle,0.0,360.0,1.0,"angle rotation   ");
	g3x_CreateScrollv_d("alf",&alpha,0.0,  1.0,1.0,"transparence cube");

	g3x_SetScrollWidth(4);
	g3x_CreateScrollh_d("shin",&shin,0.0,1.0,1.0,"intensite lumiere brillance ");
	g3x_CreateScrollh_d("spec",&spec,0.0,1.0,1.0,"intensite lumiere speculaire");
	g3x_CreateScrollh_d("diff",&diff,0.0,1.0,1.0,"intensite lumiere diffuse   ");
	g3x_CreateScrollh_d("ambi",&ambi,0.0,1.0,1.0,"intensite lumiere ambiante  ");

  /* action attachées à des touches */
  g3x_SetKeyAction('g',action1,"variation de couleur");
  g3x_SetKeyAction('G',action2,"variation de couleur");
  g3x_SetKeyAction('c',camera_info,"pos./dir. de la camera => terminal");

	/* initialisation d'une carte de couleurs */
	g3x_FillColorMap(colmap,MAXCOL);

  /* définition des fonctions */
  g3x_SetExitFunction(Exit  );     /* la fonction de sortie */
  g3x_SetDrawFunction(Draw);     /* la fonction de Dessin */
	g3x_SetAnimFunction(Anim);


	/* JUSTE POUT ILLUSTRATION DU TRACEUR D'ALLOC EN COMPIL DEGUG */
	void* ptr=malloc(1);

	/* boucle d'exécution principale */
  return g3x_MainStart();
  /* rien après ça */
}

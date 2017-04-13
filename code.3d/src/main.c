#include <g3x.h>
#define CONE 1
#define CUBE 2
#define SPHERE 3
#define TOR 4


typedef struct object{
  G3Xpoint *Vrtx;
  G3Xvector *Norm;
  int *display;
}Object;
/* Tableau de formes */
Object o[5];
/* flag d'affichag/masquage */
static bool FLAG_CUBE=true;
static bool FLAG_CONE=true;
static bool FLAG_SPHERE =true;
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
static double densite = 1000.;

#define MAXCOL 25
static G3Xcolor colmap[MAXCOL];

int nbv, nbn;

static void InitSphere(void){
  int N = densite/2;
  int P = densite/2;
  G3Xpoint *p;
  G3Xvector *n;
  int *tab;
    o[SPHERE].Vrtx = (G3Xpoint *)calloc(N*P,sizeof(G3Xpoint));
    o[SPHERE].Norm = (G3Xvector *)calloc(N*P,sizeof(G3Xvector));
    o[SPHERE].display =(int *)calloc(N*P,sizeof(int));
    p = o[SPHERE].Vrtx;
    n = o[SPHERE].Norm;
    tab=o[SPHERE].display;
    double theta = 2*PI/N,phi= PI/P;

    int i=0;
    int j=0;
    for(i=0;i<N;i++)
    {
      for(j=0;j<P;j++)
      {
        theta = g3x_Rand_Delta(2*PI/N,0.50);
        phi   = g3x_Rand_Delta(PI/P,0.50);
        (*p)[0] =  cos(i*theta)*sin(j*phi);
        (*p)[1] =  sin(i*theta)*sin(j*phi);
        (*p)[2] =  cos(j*phi);
        p++;
      }
    }
    for(i=0;i<N*P;i++){
      tab[i] =1;
    }
    memcpy(o[SPHERE].Norm,o[SPHERE].Vrtx,N*P*sizeof(G3Xcoord));
}

static void InitCube(){

  int nbp = densite/2;
  int nbm = densite/2;
  int i,j;


  o[CUBE].Vrtx = (G3Xpoint *)calloc(nbv,sizeof(G3Xpoint));
  o[CUBE].Norm = (G3Xvector *)calloc(nbn,sizeof(G3Xvector));
  o[CUBE].display =(int *)calloc(nbn,sizeof(int));

  double a = 2.*PI/nbv;
  double phi = PI/nbp;

  G3Xpoint *v = o[CUBE].Vrtx;
  G3Xvector *n = o[CUBE].Norm;
  int *boolean =o[CUBE].display;

  /*bande du cilindre*/
  double r = g3x_Rand_Delta(0,1);
  double theta = g3x_Rand_Delta(0,2*PI);


  /*disque de base */
  for(i=0; i < nbv/6; i++){
    double r = g3x_Rand_Delta(0,1);
    double theta = g3x_Rand_Delta(0,2*PI);
    double phi = g3x_Rand_Delta(0,2*PI);
    boolean[i]=0;
    (*n)[0]= 0;
    (*v)[0] =1;
    (*n)[1]= 0;
    (*v)[1] = g3x_Rand_Delta(0,1);
    (*n)[2]= -1;
    (*v)[2] = g3x_Rand_Delta(0,1);
    v++;
    n++;
  }
  for(i=nbv/6; i < nbv*2/6; i++){
    double r = g3x_Rand_Delta(0,1);
    double theta = g3x_Rand_Delta(0,2*PI);
    double phi = g3x_Rand_Delta(0,2*PI);
    boolean[i]=1;
    (*n)[0]= 0;
    (*v)[0] = -1;
    (*n)[1]= 0;
    (*v)[1] = g3x_Rand_Delta(0,1);
    (*n)[2]= -1;
    (*v)[2] = g3x_Rand_Delta(0,1);
    v++;
    n++;
  }
  for(i=nbv*2/6; i < nbv*3/6; i++){
    double r = g3x_Rand_Delta(0,1);
    double theta = g3x_Rand_Delta(0,2*PI);
    double phi = g3x_Rand_Delta(0,2*PI);
    boolean[i]=1;
    (*n)[0]= 0;
    (*v)[0] = g3x_Rand_Delta(0,1);
    (*n)[1]= 0;
    (*v)[1] = -1;
    (*n)[2]= -1;
    (*v)[2] = g3x_Rand_Delta(0,1);
    v++;
    n++;
  }
  for(i=nbv*3/6; i < nbv*4/6; i++){
    double r = g3x_Rand_Delta(0,1);
    double theta = g3x_Rand_Delta(0,2*PI);
    double phi = g3x_Rand_Delta(0,2*PI);
    boolean[i]=1;
    (*n)[0]= 0;
    (*v)[0] = g3x_Rand_Delta(0,1);
    (*n)[1]= 0;
    (*v)[1] = 1;
    (*n)[2]= -1;
    (*v)[2] = g3x_Rand_Delta(0,1);
    v++;
    n++;
  }
  for(i=nbv*4/6; i < nbv*5/6; i++){
    double r = g3x_Rand_Delta(0,1);
    double theta = g3x_Rand_Delta(0,2*PI);
    double phi = g3x_Rand_Delta(0,2*PI);
    boolean[i]=1;
    (*n)[0]= 0;
    (*v)[0] = g3x_Rand_Delta(0,1);
    (*n)[1]= 0;
    (*v)[1] = g3x_Rand_Delta(0,1);
    (*n)[2]= -1;
    (*v)[2] = -1;
    v++;
    n++;
  }
  for(i=nbv*5/6; i < nbv*6/6; i++){
    double r = g3x_Rand_Delta(0,1);
    double theta = g3x_Rand_Delta(0,2*PI);
    double phi = g3x_Rand_Delta(0,2*PI);
    boolean[i]=1;
    (*n)[0]= 0;
    (*v)[0] = g3x_Rand_Delta(0,1);
    (*n)[1]= 0;
    (*v)[1] = g3x_Rand_Delta(0,1);
    (*n)[2]= -1;
    (*v)[2] = +1;
    v++;
    n++;
  }


  /*disque du haut*/
  /*TODO*/
}

static void InitCone(){

  int nbp = densite/2;
  int nbm = densite/2;
  int i,j;
  nbv = nbp*nbm;
  nbn = nbv;

  o[CONE].Vrtx = (G3Xpoint *)calloc(nbv,sizeof(G3Xpoint));
  o[CONE].Norm = (G3Xvector *)calloc(nbn,sizeof(G3Xvector));
  o[CONE].display =(int *)calloc(nbn,sizeof(int));

  double a = 2.*PI/nbv;
  double phi = PI/nbp;

  G3Xpoint *v = o[CONE].Vrtx;
  G3Xvector *n = o[CONE].Norm;
  int *tab= o[CONE].display;

  for(i= nbv/5+1; i < nbv; i++){
    double t = g3x_Rand_Delta(1,1);
    double k = g3x_Rand_Delta(0,PI);
    (*n)[0]= (1-t/2)*cos(i*k);
    (*v)[0] = (*n)[0];
    (*n)[1]= (1-t/2)*sin(i*k);
    (*v)[1] = (*n)[1];
    (*n)[2]= t;
    (*v)[2] = (*n)[2];
    tab[i]=1;
    v++;
    n++;
  }

  for(i=0; i < nbv/5; i++){
    double r = g3x_Rand_Delta(0,1);
    double theta = g3x_Rand_Delta(0,2*PI);
    (*n)[0]= 0;
    (*v)[0] = r*cos(theta);
    (*n)[1]= 0;
    (*v)[1] = r*sin(theta);
    (*n)[2]= -1;
    (*v)[2] = 0;
    tab[i]=1;
    v++;
    n++;
  }

}


static void drawCone(){

  G3Xpoint *v = o[CONE].Vrtx;
  G3Xvector *n = o[CONE].Norm ;
  int *tab = o[CONE].display;
  while(v < o[CONE].Vrtx+nbv){

      glNormal3dv(*n);
      glVertex3dv(*v);
    n++;
    v++;
  }

}

static void drawCube(){

  G3Xpoint *v = o[CUBE].Vrtx;
  G3Xvector *n = o[CUBE].Norm ;
  int *tab = o[CUBE].display;
  while(v < o[CUBE].Vrtx+nbv){

      glNormal3dv(*n);
      glVertex3dv(*v);
    n++;
    v++;
  }

}

static void drawSphere(){

  G3Xpoint *v = o[SPHERE].Vrtx;
  G3Xvector *n = o[SPHERE].Norm ;
  int *tab = o[SPHERE].display;
  while(v < o[SPHERE].Vrtx+nbv){

      glNormal3dv(*n);
      glVertex3dv(*v);
    n++;
    v++;
  }

}

static void Init(void)
{
	InitCone();
  InitCube();
  InitSphere();
}
/*= FONCTION D'ANIMATION =*/
static void Anim(void)
{

}

/*= FONCTION DE DESSIN PRINCIPALE =*/
static void Draw(void)
{
  glBegin(GL_POINTS);
  /*glPointSize(1.);*/

  glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    if(FLAG_CUBE){
      g3x_Material(rouge,ambi,diff,spec,shin,1.);
      drawCube();
    }
    if(FLAG_CONE){
      g3x_Material(vert,ambi,diff,spec,shin,alpha);
      drawCone();
    }
  glDisable(GL_BLEND);

  if(FLAG_SPHERE){
    g3x_Material(bleu,ambi,diff,spec,shin,1.);
    drawSphere();
  }


  glEnd();

}

/*= action : affiche les parametre camera dans le terminal =*/
static void camera_info(void)
{
	G3Xcamera* cam=g3x_GetCamera();
	fprintf(stderr,"position (x:%lf,y:%lf,z:%lf)\n",(*cam->pos)[0],(*cam->pos)[1],(*cam->pos)[2]);
	fprintf(stderr,"cible    (x:%lf,y:%lf,z:%lf)\n",(*cam->tar)[0],(*cam->tar)[1],(*cam->tar)[2]);
	fprintf(stderr,"coord. spheriques (d:%lf,theta:%lf,phi:%lf)\n",cam->dist,cam->theta,cam->phi);
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
  /* initialisation de la fenêtre graphique et paramétrage Gl */
  g3x_InitWindow(*argv,768,512);

  /* paramètres caméra */
  /* param. géométrique de la caméra. cf. gluLookAt(...) */
  g3x_SetPerspective(40.,100.,1.);
  /* position, orientation de la caméra */
  g3x_SetCameraSpheric(0.25*PI,+0.25*PI,6.,(G3Xpoint){0.,0.,0.});

  g3x_CreateSwitch("sphere",&FLAG_SPHERE,"affiche/masques la sphere  ");
	g3x_CreateSwitch("cube ",&FLAG_CUBE ,"affiche/masques le cube     ");
	g3x_CreateSwitch("cone  ",&FLAG_CONE  ,"affiche/masques le cone     ");

  /* initialisation d'une carte de couleurs*/
	g3x_FillColorMap(colmap,MAXCOL);

  /* définition des fonctions */
  g3x_SetInitFunction(Init);     /* la fonction de sortie */
  g3x_SetExitFunction(Exit);     /* la fonction de sortie */
  g3x_SetDrawFunction(Draw);     /* la fonction de Dessin */
	g3x_SetAnimFunction(Anim);

	/* boucle d'exécution principale */
  return g3x_MainStart();
  /* rien après ça */
}

#include <g3x.h>
#define CONE 1
#define CUBE 2
#define SPHERE 3
#define TOR 4

/* Structure d'une forme */
typedef struct object{
  G3Xpoint *Vrtx;
  G3Xvector *Norm;
  G3Xpoint *Cpy;
  int *display;
  int zoom;
}Object;
/* Tableau de formes */
Object shape[5];

/* Structure d'un noeud d'arbre */
typedef struct node{
  int shape_name;
  struct object *shape;
  struct node *left;
  struct node *right;
} node;
/* Initialisation de l'arbre */
node *Tree = NULL;

/*
 * FONCTIONS DE MANIPULATION D'ARBRE
 */
 /* TODO il faut que je rajoute un code d'operations dans la structure de noeud et
 ensuite une fonction compute qui prend en parametre un noeud, et utilise ses deux fils
 afin d'avoir le resultat de l'operation */
 static int RIGHT = 1;
 static int LEFT = 0;
 void addNode(node **tree, int key, Object **shape, int direction)
 {
     node *tmpNode;
     node *tmpTree = *tree;

     node *elem = malloc(sizeof(node));
     elem->shape_name = key;
     elem->shape = *shape;
     elem->left = NULL;
     elem->right = NULL;

     if(tmpTree){
       tmpNode = tmpTree;
       if(direction == LEFT){
         tmpNode->left = elem;
       }else{
         tmpNode->right = elem;
       }
     }else  *tree = elem;
 }

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
static int density = 500;

#define MAXCOL 25
static G3Xcolor colmap[MAXCOL];

int nbv, nbn;

/*
 * Fonctions utilitaires
 */

int max(int a, int b, int c){
  if(a>b && a>c){
    return a;
  }
  else if(b>c){
    return b;
  }
  else{
    return c;
  }
}

int pow2(int a){
	return a*a;
}

/*
 * Gestion du zoom
 */
 static initZoomValue(){
 	int i=1;
 	for(;i<5;i++){
 		shape[i].zoom=1;
 	}
 }

 static double zoom=1;
 static double k=1.005;

 void zoomFunc(Object *shape){
  G3Xpoint *v = shape->Vrtx;
   G3Xpoint *m = shape->Cpy;
   G3Xvector *n = shape->Norm;
   while(v < shape->Vrtx+nbv){
   	if(zoom<1.05 && zoom>0.95){
   		return;

   	}else if(zoom>1){
   		(*v)[0]*=k;
   		(*v)[1]*=k;
   		(*v)[2]*=k;

   	}
   	else{
   		(*v)[0]/=k;
   		(*v)[1]/=k;
   		(*v)[2]/=k;
   	}
     v++;

   }
   shape->zoom=zoom;

 }

/*
 * Fonctions d'initialisation des formes
 */

static void InitSphere(void){
  int N = density/2;
  int P = density/2;
  G3Xpoint *p;
  G3Xvector *n;
  int *tab;
    shape[SPHERE].Vrtx = (G3Xpoint *)calloc(N*P,sizeof(G3Xpoint));
    shape[SPHERE].Norm = (G3Xvector *)calloc(N*P,sizeof(G3Xvector));
    shape[SPHERE].display =(int *)calloc(N*P,sizeof(int));
    p = shape[SPHERE].Vrtx;
    n = shape[SPHERE].Norm;
    tab=shape[SPHERE].display;
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
    memcpy(shape[SPHERE].Norm,shape[SPHERE].Vrtx,N*P*sizeof(G3Xcoord));
}

static void InitCube(){

  int nbp = density/2;
  int nbm = density/2;
  int i,j;


  shape[CUBE].Vrtx = (G3Xpoint *)calloc(nbv,sizeof(G3Xpoint));
  shape[CUBE].Norm = (G3Xvector *)calloc(nbn,sizeof(G3Xvector));
  shape[CUBE].display =(int *)calloc(nbn,sizeof(int));

  double a = 2.*PI/nbv;
  double phi = PI/nbp;

  G3Xpoint *v = shape[CUBE].Vrtx;
  G3Xvector *n = shape[CUBE].Norm;
  int *boolean =shape[CUBE].display;


  double r = g3x_Rand_Delta(0,1);
  double theta = g3x_Rand_Delta(0,2*PI);



  for(i=0; i < nbv/6; i++){
    double r = g3x_Rand_Delta(0,1);
    double theta = g3x_Rand_Delta(0,2*PI);
    double phi = g3x_Rand_Delta(0,2*PI);
    boolean[i]=1;
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

  int nbp = density/2;
  int nbm = density/2;
  int i,j;
  nbv = nbp*nbm;
  nbn = nbv;

  shape[CONE].Vrtx = (G3Xpoint *)calloc(nbv,sizeof(G3Xpoint));
  shape[CONE].Norm = (G3Xvector *)calloc(nbn,sizeof(G3Xvector));
  shape[CONE].display =(int *)calloc(nbn,sizeof(int));
  shape[CONE].Cpy=(G3Xpoint *)calloc(nbv,sizeof(G3Xpoint));

  double a = 2.*PI/nbv;
  double phi = PI/nbp;

  G3Xpoint *v = shape[CONE].Vrtx;
  G3Xpoint *cpy = shape[CONE].Cpy;
  G3Xvector *n = shape[CONE].Norm;

  int *tab= shape[CONE].display;

  for(i= nbv/5+1; i < nbv; i++){
    double t = g3x_Rand_Delta(1,1);
    double k = g3x_Rand_Delta(0,PI);
    (*n)[0]= (1-t/2)*cos(i*k);
    (*v)[0] = (*n)[0];

    (*n)[1]= (1-t/2)*sin(i*k);
    (*v)[1] = (*n)[1];
    (*n)[2]= t;
    (*v)[2] = (*n)[2];
    (*cpy)[0]=((*v)[0]);
    (*cpy)[1]=((*v)[1]);
    (*cpy)[2]=((*v)[2]);
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

/*
 * Fonctions de dessins
 */

static void drawCone(){

  G3Xpoint *v = shape[CONE].Vrtx;
  G3Xpoint *m = shape[CONE].Cpy;
  G3Xvector *n = shape[CONE].Norm ;
  int *tab = shape[CONE].display;
  int i=0,j=0;
  zoomFunc(&shape[CONE]);

  while(v < shape[CONE].Vrtx+nbv){
  	if(tab[i] > 0){

      glNormal3dv(*n);
      glVertex3dv(*v);
  	}
    n++;
    v++;
    i++;
  }

}

static void drawCube(){

  G3Xpoint *v = shape[CUBE].Vrtx;
  G3Xvector *n = shape[CUBE].Norm ;
  int *tab = shape[CUBE].display;
  int i=0;
  zoomFunc(&shape[CUBE]);
  while(v < shape[CUBE].Vrtx+nbv){
  	if(tab[i] > 0){
      glNormal3dv(*n);
      glVertex3dv(*v);
    }
    n++;
    v++;
    i++;
  }

}

static void drawSphere(){

  G3Xpoint *v = shape[SPHERE].Vrtx;
  G3Xvector *n = shape[SPHERE].Norm ;
  int *tab = shape[SPHERE].display;
  int i=0;
  zoomFunc(&shape[SPHERE]);
  while(v < shape[SPHERE].Vrtx+nbv){
  	  if(tab[i] > 0){
        glNormal3dv(*n);
        glVertex3dv(*v);
      }
      n++;
      v++;
      i++;
  }

}

/*
 * Gestion de l'intersection d'objets
 */

/*intesection*/

int isSphereIntersectPoint(Object o, G3Xpoint p){
  G3Xpoint point;
  point[0]=p[0]*(*o.Vrtx[0]);
  point[1]=p[1]*(*o.Vrtx[1]);
  point[2]=p[2]*(*o.Vrtx[2]);
  return (pow2(point[0])+pow2(point[1])+pow2(point[2]) < 1 ? 0 : 1);
}

int isCubeIntersectPoint(Object o, G3Xpoint p){
  G3Xpoint point;
  point[0]=p[0]*(*o.Vrtx[0]);
  point[1]=p[1]*(*o.Vrtx[1]);
  point[2]=p[2]*(*o.Vrtx[2]);
  return (max(point[0],point[1],point[2]) < 1 ? 0 : 1);
}

/*o1 inclu dans 02*/
void intersectShapes(Object o2,Object o1,int(*function)(Object,G3Xpoint)){
	int i;
	int N = density/2;
  	int P = density/2;
	for(i=0;i<N*P;i++){
		o1.display[i]=(*function)(o2,o1.Vrtx[i]);
	}
}

/*
 * Fonctions principales du programme
 */

static void Init(void)
{
	initZoomValue();
  InitCone();
  InitCube();
  InitSphere();

  intersectShapes(shape[CUBE], shape[SPHERE], isCubeIntersectPoint);
  intersectShapes(shape[CUBE], shape[CONE], isCubeIntersectPoint);
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
    glTranslatef(0.,10.,10.);
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
  g3x_InitWindow(*argv,1024,512);

  /* paramètres caméra */
  /* param. géométrique de la caméra. cf. gluLookAt(...) */
  g3x_SetPerspective(40.,100.,1.);
  /* position, orientation de la caméra */
  g3x_SetCameraSpheric(0.25*PI,+0.25*PI,6.,(G3Xpoint){0.,0.,0.});

  g3x_CreateSwitch("sphere",&FLAG_SPHERE,"affiche/masques la sphere  ");
	g3x_CreateSwitch("cube ",&FLAG_CUBE ,"affiche/masques le cube     ");
	g3x_CreateSwitch("cone  ",&FLAG_CONE  ,"affiche/masques le cone     ");

	/*zoom*/

	g3x_CreateScrollv_d("zoom",&zoom,0.8,1.2,0.1,"zoom");
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

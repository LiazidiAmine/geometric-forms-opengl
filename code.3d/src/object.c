#include <g3x.h>
#define nbp 250
#define nbm 250
#define nbv 250*250
#define nbn 250*250



typedef struct object{
	G3Xpoint *Vrtx;
	G3Xvector *Norm;
	int *display;
}Object;

void createObject(Object o){
	o.Vrtx=(G3Xpoint *)calloc(nbv,sizeof(G3Xpoint));
	if(o.Vrtx==NULL){
		fprintf(stderr, "calloc G3Xpoint");
	}
	o.Norm=(G3Xvector *)calloc(nbn,sizeof(G3Xvector));
	if(o.Norm==NULL){
		fprintf(stderr, "calloc G3Xvector");
	}
	o.display=(int *)calloc(nbn,sizeof(int));
	if(o.display==NULL){
		fprintf(stderr, "calloc display");
	}
}

static void Init2(Object o){
	int i,j;
	
	double a = 2.*PI/nbv;
	double phi = PI/nbp;
	
	G3Xpoint *v = o.Vrtx;
	G3Xvector *n = o.Norm;;
	int *boolean = o.display;
	
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
	
}

static void draw2(Object o){
	glPushMatrix();
	g3x_Material(G3Xr,.25,.25,.25,.25,.25);
	glPointSize(1.);
	glBegin(GL_POINTS);
	G3Xpoint *v = o.Vrtx;
	G3Xvector *n = o.Norm;
	int *tab = o.display;
	int i=0;
	while(v < o.Vrtx+nbv){
		
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

int main(int argc, char** argv)
{ 
  Object o;
  createObject(o);
  /* initialisation de la fenêtre graphique et paramétrage Gl */
  g3x_InitWindow(*argv,768,512);

  /* définition des fonctions */
  g3x_SetInitFunction(Init2(o));     /* la fonction de sortie */
  g3x_SetExitFunction(Exit);     /* la fonction de sortie */
  g3x_SetDrawFunction(draw2(o));     /* la fonction de Dessin */
	g3x_SetAnimFunction(Anim);
	
	/* boucle d'exécution principale */
  return g3x_MainStart();
  /* rien après ça */
}
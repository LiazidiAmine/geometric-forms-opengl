/*=================================================================*/
/*= E.Incerti - incerti@upem.fr                                   =*/
/*= Université Paris-Est-Marne-la-Vallée                          =*/
/*= Exemple de fonctionalités de lib. graphique <g3x>             =*/
/*=================================================================*/

#include <g3x.h>



G3Xpoint *pts,*p;
G3Xvector *nor,*n;


/*= FONCTION DE MODELISATION =*/
static void Init(void)
{
  int N = 100;
  int P = 50;
    o[CONE].Vrtx = (G3Xpoint *)calloc(N*P,sizeof(G3Xpoint));
    o[CONE].Norm = (G3Xvector *)calloc(N*P,sizeof(G3Xvector));

    p = o[CONE].Vrtx;
    n = o[CONE].Norm;

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
    memcpy(o[CONE].Norm,o[CONE].Vrtx,N*P*sizeof(G3Xcoord));
}

/*= FONCTION D'ANIMATION =*/
static void Anim(void)
{
  
}

/*= FONCTION DE DESSIN PRINCIPALE =*/
static void Dessin(void)
{
  G3Xpoint *p;
    G3Xvector *n;
  
  g3x_Material(G3Xr,0.25,0.5,0.5,0.5,0.5);

  glBegin(GL_POINTS);
    
    p = pts;
    n= nor;
    while(p<pts+N*P)
    {
      
      glNormal3dv(*n);
      n++;
      glVertex3dv(*p);
      p++;
      
    }

  glEnd();
  
}

/*=    ACTION A EXECUTER EN SORTIE   =*/
/*= libération de mémoire, nettoyage =*/
/*= -> utilise la pile de <atexit()> =*/
static void Exit(void)
{
  /* rien à faire ici puisqu'il n'y a pas d'allocation dynamique */
  fprintf(stderr,"\nbye !\n");
  free(pts);
  free(nor);
}


int main(int argc, char** argv)
{ 
  
  /* initialisation de la fenêtre graphique et paramétrage Gl */
  g3x_InitWindow(*argv,800,600);

  /* définition des fonctions */
  g3x_SetInitFunction(Init);
  g3x_SetExitFunction(Exit);       /* la fonction de sortie */
  g3x_SetDrawFunction(Dessin);     /* la fonction de Dessin */
  g3x_SetAnimFunction(Anim);
  
  /* boucle d'exécution principale */
  return g3x_MainStart();
  /* rien après ça */
}
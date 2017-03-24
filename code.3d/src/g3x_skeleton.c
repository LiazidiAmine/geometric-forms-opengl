/*=================================================================*/
/*= E.Incerti - incerti@upem.fr                                   =*/
/*= Universit� Paris-Est-Marne-la-Vall�e                          =*/
/*= Exemple de fonctionalit�s de lib. graphique <g3x>             =*/
/*=================================================================*/

#include <g3x.h>

/*= FONCTION DE MODELISATION =*/
static void Init(void)
{
	fprintf(stderr,"\nInit\n");	
}

/*= FONCTION D'ANIMATION =*/
static void Anim(void)
{
	fprintf(stderr,"Anim-");		
}

/*= FONCTION DE DESSIN PRINCIPALE =*/
static void Draw(void)
{
	g3x_Material(G3Xr,.25,.25,.25,.25,.25);
	glutSolidSphere(1.,40,40);
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

  /* d�finition des fonctions */
  g3x_SetInitFunction(Init);     /* la fonction de sortie */
  g3x_SetExitFunction(Exit);     /* la fonction de sortie */
  g3x_SetDrawFunction(Draw);     /* la fonction de Dessin */
	g3x_SetAnimFunction(Anim);
	
	/* boucle d'ex�cution principale */
  return g3x_MainStart();
  /* rien apr�s �a */
}

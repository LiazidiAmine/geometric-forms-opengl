#include <g3x.h>

/*= FONCTION DE MODELISATION =*/
static void Init(void)
{
	fprintf(stderr,"\nInit\n");
}

/*= FONCTION D'ANIMATION =*/
static void Anim(void)
{

}

/*= FONCTION DE DESSIN PRINCIPALE =*/
static void Draw(void)
{

}

static void Exit(void)
{
  /* rien � faire ici puisqu'il n'y a pas d'allocation dynamique */
	fprintf(stderr,"\nbye !\n");
}


int main(int argc, char** argv)
{
	/* boucle d'ex�cution principale */
  return g3x_MainStart();
  /* rien apr�s �a */
}

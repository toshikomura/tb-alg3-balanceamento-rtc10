#include "bs-tree.h"

int main()
{
	tree raiz = NULL;
	object chave;
	char tipo;
	int num_rot=0;
	tipo=getchar();
	scanf("%d\n",&chave);
	while ((tipo=='i') || (tipo=='r') || (tipo=='b'))
	{
		printf("%c %d\n",tipo, chave);
		if (tipo=='i')
		{
			insereSemBal(&raiz,&chave);
			print_tree_border(&raiz);
		}
		else if (tipo=='r')
		{
			removeSemBal(&raiz,&chave);
			print_tree_border(&raiz);
		}
		else if (tipo=='b')
		{
			search_node(&raiz,&chave);
		}
		tipo=getchar();
		scanf("%d\n",&chave);
	}
	partPontoMed(&raiz,&num_rot);
	calcula_balanc(&raiz);
	print_tree_border(&raiz);
	printf("%d\n", num_rot);
}

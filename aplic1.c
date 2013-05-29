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
			insert_node(&raiz,&chave,&num_rot);
			print_tree_border(&raiz);
		}
		else if (tipo=='r')
		{
			remove_node(&raiz,&chave,&num_rot);
			print_tree_border(&raiz);
		}
		else if (tipo=='b')
		{
			search_node(&raiz,&chave);
		}
		tipo=getchar();
		scanf("%d\n",&chave);
	}
	printf("%d\n", num_rot);
}

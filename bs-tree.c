#include "bs-tree.h"

/*----------------------------------------------------------------------------*/
/* Imprime um object em stream                                                */
/*----------------------------------------------------------------------------*/
void fprintf_object(FILE *stream, object o) {
    fprintf(stream, "%d", o);
}

/*----------------------------------------------------------------------------*/
/* Faz a compraracao entre dois objects                                       */
/*----------------------------------------------------------------------------*/
int objectcmp(object *o1, object *o2) {
  return *o1 < *o2 ? -1 : *o1 > *o2 ? 1 : 0;
}

/*----------------------------------------------------------------------------*/
/* Retorna o módulo de n                                                      */
/*----------------------------------------------------------------------------*/
int modulo(int n)
{
	if (n<0)
		return (-1)*n;
	return n;
}

/*----------------------------------------------------------------------------*/
/* Cria e aloca um novo no                                                    */
/*----------------------------------------------------------------------------*/
node *create_node(node **n) {
	node *new_node;
	if ( !(new_node = malloc(sizeof(node)))) {
		 fprintf (stderr, "Error while running Binary Tree Library: Alloc node failed.\n");
		 exit (1);
	}
	new_node->value = 0;
	new_node->balance = 0;
	new_node->contanodo = 0;
	new_node->left = NULL;
	new_node->right = NULL;
	*n = new_node;
	return *n;
}

/*----------------------------------------------------------------------------*/
/* Visualizacao da arvore                                                     */ 
/*----------------------------------------------------------------------------*/
int print_tree_border(node **n)
{
	printf("(");
	print_tree(n);
	printf(")\n");
}

int print_tree(node **n)
{
	if( ! *n )
		return 0;
	printf("(");
	if ((*n)->left)
		print_tree(&(*n)->left);
	printf(") %d[%d] (",(*n)->value,(*n)->balance);
	if ((*n)->right)
		print_tree(&(*n)->right);
	printf(")");
}

void show_tree (FILE *stream, node *n, int b) {
	int i;
	if (n == NULL) {
		for (i = 0; i < b; i++) 
			fprintf(stream, "      ");
		fprintf(stream, "*\n");
		return;
	}
	show_tree(stream, n->right, b+1);
	for (i = 0; i < b; i++) 
		printf("      ");
        fprintf_object (stream, n->value);
	fprintf(stream, "(%i)",n->balance);
	fprintf(stream, "\n");

	show_tree(stream, n->left, b+1);
}

/*----------------------------------------------------------------------------*/
/* Destroi e libera a memoria alocada para o respectivo node                  */
/*----------------------------------------------------------------------------*/
node* destroy_node(node **n) {
	if (*n) {
		(*n)->value = 0;
		(*n)->balance = 0;
		(*n)->left = NULL;
		(*n)->right = NULL;
		free(*n);
	}
	return NULL;
}

/*----------------------------------------------------------------------------*/
/* Devolve o menor dos maiores objetos inserido na arvore apartir do node n   */
/*----------------------------------------------------------------------------*/
object* lower_of_bigger(node **n) {
	if ((*n)->left == NULL)
		return (&((*n)->value));
 	else 
		return lower_of_bigger(&(*n)->left);
}

/*----------------------------------------------------------------------------*/
/* Devolve o maior dos menores objetos inserido na arvore apartir do node n   */
/*----------------------------------------------------------------------------*/
object* bigger_of_lower(node **n) {
	if ((*n)->right == NULL)
		return (&((*n)->value));
 	else 
		return bigger_of_lower(&(*n)->right);
}

/*----------------------------------------------------------------------------*/
/* Rotaciona o node para a esquerda                                           */
/*----------------------------------------------------------------------------*/
void rotation_left(node **n) {
	node *a = *n;
	node *b = (*n)->right;

	a->right = b->left;
	b->left = a;

	(*n) = b;
	(*n)->left->balance = ((*n)->left->balance*2 - (*n)->balance + modulo((*n)->balance) + 2)/2;
	(*n)->balance = ((*n)->balance*2 + (*n)->left->balance + modulo((*n)->left->balance) + 2)/2;
}

/*----------------------------------------------------------------------------*/
/* Rotaciona o node para a direita                                            */
/*----------------------------------------------------------------------------*/
void rotation_right(node **n) {
	node *a = *n;
	node *b = (*n)->left;

	a->left = b->right;
	b->right = a;

	(*n) = b;
	(*n)->right->balance = ((*n)->right->balance*2 - (*n)->balance - modulo((*n)->balance) - 2)/2;
	(*n)->balance = ((*n)->balance*2 + (*n)->right->balance - modulo((*n)->right->balance) - 2)/2;
}

/*----------------------------------------------------------------------------*/
/* Insere um node na arvore, sem balancear                                    */
/*----------------------------------------------------------------------------*/
int insereSemBal(node **n, object *o) {
	node *current = *n;
	if( !current ) {
		if( !(current = create_node(&current))) 
            		return 0;
		current->value = *o;
		*n = current;
		return 1;
	} else if( objectcmp(o,&current->value) == -1 ) {
		if( insereSemBal(&(current->left), o) == 1){
			current->balance++;
			return (current->balance > 0);
		}
	} else if( objectcmp(o,&current->value) == 1 ) {
		if( insereSemBal(&(current->right), o) == 1){
			current->balance--;
			return (current->balance < 0);
		}
	}
	return 0;
}

/*----------------------------------------------------------------------------*/
/* Insere um node na arvore, balanceando                                      */
/*----------------------------------------------------------------------------*/
int insert_node(node **n, object *o, int *num_rots) {
	node *current = *n;
	if( !current ) {
		if( !(current = create_node(&current))) 
            		return 0;
		current->value = *o;
		*n = current;
		return 1;
	} else if( objectcmp(o,&current->value) == -1 ) {
		if( insert_node(&(current->left), o, num_rots) == 1){
			current->balance++;
			if (current->balance == 2 ) {
				if ( (current->left)->balance == 1) {
					rotation_right(&current);
					*num_rots+=1;
				}
				else if ( (current->left)->balance == -1) {
                                        rotation_left(&(current->left));
                                        rotation_right(&current);
					*num_rots+=2;
				}
				*n = current;
			}
			return (current->balance > 0);
		}
	} else if( objectcmp(o,&current->value) == 1 ) {
		if( insert_node(&(current->right), o, num_rots) == 1){
			current->balance--;
			if ( current->balance == -2 ) {
				if ( (current->right)->balance == -1) {
					rotation_left(&current);
					*num_rots+=1;
				}
				else if ( (current->right)->balance == 1) {
                                        rotation_right(&(current->right));
                                        rotation_left(&current);
					*num_rots+=2;
				}
				*n = current;
			}
			return (current->balance < 0);
		}
	}
	return 0;
}

/*----------------------------------------------------------------------------*/
/* Remocao, sem balancear                                                     */
/*----------------------------------------------------------------------------*/
int removeSemBal(node **n, object *o) {
	if( ! *n )
		return 0;
	if( objectcmp(o,&((*n)->value)) == -1 ) {
		if( removeSemBal(&((*n)->left), o) == 1){
			(*n)->balance -= 1;
			return ((*n)->balance >= 0);
		}
	}
 	else if( objectcmp(o,&((*n)->value)) == 1 ) {
		if( removeSemBal(&((*n)->right), o) == 1){
			(*n)->balance += 1;
			return ((*n)->balance <= 0);
		}
	}
	else if ( objectcmp(o, &((*n)->value)) == 0) {
		if ((*n)->left && (*n)->right) {
			object* lower = lower_of_bigger(&((*n)->right));
			(*n)->value =  *lower;
			if (removeSemBal(&((*n)->right), lower) == 1) { //IDEM RIGHT ¬¬
			(*n)->balance += 1;
			return ((*n)->balance == 0);

			}
		}
		else {
			node *m = *n;
			if ((*n)->left)
				*n = (*n)->left;
			else 
				*n = (*n)->right;
			destroy_node(&m);
		return 1;	
		}
}

	return 0;
}

/*----------------------------------------------------------------------------*/
/* Remocao, balanceando                                                       */
/*----------------------------------------------------------------------------*/
int remove_node(node **n, object *o, int *num_rots) {
	if( ! *n )
		return 0;
	if( objectcmp(o,&((*n)->value)) == -1 ) {
		if( remove_node(&((*n)->left), o, num_rots) == 1){
			(*n)->balance -= 1;
			if ( (*n)->balance == -2 ) {
				if ( (*n)->right ){
					if ( ((*n)->right)->balance == 1) {
						rotation_right(&(*n)->right);
						rotation_left(n);
						*num_rots+=2;
					}
					else if ( ((*n)->right)->balance == 0) {
						rotation_left(n);
						*num_rots+=1;
					}
					else if ( ((*n)->right)->balance == -1) {
						rotation_left(n);
						*num_rots+=1;
					}
				}
			}
			return ((*n)->balance == 0);
		}
	}
 	else if( objectcmp(o,&((*n)->value)) == 1 ) {
		if( remove_node(&((*n)->right), o, num_rots) == 1){
			(*n)->balance += 1;
			if ( (*n)->balance == 2 ) {
				if ( (*n)->left ) {
					if ( ((*n)->left)->balance == 1 ) {
						rotation_right(n);
						*num_rots+=1;
					}
					else if ( ((*n)->left)->balance == 0) {
						rotation_right(n);
						*num_rots+=1;
					}
					else if ( ((*n)->left)->balance == -1) {
						rotation_left(&(*n)->left);
						rotation_right(n);
						*num_rots+=2;
					}
				}
			}
			return ((*n)->balance == 0);
		}
	}
	else if ( objectcmp(o, &((*n)->value)) == 0) {
		if ((*n)->left && (*n)->right) {
			object* lower = lower_of_bigger(&((*n)->right));
			(*n)->value =  *lower;
			if (remove_node(&((*n)->right), lower, num_rots) == 1) { //IDEM RIGHT ¬¬
			(*n)->balance += 1;
			if ( (*n)->balance == 2 ) {
				if ( (*n)->left ) {
					if ( ((*n)->left)->balance == 1 ) {
						rotation_right(n);
						*num_rots+=1;
					}
					else if ( ((*n)->left)->balance == 0) {
						rotation_right(n);
						*num_rots+=1;
					}
					else if ( ((*n)->left)->balance == -1) {
						rotation_left(&(*n)->left);
						rotation_right(n);
						*num_rots+=2;
					}
				}
			}
			return ((*n)->balance == 0);

			}
		}
		else {
			node *m = *n;
			if ((*n)->left)
				*n = (*n)->left;
			else 
				*n = (*n)->right;
			destroy_node(&m);
		return 1;	
		}
}

	return 0;
}

/*----------------------------------------------------------------------------*/
/* Calcular balanceamento de todos os nodos abaixo da raiz                    */
/*----------------------------------------------------------------------------*/
int calcula_balanc(node **n)
{
	int hesq=0, hdir=0;
	if ((*n)->left)
		hesq=calcula_balanc(&(*n)->left);
	if ((*n)->right)
		hdir=calcula_balanc(&(*n)->right);
	(*n)->balance=hesq-hdir;
	if (hesq>hdir)
		return hesq+1;
	else
		return hdir+1;
}

/*----------------------------------------------------------------------------*/
/* Calcular contanodo de todos os nodos abaixo da raiz                        */ 
/*----------------------------------------------------------------------------*/
int calcula_contanodos(node **n)
{
	int pesq =0, pdir=0;
	if( (*n)->left )
		pesq = calcula_contanodos(&(*n)->left);
	if( (*n)->right )
		pdir = calcula_contanodos(&(*n)->right);
	(*n)->contanodo = pesq + pdir + 1;
	return (*n)->contanodo;
		
}

/*----------------------------------------------------------------------------*/
/* Particionar um nodo, pelo elemento de número 'val'                         */ 
/*----------------------------------------------------------------------------*/
int particionar(node **n, int val, int *num_rots)
{
	int nesq;
	if( (*n)->left )
		nesq = (*n)->left->contanodo;
	else
		nesq = 0;
	if (val==(nesq+1))
		return 0;
	else if (val<=nesq) {
		particionar(&(*n)->left,val, num_rots);
		rotation_right(n);
		*num_rots+=1;
	}
	else {
		particionar(&(*n)->right,val-(nesq+1), num_rots);
		rotation_left(n);
		*num_rots+=1;
	}
}

/*----------------------------------------------------------------------------*/
/* Balancear a arvore utilizando particionamento pelo ponto medio             */ 
/*----------------------------------------------------------------------------*/
int partPontoMed(node **n, int *num_rots)
{
	calcula_contanodos(n);
	int metade=ceil((*n)->contanodo/2.0);
	particionar(n,metade, num_rots);
	if( (*n)->left )
		partPontoMed(&(*n)->left, num_rots);
	if( (*n)->right )
		partPontoMed(&(*n)->right, num_rots);
	
}


/*----------------------------------------------------------------------------*/
/* Busca um objeto dentro dos nodes da arvore,                                */ 
/* quando escontra devolve um ponteiro para o node                            */
/*----------------------------------------------------------------------------*/
void search_node(node **n, object *o) {
	node *cptree = *n;
	printf("%d",cptree->value);
	do {
		if (objectcmp(o, &cptree->value) == -1 )
			cptree = cptree->left;
		else
			cptree = cptree->right;
		printf(",%d",cptree->value);
	} while ( objectcmp(o, &cptree->value) != 0 );
	printf("\n");
}

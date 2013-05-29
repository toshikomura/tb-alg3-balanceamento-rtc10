/*----------------------------------------------------------------------------*/
/* Universidade Federal do Parana                                             */
/*                                                                            */
/* Algoritmos e Estruturas de dados III                                       */
/* Primeiro Trabalho de implementacao                                         */
/*                                                                            */
/* Professora Carmem Satie Hara                                               */
/* Monitores: Guilherme Alex Derenievicz e Jonatas Teixeira                   */
/*                                                                            */
/*----------------------------------------------------------------------------*/


#ifndef _bstree_
#define _bstree_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/*----------------------------------------------------------------------------*/
/* Objeto inserido dentro de cada no da arvore                                */ 
/*----------------------------------------------------------------------------*/
typedef int object;

/*----------------------------------------------------------------------------*/
/* Estrutura de arvore binaria sem balanceamento                              */ 
/*----------------------------------------------------------------------------*/
typedef struct node {
    object value;
    char balance;
    char contanodo;
    struct node *left;
    struct node *right;
} node;

typedef node *tree;


/*----------------------------------------------------------------------------*/
/* Funcoes para trabalhar com o objeto                                        */
/*----------------------------------------------------------------------------*/
void fprintf_object                 (FILE *stream, object o);
int objectcmp                       (object *o1, object *o2);
int modulo                          (int n);

/*----------------------------------------------------------------------------*/
/* Funcoes para trabalhar com os nos                                          */
/*----------------------------------------------------------------------------*/
node *create_node                   (node **n);
node* destroy_node                  (node **n);

/*----------------------------------------------------------------------------*/
/* Funcoes de rotacoes                                                        */
/*----------------------------------------------------------------------------*/
void rotation_left                  (node **n);
void rotation_right                 (node **n);

/*----------------------------------------------------------------------------*/
/* Funcoes de incersao remocao e busca                                        */
/*----------------------------------------------------------------------------*/
int insereSemBal                    (node **n, object *o);
int insert_node                     (node **n, object *o, int *num_rots);
int removeSemBal                    (node **n, object *o);
int remove_node                     (node **n, object *o, int *num_rots);
void search_node                    (node **n, object *o);


/*----------------------------------------------------------------------------*/
/* Funcoes que podem auxiliar o desenvolvimento do trabalho                   */
/*----------------------------------------------------------------------------*/
object* lower_of_bigger             (node **n);
object* bigger_of_lower             (node **n);
void show_tree                      (FILE *stream, node *n, int b);
int print_tree_border               (node **n);
int print_tree                      (node **n);
int calcula_balanc                  (node **n);
int calcula_contanodos              (node **n);
int particionar                     (node **n, int val, int *num_rots);
int partPontoMed                    (node **n, int *num_rots);

#endif

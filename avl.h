#include <stdio.h>
#include <stdlib.h>

#ifndef AVL_H_INCLUDED
#define AVL_H_INCLUDED
typedef struct _no{
int chave;
struct _no *pai;
struct _no *esq;
struct _no *dir;
int h_esq;
int h_dir;

}No;

No *cria_avl_vazia();
No* busca_abb(No *r,int in_chave);
int maior_h(No *x);
No *criar_folha(int in_chave,No *pai);
void equilibra_avl(No **r_avl,No *x);
No* inserir_abb_r(No **r,int in_chave,No* pai);
void inserir_avl(No **r_avl,int in_chave);
No *minimo_abb(No* r);
int remover_avl(No **r,int in_chave);
void p_emordem(No *r);
 void destruir_avl(No **r);
 void apagar_avl_r(No *r);


#endif // AVL_H_INCLUDED

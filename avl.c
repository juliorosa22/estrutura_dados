#include <stdio.h>
#include <stdlib.h>
#include "avl.h"
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
No *r_dir(No **r_avl, No *r);
No *r_esq(No **r_avl, No *r);

No *cria_avl_vazia(){
    return NULL;

}

No* busca_abb(No *r,int in_chave){

    if(r==NULL||r->chave==in_chave){
        return r;
    }

    if(in_chave > r->chave){

        return busca_abb(r->dir,in_chave);
    }else{

        return busca_abb(r->esq,in_chave);
    }
}

int maior_h(No *x){//funcao que verifica a maior altura de cada lado do no
    int maior;
    if(x->h_dir > x->h_esq){
        maior = x->h_dir;
    }
    else{
        maior = x->h_esq;
    }

    return maior;

}

No *criar_folha(int in_chave,No* pai){
    No* novo = malloc(sizeof(*novo));
    novo->chave = in_chave;
    novo->pai = pai;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->h_dir = 0;
    novo->h_esq = 0;
    return novo;
}

int fator_b(No *x){
if(x ==NULL)
    return 0;
else
    return  x->h_dir - x->h_esq;

}

void equilibra_avl(No **r_avl,No *x){

if(x==NULL)//caso chegue no pai da raiz q eh null
    return;
/*if(x->esq==NULL && x->dir==NULL){//caso seja um pai de uma folha
    if(x->pai->esq == x){//caso o no inserido seja filho esquerdo do pai
            x->pai->h_esq++;
    }else{
        x->pai->h_dir++;
    }
}*/
if(fator_b(x)>1){
    if(fator_b(x->dir)==-1){//caso de rotaçao dupla dir,esq
        x->dir = r_dir(r_avl,x->dir);
    }

    x = r_esq(r_avl,x);
}
if(fator_b(x)<-1){
    if(fator_b(x->esq)==1)//rotaçao dupla esq,dir
        x->esq = r_esq(r_avl,x->esq);
    x= r_dir(r_avl,x);

}


//ajusta as alturas dos nos da arvore
if(x->pai!=NULL){
        if(x->pai->esq == x){//caso o no inserido seja filho esquerdo do pai
            if(x->pai->h_esq == maior_h(x)){//verifica se eh necessaria a mudança na altura do pai, caso o no inserido nao provoque modificaçao na altura de um descendente
              x->pai->h_esq++;
            }
            else{
                x->pai->h_esq = maior_h(x)+1;//caso usado na remoçao
            }
        }else{
            if(x->pai->h_dir == maior_h(x)){
                x->pai->h_dir++;//caso o no seja filho direito do pai
            }else{
                x->pai->h_dir = maior_h(x)+1;//caso usado na remoçao
            }
        }
}

equilibra_avl(r_avl,x->pai);

}

No* inserir_abb_r(No **r,int in_chave,No* pai){

if(*r== NULL){
    *r = criar_folha(in_chave,pai);
    return *r;
}else{
    if((*r)->chave > in_chave){
        return inserir_abb_r(&((*r)->esq),in_chave,*r);

    }else{
        return inserir_abb_r(&((*r)->dir),in_chave,*r);

        }

    }
}

void inserir_avl(No **r_avl,int in_chave){
    No *novo_no;
    novo_no = inserir_abb_r(r_avl,in_chave,NULL);//retorna o endereço do novo no inserido
    equilibra_avl(r_avl,novo_no);//balanceamento a apartir do novo no inserido
    return;
}


No *minimo_abb(No* r){

    if(r==NULL)
        return NULL;

    if(r->esq==NULL)
        return r;

    return minimo_abb(r->esq);

}

void mover_no_abb(No **r,No *destino,No *origem){

    if(destino==NULL)
        return;

    if(destino->pai==NULL){//caso o destino seja a raiz
        *r = origem;

    }else{
        if(destino == destino->pai->esq){
            destino->pai->esq = origem;
        }
        else{
            destino->pai->dir = origem;
        }

    }
    if(origem!=NULL){
            origem->pai = destino->pai;
    }
}



int remover_avl(No **r,int in_chave){

    No *x = busca_abb(*r,in_chave);//encontra o no na arvore que sera removido

    if(x!=NULL){
            int valor_removido = x->chave;
        if(x->esq==NULL){//caso o no que sera removido nao tenha sub arvore esquerda ou caso seja uma folha
            if(x->pai!=NULL){
                No *pai_x2 = x->pai;
                if(pai_x2->esq == x){
                    --(pai_x2->h_esq);
                }else{
                    --(pai_x2->h_dir);
                }
                mover_no_abb(r,x,x->dir);
                equilibra_avl(r,pai_x2);
            }else{

                mover_no_abb(r,x,x->dir);
            }
        }
        else{
                if(x->dir==NULL){
                    if(x->pai!=NULL){
                        No *pai_x1 = x->pai;
                        if(pai_x1->esq == x){//caso o pai do no que sera removido exista , altera diminiu a altura do lado que o no q sera removido for filho do pai
                            --(pai_x1->h_esq);
                        }else{
                            --(pai_x1->h_dir);
                        }
                        mover_no_abb(r,x,x->esq);
                        equilibra_avl(r,pai_x1);
                    }
                    else{
                        mover_no_abb(r,x,x->esq);//caso o no a ser removido nao tenha sub arvore direita
                    }
                }
                else{//caso em que o no removido tem as duas sub arvores

                    No *sucessor = minimo_abb(x->dir);

                    if(sucessor->pai!= x){//caso o sucessor nao seja filho direto do no que sera removido
                        No *pai_sucessor = sucessor->pai;
                        --(pai_sucessor->h_esq);//dimiunui a altura da sub arvore esquerda do pai do sucessor q ira substituir o no que sera removido
                        mover_no_abb(r,sucessor,sucessor->dir);//move faz o pai do sucessor apontar para a sua sub arvore direita
                        sucessor->dir = x->dir;//faz a sub arvore direita do sucessor apontar para a sub arvore direita do no que sera removido
                        sucessor->dir->pai = sucessor;//faz o com que o pai da sub arvore direita seja o sucessor

                        sucessor->h_esq = x->h_esq;//iguala a altura da sub arvore esquerda do no removido a altura esquerda do sucessor
                        mover_no_abb(r,x,sucessor); //move o sucessor para o lugar do no que sera removido
                        sucessor->esq = x->esq;
                        sucessor->esq->pai = sucessor;
                        equilibra_avl(r,pai_sucessor);//arruma a avl a partir do antigo pai do sucessor


                }else{
                        sucessor->h_esq = x->h_esq;
                        mover_no_abb(r,x,sucessor); //move o sucessor para o lugar do no que sera removido
                        sucessor->esq = x->esq;
                        sucessor->esq->pai = sucessor;
                        equilibra_avl(r,sucessor);//como o sucessor eh filho direto do no removido altera-se a altura da sub arvore esquerda e realiza o balancemaneto a partir do proprio sucessor
                }
            }
        }

        free(x);
        return valor_removido;
    }else{
        return -1;//

    }


}

void p_emordem(No *r){

if(r!=NULL){

    p_emordem(r->esq);
    printf("%d [%d]\n",r->chave,(r->h_dir-r->h_esq));
    p_emordem(r->dir);

    }
}
//rotação a direita
No *r_dir(No **r_avl, No *r){
    No *r_novo = r->esq;
    mover_no_abb(r_avl,r,r_novo);
    r->esq = r_novo->dir;
    r_novo->dir = r;
    if(r->esq != NULL){
        r->esq->pai = r;
        r->h_esq = maior_h(r->esq)+1;
    }else{

        r->h_esq = 0;
    }
    r->pai = r_novo;
    r_novo->h_dir = maior_h(r)+1;
    return r_novo;

    }

//rotação a esquerda
No *r_esq(No **r_avl, No *r){
    No *r_novo = r->dir;
    mover_no_abb(r_avl,r,r_novo);
    r->dir = r_novo->esq;
    r_novo->esq = r;
    if(r->dir != NULL){
        r->dir->pai = r;
        r->h_dir = maior_h(r->dir)+1;
    }else{

        r->h_dir = 0;
    }
    r->pai = r_novo;
    r_novo->h_esq = maior_h(r)+1;
    return r_novo;

    }

 void destruir_avl(No **r){
    apagar_avl_r(*r);
    *r=NULL;

 }
void apagar_avl_r(No *r){
    if(r!=NULL){
        apagar_avl_r(r->esq);
        apagar_avl_r(r->dir);
        free(r);
    }

}



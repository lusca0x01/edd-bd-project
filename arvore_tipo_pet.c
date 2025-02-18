#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tipo_pet.h"
#include "arvore_tipo_pet.h"

int compararTipoPets(TipoPet *p1, TipoPet *p2, const char *coluna)
{
    if (strcmp(coluna, "codigo;") == 0)
    {
        return (p1->codigo > p2->codigo) - (p1->codigo < p2->codigo);
    }
    else if (strcmp(coluna, "descricao;") == 0)
    {
        return strcmp(p1->descricao, p2->descricao);
    }
    return 0;
}

ArvoreTipoPet *inserirNaArvoreTipoPet(ArvoreTipoPet *raiz, TipoPet *tipo_pet, const char *coluna)
{
    if (raiz == NULL)
    {
        ArvoreTipoPet *novoNo = (ArvoreTipoPet *)malloc(sizeof(ArvoreTipoPet));
        novoNo->tipo_pet = tipo_pet;
        novoNo->esq = novoNo->dir = NULL;
        return novoNo;
    }

    if (compararTipoPets(tipo_pet, raiz->tipo_pet, coluna) < 0)
    {
        raiz->esq = inserirNaArvoreTipoPet(raiz->esq, tipo_pet, coluna);
    }
    else
    {
        raiz->dir = inserirNaArvoreTipoPet(raiz->dir, tipo_pet, coluna);
    }

    return raiz;
}

void imprimirTipoPet(TipoPet *tipo_pet, bool listaOCodigo, bool listaADescricao)
{
    bool primeiroCampo = true;

    if (listaOCodigo)
    {
        printf("Código: %d", tipo_pet->codigo);
        primeiroCampo = false;
    }
    if (listaADescricao)
    {
        printf("%sDescrição: %d", primeiroCampo ? "" : " | ", tipo_pet->descricao);
        primeiroCampo = false;
    }

    printf("\n");
}

void percorrerEmOrdemTipoPet(ArvoreTipoPet *raiz, const char *coluna, bool listaOCodigo, bool listaADescricao)
{
    if (raiz == NULL)
        return;

    percorrerEmOrdemTipoPet(raiz->esq, coluna, listaOCodigo, listaADescricao);
    imprimirTipoPet(raiz->tipo_pet, listaOCodigo, listaADescricao);
    percorrerEmOrdemTipoPet(raiz->dir, coluna, listaOCodigo, listaADescricao);
}

void liberarArvoreTipoPet(ArvoreTipoPet **raiz)
{
    if (*raiz == NULL)
        return;

    liberarArvoreTipoPet(&(*raiz)->esq);
    liberarArvoreTipoPet(&(*raiz)->dir);

    free(*raiz);
    *raiz = NULL;
}

void listarTiposPetOrderBy(TipoPet *raiz, const char *coluna, bool listaOCodigo, bool listaADescricao)
{
    if (!raiz)
    {
        printf("Nenhum Tipo Pet cadastrado.\n");
        return;
    }
    ArvoreTipoPet *arvore = NULL;
    TipoPet *atual = raiz;

    while (atual)
    {
        arvore = inserirNaArvoreTipoPet(arvore, atual, coluna);
        atual = atual->prox;
    }

    percorrerEmOrdemTipoPet(arvore, coluna, listaOCodigo, listaADescricao);
    liberarArvoreTipoPet(&arvore);
}

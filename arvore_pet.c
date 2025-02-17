#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pet.h"
#include "arvore_pet.h"

int compararPets(Pet *p1, Pet *p2, const char *coluna)
{
    if (strcmp(coluna, "codigo;") == 0)
    {
        return (p1->codigo > p2->codigo) - (p1->codigo < p2->codigo);
    }
    else if (strcmp(coluna, "nome;") == 0)
    {
        return strcmp(p1->nome, p2->nome);
    }
    else if (strcmp(coluna, "codigo_pes;") == 0)
    {
        return (p1->codigo_pes > p2->codigo_pes) - (p1->codigo_pes < p2->codigo_pes);
    }
    else if (strcmp(coluna, "codigo_tipo;") == 0)
    {
        return (p1->codigo_tipo > p2->codigo_tipo) - (p1->codigo_tipo < p2->codigo_tipo);
    }
    return 0;
}

ArvorePet *inserirNaArvore(ArvorePet *raiz, Pet *pet, const char *coluna)
{
    if (raiz == NULL)
    {
        ArvorePet *novoNo = (ArvorePet *)malloc(sizeof(ArvorePet));
        novoNo->pet = pet;
        novoNo->esq = novoNo->dir = NULL;
        return novoNo;
    }

    if (compararPets(pet, raiz->pet, coluna) < 0)
    {
        raiz->esq = inserirNaArvore(raiz->esq, pet, coluna);
    }
    else
    {
        raiz->dir = inserirNaArvore(raiz->dir, pet, coluna);
    }

    return raiz;
}

void imprimirPet(Pet *pet, bool listaOCodigo, bool listaOCodigoPessoa, bool listaONome, bool listaOCodigoTipo)
{
    bool primeiroCampo = true;

    if (listaOCodigo)
    {
        printf("Código: %d", pet->codigo);
        primeiroCampo = false;
    }
    if (listaOCodigoPessoa)
    {
        printf("%sCódigo Pessoa: %d", primeiroCampo ? "" : " | ", pet->codigo_pes);
        primeiroCampo = false;
    }
    if (listaONome)
    {
        printf("%sNome: %s", primeiroCampo ? "" : " | ", pet->nome);
        primeiroCampo = false;
    }
    if (listaOCodigoTipo)
    {
        printf("%sCódigo Tipo: %d", primeiroCampo ? "" : " | ", pet->codigo_tipo);
    }

    printf("\n");
}

void percorrerEmOrdem(ArvorePet *raiz, const char *coluna, bool listaOCodigo, bool listaOCodigoPessoa, bool listaONome, bool listaOCodigoTipo)
{
    if (raiz == NULL)
        return;

    percorrerEmOrdem(raiz->esq, coluna, listaOCodigo, listaOCodigoPessoa, listaONome, listaOCodigoTipo);
    imprimirPet(raiz->pet, listaOCodigo, listaOCodigoPessoa, listaONome, listaOCodigoTipo);
    percorrerEmOrdem(raiz->dir, coluna, listaOCodigo, listaOCodigoPessoa, listaONome, listaOCodigoTipo);
}

void liberarArvore(ArvorePet **raiz)
{
    if (*raiz == NULL)
        return;

    liberarArvore(&(*raiz)->esq);
    liberarArvore(&(*raiz)->dir);

    free(*raiz);
    *raiz = NULL;
}

void listarPetsOrderBy(Pet *raiz, const char *coluna, bool listaOCodigo, bool listaOCodigoPessoa, bool listaONome, bool listaOCodigoTipo)
{
    if (!raiz)
    {
        printf("Nenhuma Pet cadastrada.\n");
        return;
    }
    ArvorePet *arvore = NULL;
    Pet *atual = raiz;

    while (atual)
    {
        arvore = inserirNaArvore(arvore, atual, coluna);
        atual = atual->prox;
    }

    percorrerEmOrdem(arvore, coluna, listaOCodigo, listaOCodigoPessoa, listaONome, listaOCodigoTipo);
    liberarArvore(&arvore);
}

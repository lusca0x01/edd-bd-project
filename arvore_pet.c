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

ArvorePet *inserirNaArvorePet(ArvorePet *raiz, Pet *pet, const char *coluna)
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
        raiz->esq = inserirNaArvorePet(raiz->esq, pet, coluna);
    }
    else
    {
        raiz->dir = inserirNaArvorePet(raiz->dir, pet, coluna);
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

void percorrerEmOrdemPet(ArvorePet *raiz, const char *coluna, bool listaOCodigo, bool listaOCodigoPessoa, bool listaONome, bool listaOCodigoTipo)
{
    if (raiz == NULL)
        return;

    percorrerEmOrdemPet(raiz->esq, coluna, listaOCodigo, listaOCodigoPessoa, listaONome, listaOCodigoTipo);
    imprimirPet(raiz->pet, listaOCodigo, listaOCodigoPessoa, listaONome, listaOCodigoTipo);
    percorrerEmOrdemPet(raiz->dir, coluna, listaOCodigo, listaOCodigoPessoa, listaONome, listaOCodigoTipo);
}

void liberarArvorePet(ArvorePet **raiz)
{
    if (*raiz == NULL)
        return;

    liberarArvorePet(&(*raiz)->esq);
    liberarArvorePet(&(*raiz)->dir);

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
        arvore = inserirNaArvorePet(arvore, atual, coluna);
        atual = atual->prox;
    }

    percorrerEmOrdemPet(arvore, coluna, listaOCodigo, listaOCodigoPessoa, listaONome, listaOCodigoTipo);
    liberarArvorePet(&arvore);
}

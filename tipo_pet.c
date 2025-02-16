#include "tipo_pet.h"
#include <string.h>
#include <stdio.h>

#define ARQUIVO_TipoPet "tipopet.dat"

TipoPet *carregarTipoPets()
{
    FILE *file = fopen(ARQUIVO_TipoPet, "rb");
    if (!file)
        return NULL;

    TipoPet *lista = NULL;
    TipoPet temp;

    while (fread(&temp, sizeof(TipoPet), 1, file))
    {
        inserirTipoPet(&lista, temp);
    }

    fclose(file);
    return lista;
}

void salvarTipoPets(TipoPet *lista)
{
    FILE *file = fopen(ARQUIVO_TipoPet, "wb");
    if (!file)
        return;

    TipoPet *atual = lista;
    while (atual)
    {
        fwrite(atual, sizeof(TipoPet), 1, file);
        atual = atual->prox;
    }

    fclose(file);
}

TipoPet *buscarTipoPetPorCodigo(TipoPet *lista, int codigo)
{
    while (lista)
    {
        if (lista->codigo == codigo)
        {
            return lista;
        }
        lista = lista->prox;
    }
    return NULL;
}

TipoPet *buscarTipoPetPorDescricao(TipoPet *lista, char descricao[50])
{
    while (lista)
    {
        if (strcmp(lista->descricao, descricao))
        {
            return lista;
        }
        lista = lista->prox;
    }
    return NULL;
}

void atualizarTipoPetPorCodigo(TipoPet *lista, int codigo, TipoPet novoTipoPet)
{
    TipoPet *tipo_pet = buscarTipoPetPorCodigo(lista, codigo);

    if (!tipo_pet)
    {
        printf("Tipo Pet não encontrado!\n");
        return;
    }

    strncpy(tipo_pet->descricao, novoTipoPet.descricao, sizeof(tipo_pet->descricao) - 1);
    tipo_pet->descricao[sizeof(tipo_pet->descricao) - 1] = '\0';
}

void atualizarTipoPetPorDescricao(TipoPet *lista, char descricao[50], TipoPet novoTipoPet)
{
    TipoPet *tipo_pet = buscarTipoPetPorDescricao(lista, descricao);

    if (!tipo_pet)
    {
        printf("Pet não encontrada!\n");
        return;
    }

    strncpy(tipo_pet->descricao, novoTipoPet.descricao, sizeof(tipo_pet->descricao) - 1);
    tipo_pet->descricao[sizeof(tipo_pet->descricao) - 1] = '\0';
}

void inserirTipoPet(TipoPet **lista, TipoPet novaTipoPet)
{
    if (buscarTipoPetPorCodigo(*lista, novaTipoPet.codigo))
    {
        printf("Erro: Código de TipoPet já existe!\n");
        return;
    }

    TipoPet *novo = (TipoPet *)malloc(sizeof(TipoPet));
    if (!novo)
    {
        printf("Erro ao alocar memória!\n");
        return;
    }

    *novo = novaTipoPet;
    novo->prox = *lista;
    novo->ant = NULL;

    if (*lista)
    {
        (*lista)->ant = novo;
    }

    *lista = novo;
}

void removerTipoPet(TipoPet **lista, int codigo)
{
    TipoPet *atual = buscarTipoPetPorCodigo(*lista, codigo);
    if (!atual)
    {
        printf("Erro: TipoPet não encontrada!\n");
        return;
    }

    if (atual->ant)
    {
        atual->ant->prox = atual->prox;
    }
    else
    {
        *lista = atual->prox;
    }

    if (atual->prox)
    {
        atual->prox->ant = atual->ant;
    }

    free(atual);
}

void listarTipoPets(TipoPet *lista)
{
    while (lista)
    {
        printf("Código: %d | Descricao: %s\n",
               lista->codigo, lista->descricao);
        lista = lista->prox;
    }
}

void liberarListaTipoPets(TipoPet **lista)
{
    TipoPet *atual = *lista;
    while (atual)
    {
        TipoPet *prox = atual->prox;
        free(atual);
        atual = prox;
    }
    *lista = NULL;
}

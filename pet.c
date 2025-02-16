#include "pet.h"
#include <string.h>
#include <stdio.h>

#define ARQUIVO_PET "pet.dat"

Pet *carregarPets()
{
    FILE *file = fopen(ARQUIVO_PET, "rb");
    if (!file)
        return NULL;

    Pet *lista = NULL;
    Pet temp;

    while (fread(&temp, sizeof(Pet), 1, file))
    {
        inserirPet(&lista, temp);
    }

    fclose(file);
    return lista;
}

void salvarPets(Pet *lista)
{
    FILE *file = fopen(ARQUIVO_PET, "wb");
    if (!file)
        return;

    Pet *atual = lista;
    while (atual)
    {
        fwrite(atual, sizeof(Pet), 1, file);
        atual = atual->prox;
    }

    fclose(file);
}

Pet *buscarPetPorCodigo(Pet *lista, int codigo)
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

void inserirPet(Pet **lista, Pet novaPet)
{
    if (buscarPetPorCodigo(*lista, novaPet.codigo))
    {
        printf("Erro: Código de Pet já existe!\n");
        return;
    }

    Pet *novo = (Pet *)malloc(sizeof(Pet));
    if (!novo)
    {
        printf("Erro ao alocar memória!\n");
        return;
    }

    *novo = novaPet;
    novo->prox = *lista;
    novo->ant = NULL;

    if (*lista)
    {
        (*lista)->ant = novo;
    }

    *lista = novo;
}

void removerPet(Pet **lista, int codigo)
{
    Pet *atual = buscarPetPorCodigo(*lista, codigo);
    if (!atual)
    {
        printf("Erro: Pet não encontrada!\n");
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

void listarPets(Pet *lista)
{
    while (lista)
    {
        printf("Código: %d | Código Pessoa: %d | Nome: %s | Código tipo: %d\n",
               lista->codigo, lista->codigo_pes, lista->nome, lista->codigo_tipo);
        lista = lista->prox;
    }
}

void liberarListaPets(Pet **lista)
{
    Pet *atual = *lista;
    while (atual)
    {
        Pet *prox = atual->prox;
        free(atual);
        atual = prox;
    }
    *lista = NULL;
}

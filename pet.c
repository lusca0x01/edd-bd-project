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

Pet *buscarPetPorNome(Pet *lista, char nome[50])
{
    while (lista)
    {
        if (strcmp(lista->nome, nome))
        {
            return lista;
        }
        lista = lista->prox;
    }
    return NULL;
}

void atualizarPetPorCodigo(Pet *lista, int codigo, Pet novoPet)
{
    Pet *pet = buscarPetPorCodigo(lista, codigo);

    if (!pet)
    {
        printf("Pet não encontrada!\n");
        return;
    }

    strncpy(pet->nome, novoPet.nome, sizeof(pet->nome) - 1);
    pet->nome[sizeof(pet->nome) - 1] = '\0';
}

void atualizarPetPorNome(Pet *lista, char nome[50], Pet novoPet)
{
    Pet *pet = buscarPetPorNome(lista, nome);

    if (!pet)
    {
        printf("Pet não encontrada!\n");
        return;
    }

    strncpy(pet->nome, novoPet.nome, sizeof(pet->nome) - 1);
    pet->nome[sizeof(pet->nome) - 1] = '\0';
}

void inserirPet(Pet **lista, Pet novoPet)
{
    if (buscarPetPorCodigo(*lista, novoPet.codigo))
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

    *novo = novoPet;
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

void listarPets(Pet *lista, bool listaOCodigo, bool listaOCodigoPessoa, bool listaONome, bool listaOCodigoTipo, int codigo)
{
    if (!lista)
    {
        printf("Nenhum pet cadastrado.\n");
        return;
    }

    if (codigo >= 0)
    {
        Pet *atual = buscarPetPorCodigo(lista, codigo);

        bool primeiroCampo = true;

        if (listaOCodigo)
        {
            printf("Código: %d ", atual->codigo);
            primeiroCampo = false;
        }
        if (listaOCodigoPessoa)
        {
            printf("%sCódigo Pessoa: %d", primeiroCampo ? "" : " | ", atual->codigo_pes);
            primeiroCampo = false;
        }
        if (listaONome)
        {
            printf("%sNome: %s", primeiroCampo ? "" : " | ", atual->nome);
            primeiroCampo = false;
        }
        if (listaOCodigoTipo)
        {
            printf("%Código Tipo: %d", primeiroCampo ? "" : " | ", atual->codigo_tipo);
        }

        printf("\n");
        return;
    }

    while (lista)
    {
        bool primeiroCampo = true;

        if (listaOCodigo)
        {
            printf("Código: %d ", lista->codigo);
            primeiroCampo = false;
        }
        if (listaOCodigoPessoa)
        {
            printf("%sCódigo Pessoa: %d", primeiroCampo ? "" : " | ", lista->codigo_pes);
            primeiroCampo = false;
        }
        if (listaONome)
        {
            printf("%sNome: %s", primeiroCampo ? "" : " | ", lista->nome);
            primeiroCampo = false;
        }
        if (listaOCodigoTipo)
        {
            printf("%Código Tipo: %d", primeiroCampo ? "" : " | ", lista->codigo_tipo);
        }

        printf("\n");
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

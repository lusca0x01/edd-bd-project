#include "pessoa.h"
#include <string.h>
#include <stdio.h>

#define ARQUIVO_PESSOAS "pessoas.dat"

Pessoa *carregarPessoas()
{
    FILE *file = fopen(ARQUIVO_PESSOAS, "rb");
    if (!file)
        return NULL;

    Pessoa *lista = NULL;
    Pessoa temp;

    while (fread(&temp, sizeof(Pessoa), 1, file))
    {
        inserirPessoa(&lista, temp);
    }

    fclose(file);
    return lista;
}

void salvarPessoas(Pessoa *lista)
{
    FILE *file = fopen(ARQUIVO_PESSOAS, "wb");
    if (!file)
        return;

    Pessoa *atual = lista;
    while (atual)
    {
        fwrite(atual, sizeof(Pessoa), 1, file);
        atual = atual->prox;
    }

    fclose(file);
}

Pessoa *buscarPessoaPorCodigo(Pessoa *lista, int codigo)
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

void inserirPessoa(Pessoa **lista, Pessoa novaPessoa)
{
    if (buscarPessoaPorCodigo(*lista, novaPessoa.codigo))
    {
        printf("Erro: Código de pessoa já existe!\n");
        return;
    }

    Pessoa *novo = (Pessoa *)malloc(sizeof(Pessoa));
    if (!novo)
    {
        printf("Erro ao alocar memória!\n");
        return;
    }

    *novo = novaPessoa;
    novo->prox = *lista;
    novo->ant = NULL;

    if (*lista)
    {
        (*lista)->ant = novo;
    }

    *lista = novo;
}

void removerPessoa(Pessoa **lista, int codigo)
{
    Pessoa *atual = buscarPessoaPorCodigo(*lista, codigo);
    if (!atual)
    {
        printf("Erro: Pessoa não encontrada!\n");
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

void listarPessoas(Pessoa *lista)
{
    while (lista)
    {
        printf("Código: %d | Nome: %s | Telefone: %s | Endereço: %s | Nascimento: %s\n",
               lista->codigo, lista->nome, lista->fone, lista->endereco, lista->data_nascimento);
        lista = lista->prox;
    }
}

void liberarListaPessoas(Pessoa **lista)
{
    Pessoa *atual = *lista;
    while (atual)
    {
        Pessoa *prox = atual->prox;
        free(atual);
        atual = prox;
    }
    *lista = NULL;
}

#include "pessoa.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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

Pessoa *buscarPessoaPorNome(Pessoa *lista, char nome[50])
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

void atualizarPessoaPorCodigo(Pessoa *lista, int codigo, Pessoa novaPessoa)
{
    Pessoa *pessoa = buscarPessoaPorCodigo(lista, codigo);

    if (!pessoa)
    {
        printf("Pessoa não encontrada!\n");
        return;
    }

    strncpy(pessoa->nome, novaPessoa.nome, sizeof(pessoa->nome) - 1);
    pessoa->nome[sizeof(pessoa->nome) - 1] = '\0';
    strncpy(pessoa->fone, novaPessoa.fone, sizeof(pessoa->fone) - 1);
    pessoa->fone[sizeof(pessoa->fone) - 1] = '\0';
    strncpy(pessoa->data_nascimento, novaPessoa.data_nascimento, sizeof(pessoa->data_nascimento) - 1);
    pessoa->data_nascimento[sizeof(pessoa->data_nascimento) - 1] = '\0';
    strncpy(pessoa->endereco, novaPessoa.endereco, sizeof(pessoa->endereco) - 1);
    pessoa->endereco[sizeof(pessoa->endereco) - 1] = '\0';
}

void atualizarPessoaPorNome(Pessoa *lista, char nome[50], Pessoa novaPessoa)
{
    Pessoa *pessoa = buscarPessoaPorNome(lista, nome);

    if (!pessoa)
    {
        printf("Pessoa não encontrada!\n");
        return;
    }

    strncpy(pessoa->nome, novaPessoa.nome, sizeof(pessoa->nome) - 1);
    pessoa->nome[sizeof(pessoa->nome) - 1] = '\0';
    strncpy(pessoa->fone, novaPessoa.fone, sizeof(pessoa->fone) - 1);
    pessoa->fone[sizeof(pessoa->fone) - 1] = '\0';
    strncpy(pessoa->data_nascimento, novaPessoa.data_nascimento, sizeof(pessoa->data_nascimento) - 1);
    pessoa->data_nascimento[sizeof(pessoa->data_nascimento) - 1] = '\0';
    strncpy(pessoa->endereco, novaPessoa.endereco, sizeof(pessoa->endereco) - 1);
    pessoa->endereco[sizeof(pessoa->endereco) - 1] = '\0';
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

void listarPessoas(Pessoa *lista, bool listaOCodigo, bool listaONome, bool listaOTelefone, bool listaOEndereco, bool listaONascimento, int codigo)
{
    if (!lista)
    {
        printf("Nenhuma pessoa cadastrada.\n");
        return;
    }

    if (codigo >= 0)
    {
        Pessoa *atual = buscarPessoaPorCodigo(lista, codigo);

        bool primeiroCampo = true;

        if (listaOCodigo)
        {
            printf("Código: %d", atual->codigo);
            primeiroCampo = false;
        }
        if (listaONome)
        {
            printf("%sNome: %s", primeiroCampo ? "" : " | ", atual->nome);
            primeiroCampo = false;
        }
        if (listaOTelefone)
        {
            printf("%sTelefone: %s", primeiroCampo ? "" : " | ", atual->fone);
            primeiroCampo = false;
        }
        if (listaOEndereco)
        {
            printf("%sEndereço: %s", primeiroCampo ? "" : " | ", atual->endereco);
            primeiroCampo = false;
        }
        if (listaONascimento)
        {
            printf("%sNascimento: %s", primeiroCampo ? "" : " | ", atual->data_nascimento);
        }

        printf("\n");
        return;
    }

    while (lista)
    {
        bool primeiroCampo = true;

        if (listaOCodigo)
        {
            printf("Código: %d", lista->codigo);
            primeiroCampo = false;
        }
        if (listaONome)
        {
            printf("%sNome: %s", primeiroCampo ? "" : " | ", lista->nome);
            primeiroCampo = false;
        }
        if (listaOTelefone)
        {
            printf("%sTelefone: %s", primeiroCampo ? "" : " | ", lista->fone);
            primeiroCampo = false;
        }
        if (listaOEndereco)
        {
            printf("%sEndereço: %s", primeiroCampo ? "" : " | ", lista->endereco);
            primeiroCampo = false;
        }
        if (listaONascimento)
        {
            printf("%sNascimento: %s", primeiroCampo ? "" : " | ", lista->data_nascimento);
        }

        printf("\n");
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

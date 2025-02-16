#ifndef PESSOA_H
#define PESSOA_H

#include <stdbool.h>

typedef struct Pessoa
{
    int codigo;
    char nome[50];
    char fone[20];
    char data_nascimento[11];
    char endereco[100];
    struct Pessoa *ant, *prox;
} Pessoa;

Pessoa *carregarPessoas();
void salvarPessoas(Pessoa *lista);
Pessoa *buscarPessoaPorCodigo(Pessoa *lista, int codigo);
Pessoa *buscarPessoaPorNome(Pessoa *lista, char nome[50]);
void atualizarPessoaPorCodigo(Pessoa *lista, int codigo, Pessoa novaPessoa);
void atualizarPessoaPorNome(Pessoa *lista, char nome[50], Pessoa novaPessoa);
void inserirPessoa(Pessoa **lista, Pessoa novaPessoa);
void removerPessoa(Pessoa **lista, int codigo);
void listarPessoas(Pessoa *lista, bool listaOCodigo, bool listaONome, bool listaOTelefone, bool listaOEndereco, bool listaONascimento);
void liberarListaPessoas(Pessoa **lista);

#endif

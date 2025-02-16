#ifndef PESSOA_H
#define PESSOA_H

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
void inserirPessoa(Pessoa **lista, Pessoa novaPessoa);
void removerPessoa(Pessoa **lista, int codigo);
void listarPessoas(Pessoa *lista);

#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pessoa.h"
#include "arvore_pessoa.h"

int compararPessoas(Pessoa *p1, Pessoa *p2, const char *coluna)
{
    if (strcmp(coluna, "codigo;") == 0)
    {
        return (p1->codigo > p2->codigo) - (p1->codigo < p2->codigo);
    }
    else if (strcmp(coluna, "nome;") == 0)
    {
        return strcmp(p1->nome, p2->nome);
    }
    else if (strcmp(coluna, "fone;") == 0)
    {
        return strcmp(p1->fone, p2->fone);
    }
    else if (strcmp(coluna, "data_nascimento;") == 0)
    {
        return strcmp(p1->data_nascimento, p2->data_nascimento);
    }
    else if (strcmp(coluna, "endereco;") == 0)
    {
        return strcmp(p1->endereco, p2->endereco);
    }
    return 0;
}

ArvorePessoa *inserirNaArvorePessoa(ArvorePessoa *raiz, Pessoa *pessoa, const char *coluna)
{
    if (raiz == NULL)
    {
        ArvorePessoa *novoNo = (ArvorePessoa *)malloc(sizeof(ArvorePessoa));
        novoNo->pessoa = pessoa;
        novoNo->esq = novoNo->dir = NULL;
        return novoNo;
    }

    if (compararPessoas(pessoa, raiz->pessoa, coluna) < 0)
    {
        raiz->esq = inserirNaArvorePessoa(raiz->esq, pessoa, coluna);
    }
    else
    {
        raiz->dir = inserirNaArvorePessoa(raiz->dir, pessoa, coluna);
    }

    return raiz;
}

void imprimirPessoa(Pessoa *pessoa, bool listaOCodigo, bool listaONome, bool listaOTelefone, bool listaOEndereco, bool listaONascimento)
{
    bool primeiroCampo = true;

    if (listaOCodigo)
    {
        printf("Código: %d", pessoa->codigo);
        primeiroCampo = false;
    }
    if (listaONome)
    {
        printf("%sNome: %s", primeiroCampo ? "" : " | ", pessoa->nome);
        primeiroCampo = false;
    }
    if (listaOTelefone)
    {
        printf("%sTelefone: %s", primeiroCampo ? "" : " | ", pessoa->fone);
        primeiroCampo = false;
    }
    if (listaOEndereco)
    {
        printf("%sEndereço: %s", primeiroCampo ? "" : " | ", pessoa->endereco);
        primeiroCampo = false;
    }
    if (listaONascimento)
    {
        printf("%sNascimento: %s", primeiroCampo ? "" : " | ", pessoa->data_nascimento);
    }

    printf("\n");
}

void percorrerEmOrdemPessoa(ArvorePessoa *raiz, const char *coluna, bool listaOCodigo, bool listaONome, bool listaOTelefone, bool listaOEndereco, bool listaONascimento)
{
    if (raiz == NULL)
        return;

    percorrerEmOrdemPessoa(raiz->esq, coluna, listaOCodigo, listaONome, listaOTelefone, listaOEndereco, listaONascimento);
    imprimirPessoa(raiz->pessoa, listaOCodigo, listaONome, listaOTelefone, listaOEndereco, listaONascimento);
    percorrerEmOrdemPessoa(raiz->dir, coluna, listaOCodigo, listaONome, listaOTelefone, listaOEndereco, listaONascimento);
}

void liberarArvorePessoa(ArvorePessoa **raiz)
{
    if (*raiz == NULL)
        return;

    liberarArvorePessoa(&(*raiz)->esq);
    liberarArvorePessoa(&(*raiz)->dir);

    free(*raiz);
    *raiz = NULL;
}

void listarPessoasOrderBy(Pessoa *raiz, const char *coluna, bool listaOCodigo, bool listaONome, bool listaOTelefone, bool listaOEndereco, bool listaONascimento)
{
    if (!raiz)
    {
        printf("Nenhuma pessoa cadastrada.\n");
        return;
    }
    ArvorePessoa *arvore = NULL;
    Pessoa *atual = raiz;

    while (atual)
    {
        arvore = inserirNaArvorePessoa(arvore, atual, coluna);
        atual = atual->prox;
    }

    percorrerEmOrdemPessoa(arvore, coluna, listaOCodigo, listaONome, listaOTelefone, listaOEndereco, listaONascimento);
    liberarArvorePessoa(&arvore);
}

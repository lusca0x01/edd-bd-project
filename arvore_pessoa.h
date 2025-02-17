#ifndef ARVORE_PESSOA_H
#define ARVORE_PESSOA_H

typedef struct ArvorePessoa {
    struct Pessoa *pessoa;
    struct ArvorePessoa *esq, *dir;
} ArvorePessoa;

void imprimirPessoa(Pessoa *pessoa, bool listaOCodigo, bool listaONome, bool listaOTelefone, bool listaOEndereco, bool listaONascimento);
void listarPessoasOrderBy(Pessoa *raiz, const char *coluna, bool listaOCodigo, bool listaONome, bool listaOTelefone, bool listaOEndereco, bool listaONascimento);

#endif
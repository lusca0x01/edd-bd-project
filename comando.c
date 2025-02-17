#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "comando.h"
#include "arvore_pessoa.h"
#include "arvore_pet.h"
#include "arvore_tipo_pet.h"


void inicializarFila(FilaComandos *fila)
{
    fila->inicio = fila->fim = NULL;
}

void adicionarComando(FilaComandos *fila, char *descricao)
{
    Comando *novo = (Comando *)malloc(sizeof(Comando));
    if (!novo)
    {
        printf("Erro: Falha na alocação de memória para comando.\n");
        return;
    }
    strncpy(novo->descricao, descricao, sizeof(novo->descricao) - 1);
    novo->descricao[sizeof(novo->descricao) - 1] = '\0';
    novo->prox = NULL;

    if (fila->fim)
        fila->fim->prox = novo;
    else
        fila->inicio = novo;

    fila->fim = novo;
}

char *removerComando(FilaComandos *fila)
{
    if (!fila->inicio)
    {
        printf("Erro: Tentativa de remover comando de uma fila vazia.\n");
        return NULL;
    }

    Comando *temp = fila->inicio;
    char *descricao = strdup(temp->descricao);

    fila->inicio = temp->prox;
    if (!fila->inicio)
        fila->fim = NULL;

    free(temp);
    return descricao;
}

int validarComando(char *comando)
{
    return (
        strncmp(comando, "insert into", 11) == 0 ||
        strncmp(comando, "update", 6) == 0 ||
        strncmp(comando, "delete from", 11) == 0 ||
        strncmp(comando, "select * from", 13) == 0);
}

int temPetsAssociados(Pet *lista, int codigoPessoa)
{
    for (Pet *atual = lista; atual; atual = atual->prox)
    {
        if (atual->codigo_pes == codigoPessoa)
            return 1;
    }
    return 0;
}

void processarComandos(FilaComandos *fila, Pessoa **listaPessoas, TipoPet **listaTiposPet, Pet **listaPets)
{
    char *comando;
    while ((comando = removerComando(fila)))
    {
        if (validarComando(comando))
        {
            char colunaOrdenacao[50] = {0};
            int possuiOrderBy = temOrderBy(comando, colunaOrdenacao);
            if (strstr(comando, "insert into"))
            {
                if (strstr(comando, "insert into pessoa"))
                {
                    Pessoa novaPessoa = {0};
                    if (strstr(comando, "fone") && strstr(comando, "endereco"))
                    {
                        sscanf(comando, "insert into pessoa (codigo, nome, fone, endereco, data_nascimento) values (%d, '%[^']', '%[^']', '%[^']', '%[^']');",
                               &novaPessoa.codigo, novaPessoa.nome, novaPessoa.fone, novaPessoa.endereco, novaPessoa.data_nascimento);
                    }
                    else if (strstr(comando, "fone"))
                    {
                        sscanf(comando, "insert into pessoa (codigo, nome, fone, data_nascimento) values (%d, '%[^']', '%[^']', '%[^']', '%[^']');",
                               &novaPessoa.codigo, novaPessoa.nome, novaPessoa.fone, novaPessoa.data_nascimento);
                    }
                    else if (strstr(comando, "endereco"))
                    {
                        sscanf(comando, "insert into pessoa (codigo, nome, endereco, data_nascimento) values (%d, '%[^']', '%[^']', '%[^']', '%[^']');",
                               &novaPessoa.codigo, novaPessoa.nome, novaPessoa.endereco, novaPessoa.data_nascimento);
                    }
                    else
                    {
                        sscanf(comando, "insert into pessoa (codigo, nome, data_nascimento) values (%d, '%[^']', '%[^']', '%[^']', '%[^']');",
                               &novaPessoa.codigo, novaPessoa.nome, novaPessoa.data_nascimento);
                    }

                    inserirPessoa(listaPessoas, novaPessoa);
                }
                else if (strstr(comando, "insert into tipo_pet"))
                {
                    TipoPet novoTipoPet = {0};
                    sscanf(comando, "insert into tipo_pet (codigo, descricao) values (%d, '%[^']');",
                           &novoTipoPet.codigo, novoTipoPet.descricao);
                    inserirTipoPet(listaTiposPet, novoTipoPet);
                }
                else if (strstr(comando, "insert into pet"))
                {
                    Pet novoPet = {0};
                    sscanf(comando, "insert into pet (codigo, codigo_cli, nome, codigo_tipo) values (%d, %d, '%[^']', %d);",
                           &novoPet.codigo, &novoPet.codigo_pes, novoPet.nome, &novoPet.codigo_tipo);
                    inserirPet(listaPets, novoPet);
                }
            }
            else if (strstr(comando, "delete from"))
            {
                if (strstr(comando, "delete from pessoa"))
                {
                    int codigo;
                    sscanf(comando, "delete from pessoa where codigo = %d;", &codigo);
                    if (temPetsAssociados(*listaPets, codigo))
                    {
                        printf("Erro: Pessoa com código %d tem pets associados e não pode ser removida.\n", codigo);
                    }
                    else
                    {
                        removerPessoa(listaPessoas, codigo);
                    }
                }
                else if (strstr(comando, "delete from tipo_pet"))
                {
                    int codigo;
                    sscanf(comando, "delete from tipo_pet where codigo = %d;", &codigo);
                    removerTipoPet(listaTiposPet, codigo);
                }
                else if (strstr(comando, "delete from pet"))
                {
                    int codigo;
                    sscanf(comando, "delete from pet where codigo = %d;", &codigo);
                    removerPet(listaPets, codigo);
                }
            }
            else if (strstr(comando, "update"))
            {
                if (strstr(comando, "update pessoa"))
                {
                    int codigo;
                    Pessoa novaPessoa = {0};
                    sscanf(comando, "update pessoa set nome = '%[^']', fone = '%[^']', endereco = '%[^']', data_nascimento = '%[^']' where codigo = %d;",
                           novaPessoa.nome, novaPessoa.fone, novaPessoa.endereco, novaPessoa.data_nascimento, &codigo);
                    atualizarPessoaPorCodigo(*listaPessoas, codigo, novaPessoa);
                }
                else if (strstr(comando, "update tipo_pet"))
                {
                    int codigo;
                    TipoPet novoTipoPet = {0};
                    sscanf(comando, "update tipo_pet set descricao = '%[^']' where codigo = %d;", novoTipoPet.descricao, &codigo);
                    atualizarTipoPetPorCodigo(*listaTiposPet, codigo, novoTipoPet);
                }
                else if (strstr(comando, "update pet"))
                {
                    int codigo;
                    Pet novoPet = {0};
                    sscanf(comando, "update pet set nome = '%[^']', codigo_cli = %d, codigo_tipo = %d where codigo = %d;",
                           novoPet.nome, &novoPet.codigo_pes, &novoPet.codigo_tipo, &codigo);
                    atualizarPetPorCodigo(*listaPets, codigo, novoPet);
                }
            }
            else if (strstr(comando, "select"))
            {
                if (strstr(comando, "from pessoa"))
                {
                    int codigo = -1;
                    bool listaOCodigo = strstr(comando, "codigo") != NULL;
                    bool listaONome = strstr(comando, "nome") != NULL;
                    bool listaOTelefone = strstr(comando, "fone") != NULL;
                    bool listaOEndereco = strstr(comando, "endereco") != NULL;
                    bool listaONascimento = strstr(comando, "data_nascimento") != NULL;

                    if (strstr(comando, "where"))
                    {
                        if (sscanf(comando, "select %*s from pessoa where codigo = %d;", &codigo) != 1)
                        {
                            printf("Erro: Não foi possível extrair o código do comando.\n");
                            codigo = -1;
                        }
                    }
                    //implementar order by
                    if (strstr(comando, "*")){
                        if (possuiOrderBy)
                            listarPessoasOrderBy(*listaPessoas, colunaOrdenacao, true, true, true, true, true);
                        else
                            listarPessoas(*listaPessoas, true, true, true, true, true, codigo);
                    }
                    else{
                        if (possuiOrderBy)
                            listarPessoasOrderBy(*listaPessoas, colunaOrdenacao, listaOCodigo, listaONome, listaOTelefone, listaOEndereco, listaONascimento);
                        listarPessoas(*listaPessoas, listaOCodigo, listaONome, listaOTelefone, listaOEndereco, listaONascimento, codigo);
                    }
                }
                else if (strstr(comando, "from tipo_pet"))
                {
                    int codigo = -1;
                    bool listaOCodigo = strstr(comando, "codigo") != NULL;
                    bool listaADescricao = strstr(comando, "descricao") != NULL;

                    if (strstr(comando, "where"))
                    {
                        if (sscanf(comando, "select %*s from tipo_pet where codigo = %d;", &codigo) != 1)
                        {
                            printf("Erro: Não foi possível extrair o código do comando.\n");
                            codigo = -1;
                        }
                    }
                    if (strstr(comando, "*")){
                        if (possuiOrderBy){
                            listarTiposPetOrderBy(*listaTiposPet, colunaOrdenacao, true, true);
                        }else{
                        listarTiposPet(*listaTiposPet, true, true, codigo);
                        }
                    }
                    else{
                        if (possuiOrderBy)
                            listarTiposPetOrderBy(*listaTiposPet, colunaOrdenacao, listaOCodigo, listaADescricao);
                        listarTiposPet(*listaTiposPet, listaOCodigo, listaADescricao, codigo);
                    }
                }
                else if (strstr(comando, "from pet"))
                {
                    int codigo = -1;
                    bool listaOCodigo = strstr(comando, "codigo") != NULL;
                    bool listaOCodigoPessoa = strstr(comando, "codigo_pessoa") != NULL;
                    bool listaONome = strstr(comando, "nome") != NULL;
                    bool listaOCodigoTipo = strstr(comando, "codigo_tipo") != NULL;

                    if (strstr(comando, "where"))
                    {
                        if (sscanf(comando, "select %*s from pet where codigo = %d;", &codigo) != 1)
                        {
                            printf("Erro: Não foi possível extrair o código do comando.\n");
                            codigo = -1;
                        }
                    }
                    if (strstr(comando, "*"))
                    {
                        if (possuiOrderBy){
                            listarPetsOrderBy(*listaPets, colunaOrdenacao, true, true, true, true);
                        }else
                        listarPets(*listaPets, true, true, true, true, codigo);
                    }
                    else{
                        if (possuiOrderBy){
                            listarPetsOrderBy(*listaPets, colunaOrdenacao, listaOCodigo, listaOCodigoPessoa, listaONome, listaOCodigoTipo);
                        } else
                        listarPets(*listaPets, listaOCodigo, listaOCodigoPessoa, listaONome, listaOCodigoTipo, codigo);
                        
                    }
                }
            }
            else
            {
                printf("Comando não reconhecido: %s\n", comando);
            }
        }
        else
        {
            printf("Comando inválido: %s\n", comando);
        }
        free(comando);
    }
}

int temOrderBy(char *comando, char *colunaOrdenacao){
    char *orderByPos = strstr(comando, "order by");
    if (orderByPos) {
        sscanf(orderByPos, "order by %s", colunaOrdenacao);
        return 1;
    }
    return 0;
}
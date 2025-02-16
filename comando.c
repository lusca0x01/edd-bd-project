#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comando.h"
#include "pessoa.h"
#include "tipo_pet.h"
#include "pet.h"

void inicializarFila(FilaComandos *fila)
{
    fila->inicio = fila->fim = NULL;
}

void adicionarComando(FilaComandos *fila, char *descricao)
{
    Comando *novo = (Comando *)malloc(sizeof(Comando));
    strcpy(novo->descricao, descricao);
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
        return NULL;

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
        strstr(comando, "insert into") ||
        strstr(comando, "update") ||
        strstr(comando, "delete from") ||
        strstr(comando, "select * from"));
}

int temPetsAssociados(Pet *lista, int codigoPessoa)
{
    while (lista)
    {
        if (lista->codigo_pes == codigoPessoa)
            return 1;
        lista = lista->prox;
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
            // INSERT INTO PESSOA
            if (strstr(comando, "insert into pessoa"))
            {
                Pessoa novaPessoa;
                novaPessoa.endereco[0] = '\0';
                novaPessoa.data_nascimento[0] = '\0';

                if ((strstr(comando, "endereco, data_nascimento")))
                {
                    sscanf(comando, "insert into pessoa (codigo, nome, fone, endereco, data_nascimento) values (%d, '%[^']', '%[^']', '%[^']', '%[^']');",
                           &novaPessoa.codigo, novaPessoa.nome, novaPessoa.fone, novaPessoa.endereco);
                }
                if (strstr(comando, "endereco"))
                {
                    sscanf(comando, "insert into pessoa (codigo, nome, fone, endereco) values (%d, '%[^']', '%[^']', '%[^']');",
                           &novaPessoa.codigo, novaPessoa.nome, novaPessoa.fone, novaPessoa.endereco);
                }
                else if (strstr(comando, "data_nascimento"))
                {
                    sscanf(comando, "insert into pessoa (codigo, nome, fone, data_nascimento) values (%d, '%[^']', '%[^']', '%[^']');",
                           &novaPessoa.codigo, novaPessoa.nome, novaPessoa.fone, novaPessoa.data_nascimento);
                }
                else
                {
                    sscanf(comando, "insert into pessoa (codigo, nome, fone) values (%d, '%[^']', '%[^']');",
                           &novaPessoa.codigo, novaPessoa.nome, novaPessoa.fone);
                }

                inserirPessoa(listaPessoas, novaPessoa);
            }
            // INSERT INTO TIPO_PET
            else if (strstr(comando, "insert into tipo_pet"))
            {
                TipoPet novoTipoPet;
                sscanf(comando, "insert into tipo_pet (codigo, descricao) values (%d, '%[^']');",
                       &novoTipoPet.codigo, novoTipoPet.descricao);
                inserirTipoPet(listaTiposPet, novoTipoPet);
            }
            // INSERT INTO PET
            else if (strstr(comando, "insert into pet"))
            {
                Pet novoPet;
                sscanf(comando, "insert into pet (codigo, codigo_cli, nome, codigo_tipo) values (%d, %d, '%[^']', %d);",
                       &novoPet.codigo, &novoPet.codigo_pes, novoPet.nome, &novoPet.codigo_tipo);
                inserirPet(listaPets, novoPet);
            }
            // DELETE FROM PESSOA
            else if (strstr(comando, "delete from pessoa"))
            {
                int codigo;
                sscanf(comando, "delete from pessoa where codigo = %d;", &codigo);
                if (temPetsAssociados(*listaPets, codigo))
                {
                    printf("Erro: Pessoa com código %d tem pets associados e não pode ser removida.\n", codigo);
                    continue;
                }
                removerPessoa(listaPessoas, codigo);
            }
            // DELETE FROM TIPO_PET
            else if (strstr(comando, "delete from tipo_pet"))
            {
                int codigo;
                sscanf(comando, "delete from tipo_pet where codigo = %d;", &codigo);
                removerTipoPet(listaTiposPet, codigo);
            }
            // DELETE FROM PET
            else if (strstr(comando, "delete from pet"))
            {
                int codigo;
                sscanf(comando, "delete from pet where codigo = %d;", &codigo);
                removerPet(listaPets, codigo);
            }
            // SELECT * FROM PESSOA
            else if (strstr(comando, "select * from pessoa"))
            {
                listarPessoas(*listaPessoas);
            }
            // SELECT * FROM TIPO_PET
            else if (strstr(comando, "select * from tipo_pet"))
            {
                listarTiposPet(*listaTiposPet);
            }
            // SELECT * FROM PET
            else if (strstr(comando, "select * from pet"))
            {
                listarPets(*listaPets);
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
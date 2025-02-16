#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <regex.h>
#include "comando.h"

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
    regex_t regex;
    int reti;

    // Compile regular expression to match valid SQL commands
    reti = regcomp(&regex, "^(insert into|update|delete from|select).*", REG_EXTENDED);
    if (reti)
    {
        fprintf(stderr, "Could not compile regex\n");
        return 0;
    }

    // Execute regular expression
    reti = regexec(&regex, comando, 0, NULL, 0);
    regfree(&regex);

    return reti == 0;
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
    regex_t regex;
    regmatch_t matches[10];

    while ((comando = removerComando(fila)))
    {
        if (validarComando(comando))
        {
            if (strstr(comando, "insert into"))
            {
                if (strstr(comando, "pessoa"))
                {
                    Pessoa novaPessoa = {0};
                    if (regcomp(&regex, "insert into pessoa \\(([^)]+)\\) values \\(([^)]+)\\);", REG_EXTENDED) == 0)
                    {
                        if (regexec(&regex, comando, 10, matches, 0) == 0)
                        {
                            char *fields = strndup(comando + matches[1].rm_so, matches[1].rm_eo - matches[1].rm_so);
                            char *values = strndup(comando + matches[2].rm_so, matches[2].rm_eo - matches[2].rm_so);
                            // Parse fields and values here
                            free(fields);
                            free(values);
                        }
                        regfree(&regex);
                    }
                }
                else if (strstr(comando, "tipo_pet"))
                {
                    TipoPet novoTipoPet = {0};
                    if (regcomp(&regex, "insert into tipo_pet \\(([^)]+)\\) values \\(([^)]+)\\);", REG_EXTENDED) == 0)
                    {
                        if (regexec(&regex, comando, 10, matches, 0) == 0)
                        {
                            char *fields = strndup(comando + matches[1].rm_so, matches[1].rm_eo - matches[1].rm_so);
                            char *values = strndup(comando + matches[2].rm_so, matches[2].rm_eo - matches[2].rm_so);
                            // Parse fields and values here
                            free(fields);
                            free(values);
                        }
                        regfree(&regex);
                    }
                }
                else if (strstr(comando, "pet"))
                {
                    Pet novoPet = {0};
                    if (regcomp(&regex, "insert into pet \\(([^)]+)\\) values \\(([^)]+)\\);", REG_EXTENDED) == 0)
                    {
                        if (regexec(&regex, comando, 10, matches, 0) == 0)
                        {
                            char *fields = strndup(comando + matches[1].rm_so, matches[1].rm_eo - matches[1].rm_so);
                            char *values = strndup(comando + matches[2].rm_so, matches[2].rm_eo - matches[2].rm_so);
                            // Parse fields and values here
                            free(fields);
                            free(values);
                        }
                        regfree(&regex);
                    }
                }
            }
            else if (strstr(comando, "delete from"))
            {
                if (strstr(comando, "pessoa"))
                {
                    int codigo;
                    if (regcomp(&regex, "delete from pessoa where codigo = (\\d+);", REG_EXTENDED) == 0)
                    {
                        if (regexec(&regex, comando, 10, matches, 0) == 0)
                        {
                            codigo = atoi(comando + matches[1].rm_so);
                            if (temPetsAssociados(*listaPets, codigo))
                            {
                                printf("Erro: Pessoa com código %d tem pets associados e não pode ser removida.\n", codigo);
                            }
                            else
                            {
                                removerPessoa(listaPessoas, codigo);
                            }
                        }
                        regfree(&regex);
                    }
                }
                else if (strstr(comando, "tipo_pet"))
                {
                    int codigo;
                    if (regcomp(&regex, "delete from tipo_pet where codigo = (\\d+);", REG_EXTENDED) == 0)
                    {
                        if (regexec(&regex, comando, 10, matches, 0) == 0)
                        {
                            codigo = atoi(comando + matches[1].rm_so);
                            removerTipoPet(listaTiposPet, codigo);
                        }
                        regfree(&regex);
                    }
                }
                else if (strstr(comando, "pet"))
                {
                    int codigo;
                    if (regcomp(&regex, "delete from pet where codigo = (\\d+);", REG_EXTENDED) == 0)
                    {
                        if (regexec(&regex, comando, 10, matches, 0) == 0)
                        {
                            codigo = atoi(comando + matches[1].rm_so);
                            removerPet(listaPets, codigo);
                        }
                        regfree(&regex);
                    }
                }
            }
            else if (strstr(comando, "update"))
            {
                if (strstr(comando, "pessoa"))
                {
                    int codigo;
                    Pessoa novaPessoa = {0};
                    if (regcomp(&regex, "update pessoa set (.*) where codigo = (\\d+);", REG_EXTENDED) == 0)
                    {
                        if (regexec(&regex, comando, 10, matches, 0) == 0)
                        {
                            char *updates = strndup(comando + matches[1].rm_so, matches[1].rm_eo - matches[1].rm_so);
                            codigo = atoi(comando + matches[2].rm_so);
                            // Parse updates here
                            free(updates);
                        }
                        regfree(&regex);
                    }
                }
                else if (strstr(comando, "tipo_pet"))
                {
                    int codigo;
                    TipoPet novoTipoPet = {0};
                    if (regcomp(&regex, "update tipo_pet set (.*) where codigo = (\\d+);", REG_EXTENDED) == 0)
                    {
                        if (regexec(&regex, comando, 10, matches, 0) == 0)
                        {
                            char *updates = strndup(comando + matches[1].rm_so, matches[1].rm_eo - matches[1].rm_so);
                            codigo = atoi(comando + matches[2].rm_so);
                            // Parse updates here
                            free(updates);
                        }
                        regfree(&regex);
                    }
                }
                else if (strstr(comando, "pet"))
                {
                    int codigo;
                    Pet novoPet = {0};
                    if (regcomp(&regex, "update pet set (.*) where codigo = (\\d+);", REG_EXTENDED) == 0)
                    {
                        if (regexec(&regex, comando, 10, matches, 0) == 0)
                        {
                            char *updates = strndup(comando + matches[1].rm_so, matches[1].rm_eo - matches[1].rm_so);
                            codigo = atoi(comando + matches[2].rm_so);
                            // Parse updates here
                            free(updates);
                        }
                        regfree(&regex);
                    }
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
                        if (regcomp(&regex, "select .* from pessoa where codigo = (\\d+);", REG_EXTENDED) == 0)
                        {
                            if (regexec(&regex, comando, 10, matches, 0) == 0)
                            {
                                codigo = atoi(comando + matches[1].rm_so);
                            }
                            regfree(&regex);
                        }
                    }

                    if (strstr(comando, "*"))
                        listarPessoas(*listaPessoas, true, true, true, true, true, codigo);
                    else
                        listarPessoas(*listaPessoas, listaOCodigo, listaONome, listaOTelefone, listaOEndereco, listaONascimento, codigo);
                }
                else if (strstr(comando, "from tipo_pet"))
                {
                    int codigo = -1;
                    bool listaOCodigo = strstr(comando, "codigo") != NULL;
                    bool listaADescricao = strstr(comando, "descricao") != NULL;

                    if (strstr(comando, "where"))
                    {
                        if (regcomp(&regex, "select .* from tipo_pet where codigo = (\\d+);", REG_EXTENDED) == 0)
                        {
                            if (regexec(&regex, comando, 10, matches, 0) == 0)
                            {
                                codigo = atoi(comando + matches[1].rm_so);
                            }
                            regfree(&regex);
                        }
                    }

                    if (strstr(comando, "*"))
                        listarTiposPet(*listaTiposPet, true, true, codigo);
                    else
                        listarTiposPet(*listaTiposPet, listaOCodigo, listaADescricao, codigo);
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
                        if (regcomp(&regex, "select .* from pet where codigo = (\\d+);", REG_EXTENDED) == 0)
                        {
                            if (regexec(&regex, comando, 10, matches, 0) == 0)
                            {
                                codigo = atoi(comando + matches[1].rm_so);
                            }
                            regfree(&regex);
                        }
                    }

                    if (strstr(comando, "*"))
                        listarPets(*listaPets, true, true, true, true, codigo);
                    else
                        listarPets(*listaPets, listaOCodigo, listaOCodigoPessoa, listaONome, listaOCodigoTipo, codigo);
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
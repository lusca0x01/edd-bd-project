#ifndef COMANDO_H
#define COMANDO_H

typedef struct Comando
{
    char descricao[256];
    struct Comando *prox;
} Comando;

typedef struct
{
    Comando *inicio, *fim;
} FilaComandos;

void inicializarFila(FilaComandos *fila);
void adicionarComando(FilaComandos *fila, char *descricao);
char *removerComando(FilaComandos *fila);
int validarComando(char *comando);
void processarComandos(FilaComandos *fila, Pessoa **listaPessoas, TipoPet **listaTiposPet, Pet **listaPets);
#endif

#ifndef TIPO_PET_H
#define TIPO_PET_H

typedef struct TipoPet
{
    int codigo;
    char descricao[50];
    struct TipoPet *ant, *prox;
} TipoPet;

TipoPet *carregarTiposPet();
void salvarTiposPet(TipoPet *lista);
TipoPet *buscarTipoPetPorCodigo(TipoPet *lista, int codigo);
void inserirTipoPet(TipoPet **lista, TipoPet novoTipo);
void removerTipoPet(TipoPet **lista, int codigo);
void listarTiposPet(TipoPet *lista);

#endif

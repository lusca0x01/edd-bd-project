#ifndef TIPO_PET_H
#define TIPO_PET_H

#include <stdbool.h>

typedef struct TipoPet
{
    int codigo;
    char descricao[50];
    struct TipoPet *ant, *prox;
} TipoPet;

TipoPet *carregarTiposPet();
void salvarTiposPet(TipoPet *lista);
TipoPet *buscarTipoPetPorCodigo(TipoPet *lista, int codigo);
TipoPet *buscarTipoPetPorDescricao(TipoPet *lista, char descricao[50]);
void atualizarTipoPetPorCodigo(TipoPet *lista, int codigo, TipoPet novoTipoPet);
void atualizarTipoPetPorDescricao(TipoPet *lista, char descricao[50], TipoPet novoTipoPet);
void inserirTipoPet(TipoPet **lista, TipoPet novoTipo);
void removerTipoPet(TipoPet **lista, int codigo);
void listarTiposPet(TipoPet *lista, bool listaOCodigo, bool listaADescricao);
void liberarListaTiposPet(TipoPet **lista);

#endif

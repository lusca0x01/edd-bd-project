#ifndef ARVORE_TIPO_PET_H
#define ARVORE_TIPO_PET_H

typedef struct ArvoreTipoPet {
    struct TipoPet *tipo_pet;
    struct ArvorePet *esq, *dir;
} ArvoreTipoPet;

void listarTiposPetOrderBy(TipoPet *raiz, const char *coluna, bool listaOCodigo, bool listaADescricao);
void imprimirTipoPet(TipoPet *tipo_pet, bool listaOCodigo, bool listaADescricao);

#endif
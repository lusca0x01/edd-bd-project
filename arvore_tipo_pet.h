#ifndef ARVORE_TIPO_PET_H
#define ARVORE_TIPO_PET_H

typedef struct ArvoreTipoPet {
    struct TipoPet *pet;
    struct ArvorePet *esq, *dir;
} ArvoreTipoPet;

void listarPetsOrderBy(Pet *raiz, const char *coluna, bool listaOCodigo, bool listaOCodigoPessoa, bool listaONome, bool listaOCodigoTipo);
void imprimirPet(Pet *pet, bool listaOCodigo, bool listaOCodigoPessoa, bool listaONome, bool listaOCodigoTipo);

#endif
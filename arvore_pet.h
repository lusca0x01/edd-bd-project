#ifndef ARVORE_PET_H
#define ARVORE_PET_H

typedef struct ArvorePet {
    struct Pet *pet;
    struct ArvorePet *esq, *dir;
} ArvorePet;

void listarPetsOrderBy(Pet *raiz, const char *coluna, bool listaOCodigo, bool listaOCodigoPessoa, bool listaONome, bool listaOCodigoTipo);
void imprimirPet(Pet *pet, bool listaOCodigo, bool listaOCodigoPessoa, bool listaONome, bool listaOCodigoTipo);

#endif
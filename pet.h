#ifndef PET_H
#define PET_H

#include <stdbool.h>

typedef struct Pet
{
    int codigo;
    int codigo_pes;
    char nome[50];
    int codigo_tipo;
    struct Pet *ant, *prox;
} Pet;

Pet *carregarPets();
void salvarPets(Pet *lista);
Pet *buscarPetPorCodigo(Pet *lista, int codigo);
Pet *buscarPetPorNome(Pet *lista, char nome[50]);
void atualizarPetPorCodigo(Pet *lista, int codigo, Pet novoPet);
void atualizarPetPorNome(Pet *lista, char nome[50], Pet novoPet);
void inserirPet(Pet **lista, Pet novoPet);
void removerPet(Pet **lista, int codigo);
void listarPets(Pet *lista, bool listaOCodigo, bool listaOCodigoPessoa, bool listaONome, bool listaOCodigoTipo);
void liberarListaPets(Pet **lista);

#endif

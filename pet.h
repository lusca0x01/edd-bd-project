#ifndef PET_H
#define PET_H

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
void inserirPet(Pet **lista, Pet novoPet);
void removerPet(Pet **lista, int codigo);
void listarPets(Pet *lista);

#endif

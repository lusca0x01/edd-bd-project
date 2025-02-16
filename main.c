#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pessoa.h"
#include "tipo_pet.h"
#include "pet.h"
#include "comando.h"

int main()
{
    // Inicializa listas e filas
    Pessoa *listaPessoas = carregarPessoas();
    TipoPet *listaTiposPet = carregarTiposPet();
    Pet *listaPets = carregarPets();

    FilaComandos fila;
    inicializarFila(&fila);

    // Lê comandos de um arquivo
    FILE *arquivo = fopen("script.sql", "r");
    if (arquivo)
    {
        char linha[256];
        while (fgets(linha, sizeof(linha), arquivo))
        {
            adicionarComando(&fila, linha);
        }
        fclose(arquivo);
    }

    // Processa comandos
    processarComandos(&fila, &listaPessoas, &listaTiposPet, &listaPets);

    // Salva alterações
    salvarPessoas(listaPessoas);
    salvarTiposPet(listaTiposPet);
    salvarPets(listaPets);

    return 0;
}

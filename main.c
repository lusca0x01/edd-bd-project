#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "pessoa.h"
#include "tipo_pet.h"
#include "pet.h"
#include "comando.h"

int main()
{
    setlocale(LC_ALL, "pt_BR.UTF-8");

    Pessoa *listaPessoas = carregarPessoas();
    TipoPet *listaTiposPet = carregarTiposPet();
    Pet *listaPets = carregarPets();

    FilaComandos fila;
    inicializarFila(&fila);

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

    processarComandos(&fila, &listaPessoas, &listaTiposPet, &listaPets);

    printf("PRINTS DA LISTAGEM ////////////// (TESTE)\n");
    listarPessoas(listaPessoas, true, true, true, true, true, -1);
    listarPets(listaPets, true, true, true, true, -1);
    listarTiposPet(listaTiposPet, true, true, -1);
    printf("//////////////");

    salvarPessoas(listaPessoas);
    salvarTiposPet(listaTiposPet);
    salvarPets(listaPets);

    return 0;
}

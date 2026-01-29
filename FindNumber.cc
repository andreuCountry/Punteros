#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Semilla() {
    srand(time(NULL));
}

int main() {

    Semilla();

    int sizePointer = rand()%1000;

    int numberToSearch;

    int* list = nullptr;

    list = (int*) malloc(sizePointer*sizeof(int));

    printf("Valor a buscar: ");
    scanf("%d", &numberToSearch);

    int contador = 0;
    for (int i = 0; i < sizePointer; i++) {
        int randomNumber = rand()%100;

        if (randomNumber == numberToSearch) {
            contador++;
        }
        *(list+i) = randomNumber;
    }

    printf("Valor %d, localizado %d veces en el bloque", numberToSearch, contador);

    free(list);
    list = nullptr;

    return 0;
}

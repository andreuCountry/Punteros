#include <stdio.h>
#include <stdlib.h>

struct TDato{
    unsigned char nace, altura, peso;
};

FILE *muestreo;

TDato* data = nullptr;
TDato dataInSave;

int contador = 0, yearBorn;

void CreateDynamicMemory() {

    muestreo = fopen("files/muestreo.dat", "rb");

    while(fread(&dataInSave, sizeof(struct TDato), 1, muestreo)) {
        contador++;
        data = (TDato*) realloc(data, contador*sizeof(TDato));
    }

    fclose(muestreo);
}

void AskData() {
    printf("Volcado en heap correcto. \n");
    printf("Leido un total de %d del fichero de muestreo.dat \n", contador);

    printf("Nacimiento: " );
    scanf("%d", &yearBorn);
}

void ReadNewspaper() {
    
    float sumaAlturaTotal = 0.0f, sumaPesoTotal = 0.0f;
    int numbersFinded = 0;
    for (int i = 0; i < contador; i++) {

        int yearFinded = (data+i)->nace;
        if ((yearFinded + 1972) == yearBorn) {
            sumaAlturaTotal += (data+i)->altura;
            sumaPesoTotal += (data+i)->peso;
            numbersFinded++;
        }
    }

    printf("Del muestreo de %d elementos se han encontrado %d nacidos en %d. \n", contador, numbersFinded, yearBorn);
    printf("Promedio de altura: %f \n", sumaAlturaTotal / numbersFinded);
    printf("Promedio de peso: %f \n", sumaPesoTotal / numbersFinded);
}

int main() {

    CreateDynamicMemory();
    AskData();
    ReadNewspaper();

    //free(dataInSave);

    return 0;
}

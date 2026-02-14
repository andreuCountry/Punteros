
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>


#include "conjunto.cc"

#define TConjunto TLista

TConjunto *conjunto1=nullptr, *conjunto2=nullptr, *resultadoU=nullptr, *resultadoI=nullptr;

TConjunto* CrearConjunto() {
    return nullptr;
}

void IncluirConjunto(TConjunto** conjunto, int num) {
    TConjunto* newConjunto = (TConjunto*) malloc(1*sizeof(TConjunto));
    newConjunto->info = num;
    newConjunto->prox = *conjunto;
    *conjunto = newConjunto;
}

void MuestraConjunto(TConjunto* conjunto) {
    TConjunto* con;

    for(con = conjunto; con != nullptr; con = con->prox) {
        printf("El conjunto contiene valor %d \n", con->info);
    }
}

void InterseccionConjunto(TConjunto* conjunto1, TConjunto* conjunto2, TConjunto** result) {
    TConjunto* con1;
    TConjunto* con2;
    TConjunto* con3;
    bool encontrado = false;

    for(con1 = conjunto1; con1 != nullptr; con1 = con1->prox) {
        for(con2 = conjunto2; con2 != nullptr; con2 = con2->prox) {
            if (con2->info == con1->info) {
                encontrado = true;
                for (con3 = *result; con3 != nullptr; con3 = con3->prox) {
                    if (con3->info == con2->info) {
                        encontrado = false;
                    }
                }

                if (encontrado) {
                    IncluirConjunto(&resultadoI, con2->info);
                    encontrado = false;
                }
            }
        }
    }
}

void UnionConjunto(TConjunto* conjunto1, TConjunto* conjunto2, TConjunto** result) {
    TConjunto* con1;
    TConjunto* con2;
    TConjunto* con3;
    bool encontrado = false;

    for(con1 = conjunto1; con1 != nullptr; con1 = con1->prox) {
        for(con2 = conjunto2; con2 != nullptr; con2 = con2->prox) {
            if (con2->info != con1->info) {
                encontrado = true;
                for (con3 = *result; con3 != nullptr; con3 = con3->prox) {
                    if (con3->info == con2->info) {
                        encontrado = false;
                    }
                }

                if (encontrado) {
                    IncluirConjunto(&resultadoU, con2->info);
                    encontrado = false;
                }
            }
        }
    }
}

int main(){
	
    conjunto1=CrearConjunto();
    conjunto2=CrearConjunto();
    resultadoU=CrearConjunto();
    resultadoI=CrearConjunto();
    
    IncluirConjunto(&conjunto1,3);
    IncluirConjunto(&conjunto1,10);
    IncluirConjunto(&conjunto1,3);
    IncluirConjunto(&conjunto1,15);
    IncluirConjunto(&conjunto1,3);
    IncluirConjunto(&conjunto1,30);
    
    printf("\n\nVolcado conjunto 1\n");
    MuestraConjunto(conjunto1);
    
    IncluirConjunto(&conjunto2,18);
    IncluirConjunto(&conjunto2,10);
    IncluirConjunto(&conjunto2,35);
    IncluirConjunto(&conjunto2,1);
    IncluirConjunto(&conjunto2,3);
    IncluirConjunto(&conjunto2,45);

    printf("\n\nVolcado conjunto 2\n");
    MuestraConjunto(conjunto2);
    
    UnionConjunto(conjunto1,conjunto2,&resultadoU);

    printf("\n\nVolcado Union\n");
    MuestraConjunto(resultadoU);
    
    InterseccionConjunto(conjunto1,conjunto2,&resultadoI);

    printf("\n\nVolcado Interseccion\n");
    MuestraConjunto(resultadoI);
    
	return 0;
}
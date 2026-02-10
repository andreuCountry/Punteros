#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#include "TListas.cc"

TLista *lista1,*lista2;

void CrearLista(TLista** lista) {
    lista = nullptr;
}
// for(p=lista; p = nullptr; p = p->prox)

void InsertarLista(TLista** lista, int valor) {
    TLista* newLista = (TLista*) malloc(1*sizeof(TLista));
    newLista->info = valor;
    newLista->prox = *lista;
    *lista = newLista;
}

void MuestraLista(TLista* lista) {

    TLista* p;

    for(p = lista; p != nullptr; p = p->prox) {
        printf("La lista contiene valor %d \n", p->info);
    }
}

TLista* IndexaLista(TLista* lista, int index) {
    
    TLista* p = lista;

    for(int i = 0; i < index && p != nullptr; i++) {
        p = lista->prox;
    }

    return p;
}

int main() {

    CrearLista(&lista1);
    CrearLista(&lista2);
    
    InsertarLista(&lista1,3);
    InsertarLista(&lista1,5);
    InsertarLista(&lista1,15);
    InsertarLista(&lista1,28);
    InsertarLista(&lista1,25);
    InsertarLista(&lista1,45);
    InsertarLista(&lista1,105);
    InsertarLista(&lista1,280);

    printf("\n\n");
    printf(" Lista >>> ");
    MuestraLista(lista1);
    
    printf("\n\n Acceso indexado a lista por valor que ocupa posicion 0. \n");
    lista2=IndexaLista(lista1,0);
    printf(" Elemento apuntado de la lista: %d \n",lista2->info);
    /*
    printf("\n\n Buscar y apuntar. \n");
    if((lista2=BuscarLista(lista1,3,actual))==nullptr){
        printf("\nNo encontrado.");
    } else {
        printf("\n Localizado y apuntado: %d",lista2->info);
    }

    printf("\n\n Localizar y eliminar. valores 28, 3 y 280\n");
    EliminaEnLista(&lista1,28);
    printf("\n Eliminado valor 28 de la lista\n");
    printf(" Lista >>> ");
    MuestraLista(lista1);
    EliminaEnLista(&lista1,3);
    printf("\n Eliminado valor 3 de la lista\n");
    printf(" Lista >>> ");
    MuestraLista(lista1);
    EliminaEnLista(&lista1,280);
    printf("\n Eliminado valor 280 de la lista\n");
    printf(" Lista >>> ");
    MuestraLista(lista1);
    printf("\n\n");*/

	return 0;
}

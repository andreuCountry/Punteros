#include <stdio.h>

enum ACTUAL {
    actuality,
    anterior
};

struct TLista {
    int info;
    TLista *prox;
};

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

    for(int i = 0;  p != nullptr && i < index; p = p->prox) {
        i++;
    }

    return p;
}

TLista* BuscarLista(TLista* lista, int index, ACTUAL direction) {
    TLista* p = lista;
    TLista* aux = nullptr;

    for(int i = 0; p != nullptr && i != index; p = p->prox) {

        if (direction == anterior) {
            if (i + 1 == index) {
                aux = p;
            }
        }

        i++;
    }

    if (direction == anterior) {
        return aux;
    } else {
        return p;
    }
}

void EliminaEnLista(TLista** lista, int info) {
    TLista* p = *lista;
    TLista* aux = nullptr;
    bool encontrado = false;

    if (p->prox == nullptr) {
        
    }

    for(p = *lista;  p != nullptr && !encontrado; p = p->prox) {
        aux = p->prox;
        encontrado = aux->info == info;

        if (encontrado) {

            p->prox = aux->prox;
            free(aux);
        }
    }
}
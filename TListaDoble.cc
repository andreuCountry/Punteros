#include <stdio.h>
#include <stdlib.h>

struct TLista2 {
    int info;
    TLista2 *prox;
    TLista2 *ante;
};

TLista2* CrearLista() {
    TLista2* lista = nullptr;

    return lista;
}

void InsertarLista(TLista2** lista2, int valor) {
    TLista2* newLista = (TLista2*) malloc(1*sizeof(TLista2));
    newLista->info = valor;
    newLista->prox = *lista2;
    newLista->ante = nullptr;

    if ((*lista2) != nullptr) {
        (*lista2)->ante = newLista;
    }

    *lista2 = newLista;
}

void MostrarLista(TLista2* lista2) {

    TLista2* p;

    for(p = lista2; p != nullptr; p = p->prox) {
        printf(" %d", p->info);
    }
}

TLista2* BuscarEnLista(TLista2* lista2, int valor) {
    TLista2* p = lista2;
    TLista2* aux = nullptr;

    for(int i = 0; p != nullptr; p = p->prox) {

        if (p->info == valor) {
            aux = p;
        }

        i++;
    }

    if (aux != nullptr) {
        return aux;
    } else {
        return p;
    }
}

void InvertidoMostrarLista(TLista2* lista2) {
    TLista2* aux = nullptr;

    for (aux = lista2; aux->prox != nullptr; aux = aux->prox);

    for (int j = 0; aux != nullptr; aux = aux->ante) {
        printf(" %d", aux->info);
    }

}

TLista2* ExtraerLista(TLista2** lista2) {
    TLista2* p = *lista2;
    TLista2* aux = nullptr;
    TLista2* aux2 = nullptr;

    aux = p->prox;
    aux2 = p->ante;
    
    if (aux != nullptr) {
        aux->ante = aux2;
    }

    if (aux2 != nullptr) {
        aux2->prox = aux;
    }

    p->prox = nullptr;
    p->ante = nullptr;

    // si la lista sigue apuntando a uno que vas a liberar se rompe
    *lista2 = aux;

    return p;
}

int LongitudLista(TLista2* lista2) {
    
    TLista2* p = lista2;
    int contador = 0;

    for (int i = 0; p != nullptr; p = p->prox) {
        contador++;
    }

    return contador;
}

void EliminarElemento(TLista2** lista2, int value) {
    
    TLista2* p = *lista2;
    TLista2* aux = nullptr;
    TLista2* aux2 = nullptr;
    TLista2* to_delete = nullptr;

    for (int i = 0; p != nullptr; p = p->prox) {
        if (value == p->info) {
            if (p->prox != nullptr) {
                aux = p->prox;
                aux->ante = p->ante;
                aux->prox = p->prox->prox;
            }

            if (p->ante != nullptr) {
                aux2 = p->ante;
                aux2->prox = p->prox;
            }

            p->prox = nullptr;
            p->ante = nullptr;
            to_delete = p;

        }
    }

    if (to_delete != nullptr) {
        free(to_delete);
    } else {
        printf(">>> No encontrado en lista. \n");
    }

}

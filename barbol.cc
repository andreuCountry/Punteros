struct Tbarbol {
    int info;
    Tbarbol *proxRight;
    Tbarbol *proxLeft;
};

void crear_barbol(Tbarbol** barbol) {
    *barbol = nullptr;
}

Tbarbol* insertar_barbol(int value, Tbarbol* leftNode, Tbarbol* rightNode) {
    Tbarbol* newBarbol = (Tbarbol*) malloc(1*sizeof(Tbarbol));

    newBarbol->info = value;
    newBarbol->proxRight = rightNode;
    newBarbol->proxLeft = leftNode;

    return newBarbol;
}

void MostrarArbol(Tbarbol* barbol, int desplazamiento) {

    if (barbol != nullptr) {
        // EHHHHHH, first para la derechita bro
        if (barbol->proxRight != nullptr) {
            MostrarArbol(barbol->proxRight, desplazamiento+1);
        }

        for (int i = 0; i < desplazamiento; i++) {
            printf("   ");
        }

        // EHHHHHH, tenemos mid bro
        printf("%03d \n", barbol->info);
        
        // EHHHHHH, acabamos a la izquierda bro
        if (barbol->proxLeft != nullptr) {
            MostrarArbol(barbol->proxLeft, desplazamiento+1);
        }
    } else {
        printf("El arbolito no existe!!");
    }
    
}

void Vaciator(Tbarbol** barbol) {
    if ((*barbol)->proxRight != nullptr) {
        Vaciator(&(*barbol)->proxRight);
    }


    if ((*barbol)->proxLeft != nullptr) {
        Vaciator(&(*barbol)->proxLeft);
    }

    // eliminamos para el leak de memoria
    free(*barbol);
    (*barbol) = nullptr;
}
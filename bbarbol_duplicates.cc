struct tbbarbol {
    int info;
    tbbarbol *proxRight;
    tbbarbol *proxLeft;
    int duplicaditos;
};

tbbarbol* crear_barbol() {
    tbbarbol* barbol = nullptr;

    return barbol;
}

tbbarbol* buscar_barbol(tbbarbol* barbol, int info) {
    tbbarbol* aux = nullptr;
    
    if (barbol != nullptr) {
        if (barbol->info != info) {
            if (barbol->info < info) {
                aux = buscar_barbol(barbol->proxRight, info);
            } else {
                aux = buscar_barbol(barbol->proxLeft, info);
            }
        
        } else {
            barbol->duplicaditos++;
            aux = barbol;
        }
    }

    return aux;
}

void insertar_barbol(tbbarbol** barbol, int info) {

    if (buscar_barbol(*barbol, info) == NULL) {

        // insertar
        if ((*barbol) == nullptr) {
            // guardar memoria en el tbbarol actual, que es insertable
            *barbol = (tbbarbol*) malloc(sizeof(tbbarbol));

            (*barbol)->proxRight = nullptr;
            (*barbol)->proxLeft = nullptr;
            
            (*barbol)->info = info;
            (*barbol)->duplicaditos = 1;
        } else {
            if ((*barbol)->info > info) {
                insertar_barbol(&((*barbol)->proxLeft), info);
            } else {
                insertar_barbol(&((*barbol)->proxRight), info);
            }
        }
    }
}

void MostrarArbol(tbbarbol* barbol, int desplazamiento) {

    if (barbol != nullptr) {
        // EHHHHHH, first para la derechita bro
        if (barbol->proxRight != nullptr) {
            MostrarArbol(barbol->proxRight, desplazamiento+1);
        }

        for (int i = 0; i < desplazamiento; i++) {
            printf("   ");
        }

        // EHHHHHH, tenemos mid bro
        printf("%03d (%02d)\n", barbol->info, barbol->duplicaditos);
        
        // EHHHHHH, acabamos a la izquierda bro
        if (barbol->proxLeft != nullptr) {
            MostrarArbol(barbol->proxLeft, desplazamiento+1);
        }
    } else {
        printf("El arbolito no existe!!");
    }
    
}

void inorden(tbbarbol* barbol) {
    if (barbol != nullptr) {

        if (barbol->proxLeft != nullptr) {
            inorden(barbol->proxLeft);
        }

        printf("%d  ", barbol->info);

        if (barbol->proxRight != nullptr) {
            inorden(barbol->proxRight);
        }
    }
}

void preorden(tbbarbol* barbol) {
    if (barbol != nullptr) {

        printf("%d  ", barbol->info);

        if (barbol->proxLeft != nullptr) {
            preorden(barbol->proxLeft);
        }

        if (barbol->proxRight != nullptr) {
            preorden(barbol->proxRight);
        }
    }
}

void postorden(tbbarbol* barbol) {
    if (barbol != nullptr) {


        if (barbol->proxLeft != nullptr) {
            postorden(barbol->proxLeft);
        }

        if (barbol->proxRight != nullptr) {
            postorden(barbol->proxRight);
        }

        printf("%d  ", barbol->info);
    }
}
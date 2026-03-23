struct tbbarbol {
    int info;
    tbbarbol *proxRight;
    tbbarbol *proxLeft;
};

tbbarbol* crear_barbol() {
    tbbarbol* barbol = (tbbarbol*) malloc(1*sizeof(tbbarbol));

    barbol->proxRight = nullptr;
    barbol->proxLeft = nullptr;

    return barbol;
}

void insertar_barbol(tbbarbol** barbol, int info) {
    tbbarbol* newBarbol = (tbbarbol*) malloc(sizeof(tbbarbol));
    newBarbol->proxRight = nullptr;
    newBarbol->proxLeft = nullptr;

    if ((*barbol)->info != info) {
        newBarbol->info = info;
        if ((*barbol)->info < info) {
            (*barbol)->proxRight = newBarbol;
        } else {
            (*barbol)->proxLeft = newBarbol;
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
        printf("%03d \n", barbol->info);
        
        // EHHHHHH, acabamos a la izquierda bro
        if (barbol->proxLeft != nullptr) {
            MostrarArbol(barbol->proxLeft, desplazamiento+1);
        }
    } else {
        printf("El arbolito no existe!!");
    }
    
}
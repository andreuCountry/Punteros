struct Tbarbol {
    int info;
    Tbarbol *proxRight;
    Tbarbol *proxLeft;
};

Tbarbol crear_arbol() {
    Tbarbol* barbol = (Tbarbol*) malloc(1*sizeof(Tbarbol));

    barbol->proxRight = nullptr;
    barbol->proxLeft = nullptr;

    return barbol;
}
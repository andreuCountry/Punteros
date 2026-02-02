#include <esat/window.h>
#include <esat/draw.h>
#include <esat/input.h>
#include <esat/sprite.h>
#include <conio.h>
#include <esat/time.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

unsigned char si = 0, fps=25; //Control de frames por segundo
double current_time, last_time;
int windowX = 800, windowY = 600, numberFigures = 0;
float size = 1;

FILE *f;

esat::SpecialKey specialKey;

enum Types {
    RECTANGLE,
    TRIANGLE
};

struct Coordenate {
    float x, y;
};

struct Color {
    int R, G, B, A = 255;
};

struct TFigures {
    Coordenate coordenate;
    Color color;
    Types type;
    int velocity = rand()%20;
};

TFigures* figuresData = nullptr;

void GenerateSeed() {
    srand(time(NULL));
}

void DrawFigure(TFigures figure) {
    if (figure.type == Types::RECTANGLE) {


        float *tvertex = (float*) malloc(10*sizeof(float));

        *(tvertex + 0) = figure.coordenate.x;
        *(tvertex + 1) = figure.coordenate.y;

        printf("Primer par: [%f] ---- [%f]", *(tvertex + 0), *(tvertex + 1));

        *(tvertex + 2) = figure.coordenate.x + size;
        *(tvertex + 3) = figure.coordenate.y;

        *(tvertex + 4) = figure.coordenate.x + size;
        *(tvertex + 5) = figure.coordenate.y + size;

        *(tvertex + 6) = figure.coordenate.x;
        *(tvertex + 7) = figure.coordenate.y + size;

        *(tvertex + 8) = figure.coordenate.x;
        *(tvertex + 9) = figure.coordenate.y;

        esat::DrawSetFillColor(figure.color.R, figure.color.G, figure.color.B, 255);

        printf("Colores: [%d] --- [%d] --- [%d] \n", figure.color.R, figure.color.G, figure.color.B);
        esat::DrawSolidPath(tvertex, 10);

    } else {

        float *tvertex = (float*) malloc(8*sizeof(float));

        esat::DrawSolidPath(tvertex, 4);

    }
}

void Spawn(Types type) {
    float positionX = (float) esat::MousePositionX();
    float positionY = (float) esat::MousePositionY();

    Color colorFigure = {rand()%255, rand()%255, rand()%255};

    TFigures figure = {{positionX, positionY}, colorFigure, type};

    DrawFigure(figure);
}

void ControlsManage() {

    if (esat::MouseButtonDown(0)) {
        Spawn(Types::RECTANGLE);
        numberFigures++;
        figuresData = (TFigures*) realloc(figuresData, numberFigures*sizeof(TFigures));
    }

    if (esat::MouseButtonDown(1)) {
        Spawn(Types::TRIANGLE);
        numberFigures++;
        figuresData = (TFigures*) realloc(figuresData, numberFigures*sizeof(TFigures));
    }
    
}

int esat::main(int argc, char **argv) {

    GenerateSeed();

	esat::WindowInit(windowX, windowY);
	WindowSetMouseVisibility(true);



    while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

    	last_time = esat::Time(); 
            
    	esat::DrawBegin();

    	esat::DrawClear(0, 0, 255);

        ControlsManage();

    	esat::DrawEnd();
    	//Control fps 
    	do{
    		current_time = esat::Time();
    	}while((current_time-last_time)<=1000.0/fps);
    	esat::WindowFrame();

		++si%=7;
    }
  
    esat::WindowDestroy();
    
    return 0;
    
}

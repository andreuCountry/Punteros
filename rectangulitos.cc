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
float size = 5;

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

void DrawFigure() {

    for (int i = 0; i < numberFigures; i++) {

        if ((figuresData+i)->type == Types::RECTANGLE) {

            float *tvertex = (float*) malloc(10*sizeof(float));

            *(tvertex + 0) = (figuresData+i)->coordenate.x;
            *(tvertex + 1) = (figuresData+i)->coordenate.y;

            *(tvertex + 2) = (figuresData+i)->coordenate.x + size;
            *(tvertex + 3) = (figuresData+i)->coordenate.y;

            *(tvertex + 4) = (figuresData+i)->coordenate.x + size;
            *(tvertex + 5) = (figuresData+i)->coordenate.y + size;

            *(tvertex + 6) = (figuresData+i)->coordenate.x;
            *(tvertex + 7) = (figuresData+i)->coordenate.y + size;

            *(tvertex + 8) = (figuresData+i)->coordenate.x;
            *(tvertex + 9) = (figuresData+i)->coordenate.y;

            esat::DrawSetFillColor((figuresData+i)->color.R, (figuresData+i)->color.G, (figuresData+i)->color.B, 255);

            esat::DrawSolidPath(tvertex, 10);

        } else {

            float *tvertex = (float*) malloc(8*sizeof(float));

            esat::DrawSolidPath(tvertex, 4);

        }
    }

}

void Spawn(Types type) {
    float positionX = (float) esat::MousePositionX();
    float positionY = (float) esat::MousePositionY();

    Color colorFigure = {rand()%255, rand()%255, rand()%255};

    TFigures figure = {{positionX, positionY}, colorFigure, type};

    figuresData = (TFigures*) realloc(figuresData, numberFigures*sizeof(TFigures));

    *(figuresData+numberFigures) = figure;
}

void ControlsManage() {

    if (esat::MouseButtonDown(0)) {
        numberFigures++;
        Spawn(Types::RECTANGLE);
    }

    if (esat::MouseButtonDown(1)) {
        numberFigures++;
        Spawn(Types::TRIANGLE);
    }
    
}

int esat::main(int argc, char **argv) {

    GenerateSeed();

	esat::WindowInit(windowX, windowY);
	WindowSetMouseVisibility(true);



    while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

    	last_time = esat::Time(); 
            
    	esat::DrawBegin();

    	esat::DrawClear(0, 0, 0);

        ControlsManage();

        DrawFigure();

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

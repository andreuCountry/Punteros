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
float size = 20;

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
    esat::Vec2 coordenate;
    Color color;
    Types type;
    int speed = rand()%5 + 1;
};

TFigures* figuresData = nullptr;

void GenerateSeed() {
    srand(time(NULL));
}

void DrawFigure() {

    if (numberFigures > 0) {
        for (int i = 0; i < numberFigures; i++)
        {
            if ((figuresData+i)->type == Types::RECTANGLE)
            {
                esat::Vec2 *tvertex = (esat::Vec2*) malloc(4*sizeof(esat::Vec2));

                *(tvertex + 0) = (figuresData + i)->coordenate;
                *(tvertex + 1) = {(figuresData + i)->coordenate.x + size, (figuresData + i)->coordenate.y};
                *(tvertex + 2) = {(figuresData + i)->coordenate.x + size, (figuresData + i)->coordenate.y + size};
                *(tvertex + 3) = {(figuresData + i)->coordenate.x, (figuresData + i)->coordenate.y + size};

                esat::DrawSetFillColor((figuresData + i)->color.R, (figuresData + i)->color.G, (figuresData + i)->color.B, 255);

                esat::DrawSolidPath(&tvertex->x, 4);
                free(tvertex);

            } else {
                esat::Vec2 *tvertex = (esat::Vec2*) malloc(3*sizeof(esat::Vec2));

                *(tvertex + 0) = (figuresData+i)->coordenate;
                *(tvertex + 1) = {(figuresData+i)->coordenate.x + size, (figuresData+i)->coordenate.y};
                *(tvertex + 2) = {(figuresData+i)->coordenate.x + size, (figuresData+i)->coordenate.y + size};

                esat::DrawSetFillColor((figuresData+i)->color.R, (figuresData+i)->color.G, (figuresData+i)->color.B, 255);

                esat::DrawSolidPath(&tvertex->x, 3);
                free(tvertex);

            }
        }
    }

}

void Spawn(Types type) {
    float positionX = (float) esat::MousePositionX();
    float positionY = (float) esat::MousePositionY();

    Color colorFigure = {rand()%255, rand()%255, rand()%255};

    TFigures figure = {{positionX, positionY}, colorFigure, type};

    figuresData = (TFigures*) realloc(figuresData, (numberFigures + 1)*sizeof(TFigures));

    *(figuresData + numberFigures) = figure;

    if ((figuresData+numberFigures)->type == Types::RECTANGLE)
    {
        esat::Vec2 *tvertex = (esat::Vec2*) malloc(4*sizeof(esat::Vec2));

        *(tvertex + 0) = (figuresData + numberFigures)->coordenate;
        *(tvertex + 1) = {(figuresData + numberFigures)->coordenate.x + size, (figuresData + numberFigures)->coordenate.y};
        *(tvertex + 2) = {(figuresData + numberFigures)->coordenate.x + size, (figuresData + numberFigures)->coordenate.y + size};
        *(tvertex + 3) = {(figuresData + numberFigures)->coordenate.x, (figuresData + numberFigures)->coordenate.y + size};

        esat::DrawSetFillColor((figuresData+numberFigures)->color.R, (figuresData+numberFigures)->color.G, (figuresData+numberFigures)->color.B, 255);

        esat::DrawSolidPath(&tvertex->x, 4);
        free(tvertex);

    } else {
        esat::Vec2 *tvertex = (esat::Vec2*) malloc(3*sizeof(esat::Vec2));

        *(tvertex + 0) = (figuresData + numberFigures)->coordenate;
        *(tvertex + 1) = {(figuresData + numberFigures)->coordenate.x + size, (figuresData + numberFigures)->coordenate.y};
        *(tvertex + 2) = {(figuresData + numberFigures)->coordenate.x + size, (figuresData + numberFigures)->coordenate.y + size};

        esat::DrawSetFillColor((figuresData + numberFigures)->color.R, (figuresData + numberFigures)->color.G, (figuresData + numberFigures)->color.B, 255);

        esat::DrawSolidPath(&tvertex->x, 3);
        free(tvertex);

    }
    
    numberFigures++;
}

void MoveLeft() {
    for (int i = 0; i < numberFigures; i++)
    {   
        (figuresData + i)->coordenate.x -= 2;
    }
    
}

void MoveRight() {
    for (int i = 0; i < numberFigures; i++)
    {   
        (figuresData + i)->coordenate.x += 2;
    }
}

void ControlsManage() {

    if (esat::MouseButtonDown(0)) {
        Spawn(Types::RECTANGLE);
    }

    if (esat::MouseButtonDown(1)) {
        Spawn(Types::TRIANGLE);
    }

    if (esat::IsKeyPressed('Z')) {
        size += 2;
    }

    if (esat::IsKeyPressed('X')) {

        if (size - 2 > 4)
        {
            size -= 2;
        }
    }

    if (esat::IsSpecialKeyPressed(esat::kSpecialKey_Left))
    {
        MoveLeft();
    }

    if (esat::IsSpecialKeyPressed(esat::kSpecialKey_Right))
    {
        MoveRight();
    }
}

void AddMovement() {
    for (int i = 0; i < numberFigures; i++) {
        if ((figuresData + i)->coordenate.y + 2 > windowY)
        {
            (figuresData + i)->coordenate.y = 0 - size;
        }
        
        (figuresData + i)->coordenate.y += (figuresData + i)->speed;
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
        AddMovement();

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

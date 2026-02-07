#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

FILE *f;

struct BasicInfo {
    char name[15];
    char age[4];
    char job[30];
    char genre[1];
    char nacionality[30];
    char description[100];
    char personalityThings[100];
    char culture[30];
};

const int numPoolValues = 8;

struct CharacterPool {
    int constitution, strenght, charism, intelligence, education, power, dexterity, size;
};

struct Skills {
    int talkative, combat, hide, stealth, health, fatigue, jump, mana;
};

struct HP {
    int hitPoints;
    int majorWound;
    int dead;
};

struct Character {
    BasicInfo basicInfo;
    CharacterPool pool;
    Skills skills;
    int hitPoints;
};

Character character;

void GenerateSeed() {
    srand(time(NULL));
}

void PrepareFile() {
    f = fopen("files/model.dat", "r+b");

    // Add all features to send

    fclose(f);
}

void AskBasic() {

    printf("Need an identity. \n");

    printf("Name of your character: ");
    fgets(character.basicInfo.name, 15, stdin);

    printf("Age: ");
    fgets(character.basicInfo.age, 4, stdin);

    printf("Job of your character: ");
    fgets(character.basicInfo.job, 30, stdin);

    printf("Genre (H/M): ");
    fgets(character.basicInfo.genre, 1, stdin);

    printf("Nacionality: ");
    fgets(character.basicInfo.nacionality, 30, stdin);

    printf("Short description of your character: ");
    fgets(character.basicInfo.description, 100, stdin);

    printf("Personality things: ");
    fgets(character.basicInfo.personalityThings, 100, stdin);

    printf("Associated culture (Example: medieval knight, native refugee): ");
    fgets(character.basicInfo.culture, 30, stdin);
}

void CalculatePoolsFields(int pool, int num1, int num2, int num3) {

    switch (pool) {
        case 0:
            character.pool.constitution = num1 + num2 + num3;
        break;
        case 1:
            character.pool.strenght = num1 + num2 + num3;
        break;
        case 2:
            character.pool.charism = num1 + num2 + num3;
        break;
        case 3:
            character.pool.intelligence = num1 + num2 + 6;
        break;
        case 4:
            character.pool.size = num1 + num2 + 6;
        break;
        case 5:
            character.pool.power = num1 + num2 + num3;
        break;
        case 6:
            character.pool.education = num1 + num2 + 6;
        break;
        case 7:
            character.pool.dexterity = num1 + num2 + num3;
        break;
    }
}

void printBasicInfo() {
    printf("Here it is your normal information: \n");
    printf("Name: %s", character.basicInfo.name);
    printf("Age: %s", character.basicInfo.age);
    printf("Job: %s", character.basicInfo.job);
    printf("Genre: %s", character.basicInfo.genre);
    printf("Nacionality: %s", character.basicInfo.nacionality);
    printf("Description: %s", character.basicInfo.description);
    printf("Personality things: %s", character.basicInfo.personalityThings);
    printf("Culture: %s", character.basicInfo.culture);
    printf("\n");
}

void printPool() {
    printf("Here it is your pool of atributes: \n");
    printf("Constitution: %d \n", character.pool.constitution);
    printf("Strenght: %d \n", character.pool.strenght);
    printf("Charism: %d \n", character.pool.charism);
    printf("Intelligence: %d \n", character.pool.intelligence);
    printf("Power: %d \n", character.pool.power);
    printf("Size: %d \n", character.pool.size);
    printf("Dexterity: %d \n", character.pool.dexterity);
    printf("Education: %d \n \n", character.pool.education);
}

void printHP() {
    printf("Here it is your information about Hit Points: \n");
    printf("Hit points: %s", character.HP.hitPoints);
    printf("Major wound: %s", character.HP.majorWound);
    printf("Dead: %s", character.HP.dead);
    printf("\n");
}

void AskCharacterPool() {
    GenerateSeed();

    printf("We are gonna use 'dados' to calcule your values... \n");

    for (int i = 0; i < numPoolValues; i++) {
        int num1 = rand()%5 + 1, num2 = rand()%5 + 1, num3 = rand()%5 + 1;

        CalculatePoolsFields(i, num1, num2, num3);
    }

    character.HP.hitPoints = (character.constitution + character.size) / 10;
    character.HP.majorWound = character.HP.hitPoints / 2;
    character.HP.dead = character.HP.hitPoints * (-1);

    char response;
    printf("End, do you want to see it (Y/n)?");
    scanf("%c", &response);
    printf("\n");

    if (response == 'Y') {
        printPool();
    }
}

void AskSkills() {

}

void WhatSee() {
    
    int option;

    printf("1 -- See basic information \n");
    printf("2 -- Characteristics \n");
    printf("3 -- Hit points \n");
    printf("Option? ");
    scanf("%d", &option);
    printf("\n \n");

    switch (option) {
        case 1:
            printBasicInfo();
        break;
        case 2:
            printPool();
        break;
        case 3:
            printHP();
        break;
    }
}

void AskModifiers() {

}

void DeleteCharacter() {

}

void ValidateOption(int option) {
    
    switch (option) {
        case 1:
            WhatSee();
        break;
        case 2:
            AskModifiers();
        break;
        case 3:
            DeleteCharacter();
        break;
    }
}

void AskWhatToDo() {
    
    int option;

    printf("We have a preliminar version, what do you want to do? \n");
    printf("1 -- Check model \n");
    printf("2 -- Modify information \n");
    printf("3 -- Delete character \n");
    printf("4 -- Exit... \n");
    printf("Option ? ");
    scanf("%d", &option);

    ValidateOption(option);

    if (option >= 1 && option <= 3) {

        AskWhatToDo();
    }
}

int main() {

    // Call all feature to fix
    AskBasic();
    AskCharacterPool();
    AskSkills();

    AskWhatToDo();


    return 0;
}
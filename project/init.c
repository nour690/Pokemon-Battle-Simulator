#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

Type NoneType;
void initializeTypes(Type Types[]){
    FILE* file = fopen("types.txt","r");
    if (file == NULL) {
        printf("coudn't open types.txt file");
        exit(1);
    }
      //read the 18 real types from file
    for (int i = 0; i < 18; i++) {
        //reading lines without numbers at the end
        if (fscanf(file, "%s", Types[i].name) != 1) {
            printf("couldn't read type name from types.txt\n");
            exit(1);
        }
        //18 lines: defender type + multiplier 
        for (int j = 0; j < 18; j++) {
            if (fscanf(file, "%s %lf", Types[i].effects[j].defName,&Types[i].effects[j].multiplier) != 2){
                printf("error reading effect data from types.txt\n");
                exit(1);
            }
            strcpy(Types[i].effects[j].atkName, Types[i].name);
        }
        // add the 19th effect None
            strcpy(Types[i].effects[18].atkName, Types[i].name);
            strcpy(Types[i].effects[18].defName, "None");
            Types[i].effects[18].multiplier = 1.0;
    }
    fclose(file);
    //building the nonetype
    strcpy(NoneType.name, "None");
    for(int j=0; j < 18; j++){
        strcpy(NoneType.effects[j].atkName, "None");
        strcpy(NoneType.effects[j].defName, Types[j].name);
        NoneType.effects[j].multiplier = 1.0;
    }
    
    //effect None itself
    strcpy(NoneType.effects[18].atkName, "None");
    strcpy(NoneType.effects[18].defName, "None");
    NoneType.effects[18].multiplier = 1.0;
}

void initializeMoves(Move Moves[], Type Types[]){
    FILE *file= fopen("moves.txt","r");
    if (file == NULL){
        printf("couldn't open moves.txt file");
        exit(1);
    }
    for (int i = 0; i < 486; i++) {
        char moveName[50];
        char typeName[50];
        char category[50];
        char powerString[50];

        if (fscanf(file, "%s %s %s %s", moveName, typeName, category, powerString) != 4) {
            printf("error reading moves.txt line %d\n", i + 1);
            exit(1);
        }

        strcpy(Moves[i].name, moveName);
        //find a Type by name in Types[]
        int found = 0;
        for (int j = 0; j < 18; j++) {
            if (strcmp(Types[j].name, typeName) == 0) {
                Moves[i].type = Types[j]; 
                found=1;
                break;
            }
        }
        if(!found){ 
                printf("type not found for move %s typeName = [%s]\n", moveName, typeName); 
                exit(1);
            }
        if (strcmp(category, "physical") == 0) {
            Moves[i].category = PHYSICAL;
        } else if (strcmp(category, "special") == 0) {
            Moves[i].category = SPECIAL;
        }
        Moves[i].power = atoi(powerString);
    }
    fclose(file);
}

//name, type1, type2, maxHP, attack, defense, spAtk, spDef and speed
void initializePokemons(Pokemon Pokemons[],Type Types[], Move Moves[]){
    FILE *file = fopen("pokemon.txt","r");
    if(file == NULL){
        printf("couldn't open pokemon.txt file");
        exit(1);
    }
    for (int i = 0; i < 1015; i++) {
        char name[50];
        char type1Name[50];
        char type2Name[50];
        int maxHP, attack, defense, spAtk, spDef, speed;

        if(fscanf(file,"%s %s %s %d %d %d %d %d %d", name, type1Name, type2Name, &maxHP, &attack, &defense, &spAtk, &spDef, &speed) != 9){
            printf("Error reading pokemon.txt line %d\n", i);
            fclose(file);
            exit(1);
        }
        strcpy(Pokemons[i].name, name);
        Pokemons[i].maxHP = maxHP;
        Pokemons[i].currentHP = maxHP;
        Pokemons[i].attack = attack;
        Pokemons[i].defense = defense;
        Pokemons[i].spAtk = spAtk;
        Pokemons[i].spDef = spDef;
        Pokemons[i].speed = speed;
        //type 1
        for (int j = 0; j < 18; j++) {
                if (strcmp(Types[j].name, type1Name) == 0) {
                    Pokemons[i].types[0] = Types[j];
                    break;
                }
        }    
        //type 2
        if (strcmp(type2Name, "-") == 0) {
                Pokemons[i].types[1] = NoneType;
        } else {
            int found2 = 0;
            for (int j = 0; j < 18; j++) {
                if (strcmp(Types[j].name, type2Name) == 0) {
                    Pokemons[i].types[1] = Types[j];
                    found2 = 1;
                    break;
                }
            }
            if (!found2) {
                printf("Pokemon %s has unknown type2 [%s]\n", name, type2Name);
                exit(1);
            }
        }
        //assign 4 unique random moves
        for (int j = 0; j < 4; j++) {
            int random;
            int k;
            while (1) {
                random = rand() % 486;
                for (k = 0; k < j; k++) {
                    if (strcmp(Pokemons[i].moves[k].name, Moves[random].name) == 0) {
                        break;
                    }
                }
                if (k == j) {
                    break;   //valid move found 
                }
            }
            Pokemons[i].moves[j] = Moves[random];  //copy move struct
        }
    }
    fclose(file);
}
void initialize(Type Types[], Move Moves[], Pokemon Pokemons[], Player *p1, Player *p2){
    srand(time(NULL));
    initializeTypes(Types);
    initializeMoves(Moves, Types);
    initializePokemons(Pokemons, Types, Moves); 
    strcpy(p1->name, "player 1");
    strcpy(p2->name, "player 2");
    //pick 6 random pokemon for each player 
    for (int i = 0; i < 6; i++) {
        int idx1, idx2;
        int k;
        while (1) {
            idx1 = rand() % 1015;
            for (k = 0; k < i; k++) {
                if (strcmp(p1->Pokemons[k].name, Pokemons[idx1].name) == 0) {
                break; //duplicate found
                }
            }
            if (k == i) { //no duplicate found
                break;
            }
        }
        p1->Pokemons[i] = Pokemons[idx1];
        p1->Pokemons[i].currentHP = p1->Pokemons[i].maxHP;
        while (1) {
            idx2 = rand() % 1015;
            for (k = 0; k < i; k++) {
                if (strcmp(p2->Pokemons[k].name, Pokemons[idx2].name) == 0) {
                    break; //duplicate found
                }
            }
            if (k == i) {
                break; //no duplicate found
            }
        }
        p2->Pokemons[i] = Pokemons[idx2];
        p2->Pokemons[i].currentHP = p2->Pokemons[i].maxHP;
    }
    p1->currentIndex = 0;
    p2->currentIndex = 0;
    printf(" %s will start with %s\n", p1->name, p1->Pokemons[p1->currentIndex].name);
    printf(" %s will start with %s\n", p2->name, p2->Pokemons[p2->currentIndex].name);
}
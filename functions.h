//
// Created by Вадим корепанов on 05.12.17.
//

#ifndef SB1_FUNCTIONS_H
#define SB1_FUNCTIONS_H

#define DESTROYED  2
#define HIT 3
#define SHIPHERE 1
#define MISS  -1
#define FORBIDDEN 8
#define EMPTY 0
#define OUTOFRANGE -1
#define DOWN 0
#define UP 1
#define RIGHT 2
#define LEFT 3
#define maxLength 4
#define YES 1
#define NO 0
#define WAYS 4


int compfield[10][10], usr_field[10][10], visible_field[10][10];
int option;
_Bool isRightDirection, isChosen, isCorrectInput, isMoveEnd;
int xy_used[10][10];
_Bool options[4];
int x, y, x_hit, y_hit;


struct ship {
    short size;
    _Bool orientation; //1 - horizontal, 0 - vertical
    short x1;
    short y1;
} ships[10];



int isCellBad(int x, int y, int field[10][10]);

void output(int field[10][10], int field1[10][10]);

void forbidden_territory(int x1, int y1, int x2, int y2, int compfield[10][10]);

void fillin(struct ship regular_ship);

void initialization();

void cellChoice();

void directionChoice(int isOk, int i);

void inputXY();

int killed(int field[10][10], int x, int y, int field2[10][10]);

int cellStatus(int field[10][10], int x, int y);

void userHit(int *cnt, int *usr_points);

void userMiss();

void compHit(int *isMoveFirst, int *comp_points);

void compMiss();


#endif //SB1_FUNCTIONS_H

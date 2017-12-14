//
// Created by Вадим корепанов on 05.12.17.
//
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"

#define destroyed  2
#define hit 3
#define shipHere 1
#define miss  -1
#define forbidden 8



void deadSheep(int field[10][10]) {                                                                                     // Изменяет состояние из "Ранен" в "Убит"
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++) {
            if (field[i][j] == hit) field[i][j] = destroyed;
        }

}


int isCellOk(int x, int y, int field[10][10]) {                                                                         // Проверяет, нет ли вокруг заданной клетки уничтоженного корабля
    if (x - 1 >= 0) {
        if (field[x - 1][y] == destroyed) return 1;
        if ((field[x - 1][y - 1] == destroyed && y - 1 >= 0) || (field[x][y - 1] == destroyed && y - 1 >= 0)) return 1;
        if ((field[x - 1][y + 1] == destroyed && y + 1 <= 9) || (field[x][y + 1] == destroyed && y + 1 <= 9)) return 1;
    }
    if (x + 1 <= 9) {
        if (field[x + 1][y] == destroyed) return 1;
        if ((field[x + 1][y - 1] == destroyed && y - 1 >= 0) || (field[x][y - 1] == destroyed && y - 1 >= 0)) return 1;
        if ((field[x + 1][y + 1] == destroyed && y + 1 <= 9) || (field[x][y + 1] == destroyed && y + 1 <= 9)) return 1;
    }
    return 0;
}


void output(int field[10][10], int field1[10][10]) {                                                                    // Вывод 2-х полей с рамками
    printf("  ");
    for (int i = 0; i < 10; i++)
        printf("%2d ", i);
    printf("\t\t\t  ");
    for (int i = 0; i < 10; i++)
        printf("%2d ", i);
    printf("\n");
    for (int i = 0; i < 10; i++)
        printf("___");
    printf("_");
    printf("\t\t\t\t");
    for (int i = 0; i < 10; i++)
        printf("___");
    printf("_");

    printf("\n");
    for (int i = 0; i < 10; ++i) {
        printf("%d|", i);
        for (int j = 0; j < 10; ++j)
            printf("%2d ", field[i][j]);

        printf("\t\t\t");

        printf("%d|", i);
        for (int j = 0; j < 10; ++j)
            printf("%2d ", field1[i][j]);
        printf("\n");
    }
}

void forbidden_territory(int x1, int y1, int x2, int y2, int compfield[10][10]) {                                       // Делает территорию вокруг поставленного корабля недоступной для расстановки на нее других кораблей
    if (x2 > x1) {
        if (x1 - 1 >= 0) compfield[x1 - 1][y1] = forbidden;
        if (x1 - 1 >= 0 && y1 - 1 >= 0) compfield[x1 - 1][y1 - 1] = forbidden;
        if (x1 - 1 >= 0 && y1 + 1 <= 9) compfield[x1 - 1][y1 + 1] = forbidden;

        if (x2 + 1 <= 9) compfield[x2 + 1][y1] = forbidden;
        if (x2 + 1 <= 9 && y1 - 1 >= 0) compfield[x2 + 1][y1 - 1] = forbidden;
        if (x2 + 1 <= 9 && y1 + 1 <= 9) compfield[x2 + 1][y1 + 1] = forbidden;

        for (int i = x1; i <= x2; ++i) {
            if (y1 + 1 <= 9) compfield[i][y1 + 1] = forbidden;
            if (y1 - 1 >= 0) compfield[i][y1 - 1] = forbidden;
        }

    } else {
        if (y1 - 1 >= 0) compfield[x1][y1 - 1] = forbidden;
        if (x1 - 1 >= 0 && y1 - 1 >= 0) compfield[x1 - 1][y1 - 1] = forbidden;
        if (y1 - 1 >= 0 && x1 + 1 <= 9) compfield[x1 + 1][y1 - 1] = forbidden;

        if (y2 + 1 <= 9) compfield[x1][y2 + 1] = forbidden;
        if (y2 + 1 <= 9 && x1 - 1 >= 0) compfield[x1 - 1][y2 + 1] = forbidden;
        if (y2 + 1 <= 9 && x1 + 1 <= 9) compfield[x1 + 1][y2 + 1] = forbidden;

        for (int i = y1; i <= y2; ++i) {
            if (x1 + 1 <= 9) compfield[x1 + 1][i] = forbidden;
            if (x1 - 1 >= 0) compfield[x1 - 1][i] = forbidden;
        }

    }

}

void fillin(struct ship regular_ship) {                                                                                 // Рандомная расстановка корабля компьютером
    do {
        flag = 0;
        regular_ship.x1 = rand() % 10;
        regular_ship.y1 = rand() % 10;
        regular_ship.orientation = rand() % 2;
        for (int i = regular_ship.x1; i <= regular_ship.x1 + (regular_ship.orientation) * (regular_ship.size - 1); ++i)
            for (int j = regular_ship.y1;
                 j <= regular_ship.y1 + ((regular_ship.orientation + 1) % 2) * (regular_ship.size - 1); ++j) {
                if ((compfield[i][j] == shipHere) || (compfield[i][j] == forbidden) ||
                    (regular_ship.x1 + (regular_ship.orientation) * (regular_ship.size) >= 10) ||
                    (regular_ship.y1 + ((regular_ship.orientation + 1) % 2) * (regular_ship.size) >= 10))
                    flag = 1;
            }
    } while (flag == 1);
    for (int i = regular_ship.x1; i <= regular_ship.x1 + (regular_ship.orientation) * (regular_ship.size - 1); ++i)
        for (int j = regular_ship.y1;
             j <= regular_ship.y1 + ((regular_ship.orientation + 1) % 2) * (regular_ship.size - 1); ++j) {
            compfield[i][j] = shipHere;
        }
    forbidden_territory(regular_ship.x1, regular_ship.y1,
                        regular_ship.x1 + (regular_ship.orientation) * (regular_ship.size - 1),
                        regular_ship.y1 + ((regular_ship.orientation + 1) % 2) * (regular_ship.size - 1), compfield);
}


void initialization() {
    struct ship ship4 = {4, 0, 0, 0};
    struct ship ship31 = {3, 0, 0, 0};
    struct ship ship32 = {3, 0, 0, 0};
    struct ship ship21 = {2, 0, 0, 0};
    struct ship ship22 = {2, 0, 0, 0};
    struct ship ship23 = {2, 0, 0, 0};
    struct ship ship11 = {1, 0, 0, 0};
    struct ship ship12 = {1, 0, 0, 0};
    struct ship ship13 = {1, 0, 0, 0};
    struct ship ship14 = {1, 0, 0, 0};

    printf("Добро пожаловать в игру Морской Бой!\n\n");
    printf("Условные обозначения:\n0 - ничего/неизвестно, "
                   "3 - попадание по кораблю/части корабля, 2 - корабль уничтожен, -1 - "
                   "промах\n\n");
    printf("Расставьте корабли (введите матрицу 10 х 10; 1 - корабль/часть корабля, 0 - пустая клетка) \n");

    fillin(ship4);
    fillin(ship31);
    fillin(ship32);
    fillin(ship21);
    fillin(ship22);
    fillin(ship23);
    fillin(ship11);
    fillin(ship12);
    fillin(ship13);
    fillin(ship14);
}

void cellChoice() {
    do {                                                                                                            // Переход в этот цикл, если компьютер не попал
        marker = 0;
        x = rand() % 10;
        y = rand() % 10;
        if ((xy_array[x][y] == 0) && (isCellOk(x, y, usr_field) == 0)) marker = 1;
    } while (marker == 0);
}


void directionChoice(int isOk, int i){
    do {
        isOk = 0;
        if (flag2 == 0) option = rand() % 4;
        switch (option) {
            case 0: {
                if (x_hit + i <= 9) {
                    x = x_hit + i;
                    y = y_hit;
                    break;
                } else {
                    i = 1;
                    option++;
                    x = x_hit - i;
                    y = y_hit;
                    break;
                }
            }
            case 1: {
                if (x_hit - i >= 0) {
                    x = x_hit - i;
                    y = y_hit;
                    break;
                } else {
                    i = 1;
                    option--;
                    x = x_hit + i;
                    y = y_hit;
                    break;
                }
            }
            case 2: {
                if (y_hit + i <= 9) {
                    y = y_hit + i;
                    x = x_hit;
                    break;
                } else {
                    i = 1;
                    option++;
                    y = y_hit - i;
                    x = x_hit;
                    break;
                }
            }
            case 3: {
                if (y_hit - i >= 0) {
                    y = y_hit - i;
                    x = x_hit;
                    break;
                } else {
                    i = 1;
                    option--;
                    y = y_hit + i;
                    x = x_hit;
                    break;
                }
            }
        }

        if (xy_array[x][y] == 0 && isCellOk(x, y, usr_field) == 0) {
            isOk = 1;
        }
        if (flag2 == 1 && (xy_array[x][y] != 0 || isCellOk(x, y, usr_field) != 0)) {
            i = 1;
            if (option % 2 == 0) option++;
            else option--;
        }

    } while (options[option] == 1 || isOk == 0);

}

void inputXY() {
    do {
        flag3 = 0;
        printf("Ваш ход! Введите 2 числа: координату по Y и координату по X соответственно\n");
        scanf("%d %d", &x, &y);
        if (x > 9 || x < 0 || y < 0 || y > 9) {
            printf("Неверный ввод\n");
            continue;
        }
        flag3 = 1;
    }  while (flag3 == 0);

};

int killed(int field[10][10], int x, int y) {
    if ((field[x + 1][y] != shipHere || x + 1 > 9) && (field[x - 1][y] != shipHere || x - 1 < 0) &&
        (field[x][y + 1] != shipHere || y + 1 > 9) &&
        (field[x][y - 1] != shipHere || y - 1 < 0)) {
        isFirst = 1;
        if (field[x - 1][y] == hit) {
            isFirst = 0;
            if (field[x - 2][y] == hit) {
                if (field[x - 3][y] != shipHere || x - 3 < 0) return 1;
            } else if (field[x - 2][y] != shipHere || x - 2 < 0) return 1;
        }

        if (field[x + 1][y] == hit) {
            isFirst = 0;
            if (field[x + 2][y] == hit) {
                if (field[x + 3][y] != shipHere || x + 3 > 9) return 1;
            } else if (field[x + 2][y] != shipHere || x + 2 > 9) return 1;
        }

        if (field[x][y - 1] == hit) {
            isFirst = 0;
            if (field[x][y - 2] == hit) {
                if (field[x][y - 3] != shipHere || y - 3 < 0) return 1;
            } else if (field[x][y - 2] != shipHere || y - 2 < 0) return 1;
        }

        if (field[x][y + 1] == hit) {
            isFirst = 0;
            if (field[x][y + 2] == hit) {
                if (field[x][y + 3] != shipHere || y + 3 > 9) return 1;
            } else if (field[x][y + 2] != shipHere || y + 2 > 9) return 1;
        }
        if (isFirst) return 1;
    }
    return 0;
}
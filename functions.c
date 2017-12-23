//
// Created by Вадим корепанов on 05.12.17.
//
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"


void deadSheep(
        int field[10][10]) {                                                                                     // Изменяет состояние из "Ранен" в "Убит"
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++) {
            if (field[i][j] == HIT) field[i][j] = DESTROYED;
        }

}

int cellStatus(int field[10][10], int x, int y) {                                                                       //Статус данной клетки
    if (x < 0 || x > 9 || y < 0 || y > 9) return OUTOFRANGE;
    if (field[x][y] == SHIPHERE) return SHIPHERE;
    return EMPTY;

}

int isCellOk(int x, int y,
             int field[10][10]) {                                                                         // Проверяет, нет ли вокруг заданной клетки уничтоженного корабля
    for (int j = x - 1; j <= x + 1; j++) {
        for (int l = y - 1; l <= y + 1; l++)
            if (cellStatus(compfield, j, l) != OUTOFRANGE && field[j][l] == DESTROYED) return 1;
    }
    return 0;
}

void output(int field[10][10],
            int field1[10][10]) {                                                                    // Вывод 2-х полей с рамками
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

void forbidden_territory(int x1, int y1, int x2, int y2,
                         int compfield[10][10]) {                                       // Делает территорию вокруг поставленного корабля недоступной для расстановки на нее других кораблей
    if (x2 > x1) {
        for (int i = x1; i <= x2; i++) {
            for (int j = i - 1; j <= i + 1; j++) {
                for (int l = y1 - 1; l <= y1 + 1; l++)
                    if (cellStatus(compfield, j, l) == EMPTY) compfield[j][l] = FORBIDDEN;
            }
        }
    } else
        for (int i = y1; i <= y2; i++) {
            for (int j = i - 1; j <= i + 1; j++) {
                for (int l = x1 - 1; l <= x1 + 1; l++)
                    if (cellStatus(compfield, l, j) == 0) compfield[l][j] = FORBIDDEN;
            }
        }
}


void
fillin(struct ship regular_ship) {                                                                                 // Рандомная расстановка корабля компьютером
    do {
        isChosen = 0;
        regular_ship.x1 = rand() % 10;
        regular_ship.y1 = rand() % 10;
        regular_ship.orientation = rand() % 2;
        for (int i = regular_ship.x1; i <= regular_ship.x1 + (regular_ship.orientation) * (regular_ship.size - 1); ++i)
            for (int j = regular_ship.y1;
                 j <= regular_ship.y1 + ((regular_ship.orientation + 1) % 2) * (regular_ship.size - 1); ++j) {
                if ((compfield[i][j] == SHIPHERE) || (compfield[i][j] == FORBIDDEN) ||
                    (regular_ship.x1 + (regular_ship.orientation) * (regular_ship.size) >= 10) ||
                    (regular_ship.y1 + ((regular_ship.orientation + 1) % 2) * (regular_ship.size) >= 10))
                    isChosen = 1;
            }
    } while (isChosen == 1);
    for (int i = regular_ship.x1; i <= regular_ship.x1 + (regular_ship.orientation) * (regular_ship.size - 1); ++i)
        for (int j = regular_ship.y1;
             j <= regular_ship.y1 + ((regular_ship.orientation + 1) % 2) * (regular_ship.size - 1); ++j) {
            compfield[i][j] = SHIPHERE;
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
        isChosen = 0;
        x = rand() % 10;
        y = rand() % 10;
        if ((xy_used[x][y] == 0) && (isCellOk(x, y, usr_field) == 0)) isChosen = 1;
    } while (isChosen == 0);
}


void directionChoice(int isOk, int i) {
    do {
        isOk = 0;
        if (isRightDirection == 0) option = rand() % 4;
        switch (option) {
            case DOWN: {
                if (x_hit + i <= 9) {x = x_hit + i; y = y_hit; break; }
                else {i = 1; option++; x = x_hit - i; y = y_hit; break;}
            }
            case UP: {
                if (x_hit - i >= 0) {x = x_hit - i; y = y_hit; break;}
                else {i = 1; option--; x = x_hit + i; y = y_hit; break;}
            }
            case RIGHT: {
                if (y_hit + i <= 9) {y = y_hit + i; x = x_hit; break;}
                else {i = 1; option++; y = y_hit - i; x = x_hit; break;}
            }
            case LEFT: {
                if (y_hit - i >= 0) {y = y_hit - i; x = x_hit; break;}
                else {i = 1; option--; y = y_hit + i; x = x_hit; break;}
            }
        }
        if (xy_used[x][y] == 0 && isCellOk(x, y, usr_field) == 0)
            isOk = 1;
        if (isRightDirection == 1 && (xy_used[x][y] != 0 || isCellOk(x, y, usr_field) != 0)) {
            i = 1;
            if (option % 2 == 0) option++;
            else option--;
        }
    } while (options[option] == 1 || isOk == 0);
}

void inputXY() {
    do {
        isCorrectInput = 0;
        printf("Ваш ход! Введите 2 числа: координату по Y и координату по X соответственно\n");
        scanf("%d %d", &x, &y);
        if (x > 9 || x < 0 || y < 0 || y > 9) {
            printf("Неверный ввод\n");
            continue;
        }
        isCorrectInput = 1;
    } while (isCorrectInput == 0);

};


int killed(int field[10][10], int x, int y, int field2[10][10]) {                                                       //Проверка на "уничтоженность"
    int xmin = x, xmax = x, ymin = y, ymax = y;
    for (; xmin > 0; xmin--) {
        if (field[xmin - 1][y] == SHIPHERE) return 0;
        if (field[xmin - 1][y] != HIT) break;
    }
    for (; ymin > 0; ymin--) {
        if (field[x][ymin - 1] == SHIPHERE) return 0;
        if (field[x][ymin - 1] != HIT) break;
    }
    for (; xmax < 9; xmax++) {
        if (field[xmax + 1][y] == SHIPHERE) return 0;
        if (field[xmax + 1][y] != HIT) break;
    }
    for (; ymax < 9; ymax++) {
        if (field[x][ymax + 1] == SHIPHERE) return 0;
        if (field[x][ymax + 1] != HIT) break;
    }

    for (int i = xmin; i <= xmax; i++) {                                                                                //Из "ранен" в "убит"
        for (int j = ymin; j <= ymax; j++) {
            field2[i][j] = DESTROYED;
        }
    }
    return 1;
}

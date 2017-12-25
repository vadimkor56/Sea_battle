//
// Created by Вадим корепанов on 05.12.17.
//
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"

int cellStatus(int field[10][10], int x, int y) {                                                                       //Статус данной клетки
    if (x < 0 || x > 9 || y < 0 || y > 9) return OUTOFRANGE;
    if (field[x][y] == SHIPHERE) return SHIPHERE;
    return EMPTY;

}

int isCellBad(int x, int y,
             int field[10][10]) {                                                                         // Проверяет, нет ли вокруг заданной клетки уничтоженного корабля
    for (int j = x - 1; j <= x + 1; j++) {
        for (int l = y - 1; l <= y + 1; l++)
            if (cellStatus(compfield, j, l) != OUTOFRANGE && field[j][l] == DESTROYED) return YES;
    }
    return NO;
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
                    if (cellStatus(compfield, l, j) == EMPTY) compfield[l][j] = FORBIDDEN;
            }
        }
}


void
fillin(struct ship regular_ship) {                                                                                 // Рандомная расстановка корабля компьютером
    do {
        isChosen = YES;
        regular_ship.x1 = rand() % 10;
        regular_ship.y1 = rand() % 10;
        regular_ship.orientation = rand() % 2;
        for (int i = regular_ship.x1; i <= regular_ship.x1 + (regular_ship.orientation) * (regular_ship.size - 1); ++i)
            for (int j = regular_ship.y1;
                 j <= regular_ship.y1 + ((regular_ship.orientation + 1) % 2) * (regular_ship.size - 1); ++j) {
                if ((compfield[i][j] == SHIPHERE) || (compfield[i][j] == FORBIDDEN) ||
                    (regular_ship.x1 + (regular_ship.orientation) * (regular_ship.size) >= 10) ||
                    (regular_ship.y1 + ((regular_ship.orientation + 1) % 2) * (regular_ship.size) >= 10))
                    isChosen = NO;
            }
    } while (isChosen == NO);
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

    printf("Добро пожаловать в игру Морской Бой!\n\n");
    printf("Условные обозначения:\n0 - ничего/неизвестно, "
                   "3 - попадание по кораблю/части корабля, 2 - корабль уничтожен, -1 - "
                   "промах\n\n");
    printf("Расставьте корабли (введите матрицу 10 х 10; 1 - корабль/часть корабля, 0 - пустая клетка) \n");

    int maxAmount = 0;
    for (short length = maxLength; length >= 1; length--) {
        maxAmount++;
        for (short amount = 1; amount <= maxAmount; amount++) {
            ships[length + amount].size = length;
            fillin(ships[length + amount]);
        }
    }
}

void cellChoice() {
    do {                                                                                                            // Переход в этот цикл, если компьютер не попал
        isChosen = NO;
        x = rand() % 10;
        y = rand() % 10;
        if ((xy_used[x][y] == NO) && (isCellBad(x, y, usr_field) == NO)) isChosen = YES;
    } while (isChosen == NO);
}


void directionChoice(int isOk, int i) {
    do {
        isOk = NO;
        if (isRightDirection == NO) option = rand() % WAYS;
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
        if (xy_used[x][y] == NO && isCellBad(x, y, usr_field) == NO)
            isOk = YES;
        if (isRightDirection == YES && (xy_used[x][y] != NO || isCellBad(x, y, usr_field) != NO)) {
            i = 1;
            if (option % 2 == 0) option++;
            else option--;
        }
    } while (options[option] == 1 || isOk == NO);
}

void inputXY() {
    do {
        isCorrectInput = NO;
        printf("Ваш ход! Введите 2 числа: координату по Y и координату по X соответственно\n");
        scanf("%d %d", &x, &y);
        if (x > 9 || x < 0 || y < 0 || y > 9) {
            printf("Неверный ввод\n");
            continue;
        }
        isCorrectInput = YES;
    } while (isCorrectInput == NO);

};


int killed(int field[10][10], int x, int y, int field2[10][10]) {                                                       //Проверка на "уничтоженность"
    int xmin = x, xmax = x, ymin = y, ymax = y;
    for (; xmin > 0; xmin--) {
        if (field[xmin - 1][y] == SHIPHERE) return NO;
        if (field[xmin - 1][y] != HIT) break;
    }
    for (; ymin > 0; ymin--) {
        if (field[x][ymin - 1] == SHIPHERE) return NO;
        if (field[x][ymin - 1] != HIT) break;
    }
    for (; xmax < 9; xmax++) {
        if (field[xmax + 1][y] == SHIPHERE) return NO;
        if (field[xmax + 1][y] != HIT) break;
    }
    for (; ymax < 9; ymax++) {
        if (field[x][ymax + 1] == SHIPHERE) return NO;
        if (field[x][ymax + 1] != HIT) break;
    }

    for (int i = xmin; i <= xmax; i++) {                                                                                //Из "ранен" в "убит"
        for (int j = ymin; j <= ymax; j++) {
            field2[i][j] = DESTROYED;
        }
    }
    return YES;
}

void userHit(int *cnt, int *usr_points) {
    printf("Попали!\n");
    compfield[x][y] = HIT;
    visible_field[x][y] = HIT;

    if (killed(compfield, x, y, visible_field)) {
        (*cnt)++;
        printf("Вы уничтожили %d-й корабль противника!\n", *cnt);
    }

    printf("Видимое поле врага:\t\t\t\t\t\t\tВаше поле:\n");
    output(visible_field, usr_field);
    (*usr_points)++;
}

void userMiss() {
    isMoveEnd = YES;
    visible_field[x][y] = MISS;
    printf("Не повезло!\n");
}

void compHit(int *isMoveFirst, int *comp_points) {
    printf("Ход компьютера: %d %d\nОн попал!\n", x, y);
    usr_field[x][y] = HIT;
    *isMoveFirst = NO;

    if (killed(usr_field, x, y, usr_field)) {
        printf("Ваш корабль уничтожен!\n");
        *isMoveFirst = YES;
    }

    printf("Видимое поле врага:\t\t\t\t\t\t\t\tВаше поле:\n");
    output(visible_field, usr_field);

    (*comp_points)++;

}

void compMiss() {
    isMoveEnd = YES;
    usr_field[x][y] = MISS;
    printf("Ход компьютера: %d %d\nОн не попал!!\n", x, y);
    printf("Видимое поле врага:\t\t\t\t\t\t\tВаше поле:\n");
    output(visible_field, usr_field);
}

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"
#include <stdbool.h>

#define destroyed  2
#define hit 3
#define shipHere 1
#define miss  -1

int cnt = 0;
int comp_points = 0, usr_points = 0;
int i = 1;
int isOk = 0;
int main() {

    srand(time(NULL));



   initialization();

    for (int i = 0; i < 10; i++) {
        for (int k = 0; k < 10; k++)
            printf("%d ", compfield[i][k]);
        printf("\n");
    }

    for (int i = 0; i < 10; ++i)
        for (int k = 0; k < 10; ++k)
            scanf("%d", &usr_field[i][k]);
    i = 1;

    while (comp_points < 20 && usr_points < 20) {                                                                       // Главный цикл игрового процесса (пока кто-то не уничтожит все корабли противника)

        do {                                                                                                            // Серия ходов человека начинается
            flag = 0;
            inputXY();
            if (compfield[x][y] == shipHere) {
                printf("Попали!\n");
                compfield[x][y] = hit;
                visible_field[x][y] = hit;

                if (killed(compfield, x, y)) {
                    cnt++;
                    printf("Вы уничтожили %d-й корабль противника!\n", cnt);
                    deadSheep(visible_field);
                }

                printf("Видимое поле врага:\t\t\t\t\t\t\tВаше поле:\n");
                output(visible_field, usr_field);
                usr_points++;
            } else {
                flag = 1;
                visible_field[x][y] = miss;
                printf("Не повезло!\n");
            }
            if (usr_points >= 20) break;
        } while (flag == 0);                                                                                            // Серия ходов человека заканчивается

        if (usr_points >= 20) break;

        do {                                                                                                            // Серия ходов компьютера начинается
            flag = 0;
            if (flag1 == 1) {                                                                                           // Переход в этот цикл, если компьютер попал
                directionChoice(isOk, i);
                xy_array[x][y] = 1;
                i++;

                if (usr_field[x][y] == shipHere) {
                    printf("Ход компьютера: %d %d\nОн попал!!\n", x, y);
                    usr_field[x][y] = hit;
                    flag2 = 1;

                    if (killed(usr_field, x, y)) {
                        printf("Ваш корабль уничтожен!\n");
                        deadSheep(usr_field);
                        flag1 = 0;
                        i = 1;
                        for (int k = 0; k < 4; k++) options[k] = 0;
                    }

                    printf("Видимое поле врага:\t\t\t\t\t\t\tВаше поле:\n");
                    output(visible_field, usr_field);

                    comp_points++;

                } else {
                    i = 1;
                    flag = 1;
                    options[option] = 1;
                    usr_field[x][y] = miss;

                    printf("Ход компьютера: %d %d\nОн не попал!!\n", x, y);
                    if (flag2 == 1 && (option % 2 == 1)) {
                        option--;
                    }
                    if (flag2 == 1 && (option % 2 == 0)) {
                        option++;
                    }
                    printf("Видимое поле врага:\t\t\t\t\t\t\tВаше поле:\n");
                    output(visible_field, usr_field);
                }


            } else {                                                                                                            // Выходим из этого цикла при уничтожении корабля человека

                cellChoice();
                xy_array[x][y] = 1;

                if (usr_field[x][y] == shipHere) {
                    printf("Ход компьютера: %d %d\nОн попал!\n", x, y);
                    usr_field[x][y] = hit;
                    flag1 = 1;
                    flag2 = 0;
                    x_hit = x;
                    y_hit = y;

                    if (killed(usr_field, x, y)) {
                        printf("Ваш корабль уничтожен!\n");
                        deadSheep(usr_field);
                        flag1 = 0;
                    }

                    printf("Видимое поле врага:\t\t\t\t\t\t\t\tВаше поле:\n");
                    output(visible_field, usr_field);

                    comp_points++;
                } else {
                    flag = 1;
                    usr_field[x][y] = miss;
                    printf("Ход компьютера: %d %d\nОн не попал!\n", x, y);
                    printf("Видимое поле врага:\t\t\t\t\t\t\tВаше поле:\n");
                    output(visible_field, usr_field);
                }
            }                                                                                                                   // Выходим из этого цикла и переходит в цикл выше, если компьютер попал

            if (comp_points >= 20) break;
        } while (flag == 0);                                                                                            // Серия ходов компьютера заканчивается

        if (comp_points >= 20) break;

    }

    if (usr_points == 20)
        printf("Вы победили!!!");
    else
        printf("Очень жаль, Вы проиграли :(");
    return 0;
}
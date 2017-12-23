#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"
#include <stdbool.h>

int cnt = 0;
int comp_points = 0, usr_points = 0;
int i = 1;
int isOk = 0;
_Bool isMoveFirst = 1;

int main() {

    srand(time(NULL));

    initialization();

    for (int i = 0; i < 10; ++i)
        for (int k = 0; k < 10; ++k)
            scanf("%d", &usr_field[i][k]);
    i = 1;

    while (comp_points < 20 && usr_points < 20) {                                                                       // Главный цикл игрового процесса (пока кто-то не уничтожит все корабли противника)

        do {                                                                                                            // Серия ходов человека начинается
            isMoveEnd = 0;
            inputXY();
            if (compfield[x][y] == SHIPHERE) {
                printf("Попали!\n");
                compfield[x][y] = HIT;
                visible_field[x][y] = HIT;

                if (killed(compfield, x, y, visible_field)) {
                    cnt++;
                    printf("Вы уничтожили %d-й корабль противника!\n", cnt);
                }

                printf("Видимое поле врага:\t\t\t\t\t\t\tВаше поле:\n");
                output(visible_field, usr_field);
                usr_points++;
            } else {
                isMoveEnd = 1;
                visible_field[x][y] = MISS;
                printf("Не повезло!\n");
            }
            if (usr_points >= 20) break;
        } while (isMoveEnd == 0);                                                                                            // Серия ходов человека заканчивается

        if (usr_points >= 20) break;

        do {                                                                                                            // Серия ходов компьютера начинается
            isMoveEnd = 0;
            if (isMoveFirst == 1) {
                cellChoice();
                xy_used[x][y] = 1;

                if (usr_field[x][y] == SHIPHERE) {
                    printf("Ход компьютера: %d %d\nОн попал!\n", x, y);
                    usr_field[x][y] = HIT;
                    isMoveFirst = 0;
                    isRightDirection = 0;
                    x_hit = x;
                    y_hit = y;

                    if (killed(usr_field, x, y, usr_field)) {
                        printf("Ваш корабль уничтожен!\n");
                        isMoveFirst = 1;
                    }

                    printf("Видимое поле врага:\t\t\t\t\t\t\t\tВаше поле:\n");
                    output(visible_field, usr_field);

                    comp_points++;
                } else {
                    isMoveEnd = 1;
                    usr_field[x][y] = MISS;
                    printf("Ход компьютера: %d %d\nОн не попал!\n", x, y);
                    printf("Видимое поле врага:\t\t\t\t\t\t\tВаше поле:\n");
                    output(visible_field, usr_field);
                }


            } else {
                directionChoice(isOk, i);
                xy_used[x][y] = 1;
                i++;

                if (usr_field[x][y] == SHIPHERE) {
                    printf("Ход компьютера: %d %d\nОн попал!!\n", x, y);
                    usr_field[x][y] = HIT;
                    isRightDirection = 1;

                    if (killed(usr_field, x, y, usr_field)) {
                        printf("Ваш корабль уничтожен!\n");
                        isMoveFirst = 1;
                        i = 1;
                        for (int k = 0; k < 4; k++) options[k] = 0;
                    }

                    printf("Видимое поле врага:\t\t\t\t\t\t\tВаше поле:\n");
                    output(visible_field, usr_field);

                    comp_points++;

                } else {
                    i = 1;
                    isMoveEnd = 1;
                    options[option] = 1;
                    usr_field[x][y] = MISS;

                    printf("Ход компьютера: %d %d\nОн не попал!!\n", x, y);
                    if (isRightDirection == 1 && (option % 2 == 1)) {
                        option--;
                    }
                    if (isRightDirection == 1 && (option % 2 == 0)) {
                        option++;
                    }
                    printf("Видимое поле врага:\t\t\t\t\t\t\tВаше поле:\n");
                    output(visible_field, usr_field);
                }
            }

            if (comp_points >= 20) break;
        } while (isMoveEnd == 0);                                                                                            // Серия ходов компьютера заканчивается

        if (comp_points >= 20) break;

    }

    if (usr_points == 20)
        printf("Вы победили!!!");
    else
        printf("Очень жаль, Вы проиграли :(");
    return 0;
}

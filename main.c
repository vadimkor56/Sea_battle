#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"
#include <stdbool.h>

int cnt = 0;
int i = 1;
int isOk = NO;
int isMoveFirst = YES;
int comp_points = 0, usr_points = 0;

int main() {

    srand(time(NULL));

    initialization();

    for (int i = 0; i < 10; ++i) {
        for (int k = 0; k < 10; ++k)
            printf("%d ", compfield[i][k]);
        printf("\n");
    }

    for (int i = 0; i < 10; ++i)
        for (int k = 0; k < 10; ++k)
            scanf("%d", &usr_field[i][k]);
    i = 1;

    while (comp_points < 20 && usr_points < 20) {                                                                       // Главный цикл игрового процесса (пока кто-то не уничтожит все корабли противника)

        do {                                                                                                            // Серия ходов человека начинается
            isMoveEnd = NO;
            inputXY();
            if (compfield[x][y] == SHIPHERE)
                userHit(cnt, usr_points);
            else
               userMiss();
            if (usr_points >= 20) break;
        } while (isMoveEnd == NO);                                                                                            // Серия ходов человека заканчивается

        if (usr_points >= 20) break;

        do {                                                                                                            // Серия ходов компьютера начинается
            isMoveEnd = NO;
            if (isMoveFirst == YES) {
                cellChoice();
                xy_used[x][y] = YES;

                if (usr_field[x][y] == SHIPHERE) {
                    compHit(isMoveFirst, comp_points);
                    isRightDirection = NO;
                    x_hit = x;
                    y_hit = y;
                } else {
                    compMiss();
                }
            } else {
                directionChoice(isOk, i);
                xy_used[x][y] = YES;
                i++;
                if (usr_field[x][y] == SHIPHERE) {
                    compHit(isMoveFirst, comp_points);
                    isRightDirection = YES;

                    if (killed(usr_field, x, y, usr_field)) {
                        i = 1;
                        for (int k = 0; k < 4; k++) options[k] = 0;
                    }


                } else {
                    i = 1;
                    options[option] = 1;
                    compMiss();
                    if (isRightDirection == YES && (option % 2 == 1)) {
                        option--;
                    }
                    if (isRightDirection == YES && (option % 2 == 0)) {
                        option++;
                    }
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

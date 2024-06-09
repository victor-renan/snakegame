#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>

#define SIDE 10
#define RED "\x1b[31m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"

int random_num() {
    return rand() % SIDE;
}

void populate_fruit(int mapa[SIDE][SIDE], int *fruit[2]) {
    if (fruit[0] != NULL) {
        return;
    }

    int rand_row = random_num();
    int rand_col = random_num();

    if (mapa[rand_row][rand_col] != 1) {
        mapa[rand_row][rand_col] = 2;
        fruit[0] = &rand_row;
        fruit[1] = &rand_col;
    } else {
        populate_fruit(mapa, fruit);
    }
}

int swap_pos(int mapa[SIDE][SIDE], int pos[2], char direction) {
    if (direction ==  'C') {
        mapa[pos[0]][pos[1]] = 0;
        mapa[pos[0]][pos[1] + 1] = 1;
        pos[1] += 1;
    }
}

int main() {
    int mapa[SIDE][SIDE] = {
        {1,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
    };

    system("clear");

    int row = 0, col = 0, *fruit[2];
    int pos[2] = {0, 0};

    char direction = 'C';

    while (true) {
        populate_fruit(mapa, fruit);
        
        swap_pos(mapa, pos, direction);

        for (int i = 0; i < SIDE; i++) {
            for (int j = 0; j < SIDE; j++) {
                switch(mapa[i][j]) {
                    case 1:
                        printf(YELLOW "%d ", mapa[i][j]);
                        break;
                    case 2:
                        printf(RED "%d ", mapa[i][j]);
                        break;
                    default:
                        printf(BLUE "%d ", mapa[i][j]);
                        break;
                }
            }
            printf("\n");
        }
        
        usleep(200000);
        system("clear");
    }

    return 0;
}
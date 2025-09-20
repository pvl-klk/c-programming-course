#include <stdio.h>

int countLuckyTickets(void);

int main(void) {
    int numberOfLuckyTickets = countLuckyTickets();
    printf("Number of lucky tickets is %d\n", numberOfLuckyTickets);

    return 1;
}

int countLuckyTickets(void) {
    int result = 0;
    for (int i_1 = 0; i_1 <= 9; ++i_1) {
        for (int i_2 = 0; i_2 <= 9; ++i_2) {
            for (int i_3 = 0; i_3 <= 9; ++i_3) {
                for (int i_4 = 0; i_4 <= 9; ++i_4) {
                    for (int i_5 = 0; i_5 <= 9; ++i_5) {
                        for (int i_6 = 0; i_6 <= 9; ++i_6) {
                            int part_1 = i_1 + i_2 + i_3;
                            int part_2 = i_4 + i_5 + i_6;
                            if (part_1 == part_2) {
                                result += 1;
                            }
                        }
                    }
                }
            }
        }
    }
    return result;
}

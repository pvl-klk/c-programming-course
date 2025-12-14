unsigned int countLuckyTickets(void)
{
    unsigned int variants[28] = { 0 };
    for (int digit_1 = 0; digit_1 < 10; ++digit_1) {
        for (int digit_2 = 0; digit_2 < 10; ++digit_2) {
            for (int digit_3 = 0; digit_3 < 10; ++digit_3) {
                unsigned int amount = digit_1 + digit_2 + digit_3;
                variants[amount] += 1;
            }
        }
    }
    unsigned int total = 0;
    for (int index = 0; index < 28; ++index) {
        total += variants[index] * variants[index];
    }
    return total;
}

#include <stdio.h>
#include <string.h>

int main(void)
{
    const char* string = "1301020301010203";
    const char* substring = "01";

    const unsigned int stringLength = strlen(string);
    const unsigned int substringLength = strlen(substring);

    int counter = 0;
    for (int offset = 0; offset < stringLength - substringLength + 1; ++offset) {
        int flag = 1;
        for (int index = 0; index < substringLength; ++index) {
            if (string[index + offset] != substring[index]) {
                flag = 0;
                break;
            }
        }
        if (flag == 1) {
            ++counter;
        }
    }

    printf("The number of entries is %d\n", counter);

    return 0;
}

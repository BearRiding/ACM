#include <stdio.h>
#include <string>

std::string DecToBin(int dec) {
    std::string bin = "";
    do {
        bin += dec % 2;
        dec /= 2;
    } while (dec);

    return bin;
}

int BinToDec(int bin) {
    int dec = 0;
    int temp = 1;
    do {
        dec += temp * (bin % 10);
        bin = bin / 10;
        temp *= 2;
    } while (bin);

    return dec;
}

int main() {
    std::string bin = DecToBin(20);
    for (int i = bin.size() - 1; i >= 0; i--) {
        printf("%d", int(bin[i]));
    }

    int dec = BinToDec(101010);
    printf("\n%d\n", dec);
    return 0;
}
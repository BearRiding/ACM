#include <cmath>
#include <ctime>
#include <stdio.h>
#define maxn 10

int n, p[maxn], hashTable[maxn] = {false}, count = 0;

//进行了一些优化
void generateP_plus(int index) {
    if (index == n + 1) {
        for (int i = 1; i <= n; i++) {
            //            printf("%d", p[i]);
            count++;
        }
        //        printf("\n");
    }
    for (int x = 1; x <= n; x++) {
        if (!hashTable[x]) {
            bool flag = false;
            for (int pre = 1; pre < index; pre++) {
                if (fabs(index - pre) == fabs(p[pre] - x)) {
                    flag = true;
                }
            }
            if (!flag) {
                p[index] = x;
                hashTable[x] = true;
                generateP_plus(index + 1);
                hashTable[x] = false;
            }
        }
    }
}

void generateP(int index) {
    if (index == n + 1) {
        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++) {
                if (fabs(i - j) == fabs(p[i] - p[j])) {
                    return;
                }
            }
        }
        for (int i = 1; i <= n; i++) {
            //            printf("%d", p[i]);
            count++;
        }
        //        printf("\n");
    }
    for (int x = 1; x <= n; x++) {
        if (!hashTable[x]) {
            p[index] = x;
            hashTable[x] = true;
            generateP(index + 1);
            hashTable[x] = false;
        }
    }
}

int main() {
    n = 8;
    generateP_plus(1);
    printf("%d\n", count);
    count = 0;
    generateP(1);
    printf("%d\n", count);
    return 0;
}
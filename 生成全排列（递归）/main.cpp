#include <stdio.h>
#define maxn 10

int n, p[maxn], hashTable[maxn] = {false};

void generateP(int index){
    if(index == n + 1){
        for(int i = 1; i < n; i++){
            printf("%d", p[i]);
        }
        printf("\n");
    }
    for(int x = 1; x <= n; x++){
        if(!hashTable[x]){
            p[index] = x;
            hashTable[x] = true;
            generateP(index + 1);
            hashTable[x] = false;
        }
    }
}

int main(){
    n = 5;
    generateP(1);
    return 0;
}
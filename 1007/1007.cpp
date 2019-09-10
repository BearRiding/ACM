#include <iostream>
#include <string>
#include <vector>
using namespace std;

int change(char a) {
    switch (a) {
    case 'A':
        return 1;
    case 'C':
        return 2;
    case 'G':
        return 3;
    case 'T':
        return 4;
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    string *names = new string[n];
    for (int i = 0; i < n; i++) {
        cin >> names[i];
    }
    int *periority = new int[n];
    memset(periority, 0, 4 * m);
    for (int i = 0; i < n; i++) {
        int setpos[4] = {-1, -1, -1, -1};
        int **index = new int *[3];
        for (int j = 0; j < 4; j++) {
            index[j] = new int[m];
            memset(index[j], 0, 4 * m);
        }
        for (int j = 0; j < m; j++) {
            int num = change(names[i][j]);
            setpos[num] = j;

            for (int k = 1; k < num; k++) {
                if (setpos[k] != -1) {
                    index[k][setpos[num]]++;
                }
            }
        }
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < m; k++) {
                periority[i] += index[j][k];
            }
        }
    }
}
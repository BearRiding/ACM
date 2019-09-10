#include <iostream>
#include <stdio.h>
#include <string>
#include <cstring>
using namespace std;
#define LENGTH 10000000
char hush[10000000];
int total;

int change(char a)
{
    switch (a)
    {
    case 'A':
    case 'B':
    case 'C':
        return 2;
    case 'D':
    case 'E':
    case 'F':
        return 3;
    case 'G':
    case 'H':
    case 'I':
        return 4;
    case 'J':
    case 'K':
    case 'L':
        return 5;
    case 'M':
    case 'N':
    case 'O':
        return 6;
    case 'P':
    case 'R':
    case 'S':
        return 7;
    case 'T':
    case 'U':
    case 'V':
        return 8;
    case 'W':
    case 'X':
    case 'Y':
        return 9;
    default:
        return 0;
    }
}

int toint(string a)
{
    int l = 0;
    for (int i = 0; i < a.length(); i++)
    {
        l *= 10;
        l += a[i] - '0';
    }
    return l;
}

string tostring(int a)
{
    string result = "";
    int time = 7;

    while (time > 0)
    {
        int i = a % 10;
        a /= 10;
        result = char(i + '0') + result;
        time--;
    }
    return result;
}

int main()
{
    memset(hush, 0, LENGTH);
    cin >> total;
    for (int i = 0; i < total; i++)
    {
        string cnum;
        cin >> cnum;
        string num = "";
        for (int j = 0; j < cnum.length(); j++)
        {
            if (cnum[j] == '-')
                continue;
            if (cnum[j] < 'Z' && cnum[j] >= 'A')
            {
                num += '0' + change(cnum[j]);
            }
            if (cnum[j] >= '0' && cnum[j] <= '9')
            {
                num += cnum[j];
            }
        }
        int intnum = toint(num);
        hush[intnum]++;
    }
    for (int i = 0; i < LENGTH; i++)
    {
        if (hush[i] > 1)
        {
            string result = tostring(i);
            for (int j = 0; j < result.length(); j++)
            {
                if (j == 3)
                    cout << "-";
                cout << result[j];
            }
            cout << " " << (int)hush[i] << endl;
        }
    }
    // system("pause");
    return 0;
}
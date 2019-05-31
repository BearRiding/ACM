#include <iostream>
#include <vector>
using namespace std;

int main(){
    cout << "hello world";
    vector<int> lala;
    lala.emplace_back(12);
    cout << lala[0];
    getchar();
    return 0;
}
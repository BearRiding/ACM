/*
 * 八数码问题求解
 * 输入：
 * 2 3 4; 1 5 x; 7 6 8
 * 输出
 * ullddrurdllurdruldr
 * 
 * */

#include <iostream>
#include <string>
#include <bitset>
#include <math.h>
#include <assert.h>
using namespace std;

#define N 362880

string path;

bitset<N> sHash; //从前向后遍历的hash
bitset<N> eHash; //从后向前遍历的hash

const int cardinal[8] = {40320, 5040, 720, 120, 24, 6, 2, 1};
//节点，存储状态信息
struct NODE{
	int state;
	string path;
};

//hash函数，生成hash值
int hashFunc(NODE pnode){
	int hashvalue = 0;
	int alive[9] = { 0 };
	int div = 100000000;
	int num = 0;
	for(int i = 0; i < 8; i++){
		int count = 0;
		num = pnode.state / div;
		num %= 10;
		alive[num] = 1;
		for(int j = 0; j < num; j++){
			if(!alive[j]) count++;
		}
		hashvalue += count * cardinal[i];
		div /= 10;
	}
	return hashvalue;
}

int findX(NODE pnode){
	int div = 100000000;
	int num = 0;
	for(int i = 0; i < 9; i++){
		num = pnode.state / div;
		num %= 10;
		div /= 10;
		if(!num) return i;
	}
	return -1;
}

void stateChange(NODE pnode, NODE *waitState){
	int posX = findX(pnode);
	int row = posX / 3;
	int cow = posX % 3;
	posX = 9 - posX;
	int last = pnode.path[pnode.path.length()-1];
	int statetemp = 0;
	int numtemp;
	int j = 0;
	//up
	if(last != 'd' && row != 0){		
		numtemp = (pnode.state / (int)pow(10, posX+2)) % 10;
		statetemp = pnode.state - numtemp * pow(10, posX+2) + numtemp * pow(10, posX-1);		
		waitState[j].state = statetemp;
		waitState[j].path += 'u';
		j++;
	}
	//down
	if(last != 'u' && row != 2){
		numtemp = (pnode.state / (int)pow(10, posX-4)) % 10;
		statetemp = pnode.state - numtemp * pow(10, posX-4) + numtemp * pow(10, posX-1);		
		waitState[j].state = statetemp;
		waitState[j].path += 'd';
		j++;
	}
	//left
	if(last != 'r' && cow != 0){
		numtemp = (pnode.state / (int)pow(10, posX)) % 10;
		statetemp = pnode.state - numtemp * pow(10, posX) + numtemp * pow(10, posX - 1);		
		waitState[j].state = statetemp;
		waitState[j].path += 'l';
		j++;
	}
	//right
	if(last != 'l' && cow != 2){
		numtemp = (pnode.state / (int)pow(10, posX-2)) % 10;
		statetemp = pnode.state - numtemp * pow(10, posX-2) + numtemp * pow(10, posX-1);	
		waitState[j].state = statetemp;
		waitState[j].path += 'r';
		j++;
	}
}

NODE node[N];

int main()
{
	int cinnum = 0;
	char a;
	for(int i = 0;i < 9; i++){		
		cin>>a;
		if(a >= '0' && a < '9'){
			a -= '0';
			cinnum *= 10;
			cinnum += a;
		}
		else{
			a -= 'x';
			cinnum *= 10;
			cinnum += a;
		}
		
	}
	int pStart[3] = { 0, 1, 0 }, pBottom[3] = {N-1,N-2,N-1};
	node[0].path = 's';
	node[0].state = cinnum;
	node[N-1].path = 'e';
	node[N-1].state = 123456780;
	int pointer = 0;
	NODE endState;
	int site = 0;
	int endflag[2] = {1, 1};
	eHash[N-1] = 1;
	sHash[hashFunc(node[0])] = 1;
	
	while(endflag[0] || endflag[1]){
		
		while(pStart[0] != pStart[1] && endflag[0]){				
			NODE waitNode[3];			
			for(int i = 0; i < 3; i++){
				waitNode[i].state = 0;
				waitNode[i].path = node[pStart[0]].path;
			}
			stateChange(node[pStart[0]], waitNode);
			pStart[0]++;
			for(int i = 0; i < 3; i++){
				if(waitNode[i].state == 0) break;
				int hash = hashFunc(waitNode[i]);
				if(sHash[hash] == 1) continue;
				if(eHash[hash] == 1) {
					endState = waitNode[i];
					pointer = pBottom[2];
					site = 0;	
					endflag[0] = endflag[1] = 0;
					break;
				}
				

				sHash[hash] = 1;
				pStart[2]++;				
				node[pStart[2]] = waitNode[i];
			}			
		}
		if(pStart[1] == pStart[2] + 1) endflag[0] = 0;
		else pStart[1] = pStart[2] + 1;
		
		
		while(pBottom[0] != pBottom[1] && endflag[1]){				
			NODE waitNode[3];
			for(int i = 0; i < 3; i++){
				waitNode[i].state = 0;
				waitNode[i].path = node[pBottom[0]].path;
			}
			stateChange(node[pBottom[0]], waitNode);
			pBottom[0]--;
			for(int i = 0; i < 3; i++){
				if(waitNode[i].state == 0) break;
				int hash = hashFunc(waitNode[i]);
				if(eHash[hash] == 1) continue;
				if(sHash[hash] == 1) {
					endState = waitNode[i];
					pointer = pStart[2];
					site = 1;
					break;
				}
				eHash[hash] = 1;
				pBottom[2]--;
				node[pBottom[2]] = waitNode[i];
			}
		}
		if(pBottom[1] == pBottom[2] - 1) endflag[1] = 0;
		else pBottom[1] = pBottom[2] - 1;
	}

	if(site == 1){
		for(int i = 0; i < pointer; i++){
			if(node[i].state == endState.state){
				for(int j = 1; j < node[i].path.length(); j++){
					cout<<node[i].path[j];
				}
				for(int j = endState.path.length() - 1; j > 0; j--){
					if(endState.path[j] == 'u') cout<<'d';
					if(endState.path[j] == 'd') cout<<'u';
					if(endState.path[j] == 'l') cout<<'r';
					if(endState.path[j] == 'r') cout<<'l';
				}
				cout<<endl;
				return 0;
			}
		}
	}
	else{
		for(int i = N-1; i > pointer; i--){
			if(node[i].state == endState.state){
				for(int j = 1; j < endState.path.length(); j++){
					cout<<endState.path[j];
				}
				for(int j = node[i].path.length() - 1; j > 0; j--){
					
					if(node[i].path[j] == 'u') cout<<'d';
					if(node[i].path[j] == 'd') cout<<'u';
					if(node[i].path[j] == 'l') cout<<'r';
					if(node[i].path[j] == 'r') cout<<'l';
				}
				cout<<endl;
				return 0;
			}
		}
	}
	
	cout<< "unsolvable"<<endl;
	
	return 0;
}
 
 

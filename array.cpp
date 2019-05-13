#include <iostream>
#include <vector>

using namespace std;

// 1 3 2 6 5 2 2 2
int majorityNum(vector<int> input){
	int count = 1;
	int num = input[0];
	for(int i = 1; i < input.size(); i++){
		if(num == input[i]){
			count++;
		}else{
			count--;
			if(count <= 0){
				num = input[i];
				count = 1;
			}
		}
	}
	return  num;
}

// Find > 1/3
// 1 4 5 2 1 2 3 5 1 2 1 2 1 2

vector<int> majorityNumII(vector<int> input){
	int count1 = 1;
	int num1 = input[0];
	int count2 = 1;
	int num2 = input[1];
	for(int i = 2; i < input.size(); i++){
		cout << num1 << " " << count1 << " " << num2 << " " << count2 << endl;
		if(num1 == input[i]){
			count1++;
		}else if(input[i] == num2){
			count2++;
		}else{
			count1--;
			if(count1 <= 0){
				num1 = input[i];
				count1 = 1;
			}
			count2--;
			if(count2 <= 0){
				num2 = input[i];
				count2 = 1;
			}
		}
	}
	cout << num1 << " " << count1 << " " << num2 << " " << count2 << endl;
	vector<int> result;
	if(count1 > input.size() / 3){
		result.push_back(num1);
	}
	if(count2 > input.size() / 3){
		result.push_back(num2);
	}
	return result;
}


vector<int> moveZero(vector<int> input){
	int count = 0;
	for(int i = 1; i < input.size(); i++){
		if(input[i] == 0){
			swap(input[i], input[count]);
			count++;
		}
	}
	return input;
}

void swap(int &a, int &b){
	int temp = a;
	a = b;
	b = temp;
}

void printVec(vector<int> input){
	for(auto num:input) 
		cout << num << " ";
	cout << endl;
}

int main(){
	vector<int> input{4,0,1,0,5,0,0};
	vector<int> result;
	//cout << majorityNum(input) << endl;
	/*
	vector<int> result = majorityNumII(input);
	for(int i = 0; i < result.size(); i++){
		cout << result[i] << endl;
	}
	*/
	/*
	result = moveZero(input);
	printVec(result);
	*/

	return 0;
}
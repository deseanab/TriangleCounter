#include <stdexcept> // to throw exceptions if you need to
#include <fstream>   // to open & read from input file
#include <cstdlib>   // for atoi() if you want to use it
#include <set>       // for sba algorithm
#include <vector>    // for vba algorithm
#include <algorithm> // for vba algorithm
#include <iostream>
#include <sstream>
#include <time.h> //for time recording
#include <map>

using namespace std;

int countLines(char fileName[]);
void printVector(vector<int> & vec);
void thirdPass(int beginning, int next, int& count);
void sortMap();
void fillMap(char s[]);

map<int, set<int> > setMap;
map<int, vector<int> > vecMap;

int main(int argc, char *fname[]){
	int count = 0;

	clock_t startTime = clock();

	fillMap(fname[1]);
	sortMap();

	thirdPass(-1, -1, count);
	cout << "The count is " << count << endl;

	clock_t endTime = clock();
	double totalTime = (endTime - startTime) / (double)CLOCKS_PER_SEC;

	cout << "Time: " << totalTime << endl;
	cout << setMap.size() << endl;
	return 0;
}

void thirdPass(int beginning, int next, int& count){
	if (beginning < 0 && next < 0){
		map<int, vector<int> >::iterator iterator;

		for (iterator = vecMap.begin(); iterator != vecMap.end(); iterator++){
			int value = iterator->first;
			vector<int>::iterator it;

			for (it = vecMap[value].begin(); it != vecMap[value].end(); it++){
				thirdPass(value, *it, count);
			}
		}
	}
	else{
		vector<int> first = vecMap[beginning];
		vector<int> second = vecMap[next];

		int firstIndex = 0;
		int secondIndex = 0;

		int first_factor = 1;
		int second_factor = 1;
		int var = 0;

		while (firstIndex < first.size() && secondIndex < second.size()){
			if (first[firstIndex] == second[secondIndex]){
				count++;
				firstIndex++;
				secondIndex++;
				first_factor = 1;
				second_factor = 1;
				var = 0;
			}
			else{
				switch (var)
				{
				case 0:
					if (first[firstIndex] < second[secondIndex]){
						var = 1;
						break;
					}
					else{
						var = 2;
						break;
					}
				case 1:
					if (first[firstIndex] < second[secondIndex]){
						if (first.size() - first_factor < firstIndex){
							first_factor = 1;
							firstIndex += first_factor;
						}
						else{
							firstIndex += first_factor;
							first_factor = first_factor * 2;
						}
						break;
					}
					else{
						
						if (first_factor/2 == 1){
							var = 0;
							secondIndex++;
							first_factor = 1;
							second_factor = 1;
						}
						else{
							firstIndex -= first_factor / 2;
							first_factor = 1;
							firstIndex += first_factor;
							first_factor = first_factor * 2;
						}
					}
					break;
				case 2:
					if (first[firstIndex] > second[secondIndex]){
						if (second.size() - second_factor < secondIndex){
							second_factor = 1;
							secondIndex += second_factor;
						}
						else{
							secondIndex += second_factor;
							second_factor = second_factor * 2;
						}
					}
					else{
						if (second_factor/2 == 1){
							var = 0;
							firstIndex++;
							first_factor = 1;
							second_factor = 1;
						}
						else{
							secondIndex -= second_factor/2;
							second_factor = 1;
							secondIndex += second_factor;
							second_factor = second_factor * 2;
						}
					}
					break;
				}
			}
		}
		if (firstIndex < first.size() && (second.size() > 0) && (second[second.size()-1] > first[firstIndex])){
			first_factor = 1;
			while (firstIndex < first.size()){
				if (first[firstIndex] == second[secondIndex]){
					count++;
					first_factor = 1;
				}
				firstIndex++;
			}
		}
		else if (secondIndex < second.size() && first.size() > 0 && (first[first.size() - 1] > second[secondIndex])){
			second_factor = 1;
			while (secondIndex < second.size()){
				if (first[firstIndex] == second[secondIndex]){
					count++;
					second_factor = 1;
				}
				secondIndex++;
			}
		}

	}
}

void printVector(vector<int> & vec){
	vector<int>::iterator i;
	for (i = vec.begin(); i != vec.end(); ++i) {
		cout << *i << endl;
	}
	cout << endl;
}

void fillMap(char s[]){
	ifstream inputobject;
	string line = "";
	inputobject.open(s);
	if (inputobject.fail()) {
		cout << "Failed to open file" << endl;
		inputobject.clear();
	}
	else {
		cout << "opened: " << s << endl << endl;
		while (getline(inputobject, line)){
			if (line.at(0) != '#'){
				istringstream iss(line);
				int first, second;
				iss >> first;
				iss >> second;

				if (first > second){ swap(first, second); }

				if (first != second){
					vecMap[first].push_back(second);
				}
			}
		}
		inputobject.close();
	}
	cout << "Filled map" << endl;
}

int countLines(char fileName[]){
	int numLines;
	ifstream inputobject;
	string line = "";
	inputobject.open(fileName);
	if (inputobject.fail()) {
		cout << "Failed to open file" << endl;
		inputobject.clear();
	}
	else {
		while (getline(inputobject, line)){
			numLines++;
		}
	}
	return numLines;
}

void sortMap(){
	cout << "Sorting Map" << endl;
	map<int, vector<int> >::iterator it;
	for (it = vecMap.begin(); it != vecMap.end(); it++){
		//vector<int>* val;
		int start = it->first;
		//val = &vecMap[start];

		sort(vecMap[start].begin(), vecMap[start].end());
		vecMap[start].erase(unique(vecMap[start].begin(), vecMap[start].end()), vecMap[start].end());
		//printVector(vecMap[start]);
	}
	cout << "Map Sorted" << endl;
}
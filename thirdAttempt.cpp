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

//int countLines(char fileName[]);
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
	
	clock_t endTime = clock();
	double totalTime = (endTime - startTime) / (double)CLOCKS_PER_SEC;

	cout << endl;
	cout << "The count is " << count << endl;
	cout << "Time: " << totalTime << endl;
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
		int firstSize = first.size() - 1;
		int secondSize = second.size() - 1;

		bool lastfound = false;
		bool run = true;

		int first_factor = 1;
		int second_factor = 1;
		int var = 0;

		if (first.size() == 0 || second.size() == 0){
			return;
		}
		int firnum = first[firstIndex];
		int secnum = second[secondIndex];

		while (run){
			firnum = first[firstIndex];
			secnum = second[secondIndex];
			if (firstIndex >= firstSize && secondIndex >= secondSize && first_factor == 1 && second_factor == 1){
				run = false;
			}
			if (first[firstIndex] == second[secondIndex]){
				if (!lastfound) count++;
				if (firstIndex == firstSize && secondIndex == secondSize){
					lastfound = true;
				}
				if (firstIndex < firstSize) { firstIndex++; }
				if (secondIndex < secondSize) { secondIndex++; }
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
						if (firstSize - first_factor < firstIndex){// || first.size() == 1){
							first_factor = 1;
							if (firstIndex == firstSize){
								return;
								secondIndex++;
							}
							if (firstIndex < firstSize) { firstIndex++; }
							
						}
						else{
							firstIndex += first_factor;
							first_factor = first_factor * 2;
						}
						break;
					}
					else{

						if (first_factor == 2 || first_factor == 1){
							var = 0;
							if (secondIndex < secondSize) { secondIndex++; }
							first_factor = 1;
							second_factor = 1;
						}
						else{
							firstIndex -= first_factor / 2;
							first_factor = 1;
							if (firstIndex < firstSize) { firstIndex++; }
							first_factor = first_factor * 2;
						}
					}
					break;
				case 2:
					if (first[firstIndex] > second[secondIndex]){
						if (secondSize - second_factor < secondIndex){// || (second.size() == 1)){
							second_factor = 1;
							if (secondIndex == secondSize){
								return;
								firstIndex++;
							}
							if (secondIndex < secondSize) { secondIndex++; }
							
						}
						else{
							secondIndex += second_factor;
							second_factor = second_factor * 2;
						}
						
					}
					else{
						if (second_factor == 2 || second_factor == 1){
							var = 0;
							if (firstIndex < firstSize) { firstIndex++; }
							first_factor = 1;
							second_factor = 1;
						}
						else{
							secondIndex -= second_factor / 2;
							second_factor = 1;
							if (secondIndex < secondSize) { secondIndex++; }
							second_factor = second_factor * 2;
						}
					}
					break;
				}
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
		cout << "Opened: " << s << endl << endl;
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
}

void sortMap(){
	map<int, vector<int> >::iterator it;
	for (it = vecMap.begin(); it != vecMap.end(); it++){
		//vector<int>* val;
		int start = it->first;
		//val = &vecMap[start];

		sort(vecMap[start].begin(), vecMap[start].end());
		vecMap[start].erase(unique(vecMap[start].begin(), vecMap[start].end()), vecMap[start].end());
		//printVector(vecMap[start]);
	}
}
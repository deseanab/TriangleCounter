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
void fillVector(char s[], vector<pair<int, int> > &v);
void fillVector2(char s[], vector<pair<int, int> > &v);
void printVector(vector<pair<int, int> > & myVec);
int firstPass(vector<pair<int, int> > &v1, vector<pair<int, int> > &v2);
typedef map<int, set<int> >::iterator it_type;
void secondPass(int beginning, int next, int num_sides, int &count);
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
		cout << "Comparing Vectors" << endl;
		cout << count << endl;
		// Compare the vectors
		vector<int> first = vecMap[beginning];
		vector<int> second = vecMap[next];

		int firstIndex = 0;
		int secondIndex = 0;

		int first_factor = 1;
		int second_factor = 1;
		int var = 0;


		while (firstIndex < first.size() || secondIndex < second.size()){
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
						if (first.size() - first_factor < first[firstIndex]){
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
						firstIndex -= first_factor;
						first_factor = 1;
						if (first[firstIndex + 1] > second[secondIndex]){
							var = 2;
							firstIndex++;
							secondIndex++;
						}
						else{
							firstIndex += first_factor;
							first_factor = first_factor * 2;
						}
					}
					break;
				case 2:
					if (first[firstIndex] > second[secondIndex]){
						if (second.size() - second_factor < second[secondIndex]){
							second_factor = 1;
							secondIndex += second_factor;
						}
						else{
							secondIndex += second_factor;
							second_factor = second_factor * 2;
						}
						break;
					}
					else{
						secondIndex -= second_factor;
						second_factor = 1;
						if (first[firstIndex] < second[secondIndex + 1]){
							var = 1;
							firstIndex++;
							secondIndex++;
						}
						else{
							secondIndex += second_factor;
							second_factor = second_factor * 2;
						}
					}
					break;
				}
			}
		}
	}
}


















/*
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
		cout << "Comparing Vectors" << endl;
		cout << count << endl;
		// Compare the vectors
		vector<int> first = vecMap[beginning];
		vector<int> second = vecMap[next];

		vector<int>::iterator first_it = first.begin();
		vector<int>::iterator second_it = second.begin();

		int first_factor = 1;
		int second_factor = 1;
		int var = 0;


		while (first_it != first.end() || second_it != second.end()){
			if (!first_it){
				cout << "first_it went too far" << endl;
				first_it -= first_factor;
				first_factor = 1;
				first_it++;
			}
			else if (!second_it){
				cout << "second_it went too far" << endl;
				second_it -= second_factor;
				second_factor = 1;
				second_it++;
			}
			else{
				if (*first_it == *second_it){
					count++;
					first_it++;
					second_it++;
					first_factor = 1;
					second_factor = 1;
					var = 0;
				}
				else{
					switch (var)
					{
					case 0:
						if (*first_it < *second_it){
							var = 1;
							break;
						}
						else{
							var = 2;
							break;
						}
					case 1:
						if (*first_it < *second_it){
							if (first.end() - first_factor < first_it){
								first_factor = 1;
								first_it += first_factor;
							}
							else{
								first_it += first_factor;
								first_factor = first_factor * 2;
							}
							break;
						}
						else{
							first_it -= first_factor;
							first_factor = 1;
							if (*first_it + 1 > *second_it){
								var = 2;
								first_it++;
								second_it++;
							}
							else{
								first_it += first_factor;
								first_factor = first_factor * 2;
							}
						}
						break;
					case 2:
						if (*first_it > *second_it){
							if (second.end() - second_factor < second_it){
								second_factor = 1;
								second_it += second_factor;
							}
							else{
								second_it += second_factor;
								second_factor = second_factor * 2;
							}
							break;
						}
						else{
							second_it -= second_factor;
							second_factor = 1;
							if (*first_it < *second_it + 1){
								var = 1;
								first_it++;
								second_it++;
							}
							else{
								second_it += second_factor;
								second_factor = second_factor * 2;
							}
						}
						break;
					}
				}
				//return;
			}

		}
	}
}
*/


void fillVector(char s[], vector<pair<int, int> > &v){
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
				int first = 0, second = 0;
				iss >> first;
				iss >> second;
				map <int, set<int> >::iterator it;
				if (first > second){
					swap(first, second);
				}

				it = setMap.find(first);

				if (it != setMap.end()){
					setMap[first].insert(second);
				}
				else{

					setMap[first].insert(second);
				}

				pair<int, int> p;
				p = make_pair(first, second);
				//                if (first <= second){
				//                    p = make_pair(first,second);
				//                } else {
				//                    p = make_pair(second,first);
				//                }
				v.push_back(p);
			}
		}
		inputobject.close();
	}
	cout << "Filled" << endl;
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

				setMap[first].insert(second);

				vecMap[first].push_back(second);

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
	map<int, vector<int> >::iterator it;
	for (it = vecMap.begin(); it != vecMap.end(); it++){
		vector<int> val;
		int start = it->first;
		val = vecMap[start];
		sort(val.begin(), val.end());
		val.erase(unique(val.begin(), val.end()), val.end());
	}
}
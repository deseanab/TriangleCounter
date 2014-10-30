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

int main(int argc, char *fname[]){
    vector<pair<int, int> > v1;
    vector<pair<int, int> > v2;
    int count = 0;
    
    clock_t startTime = clock();
    
    fillVector(fname[1], v1);
    sort(v1.begin(), v1.end());
    v1.erase(unique(v1.begin(),v1.end()), v1.end());
	fillMap(fname[1]);
	sortMap();
    
    cout << "original vector of pairs:" << endl;
    printVector(v1);
    secondPass(-1, -1, 3, count);
    cout << "The count is " << count << endl;

    clock_t endTime = clock();
    double totalTime = (endTime - startTime) / (double) CLOCKS_PER_SEC;
    
    cout << "Time: " << totalTime << endl;
    cout << setMap.size() << endl;
    return 0;
}

void printVector(vector<pair<int, int> > & myVec)
{
    vector<pair<int, int> >::iterator i;
    for (i = myVec.begin(); i != myVec.end(); ++i) {
        cout << "(" << i->first << ", " <<  i->second << ") " << endl;
    }
    cout << endl;
}

int firstPass(vector<pair<int, int> > &v1, vector<pair<int, int> > &v2){
    int numTriangles = 0;
    for (int i = 0; i < v1.size(); i++){
        for (int k = 0; k < v1.size(); k++){
            if(!(v1[i].first == v1[i].second) && !(v1[k].first == v1[k].second)){ //checks to make sure that the edge isn't a repeat of the same number, ie: (6,6)
                if(v1[i].second == v1[k].first){ //if the second number from the first pair is equal to the first number of the second pair
                    v2.push_back(make_pair(v1[i].first,v1[k].second));
                    //create a pair from the first number from the first pair, and the second number from the second pair. If these numbers are found in the second pass, then a triangle is found
                    //doesn't need to be stored, check instantly if that pair exists
                    for (int m = 0; m < v1.size(); m++){
                        if(v1[m].first == v1[i].first && v1[m].second == v1[k].second){ //if these pairs match up, a triangle is formed
                            numTriangles++;
                        }
                    }
                }
            }
        }
    }
    return numTriangles;
}
void secondPass(int beginning, int next, int num_sides, int &count){
	
	if (beginning < 0){
		map<int, set<int> >::iterator iterator;
		
		for(iterator = setMap.begin(); iterator != setMap.end(); iterator++){
			int value = iterator->first;
			set<int>::iterator it;
			
			for(it = setMap[value].begin(); it != setMap[value].end(); it++){
				if (value != *it){
					secondPass(value, *it, num_sides - 1, count);
				}
			}
		}
	}
	else{
		if(num_sides > 1){
			for(set<int>::iterator it = setMap[next].begin(); it != setMap[next].end(); it++){
				if (next != *it){
					secondPass(beginning, *it, num_sides - 1, count);
				}
			}
		}
		else{
			for(set<int>::iterator it = setMap[beginning].begin(); it != setMap[beginning].end(); it++){
				if(*it == next){
					count++;
				}
			}
		}
	}
}
void fillVector(char s[], vector<pair<int, int> > &v){
    ifstream inputobject;
    string line = "";
    inputobject.open(s);
    if (inputobject.fail()) {
        cout << "Failed to open file" << endl;
        inputobject.clear();
    } else {
        cout << "opened: " << s << endl << endl;
        while (getline(inputobject, line)){
            if (line.at(0) != '#'){
                istringstream iss(line);
                int first = 0, second = 0;
                iss >> first;
                iss >> second;
                map <int, set<int> >::iterator it;
                if(first > second){
                	swap(first, second);
                }

                it = setMap.find(first);

                if(it != setMap.end() ){
                	setMap[first].insert(second);
                }
                else{

                	setMap[first].insert(second);
                }

                pair<int,int> p;
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
    } else {
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

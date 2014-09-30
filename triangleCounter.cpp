#include <stdexcept> // to throw exceptions if you need to
#include <fstream>   // to open & read from input file
#include <cstdlib>   // for atoi() if you want to use it
#include <set>       // for sba algorithm
#include <vector>    // for vba algorithm
#include <algorithm> // for vba algorithm
#include <iostream>
#include <sstream>
#include <time.h> //for time recording

using namespace std;

int countLines(char fileName[]);
void fillVector(char s[], vector<pair<int, int> > &v);
void printVector(vector<pair<int, int> > & myVec);
void firstPass(vector<pair<int, int> > &v1, vector<pair<int, int> > &v2);

int main(int argc, char *fname[]){
    vector<pair<int, int> > v1;
    vector<pair<int, int> > v2;
    
    clock_t t = clock();
    
    fillVector(fname[1], v1);
    sort(v1.begin(), v1.end());
    v1.erase(unique(v1.begin(),v1.end()), v1.end());
    
    cout << "original vector of pairs:" << endl;
    printVector(v1);
    
    firstPass(v1,v2,v3);
    
    return 0;
}

struct Triangle {
    pair<int, int> p1;
    pair<int, int> p2;
    pair<int, int> p3;
};

void printVector(vector<pair<int, int> > & myVec)
{
    vector<pair<int, int> >::iterator i;
    for (i = myVec.begin(); i != myVec.end(); ++i) {
        cout << "(" << i->first << ", " <<  i->second << ") " << endl;
    }
    cout << endl;
}

void firstPass(vector<pair<int, int> > &v1, vector<pair<int, int> > &v2){
    for (int i = 0; i < v1.size(); i++){
        for (int k = 0; k < v1.size(); k++){
            if(!(v1[i].first == v1[i].second) && !(v1[k].first == v1[k].second)){ //checks to make sure that the edge isn't a repeat of the same number, ie: (6,6)
                if(v1[i].second == v1[k].first){ //if the second number from the first pair is equal to the first number of the second pair
                    v2.push_back(make_pair(v1[i].first,v1[k].second));
                    //create a pair from the first number from the first pair, and the second number from the second pair. If these numbers are found in the second pass, then a triangle is found
                    //doesn't need to be stored, check instantly if that pair exists
                    for (int m = 0; m < v1.size(); m++){
                        if(v1[m].first == v1[i].first && v1[m].second == v1[k].second){ //if these pairs match up, a triangle is formed
                            Triangle t;
                            t.p1 = make_pair(v1[i].first, v1[i].second);
                            t.p2 = make_pair(v1[k].first, v1[k].second);
                            t.p3 = make_pair(v1[i].first, v1[k].second);
                            cout << "A triangle has been formed with the edges: (" << v1[i].first << ", " << v1[i].second << ") (" << v1[k].first << ", " << v1[k].second << ") (" << v1[i].first << ", " << v1[k].second << ")" << endl;
                        }
                    }
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
                pair<int,int> p;
                if (first <= second){
                    p = make_pair(first,second);
                } else {
                    p = make_pair(second,first);
                }
                v.push_back(p);
            }
        }
        inputobject.close();
    }
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
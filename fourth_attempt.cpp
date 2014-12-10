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
#include <pthread.h>
#include <unistd.h>
#include <cstdlib>

using namespace std;

struct arguments{
    int beginning_s;
    int next_s;
    int count_s;
} one,two,three,four;

void printVector(vector<int> & vec);
void thirdPass(int beginning, int next, int& count);
void sortMap();
void fillMap(char s[]);
void* print_args (void* arguments);
void* print_args2 (void* arguments);
void* print_args3 (void* arguments);
void* print_args4 (void* arguments);


map<int, set<int> > setMap;
map<int, vector<int> > vecMap;

int main(int argc, char *fname[]){
    int thread_one_count = 0, thread_two_count = 0, count = 0;
    int i;
    clock_t startTime = clock();
    
    fillMap(fname[1]);
    sortMap();
    
    one.beginning_s = -1;
    one.next_s = -1;
    one.count_s = count;
    
    two.beginning_s = -1;
    two.next_s = -1;
    two.count_s = count;
    
    three.beginning_s = -1;
    three.next_s = -1;
    three.count_s = count;
    
    four.beginning_s = -1;
    four.next_s = -1;
    four.count_s = count;
    
    pthread_t t1,t2,t3,t4;
    pthread_create(&t1, NULL, &print_args, (void*)&one);
    pthread_create(&t2, NULL, &print_args2, (void*)&two);
//    pthread_create(&t3, NULL, &print_args3, (void*)&three);
//    pthread_create(&t4, NULL, &print_args4, (void*)&four);
    
//    thirdPass(-1, -1, count);
    
//    pthread_join(t4, (void **)&i);
//    pthread_join(t3, (void **)&i);
    pthread_join(t2, (void **)&i);
    pthread_join(t1, (void **)&i);
    
    
    count = one.count_s + two.count_s + three.count_s + four.count_s;
    
    clock_t endTime = clock();
    double totalTime = (endTime - startTime) / (double)CLOCKS_PER_SEC;
    
    cout << "one.count_s " << one.count_s << endl;
    cout << "two.count_s " << two.count_s << endl;
    cout << "three.count_s " << three.count_s << endl;
    cout << "four.count_s " << four.count_s << endl;
    
    cout << "The count is " << count << endl;
    cout << "Time: " << totalTime << endl;
    
//     pthread_exit(NULL);
    
    return 0;
}
//
//void* print_args (void* param){
//    arguments *args = (arguments*)param;
//    
//    map<int, vector<int> >::iterator iterator;
//    map<int, vector<int> >::iterator quarter_it;
//    
//    int quarter = distance(vecMap.begin(),vecMap.end()) / 4;
//    
//    quarter_it = vecMap.begin();
//    advance(quarter_it,quarter);
//    
//    for (iterator = vecMap.begin(); iterator != quarter_it; advance(iterator, 1)){
//        int value = iterator->first;
//        thirdPass(value, args -> next_s, args -> count_s);
//    }
//    pthread_exit(NULL);
//    return 0;
//}
//
//void* print_args2 (void* param){
//    arguments *args = (arguments*)param;
//
//    map<int, vector<int> >::iterator quarter_it;
//    map<int, vector<int> >::iterator half_it;
//    
//    int quarter = distance(vecMap.begin(),vecMap.end()) / 4;
//    int half = distance(vecMap.begin(),vecMap.end()) / 2;
//    
//    quarter_it = vecMap.begin();
//    advance(quarter_it,quarter);
//    
//    half_it = vecMap.begin();
//    advance(half_it,half);
//    
//    for (; quarter_it != half_it; advance(quarter_it, 1)){
//        int value = quarter_it->first;
//        thirdPass(value, args -> next_s, args -> count_s);
//    }
//    pthread_exit(NULL);
//    return 0;
//}
//
//void* print_args3 (void* param){
//    arguments *args = (arguments*)param;
//
//    map<int, vector<int> >::iterator half_it;
//    map<int, vector<int> >::iterator three_quarter_it;
//    
//    int three_quarter = distance(vecMap.begin(),vecMap.end()) * 3 / 4;
//    int half = distance(vecMap.begin(),vecMap.end()) / 2;
//    
//    half_it = vecMap.begin();
//    advance(half_it,half);
//    
//    three_quarter_it = vecMap.begin();
//    advance(three_quarter_it,three_quarter);
//    
//    for (; half_it != three_quarter_it; advance(half_it, 1)){
//        int value = half_it->first;
//        thirdPass(value, args -> next_s, args -> count_s);
//    }
//    pthread_exit(NULL);
//    return 0;
//}
//
//void* print_args4 (void* param){
//    arguments *args = (arguments*)param;
//    
//    map<int, vector<int> >::iterator three_quarter_it;
//    
//    int three_quarter = distance(vecMap.begin(),vecMap.end()) * 3 / 4;
//    
//    three_quarter_it = vecMap.begin();
//    advance(three_quarter_it,three_quarter);
//    
//    for (; three_quarter_it != vecMap.end(); advance(three_quarter_it, 1)){
//        int value = three_quarter_it->first;
//        thirdPass(value, args -> next_s, args -> count_s);
//    }
//    pthread_exit(NULL);
//    return 0;
//}


void* print_args (void* param){
    arguments *args = (arguments*)param;

    map<int, vector<int> >::iterator iterator;
    map<int, vector<int> >::iterator h_it;
    
    int half = distance(vecMap.begin(),vecMap.end()) / 2;
    h_it = vecMap.begin();
    advance(h_it,half);
    
    for (iterator = vecMap.begin(); iterator != h_it; advance(iterator, 1)){
        int value = iterator->first;
        thirdPass(value, args -> next_s, args -> count_s);
    }
    return 0;
}

void* print_args2 (void* param){
    arguments *args = (arguments*)param;
    
    int half = distance(vecMap.begin(),vecMap.end()) / 2;
    
    map<int, vector<int> >::iterator h_it;
    h_it = vecMap.begin();
    advance(h_it,half);
    
    for (; h_it != vecMap.end(); advance(h_it, 1)){
        int value = h_it->first;
        
        thirdPass(value, args -> next_s, args -> count_s);
    }
    return 0;
}

void thirdPass(int beginning, int next, int& count){

    if (next < 0){
        vector<int>::iterator it;
        for (it = vecMap[beginning].begin(); it != vecMap[beginning].end(); it++){
            thirdPass(beginning, *it, count);
        }
    }
//    if (beginning < 0 && next < 0){
//        map<int, vector<int> >::iterator iterator;
//        
//        for (iterator = vecMap.begin(); iterator != vecMap.end(); iterator++){
//            int value = iterator->first;
//            vector<int>::iterator it;
//            
//            for (it = vecMap[value].begin(); it != vecMap[value].end(); it++){
//                thirdPass(value, *it, count);
//            }
//        }
//    }
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
                if (!lastfound) {
                    count++;
                }
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
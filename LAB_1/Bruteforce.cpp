#include <iostream>
#include <vector>
#include <chrono>
#include <stdlib.h> // нужен для вызова функций rand(), srand()
#include <time.h> // нужен для вызова функции time()

using namespace std;
using namespace std::chrono;

bool has_duplicates(const std::vector<int> &data) {
    for (int i = 0; i < data.size();i++){ 
        for (int j = i + 1; j < data.size(); j++){ 
            if (data[i]==data[j]){ 
                return true; 
            } 
        } 
    } 
    return false;
}


vector<int> get_duplicates(const vector<int> &data) {
    vector<int> result; 
    result=data; 
    bool flag; 
    for (int i = 0; i < result.size();i++){ 
        flag = false; 
        for (int j = i+1; j < result.size() ; j++){ 
            if (result[i]==result[j]){ 
                result.erase(result.begin() + j); 
                flag = true; 
            } 
        } 
        if (flag == false){ 
            result.erase(result.begin() + i); 
            i--;
        } 
    } 
    return result; 
}

int main() {
    vector<int> a;  
    srand(time(NULL));
    for (int i=0; i<10000;i++){
        a.push_back(rand());
    }
    auto t1 = steady_clock::now();
    has_duplicates(a);
    auto t2 = steady_clock::now();
    a = get_duplicates(a);
    auto t3 = steady_clock::now();
    auto time = duration<double>(t2 - t1).count();
    cout << "Time: " << time << " sec." << endl;
    auto time2 = duration<double>(t3 - t2).count();
    cout << "Time: " << time2 << " sec." << endl;
    return 0;
}
#include <chrono> 
#include <iostream> 
#include <vector> 
#include <list>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <stdlib.h> // нужен для вызова функций rand(), srand()
#include <time.h> // нужен для вызова функции time()
using namespace std; 
using namespace std::chrono;

bool has_duplicates(const std::vector<int> &data) { 
    auto sorted = data;
    sort(sorted.begin(),sorted.end());
    for(int i=0; i<sorted.size()-1;i++){
        if(sorted[i]==sorted[i+1]) return true;
    }
    return false;
}

set<int> get_duplicates(const std::vector<int> &data) { 
    auto sorted = data; 
    set<int> s;
    sort(sorted.begin(),sorted.end());
    for(int i=0; i<sorted.size()-1;i++){
        if(sorted[i]==sorted[i+1]){
            s.insert(sorted[i]);
        }
    }
    return s; 
}


int main(){
    vector<int> a;
    srand(time(NULL));
    for (int i=0; i<10000;i++){
        a.push_back(rand());
    }
    set<int> resullt;
    set<int> resullt2;
    cout << has_duplicates(a) << endl;
    resullt=get_duplicates(a);
    cout << endl;
    auto t1 = steady_clock::now();
    has_duplicates(a);
    auto t2 = steady_clock::now();
    resullt2 = get_duplicates(a);
    auto t3 = steady_clock::now();
    auto time = duration<double>(t2 - t1).count();
    cout << "Time: " << time << " sec." << endl;
    auto time2 = duration<double>(t3 - t2).count();
    cout << "Time: " << time2 << " sec." << endl;
}
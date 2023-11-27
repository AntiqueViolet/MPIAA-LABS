#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <ctime>
#include <chrono>
#include <utility>
#include "activity.h"
using namespace std;

// Функция сортировки процессов по времени окончания
bool compareProcesses(Process p1, Process p2) {
    return p1.finish < p2.finish;
}

std::vector<Process> get_max_activitiesGREED(std::vector<Process>& processes) {
    std::vector<Process> result;
    
    // Сортируем процессы по времени окончания
    std::sort(processes.begin(), processes.end(), compareProcesses);
    
    // Добавляем первый процесс в результат
    result.push_back(processes[0]);
    
    int last_finish_time = processes[0].finish;
    int last_start_time = processes[0].start;
    
    // Проверяем остальные процессы
    for (int i = 1; i < processes.size(); i++) {
        // Если процесс совместим с предыдущим, добавляем его в результат
        if (processes[i].start > last_start_time && processes[i].start >= last_finish_time) {
            result.push_back(processes[i]);
            last_finish_time = processes[i].finish;
            last_start_time = processes[i].start;

        }
    }
    
    return result;
}

bool isCompatible(const Process& p1, const Process& p2) {
    return p1.finish <= p2.start || p2.finish <= p1.start;
}

std::vector<Process> getMaxCompatibleSubset(const std::vector<Process>& processes) {
    int n = processes.size();
    std::vector<Process> maxSubset;
    
    for (int i = 0; i < (1 << n); i++) {
        std::vector<Process> subset;
        for (int j = 0; j < n; j++) {
            if ((i >> j) & 1) {
                subset.push_back(processes[j]);
            }
        }
        
        bool isSubsetCompatible = true;
        for (int k = 0; k < subset.size(); k++) {
            for (int l = k + 1; l < subset.size(); l++) {
                if (!isCompatible(subset[k], subset[l])) {
                    isSubsetCompatible = false;
                    break;
                }
            }
            if (!isSubsetCompatible) {
                break;
            }
        }
        
        if (isSubsetCompatible && subset.size() > maxSubset.size()) {
            maxSubset = subset;
        }
    }
    
    return maxSubset;
}



int main() {
    
    std::vector<Process> processes = {};
    int N = 25;
    for (int i = 0; i < N; ++i){
        int a = rand() % 100;
        int b = rand() % 100;
        if (b > a){
            processes.push_back(Process(a, b));
        }
        else{
            i--;
        }   
    }
    
    srand(time(NULL));
    auto t1 = std::chrono::high_resolution_clock::now();
    auto LCS1 = getMaxCompatibleSubset(processes);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration<double>(t2 - t1).count();
    std::cout << " BF Time: " << time << " sec." << std::endl;

    std::cout << "Max Activities:\n";
    for (const Process& process : LCS1) {
        std::cout << "Start: " << process.start << ", Finish: " << process.finish << "\n";
    }

    auto t3 = std::chrono::high_resolution_clock::now();
    auto LCS2 = get_max_activitiesGREED(processes);
    auto t4 = std::chrono::high_resolution_clock::now();
    auto time2 = std::chrono::duration<double>(t4 - t3).count();
    std::cout << " Greed Time: " << time2 << " sec." << std::endl;

}

#include "lcs.h"
#include <stdexcept>
#include <algorithm>
#include <ctime>
#include <iostream>
#include <chrono>
#include <utility>
#include <cmath>
#include <cstring>  
using namespace std;

std::string lcsHelper(const std::string& first, const std::string& second, int i, int j) {
    if (i == 0 || j == 0) {
        return "";
    }
    if (first[i-1] == second[j-1]) {
        return lcsHelper(first, second, i-1, j-1) + first[i-1];
    }
    std::string lcs1 = lcsHelper(first, second, i, j - 1);
    std::string lcs2 = lcsHelper(first, second, i - 1, j);
    if (lcs1.length() > lcs2.length()) {
        return lcs1;
    } else {
        return lcs2;
    }
}

std::string lcs_bruteforce(const std::string& first, const std::string& second) {
    return lcsHelper(first, second, first.length(), second.length());
}

string lcs(const string &X, const string &Y, int m, int n) {
    
    int L[m + 1][n + 1];
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                L[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                L[i][j] = L[i - 1][j - 1] + 1;
            else
                L[i][j] = max(L[i - 1][j], L[i][j - 1]);
        }
    }
 

    int index = L[m][n];
    char lcs[index + 1];
    lcs[index] = '\0';
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs[index - 1] = X[i - 1];
            i--;
            j--;
            index--;
        }
        else {
            if (L[i - 1][j] > L[i][j - 1]){
                i--;
            }
            else{j--;}
        }   
    }
    return lcs;
}

int main() {
    char S1[]="0M2C";
    const int N = 10000;
    char S2[N];

    srand(time(NULL));
    for (int i = 0; i <= N; ++i){
        S2[i] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[rand()%36];
    }


    int m = strlen(S1);
    int n = strlen(S2);
    auto t1 = std::chrono::high_resolution_clock::now();
    auto LCS = lcs(S1,S2,m,n);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration<double>(t2 - t1).count();
    cout << LCS << " ";
    std::cout << " Optim Time: " << time << " sec." << std::endl;

    auto t3 = std::chrono::high_resolution_clock::now();
    auto LCS2 = lcs_bruteforce(S1,S2);
    auto t4 = std::chrono::high_resolution_clock::now();
    auto time2 = std::chrono::duration<double>(t4 - t3).count();
    cout << LCS2 << " ";
    std::cout << " Brutforce Time: " << time2 << " sec." << std::endl;

 }
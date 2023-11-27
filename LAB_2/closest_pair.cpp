#include "closest_pair.h"
#include <stdexcept>
#include <algorithm>
#include <ctime>
#include <iostream>
#include <chrono>
#include <utility>
#include <cmath>

using namespace std;
bool pointxcmp(const Point& p1, const Point& p2) // Используется для сортировки точек в порядке возрастания по координате x
{
    return p1.x < p2.x;
}
bool pointycmp(const Point& p1,const Point& p2) // Используется для сортировки точек в порядке возрастания по координате y
{
    return p1.y < p2.y;
}

pair<Point, Point> closest_pair_between(vector<Point>& PLeft, vector<Point>& PRight, double d)
{
    double Xm = (PLeft[PLeft.size() - 1].x + PRight[0].x) / 2;;
    vector<Point> PStripe;
    
    for (int i = 0; i < PLeft.size(); i++) {
        if (abs(PLeft[i].x - Xm) < d){PStripe.push_back(PLeft[i]);}
        
    }
    for (int i = 0; i < PRight.size(); i++) {
        if (abs(PRight[i].x - Xm) < d){PStripe.push_back(PRight[i]);}
    }
    sort(PStripe.begin(), PStripe.end(), pointycmp);// Сортировать по координате y от маленького к большомy
    // pair<Point, Point> k;
    // double s = 99999;
    // for (int i = 0; i < PStripe.size(); i++)
    //     for (int j = i + 1; j < PStripe.size(); j++) {
    //         if (PStripe[i].distance(PStripe[j]) < s) {
    //             s = PStripe[i].distance(PStripe[j]);
    //             k.first=PStripe[i];
    //             k.second=PStripe[j];
    //         }
    //     }
    // return k;
    return closest_pair1(PStripe);
}

std::pair<Point, Point> closest_pair1(const std::vector<Point> &points) {
	double min = 9999;
    pair<Point, Point> a;
 	for (int i = 0; i < points.size(); i++){
  		for (int j = i+1; j < points.size(); j++){
   			if (points[i].distance(points[j]) < min){
    			min = points[i].distance(points[j]);
				a = make_pair(Point(points[i]), Point(points[j]));
   			}
  		}
 	}
	return a;
}

std::pair<Point, Point> closest_pair(const std::vector<Point> &points) {
	int i, midindex;
    double pl, pr, pb;
    double d = 0;
	if (points.size() <=3) {
        return closest_pair1(points);
	}	
	else{
		std::pair<Point, Point> tmp,tmp2,tmp3;
        vector<Point> PS = points;
        vector<Point> PLeft, PRight;
		sort(PS.begin(),PS.end(), pointxcmp);
        
        int leftindex = 0;
        int rightindex = PS.size()-1;
        
		midindex = (leftindex + rightindex) / 2;
        for (i = 0; i <= midindex; i++){
                PLeft.push_back(PS[i]);
		}
        for ( ;i < PS.size(); i++){
                PRight.push_back(PS[i]);
		}

        

		tmp = closest_pair(PLeft);
        pl =  tmp.first.distance(tmp.second);
        

        tmp2 = closest_pair(PRight);
        pr = tmp2.first.distance(tmp2.second);
        
        
        d = min(pl,pr);
        

		tmp3 = closest_pair_between(PLeft, PRight, d); // пара ближайших точек между половинами PLeft и PRight.
        pb = tmp3.first.distance(tmp3.second);

        if (pl <= pr && pl <= pb){
            return tmp;
        }
        else{ 
            if (pr <= pl && pr <= pb){
                return tmp2;
            }
            else {
                return tmp3;
            }
        }
    }
}


int main() {
    vector<Point> points;
    srand(time(NULL));
    int N = 10000;
    for (int i = 0; i <= N; i++) {
        points.push_back(Point(rand() % 100, rand() % 100));
    }
    cout << N << endl;
    auto t1 = std::chrono::high_resolution_clock::now();
    auto minimum = closest_pair1(points);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration<double>(t2 - t1).count();
    cout << minimum.first<< " ";
    cout << minimum.second;
    std::cout << " Brutforce Time: " << time << " sec." << std::endl;

    auto t3 = std::chrono::high_resolution_clock::now();
    auto minimum2 = closest_pair(points);
    auto t4 = std::chrono::high_resolution_clock::now();
    auto time2 = std::chrono::duration<double>(t4 - t3).count();
    cout << minimum2.first<< " ";
    cout << minimum2.second;
    std::cout << " RIV Time: " << time2 << " sec." << std::endl;
 }
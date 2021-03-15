#include <iostream>
#include <chrono>
#include <vector>
#include <cmath>
#include <random>
#include <fstream>
#include <sstream>
#include <eigen3/Eigen/Dense>
#include "convexHull.hpp"

using namespace std;
using namespace std::chrono;
using namespace Eigen;

default_random_engine generator;

int main(){
    high_resolution_clock::time_point start_time;
    vector<double> run_time;

    for(int i = 5; i < 100; i++){
        /* Generator random points */
        normal_distribution<double> distribution(i, 100);
        vector<Vector3d> points;
        for(int j = 0; j < i*i; j++){
            double x = distribution(generator);
            double y = distribution(generator);
            double z = distribution(generator);
            points.push_back(Vector3d(x, y, z));
        }

        start_time = high_resolution_clock::now();

        cs271::ConvexHull hull(points);
        hull.run();
        
        auto elapsedTime = duration_cast<microseconds>(high_resolution_clock::now() - start_time);
        cout<<elapsedTime.count()/1000000.0<<endl;
        run_time.push_back(elapsedTime.count()/1000000.0);

    }

    ofstream out("../result/time.txt");
    if(out.is_open()){
        for(auto time: run_time){
            out<<time<<endl;
        }
    }
    out.close();

    return 0;
}
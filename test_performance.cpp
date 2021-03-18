#include <iostream>
#include <chrono>
#include <vector>
#include <cmath>
#include <random>
#include <fstream>
#include <sstream>
#include <eigen3/Eigen/Dense>
#include "convexHull.hpp"

#define NUM_SAMPLES 2

using namespace std;
using namespace std::chrono;
using namespace Eigen;

default_random_engine generator;

int main(int argc, char *argv[]){
    
    high_resolution_clock::time_point hull_clock, collision_clock;
    vector<double> hull_runtime, collision_runtime;

    for(int i = 10; i < 1000; i += 20){
        /* Generator random points */
        normal_distribution<double> distribution(i, i);
        vector<Vector3d> points1, points2;
        for(int j = 0; j < i*i; j++){
            double x = distribution(generator);
            double y = distribution(generator);
            double z = distribution(generator);
            points1.push_back(Vector3d(x, y, z));
        }
        for(int j = 0; j < i*i; j++){
            double x = distribution(generator);
            double y = distribution(generator);
            double z = distribution(generator);
            points2.push_back(Vector3d(x, y, z));
        }

        double hull_time = 0, collision_time = 0;
        bool flag;
        for(int k = 0; k < NUM_SAMPLES; k++){
            cs271::ConvexHull hull1(points1), hull2(points2);
            hull_clock = high_resolution_clock::now();

            hull1.run();
            hull2.run();

            auto hull_elapsed = duration_cast<milliseconds>(high_resolution_clock::now() - hull_clock);

            collision_clock = high_resolution_clock::now();

            flag = cs271::isCollide(hull1, hull2);

            auto collision_elapsed = duration_cast<milliseconds>(high_resolution_clock::now() - collision_clock);

            hull_time += (hull_elapsed.count()/1000.0);
            collision_time += (hull_elapsed.count()/1000.0);
        }
        hull_time /= (2*NUM_SAMPLES);
        collision_time /= NUM_SAMPLES;

        cout<<"i = "<<i<<", convex hull time = "<<hull_time<<", collision time = "<<collision_time<<endl;
        hull_runtime.push_back(hull_time);
        collision_runtime.push_back(collision_time);
    }

    ofstream out1("../result/hull_time.txt");
    if(out1.is_open()){
        for(auto time: hull_runtime){
            out1<<time<<endl;
        }
    }
    out1.close();

    ofstream out2("../result/collision_time.txt");
    if(out2.is_open()){
        for(auto time: collision_runtime){
            out2<<time<<endl;
        }
    }
    out2.close();

    return 0;
}
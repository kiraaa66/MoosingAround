// Moose Code Attempt 1 - Kira Tarasuk

#include <iostream>
#include <random>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <map>


using namespace std;

#define players 2
#define fields 3
#define runs 10
#define gens 10
#define MNM 2



//function definitions
int expFun(int x);



int main(){

    int i;
    int j;
    int k;

    vector<vector<int>> moosePlays; // potentially use an array, perk of vector is it is user defined length
    vector<vector<int>> fieldGrowth; // keeps track of the field growth after each iteration of the game


    for (i = 0; i < runs; i++){
        // resets the original field growth every round
        fieldGrowth[0][0] = expFun(0);
        fieldGrowth[1][0] = expFun(0);
        fieldGrowth[2][0] = expFun(0);
        
        for (j = 0; j < gens; j++){ // this is the runs within the population



        }
    }



}


//functions
int expFun(int x){

    return (10*exp(x))/(1 + exp(x)); // returns the function since it cannot be declared on its own

}
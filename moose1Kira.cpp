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
#define runs 30
#define gens 40
#define MNM 2



//function definitions
int expFun(int x);



int main(){

    int i;
    int j;
    int k;

    vector<vector<int>> moosePlays;





}


//functions
int expFun(int x){

    return (10*exp(x))/(1 + exp(x)); // returns the function since it cannot be declared on its own

}
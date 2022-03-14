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
#define seed 234329 // Constant seed so output will be the same every run, for debugging


//function definitions
int expFun(int x);



int main(){

    int i;
    int j;
    int k = 0;
    int moose1Field;
    int moose2Field;
    vector<int> fieldTracker(fields);
    vector<int> mooseConsumption(players);

    default_random_engine rand(seed);
    // Set the size of the vectors (number of players, number of fields)
    vector <vector<int>> moosePlays(players); // potentially use an array, perk of vector is it is user defined length
    vector <vector<int>> fieldGrowth(fields); // keeps track of the field growth after each iteration of the game

    // Reserve space
    for (i = 0; i < players; i++) {
        moosePlays[i].reserve(gens);
    }

    for (i = 0; i < fields; i++) {
        fieldGrowth[i].reserve(gens);
    }

    uniform_int_distribution<int> fieldsel(0, fields - 1);
    for (i = 0; i < runs; i++){
        // resets the original field growth every round
        fieldGrowth[0][0] = expFun(0);
        fieldGrowth[1][0] = expFun(0);
        fieldGrowth[2][0] = expFun(0);
        
        //resets the value of the field at the beginning
        fieldTracker[0] = 0;
        fieldTracker[1] = 0;
        fieldTracker[2] = 0;
        
        //resets the moose consumption every round
        mooseConsumption[0] = 0;
        mooseConsumption[1] = 0;


        for (j = 0; j < gens; j++){ // this is the runs within the population
            //use a random generator to determine which field the moose populate to on each turn
            moosePlays[0][j] = fieldsel(rand);
            moosePlays[1][j] = fieldsel(rand);
            moose1Field = moosePlays[0][j]; // sets a variable to keep track of individual plays
            moose2Field = moosePlays[1][j];

            if (moose1Field == moose2Field){
                fieldTracker[moose1Field] -= 1; // takes away the growth rate by one if the moose are fighting
                if (fieldTracker[moose1Field] <= 0){ // makes sure that the minimum it can go to is one
                    fieldTracker[moose1Field] = 0; // Should this be 1?  See comment one line up.
                    
                }
                fieldGrowth[moose1Field][j] = expFun(fieldTracker[moose1Field]);
                for (k = 0; k < fields; k++){ // goes through each of the fields
                    if (k != moose1Field){ // this means it changes any fields the moose weren't in
                        fieldTracker[k] += 1;
                        fieldGrowth[k][j] = expFun(fieldTracker[k]); // sets the field growth to be this new one
                    }
                }
            }
            else {
                for (k = 0; k < fields; k++){

                    if (k == moose1Field){
                        mooseConsumption[0] = expFun(fieldTracker[k]) - expFun(0);
                        fieldTracker[k] -= 1;
                        
                    }
                    else if (k == moose2Field){
                        mooseConsumption[1] = expFun(fieldTracker[k]) - expFun(0);
                        fieldTracker[k] -= 1;
                    }
                    else{
                        fieldTracker[k] += 1;
                        fieldGrowth[k][j] = expFun(fieldTracker[k]);
                    }

                }
            }
            cout<< "Run " << i << "Generation " << j << "Moose 1 Field: " << moosePlays[0][j] << "Moose 2 Field: " << moosePlays[1][j] << endl; 
        }
    }

}
//functions
int expFun(int x){

    return (10*exp(x))/(1 + exp(x)); // returns the function since it cannot be declared on its own

}
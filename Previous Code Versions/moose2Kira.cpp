// Moose Code Attempt 2 - Kira Tarasuk

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
#define runs 4
#define gens 10
#define MNM 2
#define turns 4


#define seed 234329 // suggested by Michael

//function definitions
int expFun(int x);
void expFit(vector<double> fieldTracker, vector<vector<double>> fieldGrowth,  vector<vector<int>> moosePlays, vector<int> mooseConsumption);


int main(){

    int i;
    int j;
    //int k;
    //int moose1Field;
    //int moose2Field;

    default_random_engine rand(seed);

    uniform_int_distribution<int> fieldSelection(0, fields - 1);

    //vector changes given by Michael
    vector<double> trackFields(fields);
    vector<int> mooseFood(players);

    vector<vector<int>> mooseMoves(players); // potentially use an array, perk of vector is it is user defined length
    vector<vector<double>> fieldRate(fields); // keeps track of the field growth after each iteration of the game

    //new vectors for keeping track of all moves each moose has done
    vector<vector<int>> moose1Plays(runs);
    vector<vector<int>> moose2Plays(runs);



    //reserve space given by Michael
    for (i = 0; i < players; i++){
        mooseMoves[i].reserve(gens);
    }

    for (i = 0; i < fields; i++){
        fieldRate[i].reserve(gens);
    }

// this reserves space for generations in each of the moose selections, also keeps track of all their choices every run
    for (i = 0; i < runs; i++){
        moose1Plays[i].reserve(gens);
        moose2Plays[i].reserve(gens);
    }


//Uniform int distribution change given by Michael
    
    for (i = 0; i < turns; i++){
        // resets the original field growth every round
        for (j = 0; j < gens; j++){
            mooseMoves[0][j] = fieldSelection(rand); // change from Michael
            mooseMoves[1][j] = fieldSelection(rand);
        }
        //expFit(trackFields, fieldRate, mooseMoves, mooseFood); // runs this through
        
    }

    //tournament
    // currently have 4 runs with each turn 

    // setting up a tournament to determine who is the worst from the generations within an individual run








}
//functions
int expFun(int x){

    return (10*exp(x))/(1 + exp(x)); // returns the function since it cannot be declared on its own

} 


//void expFit(vector<double> fieldTracker, vector<vector<double>> fieldGrowth,  vector<vector<int>> moosePlays, vector<int> mooseConsumption){

/*
    int i;
    int j;
    int k;
    int moose1Field;
    int moose2Field;

    
    fieldGrowth[0][0] = expFun(1);
    fieldGrowth[1][0] = expFun(1);
    fieldGrowth[2][0] = expFun(1);
        
    //resets the value of the field at the beginning
    fieldTracker[0] = 1;
    fieldTracker[1] = 1;
    fieldTracker[2] = 1;
        
    //resets the moose consumption every round
    mooseConsumption[0] = 0;
    mooseConsumption[1] = 0;
        // write an algorithm that will go through each of the players


    for (j = 0; j < gens; j++){ // this is the runs within the population
            //use a random generator to determine which field the moose populate to on each turn            
        
        moose1Field = moosePlays[0][j]; // sets a variable to keep track of individual plays
        moose2Field = moosePlays[1][j];

        if (moose1Field == moose2Field){
            fieldTracker[moose1Field] -= 1; // takes away the growth rate by one if the moose are fighting
            if (fieldTracker[moose1Field] <= 0){ // makes sure that the minimum it can go to is zero so it will reset to be zero
                fieldTracker[moose1Field] = 0;
            }
            fieldGrowth[moose1Field][j] = 0; // since there was no growth this time
            for (k = 0; k < fields; k++){ // goes through each of the fields
                if (k != moose1Field){ // this means it changes any fields the moose weren't in
                        //fieldTracker[k] += 1;
                    fieldTracker [k] += 1;
                    fieldGrowth[k][j] = expFun(fieldTracker[k]); // sets the field growth to be this new one
                        //fieldTracker[k] += fieldGrowth[k][j];
                }
            }
        }
        else {
            for (k = 0; k < fields; k++){
                if (k == moose1Field){
                    mooseConsumption[0] += expFun(fieldTracker[k]) - expFun(0);
                    fieldTracker[k] -= 1;
                    if (fieldTracker[k] <= 0){ // makes sure that the minimum it can go to is zero so it will reset to be zero
                        fieldTracker[k] = 0;
                    }
                    fieldGrowth[k][j] = 0;                    
                }
                else if (k == moose2Field){
                    mooseConsumption[1] += expFun(fieldTracker[k]) - expFun(0);
                    fieldTracker[k] -= 1; 
                    if (fieldTracker[k] <= 0){ // makes sure that the minimum it can go to is zero so it will reset to be zero
                        fieldTracker[k] = 0;
                    }
                    fieldGrowth[k][j] = 0; 
                }
                else{
                    fieldTracker[k] += 1;
                    fieldGrowth[k][j] = expFun(fieldTracker[k]);
                        //fieldTracker[k] += fieldGrowth[k][j];
                }
            }
        }
        cout << "Run " << 1 << " Generation " << j << " Moose1 Field: " << moosePlays[0][j] << " || Moose2 Field: " << moosePlays[1][j] << endl; 
        cout << "Field 0 Value: " << fieldTracker[0] << " Field 1 Value: " << fieldTracker[1] << " Field 2 Value: " << fieldTracker[2] << endl;
        cout << "Moose 1 Value: " << mooseConsumption[0] << " || Moose 2 Value: " << mooseConsumption[1] << endl;

    }
*/
//}
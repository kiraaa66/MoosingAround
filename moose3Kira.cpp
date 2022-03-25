//new code part 3 - based on previus pseudocode

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
#define runs 1
#define gens 4
#define MNM 2
#define turns 10

#define seed 234329 // suggested by Michael

//function definitions
int expFun(int x);

int fitFUN(vector<int> moose1);

int main(){

    int i, j, k; //for loop variables

    default_random_engine rand(seed);
    uniform_int_distribution<int> fieldSelection(0, fields - 1);

    //set up calculating the random score each time
    vector<vector<int>> moosePlays(gens);
    vector<int> mooseVals(gens);

    for (k = 0; k < runs; k++){
        for (i = 0; i < gens; i++){
            moosePlays[i].reserve(turns);
        }
        for (i = 0; i < gens; i++){
            for (j = 0; j < turns; j++){
                moosePlays[i][j] = fieldSelection(rand);
            }
            mooseVals[i] = fitFUN(moosePlays[i]);
            cout << "Moose Val Gen: " << i << "Turn: " << j << " " << mooseVals[i] << endl; 
        }
    }

}
int expFun(int x){

    return (10*exp(x))/(1 + exp(x)); // returns the function since it cannot be declared on its own

} 

int fitFUN(vector<int> moose1){

    vector<int> moose2(turns); // moose2 picks fo this particular round

    int i, j; // for loops variables
    int moose1Val = 0;
    int moose2Val = 0;

    vector<int> fieldNum(fields);
    for (i = 0; i < fields; i++){
        fieldNum[i] = 1;
    }

    //random variables for moose 2 strategy
    default_random_engine random(seed);
    uniform_int_distribution<int> moose2Selection(0, fields - 1);

    //randomly selects the moose fields for each of the turns
    for (i = 0; i < turns; i++){
        moose2[i] = moose2Selection(random);
    }

    for (i = 0; i < turns; i++){

        if (moose1[i] == moose2[i]){ // if the field at that point is equal, then it will assign the respective values
            fieldNum[moose1[i]] -= 1;
            for (j = 0; j < fields; j++){
                if (fieldNum[j] != moose1[i]){
                    fieldNum[j] += 1;
                }
                
            }
        }
        else{
            for (j = 0; j < fields; j++){
                if (j == moose1[i]){
                    moose1Val += (expFun(fieldNum[j]) - expFun(0));
                    fieldNum[j] -= 1;
                }
                else if(j == moose2[i]){
                    moose2Val += (expFun(fieldNum[j]) - expFun(0));
                    fieldNum[j] -= 1;
                }
                else{
                    fieldNum[j] += 1;
                }
            }
        }
        
        for (j = 0; j < fields; j++){
            if (fieldNum[j] <= 0){ // no field can go below zero, so it resets the value if it does hit zero
                fieldNum[j] = 0;
            }
        }

    }
    return moose1Val;
}
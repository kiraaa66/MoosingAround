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
#define runs 15
#define gens 100000
#define MNM 3
#define turns 10
#define popsize 10

#define seed 234329 // suggested by Michael

//function definitions
int expFun(int x);

int fitFUN(vector<int> moose1);

int main(){

    int i, j, k, run; //for loop variables

    ofstream mooseOutput;

    int curbest = 0;
    int popbest;
    int endgen;
    int wfit;
    int bfit;
    int fitcap = 0; 
    // the greatest amount they could achieve would be going to a field that has been allowed to replenish its resources each time without anyone else going???? math ???
    for (i = 1; i <= turns; i++){
        fitcap += (expFun(i) - expFun(0));
    }
    int cross;
    int pert;
    default_random_engine rand(seed);
    uniform_int_distribution<int> fieldSelection(0, fields - 1);
    //uniform_int_distribution<int> tourdist(0,popsize-1);
    uniform_int_distribution<int> crossdist(0,turns-1);
    vector<int> winlos (4); // vector that holds tournament winners and losers.

    //set up calculating the random score each time
    vector<vector<int>> moosePlays(popsize);
    vector<int> mooseVals(popsize);

    mooseOutput.open("mooseOutput2.txt");

    for (run = 0; run < runs; run++){ // how many times this is run

        for (i = 0; i < popsize; i++){ // leaving enough spaces for turns
            moosePlays[i].resize(turns);
        }
        for (i = 0; i < popsize; i++){
            for (j = 0; j < turns; j++){
                moosePlays[i][j] = fieldSelection(rand); // randomly selects a field for moose1 for each turn
                //cout << "pop: " << i << " Turn " << j << " "<< moosePlays[i][j] << endl; // checking if it prints fields
            }
            //currently a seg fault in this function itself, works printing otherwise
            mooseVals[i] = fitFUN(moosePlays[i]);
            //cout << "Moose Val: " << i << " " << mooseVals[i] << endl;
            if (mooseVals[i] > curbest){ // writes out what the best value is
                curbest = mooseVals[i];
                popbest = i;
            }
        }

        //tournament
        endgen = gens; // This is to tell if we found the global optima before the end

		for(i = 1; i <= gens; i++)	{ // loop for tournaments.
			wfit = 0; // reset worst possible fitness.
			bfit = fitcap; // reset best possible fitness.
			if(curbest >= bfit)	{ // has max fitness been achieved?
				endgen = i; // marks when global optima was found.
				i = gens; // skip to the ends
				continue; // skips the rest of EA process if the best possible fitness has been found
			}
			for(j = 0; j < popsize; j++){
				if(mooseVals[j]>=wfit)	{ // best parent is fit.
					winlos[1] = winlos[0]; // shove down current best to second best.
					winlos[0] = j; // crown new best.
					wfit = mooseVals[j]; // set new bar to beat.
				}
				if(mooseVals[j]<=bfit)	{ // worst competitor is unfit.
					winlos[2] = winlos[3]; // worst becomes second worst.
					winlos[3] = j; // crown new worst.
					bfit = mooseVals[j]; // assigns the new worst to bfit
				}
			}

			cross = crossdist(rand); // pick random point between loci
			for(k=2; k<4; k++)	{ // we overwrite our two tournament losers differently depending our crossover type.
				for(j = 0; j < cross; j++)	{ // first parent is leading.
					moosePlays[winlos[k]][j] = moosePlays[winlos[k%2]][j]; // overwrite loser.
				}
				for(j = cross; j < turns; j++)	{ // second parent is leading.
					moosePlays[winlos[k]][j] = moosePlays[winlos[(k+1)%2]][j]; // overwrite rest of loser.
				}
				for(j = 0; j<MNM; j++)	{ // mutate the children born from crossover
					pert = crossdist(rand); // pick mutation point.
					moosePlays[winlos[k]][pert] = fieldSelection(rand); // overwrite this mutated entry.
				}
				mooseVals[winlos[k]] = fitFUN(moosePlays[winlos[k]]); // call on fitness function for new populations member.
				if(mooseVals[winlos[k]] > curbest)	{ // New champion
					curbest = mooseVals[winlos[k]]; // Raise the bar for best fitness.
					popbest = winlos[k]; // mark new best member of population.
				}
			}
            if ((i%10000) == 0){
                mooseOutput << mooseVals[popbest] << endl;
            }
		}
        mooseOutput << " PRODUCED MEMBER OF FITNESS " << mooseVals[popbest] << " AT GENERATION " << endgen << endl;
        //for (i = 0; i < turns; i++){
          //  mooseOutput << moosePlays[popbest][i];

        //}
        //mooseOutput << endl;

		curbest = 0; // reset curbest for next run.
		popbest = 0; // reset popbest for next run.

    }
    mooseOutput.close();
    return 0;

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
    moose2[0] = 0;
    //randomly selects the moose fields for each of the turns - old version

    for (i = 0; i < turns; i++){ //chooses moose values by just going to the field next to it each time
        moose2[i] = moose2[i-1] + 1;
        if (moose2[i] > 2){
            moose2[i] = 0;
        }
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
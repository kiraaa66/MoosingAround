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
#define popsize 4

#define seed 234329 // suggested by Michael

//function definitions
int expFun(int x);

int fitFUN(vector<int> moose1);

int main(){

    int i, j, k; //for loop variables

    int curbest = 0;
    int popbest;
    int endgen;
    int wfit;
    int bfit;
    int fitcap = 40; // work on math for what this would be
    int cross;
    int pert;

    default_random_engine rand(seed);
    uniform_int_distribution<int> fieldSelection(0, fields - 1);
    uniform_int_distribution<int> tourdist(0,popsize-1);
    uniform_int_distribution<int> crossdist(0,turns-1);
    vector<int> winlos (4); // vector that holds tournament winners and losers.

    //set up calculating the random score each time
    vector<vector<int>> moosePlays(popsize);
    vector<int> mooseVals(popsize);


    for (k = 0; k < runs; k++){ // how many times this is run

        for (i = 0; i < popsize; i++){ // leaving enough spaces for turns
            moosePlays[i].reserve(turns);
        }
        for (i = 0; i < popsize; i++){
            for (j = 0; j < turns; j++){
                moosePlays[i][j] = fieldSelection(rand); // randomly selects a field for moose1 for each turn
                cout << moosePlays[i][j] << endl; // checking if it prints fields
            }
            //currently a seg fault in this function itself, works printing otherwise
            mooseVals[i] = fitFUN(moosePlays[i]);
            cout << "Moose Val: " << i << " " << mooseVals[i] << endl;
            if (mooseVals[i] > curbest){ // writes out what the best value is
                curbest = mooseVals[i];
                popbest = i;
            }
        }







        //tournament
        endgen = gens; // Assume we fail until proven otherwise.

		for(i = 1; i <= gens; i++)	{ // loop for tournaments.
			wfit = 0; // reset worst possible fitness.
			bfit = fitcap; // reset best possible fitness.
			if(curbest >= bfit)	{ // has max fitness been achieved?
				endgen = i; // marks when global optima was found.
				i = gens; // skip to the ends
				continue; // skips the rest of EA process if the best possible fitness has been found
			}
			for(j = 0; j < popsize; j++)	{ // picking out tourney entrants.
				if(mooseVals[j]>=wfit)	{ // best parent is fit.
					winlos[1] = winlos[0]; // shove down current best to second best.
					winlos[0] = mooseVals[j]; // crown new best.
					wfit = mooseVals[j]; // set new bar to beat.
				}
				if(mooseVals[j]<=bfit)	{ // worst competitor is unfit.
					winlos[2] = winlos[3]; // worst becomes second worst.
					winlos[3] = mooseVals[j]; // crown new worst.
					bfit = mooseVals[j]; // lower the ceiling on badness.
				}
			}

			cross = crossdist(rand); // pick random point between loci
			for(k=2; k<4; k++)	{ // we overwrite our two tournament losers differently depending our crossover type.
				for(j = 0; j < cross; j++)	{ // first parent is leading.
					pop[winlos[k]][j] = pop[winlos[k%2]][j]; // overwrite loser.
				}
				for(j = cross; j < len; j++)	{ // second parent is leading.
					pop[winlos[k]][j] = pop[winlos[(k+1)%2]][j]; // overwrite rest of loser.
				}
				for(j = 0; j<MNM; j++)	{ // mutate the children born from crossover
					pert = crossdist(rand); // pick mutation point.
					pop[winlos[k]][pert] = initdist(rand); // overwrite this mutated entry.
				}
				fit[winlos[k]] = fitFUN(pop[winlos[k]]); // call on fitness function for new population member.
				if(fit[winlos[k]] > curbest)	{ // New champion
					curbest = fit[winlos[k]]; // Raise the bar for best fitness.
					popbest = winlos[k]; // mark new best member of population.
				}
			}
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
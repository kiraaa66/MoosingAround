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

/*

The following code implements a very simple version of an evolutionary algorithm.
   it uses one point crossover
   it uses tournament selection
   it uses k-point mutation.
   and the fitness function merely takes the sum of the entries found in the chromosome.
The algorithm attempts to maximize this value as much as possible.

*/

#define popsize 100 // Control on population size.
#define runs 30 // Number of iterative runs.
#define tour 15 // Number of tournament participants.
#define gens 40 // Number of EA iterations per run.
#define MNM 8 // Maximum number of mutations.

#define len 5 // how long is the chromosome of each population member.
#define locspan 7 // what range of values are permitted within a loci.

int EXPfit(vector<int> chrom); // fitness function that returns sum of chromosome entries. this is the same as a dynamic array in C

int main()	{

	// Variables Required for Evolutionary Algorithm
	int i,j,k; // loop counter variables.
	int run; // tracks what run of the EA is being done.
	int wfit; // worst fitness score possible.
	int bfit; // best fitness score possible.
	
	int endgen; // generation where global optima is found.
	int curbest = 0; // best fitness amidst population.
	int popbest = 0; // population index for best member among the population.
	int fitcap = len*(locspan-1); // fitness value that will end the run early if attained.
	int cross; // points where one / two point crossover occur.
	int pert; // point where mutation can happen.
	vector<vector<int>> pop(popsize); // creates population.
	for(i = 0; i < popsize; i++)	{ // resize each chromosome.
		pop[i].resize(len); // so that it is of a proper length.
	}
	vector<double>  fit (popsize); // separate array for fitness of pop members.
	vector<int> winlos (4); // vector that holds tournament winners and losers.
	vector<int> tourn (tour); // vector that holds tournament entrants.

	// Many Different Random Distribution Seeds
	unsigned seed = chrono::system_clock::now().time_since_epoch().count(); // time based seed.
	default_random_engine rand (seed); // generator of random values. // generates any random number
	uniform_int_distribution<int> crossdist(0,len-1); // random generator used for crossover. // gives a range that can produce a random number
	uniform_int_distribution<int> tourdist(0,popsize-1); // random generator used for tournament selection.
	uniform_int_distribution<int> initdist(0,locspan-1); // random generator used to fill chromosome entries.
	
	for(run = 0; run < runs; run++)	{ // go through each run.
		//cout << "RUN " << run+1; // printing this every time

		// Population Initialization
		for(i = 0; i < popsize; i++)	{ // initialize each chromosome
			for(j = 0; j < len; j++)	{ // each single entry
				pop[i][j] = initdist(rand); // pick value that falls within greedspan
			}
			fit[i] = EXPfit(pop[i]); // check fitness of each population member.
			if(fit[i] > curbest)	{ // is this a best fitness pop member.
				curbest = fit[i]; // then update current best.
				popbest = i; // mark this member as the population's best.
			}
		}

		// Generation Iteration
		endgen = gens; // Assume we fail until proven otherwise.

		for(i = 1; i <= gens; i++)	{ // loop for tournaments.
			wfit = 0; // reset worst possible fitness.
			bfit = fitcap; // reset best possible fitness.
			if(curbest >= bfit)	{ // has max fitness been achieved?
				endgen = i; // marks when global optima was found.
				i = gens; // skip to the ends.
				continue; // skips the rest of EA process.
			}
			for(j = 0; j < tour; j++)	{ // picking out tourney entrants.
				tourn[j] = tourdist(rand); // pick member of population.
				k = 0; // start looking from start of bracket.
				while(k < j)	{
					if(tourn[k] == tourn[j])	{ // is this a duplicate?
						tourn[j] = tourdist(rand); // sample a new entrant.
						k = 0; // start checking again.
					}
					else	{ // we can keep checking forward.
						k++; // increment to next entry.
					}
				}
				if(fit[tourn[j]]>=wfit)	{ // best parent is fit.
					winlos[1] = winlos[0]; // shove down current best to second best.
					winlos[0] = tourn[j]; // crown new best.
					wfit = fit[tourn[j]]; // set new bar to beat.
				}
				if(fit[tourn[j]]<=bfit)	{ // worst competitor is unfit.
					winlos[2] = winlos[3]; // worst becomes second worst.
					winlos[3] = tourn[j]; // crown new worst.
					bfit = fit[tourn[j]]; // lower the ceiling on badness.
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
				fit[winlos[k]] = EXPfit(pop[winlos[k]]); // call on fitness function for new population member.
				if(fit[winlos[k]] > curbest)	{ // New champion
					curbest = fit[winlos[k]]; // Raise the bar for best fitness.
					popbest = winlos[k]; // mark new best member of population.
				}
			}
			if ((i%10) == 0){
                cout << fit[popbest] << endl;
        	}

		}
		
		cout << " PRODUCED MEMBER OF FITNESS " << fit[popbest] << " AT GENERATION " << endgen << endl;
		curbest = 0; // reset curbest for next run.
		popbest = 0; // reset popbest for next run.
	}
	return(0); // time to stop.
}

int EXPfit(vector<int> chrom)	{ // this is a function OHHHHHHH
	int i; // loop counter variable.
	int fitret = 0; // return for fitness of chromosome.
	for(i = 0; i < len; i++)	{ // for each chromosome entry.
		fitret += chrom[i]; // add the value of this chromosome.
	}
	return fitret; // return this completed value.
}
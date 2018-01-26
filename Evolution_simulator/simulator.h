#ifndef SIM_H
#define SIM_H

#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>
#include "simulatorObject.h"

enum Exceptions{INCORRECT_SIZE};

template<typename Object>
struct SimCompare
{
	bool operator()(Object *o1,Object *o2)
	{
		return o1->GetFitness() > o2->GetFitness();
	}
};

template<typename Object, typename TargetType, class Comp = SimCompare<Object> >
class Simulator
{
public:

~Simulator()
{
	for( int i = 0; i < size; ++i)
	{
		delete population[i];
	}
	population.clear();
}
	
void Init(int population_size,float mutationrate,TargetType objectTarget)
{
	if(population_size < 10 || population_size > 1000)
	{
		throw INCORRECT_SIZE;
	}
	size = population_size;
	mutation = std::fabs(mutationrate - (int)mutationrate);
	numberOfGenerations = 0;
	target = objectTarget;
	for( int i = 0; i < size; ++i)
	{
		Object *object = new Object();
		object->Random();
		population.push_back(object);
	}
}
	
void SetMutation(float mutationrate)
{
	mutation = std::fabs(mutationrate - (int)mutationrate);
}
	
void MakeGeneration()
{
	for( int i = 0; i < size; ++i)
	{
		population[i]->CalculateFitness(target);
	}
	std::sort(population.begin(),population.end(),simComp);
	for( int i = 0; i < size/2; ++i)
	{
		delete population[size-i];
		population[size-i] = population[i]->Mutate(mutation);
	}
	++numberOfGenerations;
}
	
void MakeGeneration(int gens)
{
	for( int i = 0; i < gens; ++i)
	{
		MakeGeneration();
		Results(1);
	}
}

void Results()
{
	std::cout << "Generation No." << numberOfGenerations << " results:" << std::endl;
	std::cout << "Best: " << population[0]->Draw() << std::endl;
	std::cout << "Score: " << population[0]->GetFitness() << std::endl;
	std::cout << "Median: " << population[size/2]->Draw() << std::endl;
	std::cout << "Score: " << population[size/2]->GetFitness() << std::endl;
	std::cout << "Worst: " << population[size-1]->Draw() << std::endl;
	std::cout << "Score: " << population[size-1]->GetFitness() << std::endl;
}

void Results(int option)
{
	switch(option)
	{
		case 0:
		std::cout << population[0]->Draw() << std::endl;
		break;
		case 1:
		std::cout << population[0]->Draw() << "    " << numberOfGenerations << std::endl;
		break;
	}
	

}

private:

	std::vector<Object*> population;
	int size;
	float mutation;
	int numberOfGenerations;
	Comp simComp;
	TargetType target;
};

#endif //SIM_H

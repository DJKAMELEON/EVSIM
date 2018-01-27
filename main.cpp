#include <iostream>

#include "Evolution_simulator/simulator.h"
#include "Neural_nets/neuralnet.h"

int main()
{
	int populationsize = 100;
	float mutationrate = 0.3;
	double target = -12.34567;
	Simulator< NeuralNet , double > s;
	s.Init(populationsize,mutationrate,target);

	s.MakeGeneration(100);
	s.Results();
	
	return 0;
}

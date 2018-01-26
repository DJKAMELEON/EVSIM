#include <iostream>

#include "simulator.h"
#include "stringObject.h"

//void Beolvas(int &populationsize, float &mutationrate, std::string &target);

int main()
{
	int populationsize = 1000;
	float mutationrate = 0.3;
	std::string target = "Life is _STRANGE_37!";
	//Beolvas(populationsize,mutationrate,target);
	Simulator< StringObject , std::string > s;
	s.Init(populationsize,mutationrate,target);

	s.MakeGeneration(1000);
	s.Results();
	
	return 0;
}
/*
void Beolvas(int &populationsize, float &mutationrate, std::string &target)
{
	std::cout << "Population size: (10-1000)" << std::endl;
	bool fail = false;
	do
	{
		fail = false;
		std::cin >> populationsize;
		if(std::cin.fail() || populationsize < 10 || populationsize > 1000)
		{
			fail = true;
		}
	}while(fail);
	std::cout << "Mutation rate: (0.1-5.0)" << std::endl;
	do
	{
		fail = false;
		std::cin >> mutationrate;
		if(std::cin.fail() || mutationrate < 0.0 || mutationrate > 5.0)
		{
			fail = true;
		}
	}while(fail);
	std::cout << "Target string: (20char)" << std::endl;
	do
	{
		fail = false;
		std::cin >> target;
		if(std::cin.fail() || target.size() != 20)
		{
			fail = true;
		}
	}while(fail);
}*/

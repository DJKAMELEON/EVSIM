#include <iostream>
#include "neuralnet.h"

using namespace std;

int main()
{
	NeuralNet nn(3,5,3,2);
	nn.CalculateOutput();
	nn.ShowOutput();
	
	return 0;
}

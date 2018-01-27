#include "neuralnet.h"

Layer::Layer(int neuron_number) : neuron_num(neuron_number)
{
	for(int i=0;i<neuron_number;++i)
	{
		neurons.push_back(1.0);
	}
}

Layer::~Layer()
{
}

double& Layer::operator[](int index)
{
	if( index >= 0 && index < neuron_num)
	{
		return neurons[index];
	}
	throw INCORRECT_INDEX;
}

Matrix::Matrix(int rows, int columns) : _rows(rows),_columns(columns)
{
	
	for(int i=0;i<_rows;++i)
	{
		m.push_back(vector<double>(columns,0.5));
	}
}

Matrix::~Matrix()
{
	
}

double& Matrix::operator()(int i,int j)
{
	if( i >= 0 && j >= 0 && i < _rows && j < _columns)
	{
		return m[i][j];
	}
	throw INCORRECT_INDEX;
}

void Layer::CalculateNextLayer(Layer &other,Matrix matrix)
{
	for(int i = 0;i < other.GetSize();++i)
	{
		for(int j = 0;j < neuron_num;++j)
		{
			other[i] += matrix(j,i) * neurons[j];
		}
	}
}

NeuralNet::NeuralNet(int layer_number,int neuron_number,int inputs,int outputs) : layer_num(layer_number)
{
	if(layer_number < 3) throw INCORRECT_LAYER_NUMBER;
	layers.push_back(Layer(inputs));
	for(int i=0;i<layer_number-2;++i)
	{
		layers.push_back(Layer(neuron_number));
	}
	layers.push_back(Layer(outputs));
	matrixes.push_back(Matrix(inputs,neuron_number));
	for(int i=0;i<layer_number-3;++i)
	{
		matrixes.push_back(Matrix(neuron_number,neuron_number));
	}
	matrixes.push_back(Matrix(neuron_number,outputs));
	fitness = 0;
}

void NeuralNet::CalculateOutput()
{
	for(int i=0;i<layer_num-1;++i)
	{
		layers[i].CalculateNextLayer(layers[i+1],matrixes[i]);
	}
}

void NeuralNet::ShowOutput()
{
	for(int i=0;i<layers[layer_num-1].GetSize();++i)
	{
		cout << layers[layer_num-1][i] << endl;
	}
}

void NeuralNet::Random()
{

}

std::string NeuralNet::Draw()
{
	std::stringstream ss;
	ss << "Output: ";
	for(int i=0;i<layers[layer_num-1].GetSize();++i)
	{
		ss << layers[layer_num-1][i] << " ";
	}
	return ss.str();
}

int NeuralNet::GetFitness()const
{
	return fitness;
}

void NeuralNet::CalculateFitness(double &target)
{
	CalculateOutput();
	double score = 1.0;
	for(int i=0;i<layers[layer_num-1].GetSize();++i)
	{
		score *= layers[layer_num-1][i];
	}
	fitness = target > score ? 100 - (target - score) : 100 - (score - target);
	if(fitness < 0)fitness = 0;
}

NeuralNet* NeuralNet::Mutate(float mutation)
{
	NeuralNet *nn = new NeuralNet(layer_num,layers[1].GetSize(),
		layers[0].GetSize(),layers[layer_num-1].GetSize());
	return nn;
}
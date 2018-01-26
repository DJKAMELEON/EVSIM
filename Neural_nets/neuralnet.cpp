#include "neuralnet.h"
#include <iostream>

Layer::Layer(int neuron_number) : neuron_num(neuron_number)
{
	neurons = new double[neuron_number];
	for(int i=0;i<neuron_number;++i)
	{
		neurons[i] = 1.0;
	}
}

Layer::~Layer()
{
	delete[] neurons;
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

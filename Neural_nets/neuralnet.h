#ifndef NEURALNET_H
#define NEURALNET_H

#include <vector>

using namespace std;

class Matrix
{
public:
	Matrix(int rows, int columns);
	double& operator()(int i,int j);
	~Matrix();
private:
	int _rows;
	int _columns;
	vector<vector<double> > m;
};

enum Exceptions{INCORRECT_INDEX,INCORRECT_LAYER_NUMBER};

class Layer
{
public:
	Layer(int neuron_number);
	double& operator[](int index);
	void CalculateNextLayer(Layer &other,Matrix matrix);
	~Layer();
	int GetSize(){return neuron_num;}
private:
	double* neurons;
	int neuron_num;
};

class NeuralNet
{
public:
	NeuralNet(int layer_number,int neuron_number,int inputs,int outputs);
	void CalculateOutput();
	void ShowOutput();
private:
	int layer_num;
	vector<Layer> layers;
	vector<Matrix> matrixes;
};


#endif //NEURALNET_H

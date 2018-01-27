#ifndef STROBJ_H
#define STROBJ_H

#include <string>
#include <random>
#include "simulatorObject.h"

enum StrExceptions{NOT_SAME_SIZE};

static const std::string alphanum =
	"0123456789"
	"!@#$%^&* _"
	"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	"abcdefghijklmnopqrstuvwxyz";

class StringObject final : public SimulatorObject<std::string>
{
public:
	StringObject();
	~StringObject();
	StringObject(unsigned int sizeOfString);
	void Random();
	StringObject* Mutate(float mutation);
	std::string Draw();
	int GetFitness()const;
	void CalculateFitness(std::string &target);
private:
	std::string dns;
	unsigned int size;		//ezt valahogy staticolni kéne
	std::random_device rd;
	char genRandom();
	int fitness;
};

#endif //STROBJ_H

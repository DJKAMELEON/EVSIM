#include "stringObject.h"


StringObject::StringObject(unsigned int sizeOfString) : SimulatorObject<std::string>()
{
	size = sizeOfString;
}

StringObject::~StringObject(){}

StringObject::StringObject() : SimulatorObject<std::string>()
{
	size = 20;
}

void StringObject::Random()
{
	char c = genRandom();
	dns = std::string(size,c);
}

char StringObject::genRandom()
{
    return alphanum[rd() % (alphanum.size()-1)];
}

int StringObject::GetFitness()const
{
	return fitness;
}
void StringObject::CalculateFitness(std::string &target)
{
	fitness = 0;
	if(dns.size() != target.size())
	{
		throw NOT_SAME_SIZE;
	}
	for(unsigned int i = 0; i < size; ++i)
	{
		if(target[i] == dns[i])
		{
			++fitness;
		}
	}
}

StringObject* StringObject::Mutate(float mutation)
{
	StringObject *strobj = new StringObject(size);
	strobj->dns = this->dns;
	if(mutation != 0)
	{
		for(unsigned int i = 0; i < 10*mutation; ++i)
		{
			strobj->dns[rd()%(size)] = genRandom();
		}
	}
	return strobj;
}

std::string& StringObject::Draw()
{
	return dns;
}

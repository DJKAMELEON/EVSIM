#ifndef SIMOBJ_H
#define SIMOBJ_H

template<typename TargetType>
class SimulatorObject
{
public:
	virtual void Random() = 0;
	virtual void CalculateFitness(TargetType &target) = 0;
	virtual SimulatorObject* Mutate(float mutation) = 0;
	virtual std::string& Draw() = 0;
	virtual int GetFitness()const = 0;
	virtual ~SimulatorObject(){};
	
};

#endif //SIMOBJ_H

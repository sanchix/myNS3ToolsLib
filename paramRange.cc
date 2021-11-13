
#include <math.h>
#include "ns3/log.h"
#include "ns3/nstime.h"
#include "paramRange.h"


using namespace ns3;


NS_LOG_COMPONENT_DEFINE("ParamRange");



// General


template<typename T>
ParamRange<T>::ParamRange(T * param, ProgressionType_T progressionType, int indexLimit){
	_param = param;
	initialValue = *_param;
	_progressionType = progressionType;
	_indexLimit = indexLimit;
}


template<typename T>
void ParamRange<T>::SetGeometricProgressionRate(double rate){
	definedProgressionRate = true;
	geometricProgressionRate = rate;
}

template<typename T>
void ParamRange<T>::SetAritmeticProgressionRate(T rate){
	definedProgressionRate = true;
	aritmeticProgressionRate = rate;
}

template<typename T>
bool ParamRange<T>::Next(){
	
	bool hasNext = false;
	index++;
	
	if(!definedProgressionRate){
		throw;
	}
	
	if(index <= _indexLimit){
		hasNext = true;
		if(_progressionType == PROGRESSION_ARITMETIC){
			*_param = progressionAritmetic();
		}
		else if(_progressionType == PROGRESSION_GEOMETRIC){
			*_param = progressionGeometric();
		}
		NS_LOG_DEBUG("Index: " << index << ", value: " << *_param);
	}
	
	return hasNext;
}

template<typename T>
T ParamRange<T>::Current(){
	return *_param;
}

template<typename T>
void ParamRange<T>::Reset(){
	index = 0;
	*_param = initialValue;
}


// Double
/*
double DoubleParamRange::progresionAritmetic(){
	return initialValue + index * _progressionRate;
}
*/


// Time


// Trampa

template class ParamRange<Time>;
template class ParamRange<double>;
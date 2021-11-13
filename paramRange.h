#ifndef paramRange_h
#define paramRange_h


#include "ns3/nstime.h"


using namespace ns3;


typedef enum{PROGRESSION_GEOMETRIC, PROGRESSION_ARITMETIC} ProgressionType_T;

template<typename T>
class ParamRange{
	public:
		ParamRange(T * param, ProgressionType_T progressionType, int indexLimit);
		void SetGeometricProgressionRate(double rate);
		void SetAritmeticProgressionRate(T rate);
		bool Next();
		T Current();
		double CurrentDouble();
		void Reset();
	private:
		T initialValue;
		T * _param;
		int index;
		int _indexLimit;
		ProgressionType_T _progressionType;
		bool definedProgressionRate = false;
		double geometricProgressionRate;
		T aritmeticProgressionRate;
		virtual T progressionAritmetic();
		virtual T progressionGeometric();
};


/*
class DoubleParamRange : public ParamRange<double>{
	public:
		using ParamRange<double>::ParamRange;
	protected:
		double progressionAritmetic(){
			return initialValue + index * aritmeticProgressionRate;
		}
		double progressionGeometric(){
			return initialValue * pow(geometricProgressionRate, index);    // Ojo con los índices en la progresión geométrica
		}
};


class TimeParamRange : public ParamRange<Time>{
	public:
		using ParamRange<Time>::ParamRange;
	protected:
		Time progressionAritmetic(){
			return initialValue + index * aritmeticProgressionRate;
		}
		Time progressionGeometric(){
			return initialValue * pow(geometricProgressionRate, index);    // Ojo con los índices en la progresión geométrica
		}
};
*/



#endif
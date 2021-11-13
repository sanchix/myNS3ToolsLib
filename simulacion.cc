
#include <string>
#include "ns3/gnuplot.h"
#include "ns3/log.h"
#include "simulacion.h"
#include "punto.h"
#include "escenarioP5.h"
#include "tStudent.h"


using namespace ns3;
using namespace std;


NS_LOG_COMPONENT_DEFINE("Simulacion");


template <typename T>
Punto punto(T * scenaryParams, double abscisa, int numIter, int porcentajeConzianza, double (*escenario)(T * scenaryParams)){
	
	NS_LOG_FUNCTION(abscisa);
	
	int error = 0;
	Average<double> pointValue;
	double simulationValue;
	
	for(int i = 0; i < numIter; i++){
		simulationValue = escenario(scenaryParams);
		pointValue.Update(simulationValue);
	}
	
	error = tStudentInv(numIter-1, (100-porcentajeConzianza)/200) * sqrt(pointValue.Var()/numIter);
	if(error < 0){
		NS_LOG_ERROR("Failed to calcule t-Student value");
	}
	
	return Punto(abscisa, pointValue.Mean(), error);

}


template <typename T, typename U>
Gnuplot2dDataset curva(T * scenaryParams, string curveName, ParamRange<U> variableParam, int numIter, int porcentajeConzianza, double (*escenario)(T * scenaryParams)){
	
	NS_LOG_FUNCTION(curveName);
	
	variableParam.Reset();
	
	Gnuplot2dDataset curvita(curveName);
	curvita.SetStyle(Gnuplot2dDataset::LINES_POINTS);
	curvita.SetErrorBars(Gnuplot2dDataset::Y);
	
	do{
		Punto puntito = punto(scenaryParams, variableParam.CurrentDouble(), numIter, porcentajeConzianza, escenario);
		curvita.Add(puntito.abscisa(), puntito.ordenada(), puntito.error());
	}while(variableParam.Next());
	
	return curvita;
	
}


template <typename T, typename U, typename V>
Gnuplot grafica(T * scenaryParams, TitulosGrafica_t titulos, ParamRange<U> curveParam, ParamRange<V> pointParam, int numIter, int porcentajeConzianza, double (*escenario)(T * scenaryParams)){
	
	NS_LOG_FUNCTION("");
	
	Gnuplot grafiquita;
	
	curveParam.Reset();
	
	grafiquita.SetTitle(titulos.title);
	grafiquita.SetLegend(titulos.absTitle, titulos.ordTitle);
	
	do{
		char curveName[30];
		sprintf(curveName, titulos.curveExpresion, curveParam.Current());
		Gnuplot2dDataset curvita = curva(scenaryParams, string(curveName), pointParam, numIter, porcentajeConzianza, escenario);
		grafiquita.AddDataset(curvita);
	}while(curveParam.Next());
	
	return grafiquita;
	
}


// TRAMPA

template Punto punto<StageConfig_t>(StageConfig_t *, double, int, int, double (*)(StageConfig_t *));

template Gnuplot2dDataset curva<StageConfig_t, Time>(StageConfig_t * scenaryParams, string curveName, ParamRange<Time> variableParam, int numIter, int porcentajeConzianza, double (*escenario)(StageConfig_t * scenaryParams));

template Gnuplot2dDataset curva<StageConfig_t, double>(StageConfig_t * scenaryParams, string curveName, ParamRange<double> variableParam, int numIter, int porcentajeConzianza, double (*escenario)(StageConfig_t * scenaryParams));

template Gnuplot grafica<StageConfig_t, double, Time>(StageConfig_t * scenaryParams, TitulosGrafica_t titulos, ParamRange<double> curveParam, ParamRange<Time> pointParam, int numIter, int porcentajeConzianza, double (*escenario)(StageConfig_t * scenaryParams));

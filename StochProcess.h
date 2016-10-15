#ifndef STOCH_PROCESS_H
#define STOCH_PROCESS_H

#include <vector>
#include <iostream>

using namespace std;

class StochProcess
{
public:
	StochProcess(double X0_) :X0(X0_){}
	double get_terminalvalue(double T, int numberofsteps) const;
	vector<double> get_samplepath(double T, int numberofsteps) const;
	double getStockPrice() const { return X0; }
	//virtual StochProcess* clone() const = 0;
private:
	virtual double step(double currentX, double h) const = 0;
	virtual void reset() const{}
	double X0;
};
#endif

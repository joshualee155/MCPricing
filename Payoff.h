#ifndef PAYOFF_H
#define PAYOFF_H

class Payoff
{
    public:
        virtual double operator()(double spot) const = 0;
		virtual Payoff* clone() const = 0;
};
#endif

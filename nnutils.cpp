#include"nnutils.hpp"
#include<cstdlib>
#include<cmath>

double NNUtils::learningRate = 0.1;

double NNUtils::activationFunction(double x){
    return tanh(x);
}
double NNUtils::activationFunctionDerivative(double x){
    return 1.0 - (x*x);
}

double NNUtils::randomWeight(){ return rand() / double(RAND_MAX); }

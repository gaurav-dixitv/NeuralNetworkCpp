#ifndef NNUTILS_HPP
#define NNUTILS_HPP

#include<vector>

class Neuron;
typedef std::vector<Neuron> Layer;

class NNUtils{
    public:
        NNUtils() = delete;
        ~NNUtils() = delete;

        static double learningRate;

        static double activationFunction(double x);
        static double activationFunctionDerivative(double x);

        static double randomWeight();

};


#endif // NNUTILS_HPP


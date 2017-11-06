#ifndef NEURON_H
#define NEURON_H

#include<vector>
#include"nnutils.hpp"

struct Connection{
    double weight;
    double deltaWeight;
    Connection(double p_weight) {
        weight = p_weight;
    }
};

class Neuron{
    public:
        Neuron(unsigned numOutputs, unsigned index);

        void    setOutputValue(double value){mOutputValue = value;}
        double  outputValue()const {return mOutputValue;}

        void    feedForward(Layer& previousLayer);
        void    calculateDelta(Layer& nextLayer);
        void    setDelta(double delta){mDelta = delta;}
        double  delta()const { return mDelta; }

        std::vector<Connection>& outputWeights() {return mOutputWeights;}

    private:
        double mOutputValue;
        unsigned mIndex;
        double mDelta;
        std::vector<Connection> mOutputWeights;
};
#endif // NEURON_H

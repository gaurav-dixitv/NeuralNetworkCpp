#include "neuron.hpp"
#include"nnutils.hpp"


Neuron::Neuron(unsigned numOutputs, unsigned index){
    mIndex = index;
    for (int c = 0; c < numOutputs; c++)
        mOutputWeights.push_back(Connection(NNUtils::randomWeight()));
}

void Neuron::calculateDelta(Layer& nextLayer){
    mDelta = 0.0;
    for (unsigned i = 0; i < mOutputWeights.size(); i++){
        mDelta += mOutputWeights[i].weight*nextLayer[i].mDelta;
    }
}

void Neuron::feedForward(Layer& previousLayer){
    double sum = 0.0;
    for (unsigned n = 0; n < previousLayer.size(); ++n)
    {    sum += previousLayer[n].outputValue()*previousLayer[n].outputWeights()[mIndex].weight;
    }
    mOutputValue = NNUtils::activationFunction(sum);
}

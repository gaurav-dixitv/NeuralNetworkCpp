#include "neuralnet.hpp"
#include<cmath>

NeuralNet::NeuralNet(const std::vector<unsigned>& topology){
    //topology(x,y,z....n)= x,y,z...n are number of neutrons in x..n layers
    int totalLayers = topology.size();

    for (int layerNum = 0; layerNum < totalLayers; ++layerNum){
        mLayers.push_back(Layer());
        //add neurons now
        int neuronOutputs = layerNum == totalLayers - 1 ? 0 : topology[layerNum+1];
        for (unsigned n = 0; n < topology[layerNum]; ++n){
            mLayers.back().push_back(Neuron(neuronOutputs, n));
        }
    }
}

double NeuralNet::rms(const std::vector<double>& output){

    Layer& outputLayer = mLayers.back();
    double error = 0.0;
    for (unsigned n = 0; n < outputLayer.size(); ++n){
        double del = output[n] - outputLayer[n].outputValue();
        error += (del*del);
    }
    error /= outputLayer.size();
    error = sqrt(error);
    return error;
}

void NeuralNet::getResults(std::vector<double>& result) const{
    result.clear();
    for (unsigned n = 0; n < mLayers.back().size(); ++n)
        result.push_back(mLayers.back()[n].outputValue());
}

void NeuralNet::backProp(const std::vector<double>& target){

    //calculate delta for all neurons
    Layer& outputLayer = mLayers.back();

    for (unsigned i = 0; i < outputLayer.size(); ++i){
        outputLayer[i].setDelta(target[i]-outputLayer[i].outputValue());
    }
    for (size_t layer = mLayers.size() - 2; layer>0; layer--){
        Layer& nextLayer = mLayers[layer + 1];
        for (size_t n = 0; n < mLayers[layer].size(); n++){
            mLayers[layer][n].calculateDelta(nextLayer);
        }
    }
    //now update all weights
    updateWeights();
}

void NeuralNet::updateWeights(){
    for (unsigned layer = 0; layer < mLayers.size() - 1; layer++){
        for (unsigned n = 0; n < mLayers[layer].size(); n++){
            Layer& nextLayer = mLayers[layer + 1];
            for (unsigned i = 0; i < mLayers[layer][n].outputWeights().size(); i++)
            {
                mLayers[layer][n].outputWeights()[i].weight +=
                        nextLayer[i].delta()
                        * mLayers[layer][n].outputValue()
                        * NNUtils::activationFunctionDerivative(nextLayer[i].outputValue())
                        * NNUtils::learningRate;

            }
        }
    }
}

void NeuralNet::feedForward(const std::vector<double>& input){
    //insert inputvalues in layer[0]
    for (unsigned i = 0; i < input.size(); ++i){
        mLayers[0][i].setOutputValue(input[i]);
    }
    for (unsigned layer = 1; layer < mLayers.size(); ++layer)
    {
        Layer& previousLayer = mLayers[layer - 1];
        Layer& currentLayer = mLayers[layer];
        for (unsigned n = 0; n < currentLayer.size(); ++n){
            currentLayer[n].feedForward(previousLayer);
        }
    }
}





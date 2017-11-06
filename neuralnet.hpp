#ifndef NEURALNET_H
#define NEURALNET_H

#include<vector>

#include"nnutils.hpp"
#include"neuron.hpp"

class NeuralNet{
    public:
        NeuralNet(const std::vector<unsigned>& topology);

        void feedForward(const std::vector<double>& input);
        void backProp(const std::vector<double>& target);
        void getResults(std::vector<double>& result) const;

        double error() const { return mError; }
        double rms(const std::vector<double>& output);

    private:
        void updateWeights();

        std::vector<Layer> mLayers;
        double mError;
};

#endif // NEURALNET_H

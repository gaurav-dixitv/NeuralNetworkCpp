#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<iomanip>

#include"trainingset.hpp"
#include"neuralnet.hpp"

template<typename T>
void containerPrinter(T container, std::string label, std::fstream& fx){
    fx << label;
    for (typename T::iterator i = container.begin(); i != container.end(); ++i){
        fx << " " << *i;
    }
    fx << std::endl;
}

int main(){

    std::vector<unsigned> topology;
    std::vector<double> input, output, result;

    std::string trainingFile = "D:\\NN\\XOR\\xor.txt";
    std::string outputFile = "D:\\NN\\XOR\\xor_ouput.txt";

    TrainingSet trainingSet(trainingFile);
    std::fstream ff(outputFile.c_str(), std::ios::out);

    trainingSet.fetchTopology(topology);
    NeuralNet neuralNet(topology);

    ff<<std::fixed;
    ff<<std::setprecision(5);

    int sampleCount = 0;
    while (!trainingSet.eof()){

        trainingSet.nextInput(input);
        trainingSet.nextOutput(output);
        if (input.size() != topology[0]) break;

        neuralNet.feedForward(input);
        neuralNet.getResults(result);
        neuralNet.backProp(output);

        /*
        ff << "Sample: " << sampleCount << std::endl;;
        containerPrinter(inputValues, "Input: ", ff);
        containerPrinter(resultValues, "Output: ", ff);
        ff << "Error: " << myNet.rms(outputValues) <<  std::endl;;
        */
        ff << sampleCount << "\t" << neuralNet.rms(output) << std::endl;
        ++sampleCount;
    }
    return 0;
}


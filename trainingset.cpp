#include"trainingset.hpp"

#include<sstream>
#include<cassert>

TrainingSet::~TrainingSet(){
    if (m_file.is_open()) m_file.close();
}
bool TrainingSet::eof() const{
    return m_file.eof();
}
void TrainingSet::nextOutput(std::vector<double>& output){
    output.clear();
    std::string line, label;
    getline(m_file, line);
    std::stringstream ss(line);
    ss >> label;
    while (!ss.eof()){
        double value;
        ss >> value;
        output.push_back(value);
    }
}
void TrainingSet::nextInput(std::vector<double>& input){
    input.clear();
    std::string line, label;
    getline(m_file, line);
    std::stringstream ss(line);
    ss >> label;
    while (!ss.eof()){
        double value;
        ss >> value;
        input.push_back(value);
    }
}
TrainingSet::TrainingSet(std::string trainingFile){
    assert(trainingFile.empty() == false);
    m_file.open(trainingFile.c_str(), std::ios::in);
}
void TrainingSet::fetchTopology(std::vector<unsigned>& topology){
    topology.clear();
    std::string line, label;
    getline(m_file, line);
    std::stringstream ss(line);
    ss >> label;
    while (!ss.eof()){
        unsigned n;
        ss >> n;
        topology.push_back(n);
    }
}

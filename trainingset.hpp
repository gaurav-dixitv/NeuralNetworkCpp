#ifndef TRAININGSET_HPP
#define TRAININGSET_HPP

#include<vector>
#include<string>
#include<fstream>

class TrainingSet{
    public:
        TrainingSet(std::string trainingFile);
        ~TrainingSet();

        void fetchTopology(std::vector<unsigned>& topology);
        void nextInput(std::vector<double>& input);
        void nextOutput(std::vector<double>& output);
        bool eof() const;

    private:
        std::fstream m_file;
};

#endif // TRAININGSET_HPP


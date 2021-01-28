#ifndef GENE_H
#define GENE_H

#include <vector>
#include <random>


class Gene {
  public:
    Gene();
    ~Gene();
    Gene& operator=(const Gene& parentGene);
    Gene(const Gene& parentGene);
    void Randomize();
    std::vector<float> getGenome();
  
  private:
    void _Normalize();
    void _Mutate();
    std::vector<float> _genome = std::vector<float>(8);
    std::random_device _rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 _gen {_rd()}; //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> _disr {std::uniform_real_distribution<>(0.0, 1.0)};
    std::uniform_int_distribution<int> _disi {std::uniform_int_distribution<int>(0, 7)};
};

#endif
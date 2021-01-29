#include "gene.h"


Gene::Gene() {
};

Gene::~Gene()  {
}

Gene& Gene::operator=(const Gene& parentGene) {
  _genome = parentGene._genome;
  return *this;
}

Gene::Gene(const Gene& parentGene) {
  _genome = parentGene._genome;
};

std::vector<float> Gene::getGenome() {
  return _genome;
}

void Gene::Mutate() {
  // choose a random element from the genome
  // give it a new random number
  // and normalize again
  _genome[_disi(_gen)] = _disr(_gen);
  this->_Normalize();
}

void Gene::_Normalize() {
  float sum{0.0};
  for (int i=0; i < _genome.size(); ++i) {
    sum += _genome[i];
  }
  for (int i=0; i < _genome.size(); ++i) {
    _genome[i] = _genome[i]/sum;
  }  
};

void Gene::Randomize() {
  for (int i=0; i < _genome.size(); ++i) {
    _genome[i] = _disr(_gen);
  }
  this->_Normalize();
};

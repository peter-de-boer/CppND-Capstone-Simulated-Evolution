#include "gene.h"

#include <iostream>

Gene::Gene() {
};

Gene::~Gene()  {
}

Gene& Gene::operator=(const Gene& other) {
  _genome = other._genome;
  return *this;
}

Gene::Gene(const Gene& other) {
  _genome = other._genome;
};


int Gene::GetSegment() {
  // generate random float 0..1
  float r = _disr(_gen);

  float sum = _genome[0];
  int segment = 0;

  while (sum < r && segment < 7) {
    segment += 1;
    sum += _genome[segment];

  }
  return segment;
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

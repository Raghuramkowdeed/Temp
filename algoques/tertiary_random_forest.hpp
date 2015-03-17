#pragma once 

#include "utils.hpp"

namespace AlgoComp {

  class InputChangeListener {
  public:
    virtual ~InputChangeListener ( ) { };

    virtual double OnInputChange ( unsigned int input_index_, double input_value_ ) = 0;
  };

  class TertiaryRandomForest : public InputChangeListener {
  public:
    TertiaryRandomForest ( ) { }
    
    void InitializeForest ( const char * const forest_filename_ ) { } /// needs to be implemented
    
    double OnInputChange ( unsigned int input_index_, double input_value_ ) { return 0; } /// needs to be implemented

  };

}

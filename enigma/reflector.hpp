//
//  Reflector.hpp
//  enigma
//
//  Created by Joseph Kalash on 11/18/17.
//  Copyright © 2017 Joseph Kalash. All rights reserved.
//

#ifndef Reflector_hpp
#define Reflector_hpp

#include <iostream>
#include <vector>

#include "globals.h"

class Reflector {
    std::vector<EnigmaTypes::location> reflectedPairs;
    
    //Makes sure input read from file is valid otherwise exits with corresponding error
    void loadInput(EnigmaTypes::path rfFile);
public:
    Reflector(EnigmaTypes::path rfFile);
    
    //Maps an input to a potential output if found in cables, otherwise itself.
    EnigmaTypes::location reflect(EnigmaTypes::location entry) const;
};

#endif /* Reflector_hpp */

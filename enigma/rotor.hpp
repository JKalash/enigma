//
//  Rotor.hpp
//  enigma
//
//  Created by Joseph Kalash on 11/18/17.
//  Copyright © 2017 Joseph Kalash. All rights reserved.
//

#ifndef Rotor_hpp
#define Rotor_hpp

#include <stdio.h>
#include <vector>

#include "globals.h"

class Rotor {
    std::vector<unsigned short int> notches;
    std::vector<unsigned short int> wirings;
    unsigned short int position;
public:
    Rotor(EnigmaTypes::path rotFile, EnigmaTypes::path posFile);
};

#endif /* Rotor_hpp */

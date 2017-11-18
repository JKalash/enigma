//
//  Reflector.hpp
//  enigma
//
//  Created by Joseph Kalash on 11/18/17.
//  Copyright © 2017 Joseph Kalash. All rights reserved.
//

#ifndef Reflector_hpp
#define Reflector_hpp

#include <stdio.h>
#include <vector>

#include "globals.h"

using namespace std;

class Reflector {
    std::vector<unsigned short int> reflectedPairs;
public:
    Reflector(EnigmaTypes::path rfFile);
};

#endif /* Reflector_hpp */

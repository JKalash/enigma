//
//  Plugboard.hpp
//  enigma
//
//  Created by Joseph Kalash on 11/18/17.
//  Copyright © 2017 Joseph Kalash. All rights reserved.
//

#ifndef Plugboard_hpp
#define Plugboard_hpp

#include <stdio.h>
#include <vector>

#include "globals.h"

class Plugboard {
    std::vector<unsigned short int> cables;
public:
    Plugboard(EnigmaTypes::path pbFile);
};

#endif /* Plugboard_hpp */

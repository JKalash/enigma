//
//  Plugboard.hpp
//  enigma
//
//  Created by Joseph Kalash on 11/18/17.
//  Copyright © 2017 Joseph Kalash. All rights reserved.
//

#ifndef Plugboard_hpp
#define Plugboard_hpp

#include <iostream>
#include <vector>

#include "globals.h"

class Plugboard {
    std::vector<EnigmaTypes::location> cables;
    
    //Makes sure input read from file is valid before storing otherwise exits with corresponding error
    void loadInput(EnigmaTypes::path pbFile);
public:
    Plugboard(EnigmaTypes::path pbFile);
};

#endif /* Plugboard_hpp */

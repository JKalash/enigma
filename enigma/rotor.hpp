//
//  Rotor.hpp
//  enigma
//
//  Created by Joseph Kalash on 11/18/17.
//  Copyright © 2017 Joseph Kalash. All rights reserved.
//

#ifndef Rotor_hpp
#define Rotor_hpp

#include <iostream>
#include <vector>

#include "globals.h"

class Rotor {
    std::vector<EnigmaTypes::location> notches;
    std::vector<EnigmaTypes::location> wirings;
    EnigmaTypes::location position;
    
    //Makes sure input read from file is valid otherwise exits with corresponding error
    void loadRotor(EnigmaTypes::path rotFile);
    
    //Makes sure position input read from file is valid otherwise exits with corresponding error
    void loadPosition(EnigmaTypes::path posFile, EnigmaTypes::location rotorIndex);
    
public:
    Rotor(EnigmaTypes::path rotFile, EnigmaTypes::path posFile, EnigmaTypes::location rotorIndex);
    
    //Maps an input to an output
    EnigmaTypes::location map(EnigmaTypes::location original, bool rightToleft) const;
    
    //Returns true if position matches that of a notch
    bool shouldrotateLeftRotor() const;
    
    //Rotates the rotor 1 position clockwise
    void rotate();
};

#endif /* Rotor_hpp */

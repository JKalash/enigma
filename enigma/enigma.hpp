//
//  Enigma.hpp
//  enigma
//
//  Created by Joseph Kalash on 11/18/17.
//  Copyright © 2017 Joseph Kalash. All rights reserved.
//

#ifndef Enigma_hpp
#define Enigma_hpp

#include <iostream>
#include <vector>

#include "rotor.hpp"
#include "plugboard.hpp"
#include "reflector.hpp"

class Enigma {
    std::vector<Rotor> rotors;
    Plugboard plugboard;
    Reflector reflector;
public:
    Enigma(EnigmaTypes::path pbFile, EnigmaTypes::path rfFile, std::vector<EnigmaTypes::path> rotFiles, EnigmaTypes::path posFile);
};

#endif /* Enigma_hpp */

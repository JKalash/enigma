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
    
    //Takes a key input and applies a full enigma forward pass to it
    EnigmaTypes::location forwardPass(EnigmaTypes::location input);
    
    //Applies a RTL or LTR pass through all rotors
    EnigmaTypes::location rotorsPass(EnigmaTypes::location input, bool rightToLeft = true) const;
    
    //Rotates rotors recursivelt in RTL
    void rotate();
public:
    Enigma(EnigmaTypes::path pbFile, EnigmaTypes::path rfFile, std::vector<EnigmaTypes::path> rotFiles, EnigmaTypes::path posFile);
    std::string encrypt(std::string input);
};

#endif /* Enigma_hpp */

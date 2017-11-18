//
//  Enigma.cpp
//  enigma
//
//  Created by Joseph Kalash on 11/18/17.
//  Copyright © 2017 Joseph Kalash. All rights reserved.
//

#include "enigma.hpp"

Enigma::Enigma(EnigmaTypes::path pbFile, EnigmaTypes::path rfFile, std::vector<EnigmaTypes::path> rotFiles, EnigmaTypes::path posFile) : plugboard(pbFile), reflector(rfFile) {
    
    // Iterate over all rotor files vector and append a created rotor for each rotfile.
    for( int i = 0; i < rotFiles.size(); ++i)
        rotors.push_back(Rotor(rotFiles[i], posFile, i));
}


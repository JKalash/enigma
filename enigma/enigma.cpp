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

std::string Enigma::encrypt(std::string input) {
    
    //Loop over each character in the string, encrypt one at a time while making sure it is a valid input
    //Store encryption sequentially to new string
    std::string encryptionString = "";
    
    for(char& c : input) {
        
        //The only valid characters are 'A' to 'Z'
        if (c < 'A' || c > 'Z') {
            std::cout << "Invalid input character " << c << std::endl;
            exit(INVALID_INPUT_CHARACTER);
        }
        
        //Map 'A-Z' to '0-25'
        EnigmaTypes::location encodedInput = c - 'A';
        EnigmaTypes::location encryption = forwardPass(encodedInput);
        
        char decodedEncryption = (char)encryption + 'A';
        encryptionString += decodedEncryption;
    }
    
    return encryptionString;
}


EnigmaTypes::location Enigma::forwardPass(EnigmaTypes::location input) {
    
    /*  1. Enigma to plugboard
     *  2. Pluboard to each rotor
     *  3. Reflection
     *  4. backward pass through rotors
     *  5. rotor output to Plugboard
     *  6. Rotate rotors recursively (notches)
     */
    
    //1.
    EnigmaTypes::location plugboardOutput = plugboard.map(input);
    
    //2.
    EnigmaTypes::location reflectionEntry = rotorsPass(plugboardOutput);
    
    //3.
    EnigmaTypes::location reflectionOutput = reflector.reflect(reflectionEntry);
    
    //4.
    EnigmaTypes::location rotorsOutput = rotorsPass(reflectionOutput, false);
    
    //5.
    EnigmaTypes::location output = plugboard.map(rotorsOutput);
    
    //6.
    rotate();
    
    return output;
}

EnigmaTypes::location Enigma::rotorsPass(EnigmaTypes::location input, bool rightToLeft) const {
    
    EnigmaTypes::location rotorOuput = input;
    
    //If right to left, start witgh last rotor, otherwise start with leftmost one
    EnigmaTypes::location firstRotorIndex = rightToLeft ? rotors.size()-1 : 0;
    EnigmaTypes::location lastRotorIndex = rightToLeft ? 0 : rotors.size()-1;
    
    signed int increment = rightToLeft ? -1 : 1;
    
    for(int i = firstRotorIndex; (i <= lastRotorIndex && !rightToLeft) || (i >= lastRotorIndex && rightToLeft); i+= increment)
        rotorOuput = rotors[i].map(rotorOuput, rightToLeft);
    
    return rotorOuput;
}

void Enigma::rotate() {
    
    /* Rotation is as follows. For each rotor r:
     * 1. Right shift array and circulate rightmost value to first
     * 2. Update position value
     * 3. If position value matches that of a notch, rotate
     */
    
    rotors[rotors.size()-1].rotate();
    
    for(unsigned long i = rotors.size()-1; i > 0; i--) {
        if(rotors[i].shouldrotateLeftRotor())
            rotors[i].rotate();
        else break;
    }
    
}

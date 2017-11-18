//
//  Plugboard.cpp
//  enigma
//
//  Created by Joseph Kalash on 11/18/17.
//  Copyright © 2017 Joseph Kalash. All rights reserved.
//

#include <string>
#include <fstream>
#include <sstream>

#include "plugboard.hpp"

Plugboard::Plugboard(EnigmaTypes::path pbFile) {
    
    loadInput(pbFile);
}

void Plugboard::loadInput(EnigmaTypes::path pbFile) {
    
    // Try to open the files
    std::ifstream pbInput(pbFile);
    if(!pbInput) {
        std::cout << "Could not open plugboard configuration file " << pbFile << std::endl;
        exit(ERROR_OPENING_CONFIGURATION_FILE);
    }
    
    //Read input one number at a time and validate
    std::string rawInput;
    while (pbInput >> rawInput) {
        //Validate every word read sequentially to exit with proper signal value
    
        //Make sure string is only numeric / whitespace
        if( rawInput.find_first_not_of("0123456789") != std::string::npos) {
            std::cout << "Plugboard configuration file contains non numeric character in " << rawInput << std::endl;
            exit(NON_NUMERIC_CHARACTER);
        }

        //Convert string to integer
        EnigmaTypes::location loc = stoi(rawInput);
        if(loc < 0 || loc > 25) {
            std::cout << "Plugboard configuration file contains invalid index " << loc << std::endl;
            exit(INVALID_INDEX);
        }

        //Add valid location to cables
        cables.push_back(loc);

        // IMPOSSIBLE_PLUGBOARD_CONFIGURATION if connection to itself or contact connected to more than 1 other
        // In other words, duplicate should never be allowed. To check, sort and traverse

        std::vector<EnigmaTypes::location> cablesDuplicate = cables;    //The assignment here calls the *copy* constructor of the vector class. It's a DEEP copy.
        std::sort(cablesDuplicate.begin(), cablesDuplicate.end());
        for(int i = 0; i < cablesDuplicate.size() - 1; i++) {
            if (cablesDuplicate[i] == cablesDuplicate[i + 1]) {
                std::cout << "Plugboard configuration file is attempting to map an input to itself or pair each index with more than one other" << std::endl;
                exit(IMPOSSIBLE_PLUGBOARD_CONFIGURATION);
            }
        }
    }
    
    // INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS if odd number of values
    if ( cables.size() % 2 != 0) {
        std::cout << "Plugboard configuration file contains odd number of numbers" << std::endl;
        exit(INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS);
    }
    
    // Close the file
    pbInput.close();
    
}

EnigmaTypes::location Plugboard::map(EnigmaTypes::location original) const {
    
    //Try to find the location in cables
    for(int i = 0; i < cables.size(); i++)
        if ( original == cables[i] )
            return i%2 == 0 ? cables[i+1] : cables[i-1]; //Even cables map to the next odd one. Odd cables map to the even one just before them

    //No cable for following input. Stays the same
    return original;
}

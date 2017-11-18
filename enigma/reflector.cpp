//
//  Reflector.cpp
//  enigma
//
//  Created by Joseph Kalash on 11/18/17.
//  Copyright © 2017 Joseph Kalash. All rights reserved.
//

#include <string>
#include <fstream>
#include <sstream>

#include "reflector.hpp"

#define REFLECTED_PAIR_SIZE 26

Reflector::Reflector(EnigmaTypes::path rfFile) {
    
    loadInput(rfFile);
    
}

void Reflector::loadInput(EnigmaTypes::path rfFile) {
    
    // Try to open the files
    std::ifstream rfInput(rfFile);
    if(!rfInput) {
        std::cout << "Could not open reflector configuration file " << rfFile << std::endl;
        exit(ERROR_OPENING_CONFIGURATION_FILE);
    }
    
    //Read input one number at a time and validate
    std::string rawInput;
    while (rfInput >> rawInput) {
        
        //Validate every word read sequentially to exit with proper signal value
    
        //Make sure string is only numeric / whitespace
        if( rawInput.find_first_not_of("0123456789") != std::string::npos) {
            std::cout << "Reflector configuration file contains non numeric character" << std::endl;
            exit(NON_NUMERIC_CHARACTER);
        }
        
        //Convert string to array of integers
        EnigmaTypes::location loc = stoi(rawInput);
        if(loc < 0 || loc > 25) {
            std::cout << "Reflector configuration file contains invalid index " << loc << std::endl;
            exit(INVALID_INDEX);
        }
        
        //Add valid location to reflectedPairs
        reflectedPairs.push_back(loc);
        
        
        // INVALID_REFLECTOR_MAPPING if connection to itself or contact connected to more than 1 other
        // In other words, duplicate should never be allowed. To check, Sort and traverse
        std::vector<EnigmaTypes::location> pairsDuplicate = reflectedPairs;    //The assignment here calls the *copy* constructor of the vector class. It's a DEEP copy.
        std::sort(pairsDuplicate.begin(), pairsDuplicate.end());
        for(int i = 0; i < pairsDuplicate.size() - 1; i++) {
            if (pairsDuplicate[i] == pairsDuplicate[i + 1]) {
                std::cout << "Reflector configuration file is attempting to map an input to itself or pair each index with more than one other" << std::endl;
                exit(INVALID_REFLECTOR_MAPPING);
            }
        }
    }
    
    // INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS if not 13
    if (reflectedPairs.size() != REFLECTED_PAIR_SIZE) {
        std::cout << "Reflector configuration file contains odd number of reflections" << std::endl;
        exit(INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS);
    }
    
    // Close the file
    rfInput.close();
    
}

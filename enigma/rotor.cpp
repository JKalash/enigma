//
//  Rotor.cpp
//  enigma
//
//  Created by Joseph Kalash on 11/18/17.
//  Copyright © 2017 Joseph Kalash. All rights reserved.
//

#include <fstream>
#include "rotor.hpp"

#define ROTOR_SIZE 26

Rotor::Rotor(EnigmaTypes::path rotFile, EnigmaTypes::path posFile, EnigmaTypes::location rotorIndex) {
    
    //Check and store initial position
    loadPosition(posFile, rotorIndex);
    
    //Check and store rotor config file
    loadRotor(rotFile);
    
}

void Rotor::loadPosition(EnigmaTypes::path posFile, EnigmaTypes::location rotorIndex) {
    
    std::ifstream posInput(posFile);
    
    //Read pos file to figure out initial position
    EnigmaTypes::location posCounter = 0;
    std::string word;
    while (posCounter < rotorIndex && posInput >> word)
        posCounter++;   //Read previous rotor positions
    
    if (posCounter < rotorIndex) {
        std::cout << "Could not find rotor starting position" << std::endl;
        exit(NO_ROTOR_STARTING_POSITION);
    }
    
    std::string posWord;
    posInput >> posWord;
    
    //Make sure string is only numeric / whitespace
    if( posWord.find_first_not_of("0123456789") != std::string::npos) {
        std::cout << "Rotor position file contains non numeric character in " << posWord << std::endl;
        exit(NON_NUMERIC_CHARACTER);
    }
    
    //Convert string to integer
   position = stoi(posWord);
    if(position < 0 || position > 25) {
        std::cout << "Rotor invalid position " << position << std::endl;
        exit(INVALID_INDEX);
    }
    
    // Close the file
    posInput.close();
    
}

void Rotor::loadRotor(EnigmaTypes::path rotFile) {
    
    // Try to open the files
    std::ifstream rotInput(rotFile);
    if(!rotFile) {
        std::cout << "Could not open rotor configuration file" << rotFile << std::endl;
        exit(ERROR_OPENING_CONFIGURATION_FILE);
    }
    
    //We need to read 26 unique proper location integers plus optional notches
    EnigmaTypes::location locationsRead = 0;
    std::string locWord;
    while(locationsRead < ROTOR_SIZE && rotInput >> locWord) {
        
        //Validate every word read sequentially to exit with proper signal value
        
        //Make sure string is only numeric / whitespace
        if( locWord.find_first_not_of("0123456789") != std::string::npos) {
            std::cout << "Rotor file contains non numeric character in " << locWord << std::endl;
            exit(NON_NUMERIC_CHARACTER);
        }
        
        //Convert string to integer
        EnigmaTypes::location loc = stoi(locWord);
        if(loc < 0 || loc > 25) {
            std::cout << "Rotor file contains invalid index " << loc << std::endl;
            exit(INVALID_INDEX);
        }
        
        
        wirings.push_back(loc);
        
        // INVALID_ROTOR_MAPPING if connecting more than one input to same output
        // In other words, duplicate should never be allowed. To check, sort and traverse
        
        std::vector<EnigmaTypes::location> wiringDuplicates = wirings;    //The assignment here calls the *copy* constructor of the vector class. It's a DEEP copy.
        std::sort(wiringDuplicates.begin(), wiringDuplicates.end());
        for(int i = 0; i < wiringDuplicates.size() - 1; i++) {
            if (wiringDuplicates[i] == wiringDuplicates[i + 1]) {
                std::cout << "Rotor file " << rotFile << " is attempting to map more than one output to " << wiringDuplicates[i] << std::endl;
                exit(INVALID_ROTOR_MAPPING);
            }
        }
        
        locationsRead++;
    }
    
    if (locationsRead < ROTOR_SIZE) {
        std::cout << "Rotor file does not provide mapping for all inputs" << std::endl;
        exit(INVALID_ROTOR_MAPPING);
    }
    
    //Read any optional notch
    while(rotInput >> locWord) {
        
        if( locWord.find_first_not_of("0123456789") != std::string::npos) {
            std::cout << "Rotor file contains non numeric character in " << locWord << std::endl;
            exit(NON_NUMERIC_CHARACTER);
        }
        
        //Convert string to integer
        EnigmaTypes::location notchLoc = stoi(locWord);
        if(notchLoc < 0 || notchLoc > 25) {
            std::cout << "Rotor file contains invalid index " << notchLoc << std::endl;
            exit(INVALID_INDEX);
        }
        
        //Add valid notch location
        notches.push_back(notchLoc);

    }
    
    // Close the file
    rotInput.close();
    
}

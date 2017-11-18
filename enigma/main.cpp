//
//  main.cpp
//  enigma
//
//  Created by Joseph Kalash on 11/15/17.
//  Copyright © 2017 Joseph Kalash. All rights reserved.
//

#include <iostream>
#include <vector>

#include "globals.h"
#include "enigma.hpp"

#define MIN_ARG_COUNT 3
#define PB_FILE_ARG 1
#define RF_FILE_ARG 2

using namespace EnigmaTypes;
using namespace std;

int main(int argc, path argv[]) {
    
    //There cannot be any scenario where argCount < MIN_ARG_COUNT or equal to 4
    // Valid scenarios are argc = 3 (no rotor) or argc= 5+
    if (argc < MIN_ARG_COUNT || argc == 4) {
        cout << "Insufficent number of input parameters" << endl;
        exit(INSUFFICIENT_NUMBER_OF_PARAMETERS);
    }
    
    path pbFile = argv[PB_FILE_ARG];
    path rfFile = argv[RF_FILE_ARG];
    path posFile = NULL; //Assume no rotor unless arg count >= 5
        vector<path> rotFiles;
    
    
    // There either either are no rotors (arg count = 3)
    // Or 1+ rotor (arg count = 5+)
    if (argc >= 5) {
        for(int i = 3; i < argc - 1; i++) //Loop over the rest except last file (rotor pos file)
            rotFiles.push_back(argv[i]);
        
        posFile = argv[argc - 1];
    }
    
    const Enigma enigma = Enigma(pbFile, rfFile, rotFiles, posFile);
    
    return NO_ERROR;
}

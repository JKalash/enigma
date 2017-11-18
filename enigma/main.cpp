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

using namespace EnigmaTypes;
using namespace std;

int main(int argc, path argv[]) {
    
    if (argc < MIN_ARG_COUNT) {
        cout << "Insufficent number of input parameters" << endl;
        exit(INSUFFICIENT_NUMBER_OF_PARAMETERS);
    }
    
    
    path pbFile = argv[0];
    path rfFile = argv[1];
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

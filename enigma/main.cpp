//
//  main.cpp
//  enigma
//
//  Created by Joseph Kalash on 11/15/17.
//  Copyright © 2017 Joseph Kalash. All rights reserved.
//

#include <iostream>
#include <set>
#include <fstream>
#include "errors.h"

typedef unsigned short int location;

using namespace std;

class Plugboard {
    
    
};

class Rotor {
    
};

int main(int argc, const char * argv[]) {
    
    if (argc < 3) {
        cout << "Insufficent number of input parameters";
        exit(INSUFFICIENT_NUMBER_OF_PARAMETERS);
    }
    
    const char* plugboardFilePath = argv[1];
    const char* reflectorFilePath = argv[2];
    
    // Rotor files
    for(int i = 3; i <= argc; i++) {
        const char* rotorFilePath = argv[i];
    }
    
    return 0;
}

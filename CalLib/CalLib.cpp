////////////////////////////////////////////////////////////////////////////
//
//  This file is part of MPU9150Lib
//
//  Copyright (c) 2013 Pansenti, LLC
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy of 
//  this software and associated documentation files (the "Software"), to deal in 
//  the Software without restriction, including without limitation the rights to use, 
//  copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the 
//  Software, and to permit persons to whom the Software is furnished to do so, 
//  subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all 
//  copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
//  INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
//  PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
//  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION 
//  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
//  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include <iostream>
#include <fstream>
#include <string.h>
////////////////////////////////////////////////////////////////////////////
//
//  This file is part of MPU9150 C++ Library for Intel IoT Platforms
//
//  Copyright (c) 2013 Pansenti, LLC
//  Copyright (c) 2015 Wesley Milan (Ported for C++)
//
//  https://github.com/wesleymilan/Dual-MPU9150-DMP-Intel-Galileo-and-Edison-CPP
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy of 
//  this software and associated documentation files (the "Software"), to deal in 
//  the Software without restriction, including without limitation the rights to use, 
//  copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the 
//  Software, and to permit persons to whom the Software is furnished to do so, 
//  subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all 
//  copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
//  INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
//  PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
//  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION 
//  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
//  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include <stdio.h>
#include "CalLib.h"

using namespace std;

void calLibErase(char device)
{
    //EEPROM.write(sizeof(CALLIB_DATA) * device, 0); // just destroy the valid byte
}

void calLibWrite(char device, CALLIB_DATA calData)
{
    char *filename;
    
    if(device == 0)
        filename = const_cast<char *>("calibration_0.bin");
    else
        filename = const_cast<char *>("calibration_1.bin");
    
    ofstream outbal(filename, ios::out | ios::binary);
    if(!outbal) {
      cout << "Cannot open file " << filename << "\n";
      return;
    }
    
    calData.valid = CALLIB_DATA_VALID;
    
    outbal.write((char *) &calData, sizeof(CALLIB_DATA));
    outbal.close();   
}

bool calLibRead(char device, CALLIB_DATA *calData)
{
    char *filename;
    
    if(device == 0)
        filename = const_cast<char *>("calibration_0.bin");
    else
        filename = const_cast<char *>("calibration_1.bin");
    
    ifstream inbal(filename, ios::in | ios::binary);
    if(!inbal) {
      cout << "Cannot open file " << filename << "\n";
      return false;
    }

    inbal.read((char *) &calData, sizeof(CALLIB_DATA));

    //cout << calData.accelMaxZ << endl;
    
    inbal.close();

    return true;
    /*
    char *ptr = (char *)calData;
    char length = sizeof(CALLIB_DATA);
    int eeprom = sizeof(CALLIB_DATA) * device;

    calData->magValid = false;
    calData->accelValid = false;

    if ((EEPROM.read(eeprom) != CALLIB_DATA_VALID_LOW) ||
        (EEPROM.read(eeprom + 1) != CALLIB_DATA_VALID_HIGH))
      return false;                                  // invalid data

    for (char i = 0; i < length; i++)
      *ptr++ = EEPROM.read(eeprom + i);
    */
    
    return true;  
}


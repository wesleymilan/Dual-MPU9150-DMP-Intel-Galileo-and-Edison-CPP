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

#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include "I2CDev/I2Cdev.h"
#include "MPU9150Lib/MPU9150Lib.h"
#include "CalLib/CalLib.h"
#include "MotionDriver/dmpKey.h"
#include "MotionDriver/dmpmap.h"
#include "MotionDriver/inv_mpu.h"
#include "MotionDriver/inv_mpu_dmp_motion_driver.h"

using namespace std;

//  DEVICE_TO_CAILIBRATE should be set to 0 for the IMU at 0x68 and 1 for the IMU at 0x69

int device = 2;                    

MPU9150Lib MPU;                                            // the MPU object

CALLIB_DATA calData;                                       // the calibration data

//  MPU_UPDATE_RATE defines the rate (in Hz) at which the MPU updates the sensor data and DMP output

#define MPU_UPDATE_RATE  (20)

//  MAG_UPDATE_RATE defines the rate (in Hz) at which the MPU updates the magnetometer data
//  MAG_UPDATE_RATE should be less than or equal to the MPU_UPDATE_RATE

#define MAG_UPDATE_RATE  (20)

//  SERIAL_PORT_SPEED defines the speed to use for the debug serial port

void setup()
{
    calLibRead(device, &calData);               // pick up existing accel data if there   

    calData.magValid = false;
    calData.magMinX = 0x7fff;                                // init mag cal data
    calData.magMaxX = 0x8000;
    calData.magMinY = 0x7fff;                              
    calData.magMaxY = 0x8000;
    calData.magMinZ = 0x7fff;                             
    calData.magMaxZ = 0x8000;

    std::cout << "MagCal9150 starting\n";
    MPU.selectDevice(device);                   // select the correct device 
    MPU.init(MPU_UPDATE_RATE, 5, MAG_UPDATE_RATE);           // start the MPU
    std::cout << "Calibrating device " << device << "\n";
}

void loop()
{  
    bool changed;

    MPU.selectDevice(device);                   // not strictly needed here as the device never changes but good form
    if (MPU.read()) {                                        // get the latest data
        changed = false;
        if (MPU.m_rawMag[VEC3_X] < calData.magMinX) {
            calData.magMinX = MPU.m_rawMag[VEC3_X];
            changed = true;
        }
         if (MPU.m_rawMag[VEC3_X] > calData.magMaxX) {
            calData.magMaxX = MPU.m_rawMag[VEC3_X];
            changed = true;
        }
        if (MPU.m_rawMag[VEC3_Y] < calData.magMinY) {
            calData.magMinY = MPU.m_rawMag[VEC3_Y];
            changed = true;
        }
         if (MPU.m_rawMag[VEC3_Y] > calData.magMaxY) {
            calData.magMaxY = MPU.m_rawMag[VEC3_Y];
            changed = true;
        }
        if (MPU.m_rawMag[VEC3_Z] < calData.magMinZ) {
            calData.magMinZ = MPU.m_rawMag[VEC3_Z];
            changed = true;
        }
        if (MPU.m_rawMag[VEC3_Z] > calData.magMaxZ) {
            calData.magMaxZ = MPU.m_rawMag[VEC3_Z];
            changed = true;
        }

        if (changed) {
            system("clear");
            std::cout << "Calibrating Magnetometer device " << device << "\n";
            std::cout << "Move your sensor in all directions until the numbers stop to change\n";
            std::cout << "Press CTRL+C when it's done\n\n";
            std::cout << "minX: " << calData.magMinX << " maxX: " << calData.magMaxX << "\n";
            std::cout << "minY: " << calData.magMinY << " maxY: " << calData.magMaxY << "\n";
            std::cout << "minZ: " << calData.magMinZ << " maxZ: " << calData.magMaxZ << "\n";

            calData.magValid = true;
            calLibWrite(device, calData);
        }
    }
}

void usage(char *argv_0)
{
    cout << "\nUsage: " << argv_0 << " [options]\n";
    cout << "  -d <device>           Use 0 to 0x68 (104) device and 1 to 0x69 (105).\n";
    cout << "  -h                    Show this help\n";

    cout << "\nExample: " << argv_0  << " -d 0 \n\n";

    exit(1);
}

int main(int argc, char **argv) {
    
    int opt;
        
    while ((opt = getopt(argc, argv, "d:")) != -1) {
        switch (opt) {
            case 'd':
                device = atoi(optarg);
                break;
            default:
                    usage(argv[0]);
                    exit(1);
        }
    }
    
    if(device == 0 || device == 1)
    {
        setup();
        usleep(100000);

        for (;;)
            loop();

        return 0;
    }
    else usage(argv[0]);
}


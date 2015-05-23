# Dual MPU9150 DMP C++ for Intel Galileo and Edison

An implementation of 9-axis data fusion on Linux using the [InvenSense MPU-9150 IMU][1]

This library is compilation of the follow codes, made to provide a C++ library
for Linux IoT based platforms like Intel Galileo and Edison, and to be compiled
with a simple MAKE command.  You can also use this library in RaspBerry PI, but 
at this moment the code was tested just into Galileo.

The linux-mpu9150 code uses the InvenSense Embedded Motion Driver v5.1.1 SDK
to obtain fused 6-axis quaternion data from the MPU-9150 DMP. The quaternion
data is then further corrected in the linux-mpu0150 code with magnetometer 
data collected from the IMU.

 - https://github.com/richards-tech/linux-mpu9150
 - https://github.com/richards-tech/RTIMULib
 - https://github.com/richards-tech/MPU9150Lib

Installing:

Step 1:
opkg install git

Step 2:
git clone https://github.com/wesleymilan/Dual-MPU9150-DMP-Intel-Galileo-and-Edison-CPP

Step 3:
mv Dual-MPU9150-DMP-Intel-Galileo-and-Edison-CPP MPU9150

Step 4:
cd MPU9150

Step 5:
make


Calibration:

./AccelCal -d 0
./MagCal -d 0

The -d parameter means what device do you want to calibrate, use 0 for 0x68 (104) addressed 
sensor and 1 for 0x69 (105) sensor. So, you can use 2 sensor in the same I2C bus.

During the calibration you'll have to move your sensor in every direction until 
the numbers on screen stop to change, this means that calibration catch the 
limits of your sensor and it will store the data into the files "calibration_X.bin", where
"X" will be the number of your device.  To finish the calibration app just press 
CTRL+C

Now you just run "./demo" to show your sensor data in real time.

Please fork us, make your tests, help us to improve the code sending us a pull request.

Thank you for your interest.

Regards

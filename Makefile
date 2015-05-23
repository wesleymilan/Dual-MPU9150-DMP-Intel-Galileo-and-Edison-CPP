
objects=demo AccelCal MagCal
all: clean $(objects)

CXX = g++

HDRS = I2CDev/I2Cdev.h CalLib/CalLib.h MPU9150Lib/MPU9150Lib.h MPU9150Lib/MPUQuaternion.h \
MPU9150Lib/MPUVector3.h MotionDriver/inv_mpu.h MotionDriver/inv_mpu_dmp_motion_driver.h 

CMN_OBJS = I2CDev/I2Cdev.o CalLib/CalLib.o MPU9150Lib/MPU9150Lib.o MPU9150Lib/MPUQuaternion.o \
MPU9150Lib/MPUVector3.o MotionDriver/inv_mpu.o MotionDriver/inv_mpu_dmp_motion_driver.o 

DMP_OBJS = demo.o 
ACL_OBJS = AccelCal.o
MAG_OBJS = MagCal.o

CXXFLAGS = -DDMP_FIFO_RATE=9 -Wall -g -O2

$(CMN_OBJS) $(DMP_OBJS) $(ACL_OBJS) : $(HDRS)

demo: $(CMN_OBJS) $(DMP_OBJS)
	$(CXX) -o $@ $^ -lm
	
AccelCal: $(CMN_OBJS) $(ACL_OBJS)
	$(CXX) -o $@ $^ -lm

MagCal: $(CMN_OBJS) $(MAG_OBJS)
	$(CXX) -o $@ $^ -lm
	
.PHONY:clean
clean:
	-rm -f $(objects) *.o
	echo Clean done
    
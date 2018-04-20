#include "mbed.h"

I2C i2c(p28, p27);
Serial pc(USBTX, USBRX); // tx, rx

int main() {
    char data[6];
    
    char initwrite[2]={0x20,0x27};
    char initread=0xA8;
    
    short x,y,z;
   
    
    i2c.frequency(100000);
    
    i2c.write(0x32,initwrite,2);
    
    while(1)
    {
        i2c.write(0x32, &initread,1,true);
        i2c.read(0x33,data,6);
        
        x=*(short*)data;
        y=*((short*)data+1);
        z=*((short*)data+2);
        
        
        pc.printf("X: %d, Y: %d, Z: %d\n",(int)x,(int)y,(int)z);
        wait(.1); // 10Hz --> 1 Hz
        for(int i;i<6;i++) data[i]=0;
    }
    
    return 0;
}

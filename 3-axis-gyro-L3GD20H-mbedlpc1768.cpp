#include "mbed.h"

I2C i2c(p28, p27);
Serial pc(USBTX, USBRX); // tx, rx

int main() {
    char data[6];
    
    char initwrite[6]={0x00,0x10,0x01,0x20,0x02,0x00};
    char initread=0x03;
    
    short x,y,z;
    char *x_h=(char *)&x+1,*x_l=(char *)&x;
    char *y_h=(char *)&y+1,*y_l=(char *)&y;
    char *z_h=(char *)&z+1,*z_l=(char *)&z;
    
    
    i2c.frequency(100000);
    
    i2c.write(0x3c,initwrite+4,2);
    
    while(1)
    {
        i2c.write(0x3c, &initread,1,true);
        i2c.read(0x3d,data,6);
        
        *x_h=data[0],*x_l=data[1];
        *y_h=data[2],*y_l=data[3];
        *z_h=data[4],*z_l=data[5];
        
        
        pc.printf("X: %d, Y: %d, Z: %d\n",(int)x,(int)y,(int)z);
        wait(1);
        for(int i;i<6;i++) data[i]=0;
    }
    
    return 0;
}

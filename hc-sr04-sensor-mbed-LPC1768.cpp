#include "mbed.h"

I2C i2c(p28, p27);
Serial pc(USBTX, USBRX); // tx, rx

char data_mag[6],data_acc[6];
    
char initwrite[4]={0x20,0x27,0x02,0x00};
char initread_mag=0x03,initread_acc=0xA8;
    


Ticker tsample_mag;
Ticker tsample_acc;
Ticker print;

volatile int count;

void sample_mag()
{
    short x,y,z;
    char *x_h=(char *)&x+1,*x_l=(char *)&x;
    char *y_h=(char *)&y+1,*y_l=(char *)&y;
    char *z_h=(char *)&z+1,*z_l=(char *)&z;

    i2c.write(0x3c, &initread_mag,1,true);
    i2c.read(0x3d,data_mag,6);
    *x_h=data_mag[0],*x_l=data_mag[1];
    *y_h=data_mag[2],*y_l=data_mag[3];
    *z_h=data_mag[4],*z_l=data_mag[5]; 
    pc.printf("MAG:  X: %d, Y: %d, Z: %d\n",(int)x,(int)y,(int)z);
}

void sample_acc()
{
    short xx,yy,zz;
    i2c.write(0x32, &initread_acc,1,true);
    i2c.read(0x33,data_acc,6);
        
    xx=*(short*)data_acc;
    yy=*((short*)data_acc+1);
    zz=*((short*)data_acc+2);
        
    pc.printf("ACC: X: %d, Y: %d, Z: %d\n",(int)xx,(int)yy,(int)zz);
}

void print_rate()
{
    int res=count;
    count=0;
    pc.printf("Sample Rate: %d\n",res);
}

int main() {
    
    i2c.frequency(400000);
    
    i2c.write(0x3c,initwrite+2,2);
    i2c.write(0x32,initwrite,2);
    
    tsample_mag.attach(&sample_mag, 1);
    tsample_acc.attach(&sample_acc, 0.5);
    //print.attach(&print_rate, 1);
    
    while(1) wait(1);
    
    return 0;
}

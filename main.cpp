#include "mbed.h"
#include "stdlib.h"
#include "bbcar.h"
#include "bbcar_rpc.h"

Ticker servo_ticker;
PwmOut pin5(D10), pin6(D11);
BBCar car(pin5, pin6, servo_ticker);
BufferedSerial pc(USBTX,USBRX); //tx,rx
BufferedSerial uart(D1,D0); //tx,rx

DigitalInOut pin10(D9);

int main(){
   int x=0;
   char buf[10];
   uart.set_baud(9600);
   int i=0;
   float angle=0;
   parallax_ping  ping1(pin10);
   while(x==0){

      if(uart.readable()){
            
            char recv[1];
            uart.read(recv, sizeof(recv));
            buf[i++]=recv[0];

            if(recv[0] == '\n'){
                angle = atof(buf);
                i=0;
                float shift=angle;
                if(0.5>shift>-0.5){
                    car.turn(-50,-0.92);
                    ThisThread::sleep_for(8000ms);
                    x=1;
                }
                printf("%d",x);
            }
      }
   }
   car.stop();

   car.turn(-250,0.14);
   ThisThread::sleep_for(1700ms);
   car.stop();

   car.turn(-50,-0.92);
   while(1) {
      if((float)ping1<25)
      {
         car.stop();
         break;
      }
      ThisThread::sleep_for(10ms);
   }

   car.turn(-250,-0.1);
   ThisThread::sleep_for(800ms);
   car.stop();
   car.turn(-50,0.5);
   ThisThread::sleep_for(11000);
   car.stop();
   car.turn(-50,-0.92);
   ThisThread::sleep_for(7000ms);
   car.stop();
   ThisThread::sleep_for(5000ms);
   char buff[256], outbuf[256];
   FILE *devin = fdopen(&uart, "r");
   FILE *devout = fdopen(&uart, "w");
   while (1) {
      memset(buff, 0, 256);
      for( int i = 0; ; i++ ) {
         char recv = fgetc(devin);
         if(recv == '\n') {
            printf("\r\n");
            break;
         }
         buff[i] = fputc(recv, devout);
      }
   RPC::call(buff, outbuf);
   }
}
import time
import serial
import sys,tty,termios
global d
global x
x =1
d =input('order')
class _Getch:
    def __call__(self):
        fd = sys.stdin.fileno()
        old_settings = termios.tcgetattr(fd)
        try:
            tty.setraw(sys.stdin.fileno())
            ch = sys.stdin.read(1)
        finally:
            termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
        return ch



if len(sys.argv) < 1:
    print ("No port input")
s = serial.Serial(sys.argv[1])

while(x):
    if d=='park':
        s.write("/turn/run -250 0.14 \n".encode())
        time.sleep(1.3)    
        s.write("/stop/run \n".encode())
        s.write("/turn/run -50 0.92 \n".encode())
        time.sleep(5)    
        s.write("/stop/run \n".encode())
        x=0
        break

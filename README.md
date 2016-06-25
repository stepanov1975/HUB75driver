# HUB75driver
Arduino uno library for driving 1/8 refresh rate, 32x16 HUB75 interface LED matrix
Refresh rate 125FPS
12bits of clolors, 4 bits per color (RGB)
3500 bytes of program memory
RAM: 40 bytes + 768 bytes if no double buffering and 1536 bytes if double buffering used
It takes 7ms to fill all matrix using drawPixel() function (512 times)

Usage example:
```C++
//Initialisation:
HUB75driver matrix;
//if first argument is true double buffering used, need swapBuffers() to refresh
//if second argument is true additional dimming will be applyed. brightness will reduce by half
matrix.init(true, true);
matrix.begin();//Enable interupt
//Drawing
matrix.cleanScreen();//Clean screen
matrix.drawPixel(1, 1, 1, 0, 0);//put single point. parameters x,y,r,g,b
matrix.swapBuffers();//must be used if double buffering enabled
```

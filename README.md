# uFlappyBird
Flappy Bird clone on a microcontroller

[![uFlappy Bird](http://img.youtube.com/vi/RlNqW_0qTrA/0.jpg)](http://www.youtube.com/watch?v=RlNqW_0qTrA)


## Why
I thought it would be fun and challenging.
I saw a few implementations, but I didn't feel they had the same feel as the original.
My end goal was to make a PCB business card and have this as an easter egg.

## Specs
I'm using
- [Teensy 3.1](https://www.pjrc.com/store/teensy32.html) clocked at 8MHz.
- [SPI 128x64 OLED Display](https://www.adafruit.com/product/326)
- A salvaged buzzer with inline 150ohm resistor
- A savlaged button with 300ohm pullup resistor

## Resources
- Used [this](https://github.com/mrt-prodz/ATmega328-Flappy-Bird-Clone) project as a base, then changed the pipe/bird logic, removed color, changed how the game renders, added sound, and probably more stuff too.

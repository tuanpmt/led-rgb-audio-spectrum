# led-rgb-audio-spectrum
This application using [FFT library](http://www.embeddedsignals.com/ARM.htm) for ARM cortex-M3 to analyze audio and display on RGB LED

#features:
- 16x32 RGB LED
- MCU: STM32F103C8T6
#demonstration:
Youtube: [https://youtu.be/YXznM0IRcUU](https://youtu.be/YXznM0IRcUU)
[![Youtube](http://img.youtube.com/vi/YXznM0IRcUU/0.jpg)](https://youtu.be/YXznM0IRcUU)

#installations
1. Hardware Diagram: ```audio-spectrum-hardware\dv_spectrum_corel```
![](images/dv_spectrum.png)

Row board: ```audio-spectrum-hardware\dv_spectrum_row```
![](images/row.png)

Column board: ```audio-spectrum-hardware\dv_spectrum_col```
![](images/col.png)

Main board: ```audio-spectrum-hardware\dv_spectrum_main```
![](images/controller.png)

2. Firmware
```c
git clone --recursive https://github.com/tuanpmt/led-rgb-audio-spectrum.git
```

and open with Keil C

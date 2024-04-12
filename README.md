# ECE484_Midterm_Project

//compiling depth_sensor.c in windows cmd

avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o depth_sensor.o depth_sensor.c

avr-gcc -mmcu=atmega328p depth_sensor.o -o depth_sensor

avr-objcopy -O ihex -R .eeprom depth_sensor depth_sensor.hex

avrdude -patmega328p -Pcom(insert your port number here) -carduino -D -U flash:w:depth_sensor.hex:i

//compiling flow_sensor.c in windows cmd

avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o flow_sensor.o flow_sensor.c

avr-gcc -mmcu=atmega328p flow_sensor.o -o flow_sensor

avr-objcopy -O ihex -R .eeprom flow_sensor flow_sensor.hex

avrdude -patmega328p -Pcom(insert your port number here) -carduino -D -U flash:w:flow_sensor.hex:i

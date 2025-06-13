#include <reg51.h>  
// Define pins for motor control 
sbit IN1 = P2^5;  // Control pin 1 (connected to motor driver) 
sbit IN2 = P2^1;  // Control pin 2 (connected to motor driver) 
sbit IN3 = P2^2;  // Control pin 3 (connected to motor driver) 
sbit IN4 = P2^3;  // Control pin 4 (connected to motor driver) 
sbit LED = P2^4;  // LED pin to check whether the microcontroller is 
running 
// Function prototypes 
void ser_int();              
unsigned char rx();          
 // UART initialization function 
 // Function to receive data via UART 
void tx(unsigned char a);     
void delay();                
// Function to transmit data via UART 
 // Delay function for simple timing 
void main() { 
unsigned char get;        
int m;                   
LED = 0;                 
// Variable to store received UART data 
 // Loop counter 
 // Turn off LED initially 
// Blink LED 10 times to ensure the system is running 
for (m=0; m<10; m++) { 
        delay();              // Wait for some time 
        LED = LED ^ 1;        // Toggle LED state 
    } 
 
    ser_int();                // Initialize UART communication 
 
    while(1) { 
        get = rx();           // Receive a character via Bluetooth/serial 
communication 
        tx(get);              // Transmit the received character back (echo 
function) 
 
        // Motor control based on received command 
        if (get == 'F') {      
            /* Move Forward */ 
            IN1 = 1;          // Activate motor in forward direction 
            IN3 = 1;           
            IN2 = 0;  
            IN4 = 0; 
        } else if (get == 'B') { 
            /* Move Backward */ 
            IN2 = 1;          // Activate motor in reverse direction 
            IN4 = 1; 
            IN1 = 0; 
            IN3 = 0; 
        } else if (get == 'R') { 
            /* Turn Right */ 
            IN1 = 1;          // Rotate motor in a way to turn the robot to the 
right 
            IN2 = 0; 
            IN3 = 0; 
            IN4 = 0; 
        } else if (get == 'L') { 
            /* Turn Left */ 
            IN3 = 1;          // Rotate motor in a way to turn the robot to the 
left 
            IN2 = 0; 
            IN1 = 0; 
            IN4 = 0; 
        } else if (get == 'S') { 
            /* Stop the Motor */ 
            IN1 = IN2 = IN3 = IN4 = 0;  // Stop all motor control signals 
        } 
    } 
} 
 
// UART Initialization Function 
void ser_int() { 
SCON = 0x50;    // Set serial mode to 8-bit UART 
TMOD = 0x20;    // Set Timer 1 to Mode 2 (auto-reload) 
TH1 = TL1 = 0xFD; // Set baud rate to 9600 (FD for 11.0592 MHz 
clock) 
TR1 = 1;       
} 
 // Start Timer 1 
// Function to receive data via UART 
unsigned char rx() { 
while (RI == 0);   // Wait until data is received (RI = Receive 
Interrupt flag) 
RI = 0;           
return SBUF;       
} 
 // Clear the Receive Interrupt flag 
// Return the received byte from the serial buffer 
// Function to transmit data via UART 
void tx(unsigned char a) { 
SBUF = a;         
 // Load data into the serial buffer (SBUF) 
while (TI == 0);   // Wait until the data is transmitted (TI = Transmit 
Interrupt flag) 
TI = 0;           
 // Clear the Transmit Interrupt flag 
} 
// Simple delay function 
void delay() { 
int i, j, k; 
for (i = 0; i < 100; i++) { 
for (j = 0; j < 100; j++) { 
for (k = 0; k < 10; k++); 
} 
} 
}

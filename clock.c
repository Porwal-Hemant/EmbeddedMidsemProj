#include <reg51.h>

// Define ports
#define SEGMENT P1  // Segment Data
#define DIGIT   P3  // Digit Selection via Decoder

// Define digit selection bits
sbit D0 = P3^3;
sbit D1 = P3^4;

// Digit patterns for Common Cathode Seven-Segment Display (0-9)
unsigned char numbers[10] = { 0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};

// Function to introduce a short delay (for multiplexing)
void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 1275; j++);  // Approx 1ms delay
}

// Function to display a digit at a specific position
void display_digit(unsigned char digit, unsigned char position) {
    // Load segment data
    SEGMENT = numbers[digit];

    // Enable only the desired digit
    if (position == 0) D0=D1=0;
    else if (position == 1) D0=1,D1=0;
    else if (position == 2) D0=0,D1=1;
    else if (position == 3) D0=1,D1=1;

    // Hold the digit on for a short period
    delay_ms(5);
}

// Function to display the time on the 4-digit 7-segment display
void display_time(unsigned char minutes, unsigned char seconds) {
    // Display tens of minutes and ones of minutes
    display_digit(minutes / 10, 3); // Tens of minutes
    display_digit(minutes % 10, 2); // Ones of minutes

    // Display tens of seconds and ones of seconds
    display_digit(seconds / 10, 1); // Tens of seconds
    display_digit(seconds % 10, 0); // Ones of seconds
}

void main() {
    unsigned char minutes = 0;  // Initial minutes value
    unsigned char seconds = 0;  // Initial seconds value

    while (1) {
        display_time(minutes, seconds);  // Display current time
        // Increment seconds
        seconds++;
        if (seconds == 60) {
            seconds = 0;
            minutes++;
            if (minutes == 60) {
                minutes = 0; // Reset minutes after 60
            }
        }

        delay_ms(100);  // 1-second delay (simulate stopwatch tick)
    }
	}
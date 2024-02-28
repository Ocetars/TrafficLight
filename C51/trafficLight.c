/*-----------------------------------------------
  Name: Traffic Light new23
  Forum: www.doflye.net
  Written by: ocetars XIA
  Date: 2009.5
  Modification: None
  Content:  1. Purpose of the program: Use timer to learn the principle of countdown traffic light
                The main program is the same as the countdown
            2. Hardware requirements: Digital tube, 12M crystal
            3. P1 port is connected to LED for traffic light display
            4. Digital tube is used to display time
------------------------------------------------*/
#include <reg52.h> // Include header file, generally no need to change,
// The header file includes the definition of special function registers

sbit LACTCH1 = P2 ^ 2;
sbit LACTCH2 = P2 ^ 3;
sbit LACTCH3 = P2 ^ 2; // New latch
sbit LACTCH4 = P2 ^ 3;
/*------------------------------------------------
                Global Variables
------------------------------------------------*/
bit redAflag, greenAflag, yellowAflag, turnRedAflag, new; // Define red, green, yellow light flag bits
bit redBflag, greenBflag, yellowBflag, turnRedBflag; // Define red, green, yellow light flag bits

redA = 0X7F; // Define red light
yellowA = 0XBF; // Define yellow light
greenA = 0XDF; // Define green light
redB = 0XF7; // Define red light
yellowB = 0XFB; // Define yellow light
greenB = 0XFD; // Define green light


code unsigned char tab[] =
    {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};
// Common cathode digital tube 0-9

unsigned char Dis_Shiwei; // Define tens place
unsigned char Dis_Gewei;  // Define ones place
unsigned char Dis_ShiweiB;
unsigned char Dis_GeweiB;
/*------------------------------------------------

------------------------------------------------*/
void delay(unsigned int cnt)
{
  while (--cnt)
    ;
}
/*------------------------------------------------
              Main Program
------------------------------------------------*/
main()
{
  TMOD |= 0x01; // Timer setting 10ms in 12M crystal
  TH0 = 0xd8;
  TL0 = 0xf0;
  IE = 0x82; // Open interrupt
  TR0 = 1;

  // P1 = greenA; // Green light on
  P1 = 0XD7;
  yellowAflag = 1 ;
  while (1)
  {
    P0 = Dis_Shiwei; // Display tens place
    LACTCH1 = 1;     // Latch
    LACTCH1 = 0;
    P0 = 0xfe;
    LACTCH2 = 1; // Latch
    LACTCH2 = 0;
    delay(300);     // Short delay
    P0 = Dis_Gewei; // Display ones place
    LACTCH1 = 1;    // Latch
    LACTCH1 = 0;
    P0 = 0xfd;
    LACTCH2 = 1; // Latch
    LACTCH2 = 0;
    delay(300);
    P0 = Dis_ShiweiB; // Display tens place
    LACTCH3 = 1;      // Latch
    LACTCH3 = 0;
    P0 = 0xef;
    LACTCH4 = 1; // Latch
    LACTCH4 = 0;
    delay(300);      // Short delay
    P0 = Dis_GeweiB; // Display ones place
    LACTCH3 = 1;     // Latch
    LACTCH3 = 0;
    P0 = 0xdf;
    LACTCH4 = 1; // Latch
    LACTCH4 = 0;
    delay(300);
  }
}
/*------------------------------------------------
            Timer 0 Interrupt Function
------------------------------------------------*/
void tim(void) interrupt 1
{
  static unsigned char second = 30, count; // Initial value 99 A is green first
  static unsigned char secondB = 30; // Initial value for second traffic light system
  TH0 = 0xd8; // Reassign
  TL0 = 0xf0;
  count++;
  if (count == 100)
  {
    count = 0;
    second--; // Second minus 1
    secondB--; 
    if (second == 0)
    {
      if (yellowAflag)
      {
        second = 5;
        secondB = 5;
        // P1 = yellowA; // Yellow light on for 5 seconds
        P1 = 0XB7;

        // turnRedAflag = 0;
        redAflag = 1;
        yellowAflag = 0;
        greenAflag = 1;
      }
      else if (redAflag)
      {
        second = 15;
        secondB = 15;
        // P1 = redA; // Red light on for 3 seconds
        P1 = 0X7D;

        turnRedAflag = 1;
        redAflag = 0;
        yellowAflag = 0;
        greenAflag = 1;
      }
      else if (turnRedAflag)
      {
        second = 5;
        secondB = 5;
        P1 = 0X7B; // Red light on for 5 seconds

        redAflag = 0;
        turnRedAflag = 0;
        yellowAflag = 0;
        greenAflag = 0;
        new = 1;
      }
      else if (new)
      {
        second = 30;
        secondB = 35;
        P1 = 0XD7; // A green, B red

        redAflag = 0;
        yellowAflag = 1;
        greenAflag = 0;
        new = 0;
      }
      

    }
    Dis_Shiwei = tab[second / 10]; // Processing tens place display value
    Dis_Gewei = tab[second % 10];  // Processing ones place display value
    Dis_ShiweiB = tab[secondB / 10]; // Processing tens place display value for second traffic light system
    Dis_GeweiB = tab[secondB % 10];  // Processing ones place display value for second traffic light system  
  }
}
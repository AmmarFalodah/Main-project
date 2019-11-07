// LCD module connections
sbit LCD_RS at RB5_bit;
sbit LCD_EN at RB4_bit;
sbit LCD_D4 at RB0_bit;
sbit LCD_D5 at RB1_bit;
sbit LCD_D6 at RB2_bit;
sbit LCD_D7 at RB3_bit;

sbit LCD_RS_Direction at TRISB5_bit;
sbit LCD_EN_Direction at TRISB4_bit;
sbit LCD_D4_Direction at TRISB0_bit;
sbit LCD_D5_Direction at TRISB1_bit;
sbit LCD_D6_Direction at TRISB2_bit;
sbit LCD_D7_Direction at TRISB3_bit;


////////////////////////////////////////////////////////////////////////////////
// Project:         Thumper_Servo_01                                          //
// Fiile:           Main.c                                                    //
// Function:        Test Adafruit servo driver PCA9685                        //
// MCU:             PIC18F8722                                                //
// Board:           BIGPIC5                                                   //
// Power            5V.                                                       //
// Compiler:        mikroC PRO for PIC version 6.6.2                          //
// Programmer:      On-board Mikro                                            //
// Author:          WVL                                                       //
// Date:            February 2013                                             //
////////////////////////////////////////////////////////////////////////////////
#define Write_address 0x80  // I2C address for PCA9865 with no solder bridges
#define Read_address Write_address+1
#define PCA9685_software_reset 0x06
#define Reset   0x01        // Reset the device
#define MODE1   0x00        // 0x00 location for Mode1 register address
#define MODE2   0x01        // 0x01 location for Mode2 reigster address
#define LED0    0x06        // location for start of LED0 registers
#define ALL_CH_ON_L_reg   0xFA
#define ALL_CH_ON_H_reg   0xFB
#define ALL_CH_OFF_L_reg  0xFC
#define ALL_CH_OFF_H_reg  0xFD
#define HEARTBEAT portb.rb0 // green led on ETT board
////////////////////////////////////////////////////////////////////////////////
// Prototype functions - functions at end
void PCA9685_init();
void PCA9685_send(unsigned int value, unsigned char led);
void PCA9685AllLedOff();
unsigned char PCA9685_read_byte(unsigned char chip_register);
unsigned adc_value;
void PCA9685_write_byte(unsigned char chip_register, unsigned char value);
void PCA9685_write_word(unsigned char chip_register, unsigned int word_value);
void PCA9685_soft_reset();
////////////////////////////////////////////////////////////////////////////////
char LED2VALUE[6];
char adc_value_text[10];
  // txt is "  437" (two blanks here)


 int step0a = 250 ;
 int step0b = 150 ;
 int step2a = 250 ;
 int step2b = 150 ;
 int step4a = 250 ;
 int step4b = 150 ;
 int step6a = 250 ;
 int step6b = 150 ;
 int step8a = 250 ;
 int step8b = 150 ;
 int step10a = 250 ;
 int step10b = 150 ;

void main(){
     unsigned int jx1=0;
     unsigned int jy1=0;
     unsigned int jx2=0;
     unsigned int jy2=0;
     unsigned int jx3=0;
     unsigned int jy3=0;


    // block variables
   // unsigned char               n = 0;   // LED flash
    //unsigned int            loop = 0;   // loop counter
   // unsigned int             pwm = 0;
   // unsigned int                 x=0;
      ////  Variables foe LED0 off bytes

     unsigned int                LED0off_byte=200;
      ////  Variables foe LED2 off bytes

     unsigned int                LED2off_byte=200;
      ////  Variables foe LED4 off bytes

     unsigned int                LED4off_byte=320;
     ////  Variables foe LED6 off bytes

     unsigned int                LED6off_byte=200;
     ////  Variables foe LED8 off bytes

     unsigned int                LED8off_byte=200;
     ////  Variables foe LED10 off bytes

     unsigned int                LED10off_byte=200;
                   // disable comparators
    // set up peripherals
    I2C1_Init(100000);
    PCA9685_init();
    Lcd_Init();
    ADC_Init();  // Initialize ADC module with default settings
    ADCon1 = 0b00001110;

    //Lcd_Out(1, 3, "Hello!");




    TRISC = 0b11111111;                 // I2C2 pins must be inputs
    TRISD = 0b11111111;
    while(1){
    /// jx1 = ADC_Read(1);    // read analog value from ADC module channel
      adc_value = ADC_Read(1);

    wordtostr(adc_value,adc_value_text);

    Lcd_Out(1,1,adc_value_text);

    delay_ms(100);

         WordToStr(LED0off_byte, LED2VALUE);
         Lcd_Out(2, 3, LED2VALUE);

             /////////////////////////**0**////////////////////////////////
         if ((ADC_Read(0))>step0a)
        {
            LED0off_byte= LED0off_byte+15;
            
            step0a= step0a+30;
            step0b= step0b+30;
            if ( LED0off_byte> 570)
            {
             LED0off_byte=570;
            }

            while((ADC_Read(0))>step0a) ;

         }
        if ((ADC_Read(0))<step0b)
        {
         LED0off_byte= LED0off_byte-15;
         step0a= step0a-30;
         step0b= step0b-30;
        while((ADC_Read(0))<step0b);

         }
         if ( LED0off_byte<140 )
         {
          LED0off_byte=140;
         }
          /////////////////////////**2**////////////////////////////////
          
          if ((ADC_Read(1))>step2a)
        {
            LED2off_byte= LED2off_byte+15;

            step2a= step2a+30;
            step2b= step2b+30;
            if ( LED2off_byte> 570)
            {
             LED2off_byte=570;
            }

            while((ADC_Read(1))>step2a) ;

         }
        if ((ADC_Read(1))<step2b)
        {
         LED2off_byte= LED2off_byte-15;
         step2a= step2a-30;
         step2b= step2b-30;
        while((ADC_Read(1))<step2b);

         }
         if ( LED2off_byte<140 )
         {
          LED2off_byte=140;
         }

         /////////////////////////**4**////////////////////////////////
         
          if ((ADC_Read(2))>step4a)
        {
            LED4off_byte= LED4off_byte+15;

            step4a= step4a+30;
            step4b= step4b+30;
            if ( LED4off_byte> 570)
            {
             LED4off_byte=570;
            }

            while((ADC_Read(2))>step4a) ;

         }
        if ((ADC_Read(2))<step4b)
        {
         LED4off_byte= LED4off_byte-15;
         step4a= step4a-30;
         step4b= step4b-30;
        while((ADC_Read(2))<step4b);

         }
         if ( LED4off_byte<140 )
         {
          LED4off_byte=140;
         }
         
         /////////////////////////**6**////////////////////////////////

         if ((ADC_Read(3))>step6a)
        {
            LED6off_byte= LED6off_byte+15;

            step6a= step6a+30;
            step6b= step6b+30;
            if ( LED6off_byte> 570)
            {
             LED6off_byte=570;
            }

            while((ADC_Read(3))>step6a) ;

         }
        if ((ADC_Read(3))<step6b)
        {
         LED6off_byte= LED6off_byte-15;
         step6a= step6a-30;
         step6b= step6b-30;
        while((ADC_Read(3))<step6b);

         }
         if ( LED6off_byte<140 )
         {
          LED6off_byte=140;
         }

         /////////////////////////**8**////////////////////////////////
           
         if ((ADC_Read(4))>step8a)
        {
            LED8off_byte= LED8off_byte+15;

            step8a= step8a+30;
            step8b= step8b+30;
            if ( LED8off_byte> 570)
            {
             LED8off_byte=570;
            }

            while((ADC_Read(4))>step8a) ;

         }
        if ((ADC_Read(4))<step8b)
        {
         LED8off_byte= LED8off_byte-15;
         step8a= step8a-30;
         step8b= step8b-30;
        while((ADC_Read(4))<step8b);

         }
         if ( LED8off_byte<140 )
         {
          LED8off_byte=140;
         }
           
         /////////////////////////**10**////////////////////////////////
           
         if ((ADC_Read(5))>step10a)
        {
            LED10off_byte= LED10off_byte+15;

            step10a= step10a+30;
            step10b= step10b+30;
            if ( LED10off_byte> 570)
            {
             LED10off_byte=570;
            }

            while((ADC_Read(5))>step10a) ;

         }
        if ((ADC_Read(5))<step10b)
        {
         LED10off_byte= LED10off_byte-15;
         step10a= step10a-30;
         step10b= step10b-30;
        while((ADC_Read(5))<step10b);

         }
         if ( LED10off_byte<140 )
         {
          LED10off_byte=140;
         }
           
           ///////////////////LED0/////////////////////////////////
        PCA9685_Write_word(6,0x0000);// turn on at time 0
        PCA9685_Write_word(8,LED0off_byte);// turn off at time 409 0r 0x0199

         ///////////////////LED2/////////////////////////////////
        PCA9685_Write_word(14,0x0000);// turn on at time 0
        PCA9685_Write_word(16,LED2off_byte);// turn off at time 409 0r 0x0199

        ////////////////////////LED4//////////////////////////////////
        PCA9685_Write_word(22,0x0000);// turn on at time 0
        PCA9685_Write_word(24,LED4off_byte);// turn off at time 409 0r 0x0199

         ////////////////////////LED6//////////////////////////////////
        PCA9685_Write_word(30,0x0000);// turn on at time 0
        PCA9685_Write_word(32,LED6off_byte);// turn off at time 409 0r 0x0199

         ////////////////////////LED8//////////////////////////////////
        PCA9685_Write_word(38,0x0000);// turn on at time 0
        PCA9685_Write_word(40,LED8off_byte);// turn off at time 409 0r 0x0199

         ////////////////////////LED10//////////////////////////////////
        PCA9685_Write_word(46,0x0000);// turn on at time 0
        PCA9685_Write_word(48,LED10off_byte);// turn off at time 409 0r 0x0199



    }
}
////////////////////////////////////////////////////////////////////////////////
// Functions
// Init the chip with pwm frequency and MODE2 settings
void PCA9685_init(){
     I2C1_start();             // Start
     I2C1_Wr(Write_address);   // Slave Write_address
     I2C1_Wr(MODE1);           // Mode 1 ADDRESS
     I2C1_Wr(0b00110001);      // Sleep and change default PWM frequency
     I2C1_stop();              // Stop
     delay_ms(1);              // Required 50 us delay
     I2C1_start();             // Start
     I2C1_Wr(Write_address);   // Slave Write_address
     I2C1_Wr(0xFE);            // PWM frequency PRE_SCALE ADDRESS to set pwm at 100Hz
     I2C1_Wr(0x6E);            // Osc_clk/(4096*update_rate)=25000000/(4096*100)=60=0x3C
     I2C1_stop();              // Stop
     delay_ms(1);              // delay at least 500 us
     I2C1_start();             // Start
     I2C1_Wr(Write_address);   // Slave Write_address
     I2C1_Wr(MODE1);           // Mode 1 register ADDRESS
     I2C1_Wr(0b10100001);      // Set MODE1
     I2C1_stop();              // Stop
     delay_ms(1);              // delay at least 500 us
     I2C1_start();             // Start
     I2C1_Wr(Write_address);   // Slave Address
     I2C1_Wr(MODE2);           // Mode2 register ADDRESS
     I2C1_Wr(0b00000100);      // Set MODE2
     I2C1_stop();              //
}
// Send pulse length[0-4095] to selected LED/SERVO[0-15]
void PCA9685_send(unsigned int value, unsigned char led){
     unsigned char pulse_length;// temp variable for PWM
     I2C1_start();              // Start
     I2C1_Wr(Write_address);    // address of selected pca9685
     I2C1_Wr(LED0 + 4 * led);   // select slected LED ADDRESS
     I2C1_Wr(0x00);             // LED_ON_L
     I2C1_Wr(0x00);             // LED_ON_H
     pulse_length = value;      // PWM value lo byte
     I2C1_Wr(pulse_length);     // LED_OFF_L
     pulse_length = value>>8;   // pwm 16 bit long, now shift upper 8 to lower 8
     I2C1_Wr(pulse_length);     // LED_OFF_H
     I2C1_stop();               // stop
}
void PCA9685AllLedOff(){
     I2C1_start();              // atart
     I2C1_Wr(Write_address);    // select pca9685
     I2C1_Wr(ALL_CH_OFF_L_reg); // All LEDs Off regiter
     I2C1_Wr(0b00000000);       // low byte
     I2C1_Wr(0b00010000);       // high byte, bit4 set so full_off see page 21
     I2C1_stop();               // Stop
}
// Read a byte and return it's value
unsigned char PCA9685_read_byte(unsigned char chip_register){
    unsigned char temp = 0x00;
    I2C1_Start();
    I2C1_Wr(Write_address);
    I2C1_Wr(chip_register);
    I2C1_Start();
    I2C1_Wr(Read_address);
    temp = I2C1_Rd(0);
    I2C1_Stop();
    return temp;
}
void PCA9685_write_byte(unsigned char chip_register, unsigned char value){
     I2C1_Start();
     I2C1_Wr(Write_address);
     I2C1_Wr(chip_register);
     I2C1_Wr(value);
     I2C1_Stop();
}
// Write 16bits to chip_register, increments automatically from lo to hi byte
void PCA9685_write_word(unsigned char chip_register, unsigned int word_value){
     unsigned char hb = 0x00;
     unsigned char lb = 0x00;
     lb = (word_value & 0x00FF);
     hb = ((word_value & 0xFF00) >> 0x08);
     PCA9685_write_byte(chip_register,lb);
     PCA9685_write_byte((chip_register+1),hb);
}
// Soft re-set
void PCA9685_soft_reset(){
    I2C1_Start();
    I2C1_Wr(0x00);
    I2C1_Wr(PCA9685_software_reset);
    I2C1_Stop();
}
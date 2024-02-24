//Autor: Rafael Ferrari



#include <16f877a.h>
#device ADC = 10
#fuses HS,NOWDT,NOPROTECT,NOPUT,NOLVP,BROWNOUT
#use delay(clock=2M)
#use standard_io(D)

#include "map_function.c"


#define LCD_DB4   PIN_D4         // Pines de la pantalla LCD
#define LCD_DB5   PIN_D5
#define LCD_DB6   PIN_D6
#define LCD_DB7   PIN_D7
#define LCD_RS    PIN_D2
#define LCD_E     PIN_D3
#include <lcd.c>



long valor_adc;
int valor_pwm;
int porcentaje;


void main()
{
   lcd_init();
   setup_timer_2(t2_div_by_16, 255, 1);         // Configura timer 2
   setup_ccp1(ccp_pwm); 
   setup_ccp2(ccp_pwm);// Configura modulo CCP1 como pwm
   setup_adc_ports(AN0); 
   setup_adc(adc_clock_internal);               // Reloj interno para conversion del ADC
   set_pwm1_duty(0);    
   set_pwm2_duty(0); // Inicia el pwm 1 en 0
   
   while(true)
   {
      set_adc_channel(0);
      
      delay_us(2);
      valor_adc = read_adc();
      valor_pwm = map(valor_adc, 0, 1023, 0, 255);
      porcentaje = map(valor_pwm, 0, 255, 0, 100);
      set_pwm1_duty(valor_pwm);
      set_pwm2_duty(valor_pwm);
      lcd_gotoxy(1,1);
      printf(lcd_putc,"PWM: %u ",valor_pwm);
      lcd_gotoxy(1,2);
      printf(lcd_putc,"Porcentaje: %u%% "porcentaje);
      delay_ms(50);
   }
}


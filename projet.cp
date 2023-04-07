#line 1 "C:/Users/ASUS/OneDrive/Desktop/projet_micro/projet.c"



 int temp_res;

 sbit LCD_RS at RC2_bit;
 sbit LCD_EN at RC3_bit;

 sbit LCD_D4 at RC4_bit;
 sbit LCD_D5 at RC5_bit;
 sbit LCD_D6 at RC6_bit;
 sbit LCD_D7 at RC7_bit;




 sbit LCD_RS_Direction at TRISC2_bit;
 sbit LCD_EN_Direction at TRISC3_bit;
 sbit LCD_D4_Direction at TRISC4_bit;
 sbit LCD_D5_Direction at TRISC5_bit;
 sbit LCD_D6_Direction at TRISC6_bit;
 sbit LCD_D7_Direction at TRISC7_bit;
 int i,pluie;
 int nb_panne=0;
 float adcValue=0;
 float realvalue;
 char txt[20];
 int desactiver,activer;





void main() {
 ADC_init();
TRISB=255;
 TRISD=0;
 INTCON.GIE = 1;
 INTCON.RBIE = 1;
 INTCON.INTE= 1;
 OPTION_REG.INTEDG= 1 ;
 desactiver=0;
 pluie=0;
 activer=0;
 PORTD.RD5 = 0;


 Lcd_Init();
 Lcd_cmd(_LCD_CLEAR);

 Lcd_out(2,3,"SMART GARDEN");
 Adc_Init();

 while(1)
 {
 adcValue = ADC_Read(0);
 realvalue=adcValue/(10.2);


 if(activer==1){
 Lcd_cmd(_LCD_CLEAR);
 Lcd_out(2,1,"Arrosage Gazon");
 activer=0;
 }
 if(desactiver==1){
 Lcd_cmd(_LCD_CLEAR);
 Lcd_out(2,1,"Fin Arrosage Gazon");
 desactiver=0;
 }
 if(pluie==1){
 Lcd_cmd(_LCD_CLEAR);
 Lcd_out(2,1,"Pluie !!");
 pluie=0;
 delay_ms(500);
 Lcd_cmd(_LCD_CLEAR);
 Lcd_out(2,1,"Smart Garden");
 }
 }
 if((realvalue>30)&&(realvalue<50)){
 PORTD.RD5=1;
 PORTD.RD6=0;
 Lcd_cmd(_LCD_CLEAR);
 Lcd_out(2,1,"Arrosage Gazon");
 delay_ms(1000);
 }else if(realvalue>50){
 PORTD.RD5=0;
 PORTD.RD6=0;
 Lcd_cmd(_LCD_CLEAR);
 Lcd_out(2,1,"Fin Arrosage");
 delay_ms(1000);
 Lcd_cmd(_LCD_CLEAR);
 Lcd_out(2,1,"Smart Garden");
 delay_ms(1000);

 }
 else if(realvalue<=29)
 {
 PORTD.RD5=0;
 PORTD.RD6=1;
 Lcd_cmd(_LCD_CLEAR);
 Lcd_out(2,1,"Panne");
 nb_panne++;
 delay_ms(1000);
 }
 }






void interrupt() {
 if(INTCON.INTF==1){
 if(PORTB.RB0==1){
 PORTD.RD5 = 0;
 pluie=1;
 }
 INTCON.INTF=0;
 }else if(INTCON.RBIF==1){
 if(PORTB.RB4==1)
 {
 PORTD.RD5=1;
 activer=1;
 }
 if(PORTB.RB4==0)
 {
 PORTD.RD5=0;
 desactiver=1;
 }
 INTCON.RBIF=0;
 }
}

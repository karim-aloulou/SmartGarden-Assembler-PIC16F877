#line 1 "C:/Users/msi/Desktop/fawadhel/2A 21-22/MICROCONTROLLEUR/PROJET FINAL/MyProject.c"
#line 148 "C:/Users/msi/Desktop/fawadhel/2A 21-22/MICROCONTROLLEUR/PROJET FINAL/MyProject.c"
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

int consulter;
int intrp_ouv,intrp_ferm;
int pluie, nb_panne;
float realvalue, adcValue;
char string_panne[20]="";
int test_arrosage;
int variable;
char string_variable[20]="";
int test_panne;
int NB;

void main()
{

 TRISB=255;
 TRISA=255;
 TRISD=0;
 INTCON.GIE = 1;
 INTCON.RBIE = 1;

 OPTION_REG.INTEDG= 1 ;
 intrp_ouv=0;
 pluie=0;
 nb_panne=0;
 consulter=0;
 intrp_ferm=0;
 adcValue=0;
 test_arrosage =0;
 variable =0;
 test_panne=0;
 Lcd_Init();
 ADC_Init();
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_Cmd(_LCD_CURSOR_OFF);

 Lcd_Out(1, 1, "Smart Garden!!");
 delay_ms(500);
 Lcd_Cmd(_LCD_CURSOR_OFF);
 while (1)
 { Lcd_Cmd(_LCD_CURSOR_OFF);
 adcValue = ADC_Read(0);
 realvalue=adcValue*0.489;

 if(intrp_ouv==1 )
 {
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_out(1,1,"Arrosage Gazon");
 intrp_ouv=0;
 delay_ms(500);
 }
 if(intrp_ferm==1 )
 {
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_out(1,1,"Fin Arrosage");
 intrp_ferm=0;
 delay_ms(500);
 }
 if(pluie==1)
 {
 Lcd_cmd(_LCD_CLEAR);
 Lcd_out(1,1,"Pluie !!");

 delay_ms(500);
 Lcd_cmd(_LCD_CLEAR);
 Lcd_out(1,1,"Smart Garden");
 }

 if (realvalue >=30 && realvalue<=50)
 test_arrosage=1;
 if(realvalue==30)
 {
 test_panne = 1;
 }
 if(test_arrosage==1&& pluie==0 )
 {
 PORTD.RD5=1;

 Lcd_cmd(_LCD_CLEAR);
 Lcd_out(1,1,"Arrosage Gazon");
 test_panne = 1;
 test_arrosage=0;
 delay_ms(500);
 Lcd_cmd(_LCD_CLEAR);
 Lcd_out(1,1,"Smart Garden");
 }
 if(realvalue>=50){
 test_arrosage =0;
 PORTD.RD5=0;

 Lcd_cmd(_LCD_CLEAR);
 Lcd_out(1,1,"Fin Arrosage");
 delay_ms(1000);
 Lcd_cmd(_LCD_CLEAR);
 Lcd_out(1,1,"Smart Garden!!");
 test_panne = 1;
 delay_ms(1000);
 }
 if(realvalue<=29)
 {
 test_arrosage =0;
 PORTD.RD5=0;

 INTCON.T0IE=1;
 TMR0 = 0;
 OPTION_REG=0b00000101;
 NB= 183;

 Lcd_cmd(_LCD_CLEAR);

 if (test_panne == 1) {
 nb_panne++;
 PORTD.RD6=1;
 test_panne = 0;
 }
 Lcd_out(2,1,"Panne");
 delay_ms(1500);
 Lcd_cmd(_LCD_CLEAR);
 PORTD.RD6=0;
 Lcd_out(1,1,"Smart Garden");
 }
 if (consulter == 1)
 {
 Lcd_cmd(_LCD_CLEAR);
 EEPROM_Write( 0 , nb_panne);
 variable = EEPROM_Read( 0 );
 Lcd_out(1,1,"Nombre de panne:");
 InttoStr(variable,string_variable);
 Lcd_out(2,1,string_variable);
 consulter=0;
 delay_ms(500);
 }
}
 }


 void interrupt()
{ if(INTCON.T0IF==1){
 INTCON.T0IF=0;
 NB--;

 if(NB==0){
 PORTD.RD6=0;
 INTCON.T0IE=0;
 }
}
 if(INTCON.INTF==1)
 {
 if(PORTB.RB0==1)
 {
 PORTD.RD5 = 0;

 pluie=1;
 }
 INTCON.INTF=0;

 }else if(INTCON.RBIF==1)
 {
 if(PORTB.RB4==1)
 {
 PORTD.RD5=1;

 intrp_ouv=1;
 }
 if(PORTB.RB4==0)
 {
 PORTD.RD5=0;

 intrp_ferm=1;
 }
 if(PORTB.RB5==1)
 {
 consulter=1;
 }

 INTCON.RBIF=0;

 }
 }

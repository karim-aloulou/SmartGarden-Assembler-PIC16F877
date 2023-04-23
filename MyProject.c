//Title: LCD interfacing with PIC16f877a
/*
  //LCD module connections
  sbit LCD_RS at RC2_bit; //LCD reset
  sbit LCD_EN at RC3_bit; //LCD enable
  sbit LCD_D4 at RC4_bit; //Data
  sbit LCD_D5 at RC5_bit; //Data
  sbit LCD_D6 at RC6_bit; //Data
  sbit LCD_D7 at RC7_bit; //Data
  //LCD Pin Direction
  sbit LCD_RS_Direction at TRISC2_bit;
  sbit LCD_EN_Direction at TRISC3_bit;
  sbit LCD_D4_Direction at TRISC4_bit;
  sbit LCD_D5_Direction at TRISC5_bit;
  sbit LCD_D6_Direction at TRISC6_bit;
  sbit LCD_D7_Direction at TRISC7_bit;
         int i,pluie,nb_panne=0;
         int intrp_ouv,intrp_ferm,affich_panne,realvalue_aftersecond;
         float adcValue=0;
         float realvalue;
         char txt[20];
         int NB;
  Adc_Init();
   #define ADDRESS 0
void main() {
  //Config
  TRISB=255;
  TRISD=0;
  TRISA=255;
  INTCON.GIE = 1;  //(Activer les interruptions)
  INTCON.RBIE = 1; //(Activer les interruptions RB4-->RB7)
  INTCON.INTE= 1; //(Activer les interruption RB0)
  OPTION_REG.INTEDG= 1 ;
  intrp_ouv=0;
  pluie=0;
  intrp_ferm=0;
  nb_panne=0;
  //Init
  PORTD=0;
  Lcd_Init();
  Lcd_cmd(_LCD_CLEAR);
  Lcd_out(2,1,"Smart Garden");

       while(1){
        adcValue = ADC_Read(0);
        realvalue=adcValue/(10.2);
        delay_ms(1000);
        adcValue = ADC_Read(0);
        realvalue_aftersecond=adcValue/(10.2);
 if(intrp_ouv==1){
 Lcd_cmd(_LCD_CLEAR);
  Lcd_out(2,1,"Arrosage Gazon");
  intrp_ouv=0;
 }
 if(intrp_ferm==1){
 Lcd_cmd(_LCD_CLEAR);
  Lcd_out(2,1,"Fin Arrosage Gazon");
  intrp_ferm=0;
 }
 if(pluie==1){
 Lcd_cmd(_LCD_CLEAR);
  Lcd_out(2,1,"Pluie !!");
  pluie=0;
  delay_ms(2000);
  Lcd_cmd(_LCD_CLEAR);
  Lcd_out(2,1,"Smart Garden");
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
  //intrp_ouv=1;
 }
 else if(realvalue<=29)
   {
   PORTD.RD5=0;
   INTCON.T0IE=1;
       TMR0 = 0;
          OPTION_REG=0b00000101; //prediviseur
          NB= 183;  // 5min -> NB=36600 NB=duree/(256*0.5*prediviseur)
   PORTD.RD6=1;
  Lcd_cmd(_LCD_CLEAR);
  Lcd_out(2,1,"Panne");
  }
  if(realvalue<=29 && realvalue_aftersecond>29)
  {nb_panne=EEPROM_Read(0x02)+1;
   EEPROM_Write(0x02,nb_panne);
  delay_ms(1000);
   }

   if(affich_panne==1){
    Lcd_cmd(_LCD_CLEAR);
    InttoStr(nb_panne,txt);
  Lcd_out(2,1,txt);
   delay_ms(1000);
   affich_panne=0;
   }
 }
}

void interrupt() {
if(INTCON.T0IF==1){
   INTCON.T0IF=0;
   NB--;
   if(NB==0){
     PORTD.RD6=0;
     INTCON.T0IE=0; //desactiver timer
   }
}

  if(INTCON.INTF==1){//Pluie
  if(PORTB.RB0==1){
  PORTD.RD5 = 0;
  //PORTD.RD6 = 0;
  pluie=1;
  }
  INTCON.INTF=0;   //Fin Pluie
  }else if(INTCON.RBIF==1){
  if(PORTB.RB4==1)
  {
    PORTD.RD5=1; //Arrosage
    intrp_ouv=1;
  }
  if(PORTB.RB4==0)
  {
    PORTD.RD5=0; //Arrosage
    //PORTD.RD6=0; //Buzzer
    intrp_ferm=1;
  }
  if(PORTB.RB5==1){
   affich_panne=1;
  }
  INTCON.RBIF=0;
  }
}   */
// Lcd pinout settings
sbit LCD_RS at RC2_bit;
sbit LCD_EN at RC3_bit;
sbit LCD_D4 at RC4_bit;
sbit LCD_D5 at RC5_bit;
sbit LCD_D6 at RC6_bit;
sbit LCD_D7 at RC7_bit;



// Pin direction
sbit LCD_RS_Direction at TRISC2_bit;
sbit LCD_EN_Direction at TRISC3_bit;
sbit LCD_D4_Direction at TRISC4_bit;
sbit LCD_D5_Direction at TRISC5_bit;
sbit LCD_D6_Direction at TRISC6_bit;
sbit LCD_D7_Direction at TRISC7_bit;
//Variables
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
 #define ADDRESS 0
void main()
{
     //Config
    TRISB=255;
    TRISA=255;
    TRISD=0;
    INTCON.GIE = 1;  //(Activer les interruptions)
    INTCON.RBIE = 1; //(Activer les interruptions RB4-->RB7)
    //INTCON.INTE= 1; //(Activer les interruption RB0)
    OPTION_REG.INTEDG= 1 ;  //Front Montant RB0
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
      Lcd_Cmd(_LCD_CURSOR_OFF);   // Clear display
     // Afficher "smart garden!" on Lcd starting from row 1, column 3:
     Lcd_Out(1, 1, "Smart Garden!!");
              delay_ms(500);
     Lcd_Cmd(_LCD_CURSOR_OFF);
     while (1)
      {          Lcd_Cmd(_LCD_CURSOR_OFF);
            adcValue = ADC_Read(0);//1000100010101010
            realvalue=adcValue*0.489;

            if(intrp_ouv==1 )
            {
                            Lcd_Cmd(_LCD_CLEAR);
                            Lcd_out(1,1,"Arrosage Gazon");
                            intrp_ouv=0;
                            delay_ms(500);
            }
            if(intrp_ferm==1  )
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
                      //  pluie=0;
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
               PORTD.RD5=1;  //Arrosage
               //PORTD.RD6=0;    //Buzzer
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
                   PORTD.RD5=0;      //Arrosage
                   //PORTD.RD6=0;
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
              PORTD.RD5=0; //Arrosage
                  //PORTD.RD6=1;
             INTCON.T0IE=1;   //ACTIVATION TIMER
      TMR0 = 0;
      OPTION_REG=0b00000101;
      NB= 183; // 5min -> NB=36600 NB=duree/(256*0.5*prediviseur(64))

              Lcd_cmd(_LCD_CLEAR);

              if (test_panne == 1)  {
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
                EEPROM_Write(ADDRESS, nb_panne);
                variable = EEPROM_Read(ADDRESS);
                Lcd_out(1,1,"Nombre de panne:");
                InttoStr(variable,string_variable);
                Lcd_out(2,1,string_variable);
                consulter=0;
                delay_ms(500);
              }
}
   }


    void interrupt()
{    if(INTCON.T0IF==1){
   INTCON.T0IF=0;
   NB--;

   if(NB==0){
     PORTD.RD6=0;
     INTCON.T0IE=0; //desactiver timer
   }
}
     if(INTCON.INTF==1)
     {//Pluie
             if(PORTB.RB0==1)
             {
              PORTD.RD5 = 0;
              //PORTD.RD6 = 0;
              pluie=1;
              }
                INTCON.INTF=0;   //Fin Pluie

     }else if(INTCON.RBIF==1)
     {
           if(PORTB.RB4==1)
           {
            PORTD.RD5=1; //Arrosage
            //PORTD.RD6=0; //Buzzer
            intrp_ouv=1;
            }
            if(PORTB.RB4==0)
            {
             PORTD.RD5=0; //Arrosage
             //PORTD.RD6=0; //Buzzer
             intrp_ferm=1;
             }
             if(PORTB.RB5==1)
             {
                consulter=1; //consulter le nombre de panne
             }

             INTCON.RBIF=0;

    }
       }
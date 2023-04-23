
/*
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
             while(PORTB.RB0==1)
             {
              PORTD.RD5 = 0;
              //PORTD.RD6 = 0;
             // pluie=1;
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

 #define ADDRESS 0


void main()
{
     //Config
    TRISB=255;
    TRISA=255;
    TRISD=0;
    //PORTD=0;
    INTCON.GIE = 1;  //(Activer les interruptions)
    INTCON.RBIE = 1; //(Activer les interruptions RB4-->RB7)
    INTCON.INTE= 1; //(Activer les interruption RB0)
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
     Lcd_Cmd(_LCD_CLEAR);    // Clear display
     // Afficher "smart garden!" on Lcd starting from row 1, column 3:
     Lcd_Out(1, 1, "Smart Garden!");
     Lcd_Cmd(_LCD_CURSOR_OFF);


     while (1)
      {
        adcValue = ADC_Read(0);
        realvalue=adcValue/(10.2);


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
        /*if(pluie==1)
        {
                    Lcd_cmd(_LCD_CLEAR);
                    Lcd_out(1,1,"Pluie !!");
                    pluie=0;
                    delay_ms(500);
                    Lcd_cmd(_LCD_CLEAR);
                    Lcd_out(1,1,"Smart Garden");
        }

         if(realvalue==30)
         {
                 test_arrosage=1;
                 test_panne = 1;
          }
          if(test_arrosage==1)
          {
           PORTD.RD5=1;  //Arrosage
           //PORTD.RD6=0;    //Buzzer
           Lcd_cmd(_LCD_CLEAR);
           Lcd_out(1,1,"Arrosage Gazon");
           test_panne = 1;
           test_arrosage=0;
           delay_ms(500);
           }
         if(realvalue>=50){
               test_arrosage =0;
               PORTD.RD5=0;      //Arrosage
               //PORTD.RD6=0;
               Lcd_cmd(_LCD_CLEAR);
                Lcd_out(1,1,"Fin Arrosage");
                delay_ms(1000);
                Lcd_cmd(_LCD_CLEAR);
                Lcd_out(1,1,"Smart Garden");
                test_panne = 1;
                delay_ms(1000);
         }
         if(realvalue<=29)
         {
          test_arrosage =0;
          PORTD.RD5=0; //Arrosage
          INTCON.T0IE=1; //Activer timer
          TMR0 = 0;
          OPTION_REG=0b00000111; //prediviseur
          NB= 229;  // 5min -> NB=36600 NB=duree/(256*0.5*prediviseur)
          PORTD.RD6=1;
          Lcd_cmd(_LCD_CLEAR);
          Lcd_out(2,1,"Panne");
          if (test_panne == 1)  {
             nb_panne++;
          test_panne = 0;
           }
           delay_ms(500);
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
   */
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
int test_arrosage=0;
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
    INTCON.INTE= 1; //(Activer les interruption RB0)
    OPTION_REG.INTEDG= 1 ;  //Front Montant RB0
    intrp_ouv=0;
    pluie=0;
    nb_panne=0;
    consulter=0;
    intrp_ferm=0;
    adcValue=0;
    variable =0;
    test_panne=0;
    PORTD=0;

        //PORTD=0;
     Lcd_Init();
      ADC_Init();
     Lcd_Cmd(_LCD_CLEAR);    // Clear display
     // Afficher "smart garden!" on Lcd starting from row 1, column 1:
     Lcd_Out(1, 1, "Smart Garden!!!");
     Lcd_Cmd(_LCD_CURSOR_OFF);


     while (1)
      {
        adcValue = ADC_Read(0);
        realvalue=adcValue/(10.2);


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
          if(PORTB.RB0==0){
           pluie=0;                //Reset Pluie
          }
         if(realvalue>=30 && realvalue<31 && pluie==0)
         {
                 test_arrosage=1;                  //Start Arrosage
                 test_panne = 1;
          }

          if(realvalue>=30 && realvalue<50 && test_arrosage==1 && pluie==0)
          {
           PORTD.RD5=1;  //Arrosage
           Lcd_cmd(_LCD_CLEAR);
           Lcd_out(1,1,"Arrosage Gazon");              //Update 30 -> 50
           test_panne = 1;
           delay_ms(500);
           }
         if(realvalue>=50){
               test_arrosage=0;
               PORTD.RD5=0;      //Arrosage
               pluie=0;
               Lcd_cmd(_LCD_CLEAR);
                Lcd_out(1,1,"Fin Arrosage");
                delay_ms(500);                            //End >50
                Lcd_cmd(_LCD_CLEAR);
                Lcd_out(1,1,"Smart Garden");
                test_panne = 1;
                delay_ms(200);
         }
         if(realvalue<=29)
         {
          test_arrosage =0;
          PORTD.RD5=0; //Arrosage
          INTCON.T0IE=1; //Activer timer
  TMR0 = 0;
  OPTION_REG=0b00000101; //prediviseur
  OPTION_REG.INTEDG= 1 ;
  NB= 183; //nb=duree/(256*1*prediviseur)  5min -> 300s 5min->nb=36600
  PORTD.RD6=1;  //Buzzer
          Lcd_cmd(_LCD_CLEAR);
          Lcd_out(2,1,"Panne");
          if (test_panne == 1)  {
             nb_panne++;
          test_panne = 0;
           }
           delay_ms(500);
          }
          if (consulter == 1)
          {
            Lcd_cmd(_LCD_CLEAR);

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
     INTCON.T0IE=0;  //Desactiver Timer
   }
}
     if(INTCON.INTF==1)
     {//Pluie
             if(PORTB.RB0==1)
             {
              PORTD.RD5 = 0;
              pluie=1;
              }
                INTCON.INTF=0;   //Fin Pluie

     }else if(INTCON.RBIF==1)
     {
           if(PORTB.RB4==1)
           {
            PORTD.RD5=1; //Arrosage
            intrp_ouv=1;
            }
            if(PORTB.RB4==0)
            {
             PORTD.RD5=0; //Arrosage
             intrp_ferm=1;
             }
             if(PORTB.RB5==1)
             {
                consulter=1; //consulter le nombre de panne
                EEPROM_Write(ADDRESS, nb_panne);
            variable = EEPROM_Read(ADDRESS);
             }

             INTCON.RBIF=0;

    }
}
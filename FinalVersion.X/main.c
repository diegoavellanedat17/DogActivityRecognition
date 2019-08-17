
#include "mcc_generated_files/mcc.h"
#include "I2C.h"
#include <stdio.h>
#include <stdlib.h>
#include <pic18f45k22.h>
#define _XTAL_FREQ 1000000
/*
                         Main application
 */

void EepromWrite(char SlaveAdd, char AddHigh, char AddLow,char EeData ){
    SSP1CON2bits.SEN=1;
    while(SSP1CON2bits.SEN);
    PIR1bits.SSP1IF=0;
    
    SSP1BUF=SlaveAdd;
    while(!PIR1bits.SSP1IF);
    PIR1bits.SSP1IF=0;
    
    if(SSP1CON2bits.ACKSTAT){
        SSP1CON2bits.PEN=1;
        while(SSP1CON2bits.PEN);
        return;
    }
    
    SSP1BUF=AddHigh;
    while(!PIR1bits.SSP1IF);
    PIR1bits.SSP1IF=0;
        if(SSP1CON2bits.ACKSTAT){
        SSP1CON2bits.PEN=1;
        while(SSP1CON2bits.PEN);
        return;
    }
    
    SSP1BUF=AddLow;
    while(!PIR1bits.SSP1IF);
    PIR1bits.SSP1IF=0;
    if(SSP1CON2bits.ACKSTAT){
    SSP1CON2bits.PEN=1;
    while(SSP1CON2bits.PEN);
    return;
    }
     SSP1BUF=EeData;
    while(!PIR1bits.SSP1IF);
    PIR1bits.SSP1IF=0;
    
    SSP1CON2bits.PEN=1;
    while(SSP1CON2bits.PEN);
   
}

void escribe_eeprom3(uint16_t direccion, unsigned char dato) {
    i2c_inicia_com(); //inicia la comunicación serial i2C PIC

    i2c_envia_dato(0xa4); //envía la dirección del esclavo con el que el maestro se
    //se quiere comunicar, en este cado de la EEPROM de quien su
    //dirección es de 7 bits (1010000) junto con el bit 0
    //que es el que le indica al esclavo que el maestro quiere
    //enviar o escribir un dato en la EEPROM,
    //por lo que se envia 10100000 que en hexadecimal es 0xa0

    //lo que sigue es enviar la dirección del registro de la memoria EEPROM donde se
    //escribirá el dato enviado por el maestro PIC16F1937, como estas direcciones en
    //la EEPROM 24C32 son de 2 bytes, se envía primero la parte alta de esta dirección
    //y luego la parte baja de esta dirección
    i2c_envia_dato(direccion >> 8); //envia parte alta de la direccion del registro
    //de la EEPROM donde se guardará el dato
    i2c_envia_dato(direccion); //envia parte baja de la direccion del registro
    //de la EEPROM donde se guardará el dato

    //Lo que sigue es enviar el dato a la dirección del registro de la memoria EEPROM
    //donde se guardará el dato.
    i2c_envia_dato(dato); //envia o escribe el dato en la dirección del registro
    //elegido de la memoria EEPROM

    //una vez que el esclavo recibe el dato se terminará la comunicación I2C PIC
    i2c_detener(); //finaliza la comunicación I2C PIC
}
void escribe_eeprom2(uint16_t direccion, unsigned char dato) {
    i2c_inicia_com(); //inicia la comunicación serial i2C PIC

    i2c_envia_dato(0xa2); //envía la dirección del esclavo con el que el maestro se
    //se quiere comunicar, en este cado de la EEPROM de quien su
    //dirección es de 7 bits (1010000) junto con el bit 0
    //que es el que le indica al esclavo que el maestro quiere
    //enviar o escribir un dato en la EEPROM,
    //por lo que se envia 10100000 que en hexadecimal es 0xa0

    //lo que sigue es enviar la dirección del registro de la memoria EEPROM donde se
    //escribirá el dato enviado por el maestro PIC16F1937, como estas direcciones en
    //la EEPROM 24C32 son de 2 bytes, se envía primero la parte alta de esta dirección
    //y luego la parte baja de esta dirección
    i2c_envia_dato(direccion >> 8); //envia parte alta de la direccion del registro
    //de la EEPROM donde se guardará el dato
    i2c_envia_dato(direccion); //envia parte baja de la direccion del registro
    //de la EEPROM donde se guardará el dato

    //Lo que sigue es enviar el dato a la dirección del registro de la memoria EEPROM
    //donde se guardará el dato.
    i2c_envia_dato(dato); //envia o escribe el dato en la dirección del registro
    //elegido de la memoria EEPROM

    //una vez que el esclavo recibe el dato se terminará la comunicación I2C PIC
    i2c_detener(); //finaliza la comunicación I2C PIC
}
void escribe_eeprom1(uint16_t direccion, unsigned char dato) {
    i2c_inicia_com(); //inicia la comunicación serial i2C PIC

    i2c_envia_dato(0xa0); //envía la dirección del esclavo con el que el maestro se
    //se quiere comunicar, en este cado de la EEPROM de quien su
    //dirección es de 7 bits (1010000) junto con el bit 0
    //que es el que le indica al esclavo que el maestro quiere
    //enviar o escribir un dato en la EEPROM,
    //por lo que se envia 10100000 que en hexadecimal es 0xa0

    //lo que sigue es enviar la dirección del registro de la memoria EEPROM donde se
    //escribirá el dato enviado por el maestro PIC16F1937, como estas direcciones en
    //la EEPROM 24C32 son de 2 bytes, se envía primero la parte alta de esta dirección
    //y luego la parte baja de esta dirección
    i2c_envia_dato(direccion >> 8); //envia parte alta de la direccion del registro
    //de la EEPROM donde se guardará el dato
    i2c_envia_dato(direccion); //envia parte baja de la direccion del registro
    //de la EEPROM donde se guardará el dato

    //Lo que sigue es enviar el dato a la dirección del registro de la memoria EEPROM
    //donde se guardará el dato.
    i2c_envia_dato(dato); //envia o escribe el dato en la dirección del registro
    //elegido de la memoria EEPROM

    //una vez que el esclavo recibe el dato se terminará la comunicación I2C PIC
    i2c_detener(); //finaliza la comunicación I2C PIC
}

unsigned char leer_eeprom1(uint16_t direccion) {
    unsigned char dato; //variable donde se guardará el dato leído desde la EEPROM
    i2c_inicia_com(); //inicia la comunicación serial i2C PIC
    i2c_envia_dato(0xa0); //envía la dirección del esclavo con el que el maestro se
 
    i2c_envia_dato(direccion >> 8); 
    i2c_envia_dato(direccion); 
    i2c_reinicia_com(); 
    i2c_envia_dato(0xa1); 
    dato = i2c_recibe_dato(); //lectura del dato de la ubicación de la memoria elegida
    //una vez que el maestro lee o recibe el dato se terminará la comunicación I2C PIC
    i2c_detener(); //finaliza la comunicación I2C PIC
    return dato; //la función devolverá el dato leído desde la EEPROM y guardado en
    //la variable dato
}
unsigned char leer_eeprom2(uint16_t direccion) {
    unsigned char dato; //variable donde se guardará el dato leído desde la EEPROM
    i2c_inicia_com(); //inicia la comunicación serial i2C PIC
    i2c_envia_dato(0xa2); //envía la dirección del esclavo con el que el maestro se
 
    i2c_envia_dato(direccion >> 8); 
    i2c_envia_dato(direccion); 
    i2c_reinicia_com(); 
    i2c_envia_dato(0xa3); 
    dato = i2c_recibe_dato(); //lectura del dato de la ubicación de la memoria elegida
    //una vez que el maestro lee o recibe el dato se terminará la comunicación I2C PIC
    i2c_detener(); //finaliza la comunicación I2C PIC
    return dato; //la función devolverá el dato leído desde la EEPROM y guardado en
    //la variable dato
}
unsigned char leer_eeprom3(uint16_t direccion) {
    unsigned char dato; //variable donde se guardará el dato leído desde la EEPROM
    i2c_inicia_com(); //inicia la comunicación serial i2C PIC
    i2c_envia_dato(0xa4); //envía la dirección del esclavo con el que el maestro se
 
    i2c_envia_dato(direccion >> 8); 
    i2c_envia_dato(direccion); 
    i2c_reinicia_com(); 
    i2c_envia_dato(0xa5); 
    dato = i2c_recibe_dato(); //lectura del dato de la ubicación de la memoria elegida
    //una vez que el maestro lee o recibe el dato se terminará la comunicación I2C PIC
    i2c_detener(); //finaliza la comunicación I2C PIC
    return dato; //la función devolverá el dato leído desde la EEPROM y guardado en
    //la variable dato
}
void ADC_init(){
    ANSELA=0b00000011;
    TRISA=0b00000011;
    ADCON1bits.PVCFG=0;
    ADCON1bits.NVCFG=0;
    ADCON2bits.ADCS=0b111;//Frecuencia conversion
    ADCON2bits.ADFM=0; //Justificado a la derecha
    ADCON0bits.ADON=1;
     __delay_ms(100);
    
}
unsigned int ADC_Read(unsigned char canal){
ADCON0bits.CHS &= 0x000;
ADCON0bits.CHS |=canal;
__delay_ms(2);
 ADCON0bits.GO_nDONE=1;//lanza la converscion 
 while(ADCON0bits.GO_nDONE);//Esperamos la conversion
 //return ((ADRESH<<8)+ADRESL);
  //return (ADRESL);
 return (ADRESH);
}

void Timer0Start()
{
    T0CONbits.TMR0ON=1;
    T0CONbits.T08BIT= 0;//8bits
    T0CONbits.PSA=0;
    T0CONbits.T0PS=0b111;
    T0CONbits.T0CS=0;// Usar el reloj interno
    
}

void Timer0Stop()
{
       T0CONbits.TMR0ON=0;
 
}

void setComparadores(){
  TRISBbits.RB0=0;// colocar B0 como salida
    TRISAbits.RA4=0;
    TRISAbits.RA5=0;
    TRISAbits.RA0=1;
    TRISAbits.RA1=1;
    TRISAbits.RA2=1;
    TRISAbits.RA3=1;
    //COMPARADOR1
    CM1CON0bits.C1ON=1;//Enable el comparador 1 
    CM1CON0bits.C1OUT=0; 
    CM1CON0bits.C1OE=1;
    CM1CON0bits.C1SP=0;
    CM1CON0bits.C1R=0;
    CM1CON0bits.C1CH=0x00;
    //COMPARADOR2
    CM2CON0bits.C2ON=1;//Enable el comparador 1 
    CM2CON0bits.C2OUT=0; 
    CM2CON0bits.C2OE=1;
    CM2CON0bits.C2SP=0;
    CM2CON0bits.C2R=0;
    CM2CON0bits.C2CH=0x01;
    
    CM2CON1bits.C1RSEL=0;
    CM2CON1bits.C1SYNC=0;
    CM2CON1bits.C2RSEL=0;
    CM2CON1bits.C2SYNC=0;   

    
}


void main(void)
{
    //Comparadores inicializados
    setComparadores();
    // Initialize the device
    SYSTEM_Initialize();
    //BLUETOOTH ENCENDIDO
    TRISDbits.RD3=0;
    LATDbits.LATD3=1; 
    //LED AZUL
    TRISDbits.RD4=0;
    //LED ROJO
    TRISDbits.RD5=0;
    //MemoriasEEPROM ENCENDIDAS
    TRISBbits.RB3=0;
    LATBbits.LATB3=0;
    TRISBbits.RB4=0;
    LATBbits.LATB4=0;
    TRISBbits.RB5=0;
    LATBbits.LATB5=1; 
    // Definiendo los pulsadores de la entrada
    TRISBbits.RB0=1;
    TRISBbits.RB1=1;
    ANSELBbits.ANSB0=0;
    ANSELBbits.ANSB1=0;
      //TRISBbits.RB2=1;
        //Selector de resolucion 
    TRISCbits.RC2=0;  
    LATCbits.LATC2=0; 
    //ANSELB=0b00000100;
    uint8_t adc1,adc2,adc3;
    int map1,map2,map3,cuentaL,cuentaH;
    int cuentay=0;
    int cuentaz=0;
    i2c_iniciar(); 
    ADC_init();
    cuentaL=0;
    cuentaH=0;
    
    unsigned char rec1,rec2,rec3;
         
          // Ciclo de lectura Con S2 Presionado
   if(PORTBbits.RB1==1){
         for(uint16_t cuentax=0; cuentax <96000; cuentax++){
         cuentax=cuentax*3;
         cuentay=cuentax+1;
         cuentaz=cuentax+2;
         
        if(cuentax<=31998){
        rec1=leer_eeprom1(cuentax);
        __delay_ms(5);
        rec2=leer_eeprom1(cuentay);
        __delay_ms(5);
        rec3=leer_eeprom1(cuentaz);
        }
         else if(cuentax>31998 && cuentax>=63996){
        rec1=leer_eeprom2(cuentax);
        __delay_ms(5);
        rec2=leer_eeprom2(cuentay);
        __delay_ms(5);
        rec3=leer_eeprom2(cuentaz);
        }
         else{
        rec1=leer_eeprom3(cuentax);
        __delay_ms(5);
        rec2=leer_eeprom3(cuentay);
        __delay_ms(5);
        rec3=leer_eeprom3(cuentaz);
                 
         }

         
        
        printf("%d ",rec1);
        printf("%d ",rec2);
        printf("%d\n",rec3);
       
        cuentax=cuentax/3;
         }
// Acaba la recepcion de datos entra en un ciclo infinito que debe reiniciar el dispositivo 
while(1){
            
           LATDbits.LATD4 = 1;  
        }
         
 
   }
    
                 else{
        printf("Todo va Bien 1 \n");
        __delay_ms(100);
    }
       
    
    
    if(PORTBbits.RB0==1){
        //Desactivar el BLUETOOTH
        LATDbits.LATD3=0; 
      // Ciclo de escriura con S3 Presionado      
         for(int cuentax=0; cuentax <96000; cuentax++){
             
         cuentax=cuentax*3;
         cuentay=cuentax+1;
         cuentaz=cuentax+2;
         
         adc1=ADC_Read(0);
         adc2=ADC_Read(1);
         adc3=ADC_Read(8);
       
        if(adc1<500 && cuentaL==0){
        printf("Inicio Timmer \r\n");
        Timer0Start();
        __delay_ms(1);  
       } 
       if(adc1>500 && cuentaH>100){
       
       LATCbits.LATC2=1; 
        Timer0Stop();
        PIE2bits.C1IE=1;
        PIE2bits.C2IE=1;
        INTCONbits.PEIE_GIEL=1;
        SLEEP();     
             
         } 
        
        if(cuentax<=31998){
        rec1=escribe_eeprom1(cuentax);
        __delay_ms(5);
        rec2=escribe_eeprom1(cuentay);
        __delay_ms(5);
        rec3=escribe_eeprom1(cuentaz);
        __delay_ms(5);
        }
         else if(cuentax>31998 && cuentax>=63996){
            
        rec1=escribe_eeprom2(cuentax);
        __delay_ms(5);
        rec2=escribe_eeprom2(cuentay);
        __delay_ms(5);
        rec3=escribe_eeprom2(cuentaz);
        __delay_ms(5);
        }
         else{
        rec1=escribe_eeprom3(cuentax);
        __delay_ms(5);
        rec2=escribe_eeprom3(cuentay);
        __delay_ms(5);
        rec3=escribe_eeprom3(cuentaz);
         __delay_ms(5);   
         }
 
    __delay_ms(10);
 
         }
while(1){
            
           LATDbits.LATD4 = 1;  
        }     
    }
    
    else{
        printf("Todo va Bien 2 \n");
        __delay_ms(100);
    }

}
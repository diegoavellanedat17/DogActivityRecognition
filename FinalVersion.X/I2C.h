/*
 *Funcion que se encarga de iniciar el Bus i2C
 */
void i2c_iniciar(){
    SSP1CON1bits.SSPEN=1;
    SSP1STAT=0b10000000; // velocidad standar, bus I2C
    SSP1CON1=0b00101000;  // I2C PIC habilitado en modo maestro velocidad=Fosc/(4*SSPADD+1)
    SSP1CON2=0b00000000; // comunicaci�n I2C no iniciada
    SSP1ADD=39;           //para una velocidad de 100Kbps con un oscilador de 20Mhz
}

////////////////////////////////////////////////////////////
// Funci�n de espera: mientras se est� iniciada una comunicaci�n,
// est� habilitado una recepci�n, est� habilitado una parada
// est� habilitado un reinicio de la comunicaci�n, est� iniciada
// una comunicaci�n o se este transmitiendo, el IC2 PIC se esperar�
// antes de realizar alg�n trabajo
 
void i2c_espera(){
    while((SSP1CON2 & 0b00011111) || (SSP1STAT & 0b00000100));
}

/////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
// Funci�n de inicio de la comunicaci�n I2C PIC

void i2c_inicia_com() {
    i2c_espera();        //espera que se cumplan las condiciones adecuadas
    SSP1CON2bits.SEN = 1; //inicia la comunicaci�n i2c
    while(SSP1CON2bits.SEN);
}

/////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
// Funci�n de reinicio de la comunicaci�n I2C PIC

void i2c_reinicia_com(){
    i2c_espera();         //espera que se cumplan las condiciones adecuadas
    SSP1CON2bits.RSEN = 1; //reinicia la comunicaci�n i2c
    while(SSP1CON2bits.RSEN); 
}

/////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
// Funci�n de parada de la comunicaci�n I2C PIC

void i2c_detener() {
    i2c_espera();        //espera que se cumplan las condiciones adecuadas
    SSP1CON2bits.PEN = 1; //detener la comunicaci�n i2c
    while(SSP1CON2bits.PEN); 
}

//////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
//Funci�n de transmisi�n de datos del maestro al esclavo
//esta funci�n devolver� un 0 si el esclavo a recibido 
//el dato

unsigned char i2c_envia_dato(unsigned char dato) {
    i2c_espera();   //espera que se cumplan las condiciones adecuadas
    SSP1BUF = dato;  //cargar en el regi1stro SSPBUF el dato a enviar
    return  SSP1CON2bits.ACKSTAT;//devuelve un 0 si la transmisi�n es correcta
}

//////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
//Funci�n de recepci�n de datos enviados por el esclavo al maestro
//esta funci�n es para leer los datos que est�n en el esclavo

unsigned char i2c_recibe_dato(){

    unsigned char datoleido; //variable para guardar el dato que se reciba o lea
                             //del esclavo

    i2c_espera();         //espera que se cumplan las condiciones adecuadas
    SSP1CON2bits.RCEN = 1; //reinicia la comunicaci�n i2c, ya que la comunicaci�n
                          //se ha tenido que iniciar antes, para enviar la
                          //direcci�n del esclavo y del registro a leer
    
    i2c_espera();         //espera que se cumplan las condiciones adecuadas
    datoleido = SSP1BUF;   //el dato recibido en el registro SSPBUF
                          //se guarda en la variable datoleido

    i2c_espera();         //espera que se cumplan las condiciones adecuadas

    SSP1CON2bits.ACKDT = 1;  //el maestro lo pone a 1 despu�s de leer o recibir el dato, 
                            //luego el maestro habilitar� ACKAEN y enviar� al esclavo
                            //el ACKDT para indicarle al esclavo que ya no se leer�n
                            //mas datos

    SSP1CON2bits.ACKEN = 1;//inicia secuencia final de reconocimiento de SDA y SCL por 
                          //parte del maestro para enviarle al esclavo el valor de ACKDT
                          //en este caso le enviar� un 1 para decirle que ya no se 
                          //recibir�n mas datos 
    return datoleido;
}
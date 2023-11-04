#include <RH_ASK.h> //INCLUSÃO DE BIBLIOTECA
#include <SPI.h> //INCLUSÃO DE BIBLIOTECA

RH_ASK driver; //CRIA O DRIVER PARA COMUNICAÇÃO

const int pinoMotor = 12; //PINO DIGITAL UTILIZADO PELO MOTOR
String str = ""; //VARIÁVEL DO TIPO STRING
int statusMotor = 0; //VARIÁVEL DO TIPO INT (CONTROLA O ESTADO ATUAL DO MOTOR)

void setup(){
    driver.init(); //INICIALIZA A COMUNICAÇÃO RF DO DRIVER
    Serial.begin(9600);
    pinMode(pinoMotor, OUTPUT); //DEFINE O PINO COMO SAÍDA
    digitalWrite(pinoMotor, LOW); //MOTOR INICIA DESLIGADO
}
void loop(){
    uint8_t buf[RH_ASK_MAX_MESSAGE_LEN]; //LÊ A MENSAGEM RECEBIDA (PALAVRA: motor)
    uint8_t buflen = sizeof(buf); //CRIA O COMPRIMENTO DO BUFFER PARA O TAMANHO DE buf

    if(driver.recv(buf, &buflen)){ //SE O DRIVER RECEBEU buf(INTEIRO) E buflen (COMPRIMENTO DE DADOS), FAZ
     str = ""; //VARIÁVEL RECEBE VAZIO
     int i; //VARIÁVEL LOCAL DO TIPO INTEIRO
       
     for(int i = 0; i < buflen; i++){ //PARA i IGUAL A 0, ENQUANTO i MENOR QUE buflen, INCREMENTA i
      str += (char)buf[i]; //VARIÁVEL RECEBE OS CARACTERES E FORMA A PALAVRA
     }
     if((str.equals("motor")) && (statusMotor == 0)){ //SE str FOR IGUAL A "led" E statusLed FOR IGUAL A 0, FAZ
      statusMotor = 1; //VARIÁVEL RECEBE 1
        Serial.println("Vibração mais curta! 📳");
        digitalWrite(pinoMotor, HIGH); //LIGAR O MOTOR
        delay(2000);
        digitalWrite(pinoMotor,LOW); //DESLIGAR O MOTOR
     }else{ //SENÃO, FAZ
      if((str.equals("motor")) && (statusMotor == 1)){ //SE str FOR IGUAL A "led" E statusLed FOR IGUAL A 1, FAZ
          statusMotor = 0; //VARIÁVEL RECEBE 0
            Serial.println("Vibração mais longa! 📳");
            digitalWrite(pinoMotor, HIGH); //LIGAR O MOTOR
            delay(3000);
            digitalWrite(pinoMotor,LOW); //DESLIGAR O MOTOR
      }
     }
    }
}

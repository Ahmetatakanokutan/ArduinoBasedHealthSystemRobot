#include <DHT.h>

//#include <CircularBuffer.h>
#include <MAX30100.h>
#include <MAX30100_BeatDetector.h>
#include <MAX30100_Filters.h>
#include <MAX30100_PulseOximeter.h>
#include <MAX30100_Registers.h>
#include <MAX30100_SpO2Calculator.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#define NEMPIN 3
#define buton3 5
#define buton4 6
#define buton5 7
#define REPORTING_PERIOD_MS     1000
#define analogPin  A1
#define havaPin A3 
#define buton6 10
LiquidCrystal_I2C lcd(0x27, 16, 2);

PulseOximeter oxisensor; //oksijen sensörü tanımlama

DHT nemsensor(NEMPIN,DHT11); //dhtsensör class a tanımlama

 int line=542;    //pulse sensör nabız sınırı
 byte pulsesensorpin =0;   //pulse sensör read pini
 byte buton=2;
 byte buton2=4;
 int counter=0;           //sayac
 int psensorsayac;
 long milisayac;          //fonksiyon zamanaarlama yeri
 int mx3100_sensoroksijendeger ;
int analogVal;
int atessonuc;
int havakirliligi;

 

uint32_t tsLastReport = 0;
 
void onBeatDetected()
{
    Serial.println("Beat!");
    
} 
void metin(){
   lcd.home();
  lcd.leftToRight();
 //Serial.println(psensorsayac);
//lcd ayar yeri**********************************
  lcd.setCursor(0,0);
   lcd.print("hesaplamak icin ");
   lcd.setCursor(0,1);
   lcd.print("butona basin");
   delay(1300);
   lcd.clear();
   lcd.home();
   lcd.setCursor(0,0);
   lcd.print("nabiz icin");
   lcd.setCursor(0,1);
   lcd.print("1. buton");
   delay(1300);
    lcd.clear();
   lcd.home();
   lcd.setCursor(0,0);
   lcd.print("kandaki oksjen");
   lcd.setCursor(0,1);
   lcd.print("icin 2. buton");
   delay(1300);
   lcd.clear();
   lcd.home();
   lcd.setCursor(0,0);
   lcd.print("derideki nemi");
   lcd.setCursor(0,1);
   lcd.print("veya havadaki");
    delay(1300);
   lcd.clear();
   lcd.home();
   lcd.setCursor(0,0);
   lcd.print("nemi olcmek");
   lcd.setCursor(0,1);
   lcd.print("icin 3. buton");
   delay(1300);
   lcd.clear();
   lcd.home();
   lcd.setCursor(0,0);
   lcd.print("ates olcmek");
   lcd.setCursor(0,1);
   lcd.print("icin 4. buton");
   delay(1300);
   lcd.clear();
   lcd.home();
   lcd.setCursor(0,0);
   lcd.print("hava kalitesini");
   lcd.setCursor(0,1);
   lcd.print("icin 5. buton");
   delay(1300);
   lcd.clear();
   lcd.home();
   lcd.setCursor(0,0);
   lcd.print("ekg olcmek");
   lcd.setCursor(0,1);
   lcd.print("icin 6. buton");
   
}
void setup()
{
  pinMode(buton,INPUT);
   pinMode(buton2,INPUT);
   pinMode(buton3,INPUT);
   pinMode(buton4,INPUT);
   pinMode(buton5,INPUT);
   
  nemsensor.begin() ;      // NEMSENSÖR BAŞLATMA ALANI
lcd.begin();      // LCD yi çalıştır
  metin();        //SİSTEM GİRİŞ METNİ

 Serial.begin(9600);
                              //mx3100 ayar yeri
 //////////////////////////////////////////////////////////////////////////////////////////////
    Serial.print("Initializing pulse oximeter..");
 
    // Initialize the PulseOximeter instance
    // Failures are generally due to an improper I2C wiring, missing power supply
    // or wrong target chip
    if (!oxisensor.begin()) {
        Serial.println("FAILED");
        for(;;);
    } else {
        Serial.println("SUCCESS");
        
    }
     
  
  oxisensor.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
 
    // Register a callback for the beat detection
    oxisensor.setOnBeatDetectedCallback(onBeatDetected);

}
 
void loop()
{

//mx3100 ayar yeri//////////////////////////////////////////////////////
  
    
  oxisensor.update();
    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
        Serial.print("Heart rate:");
        Serial.print(oxisensor.getHeartRate());
        Serial.print("bpm / SpO2:");
        Serial.print(oxisensor.getSpO2());
        Serial.println("%");
        mx3100_sensoroksijendeger=oxisensor.getSpO2();
        tsLastReport = millis();
    } 
    if(digitalRead(buton2)==1){
    lcd.clear();
   //lcd.home();
   lcd.setCursor(0,0);
   lcd.print("kandaki oksjen:");
   lcd.setCursor(0,1);
   lcd.print(mx3100_sensoroksijendeger);
   lcd.setCursor(3,1);
    lcd.print("%");
    delay(5000);
    metin();
//    goto cda;
  }
  

//*************************************************
//pulse sensör ayar yeri***************************
if(digitalRead(buton)==1){
  psensorsayac=analogRead(pulsesensorpin);
  
  lcd.setCursor(0,0);
  lcd.println("10 saniye icinde");
  lcd.setCursor(0,1);
  lcd.println("islem baslayacak");
  delay(2000);
  lcd.setCursor(0,0);
  lcd.println("lutfen parmaginizi");
  lcd.setCursor(0,1);
  lcd.println("sensore koyun    ");
  //Serial.println(psensorsayac);
  
  delay(10000);
   lcd.clear();
  //lcd.home();
  lcd.println("hesaplaniyor ");
  
  milisayac=millis();
for(counter=0;millis() <(milisayac + 20000);){
  psensorsayac=analogRead(pulsesensorpin);
  Serial.println(psensorsayac);
if(analogRead(pulsesensorpin)>line){
  
counter++;
  
   
                          
                 
   }
  delay(20);

}
lcd.home();
lcd.setCursor(0,0);
lcd.println("dakikadaki nabiz         ");

lcd.setCursor(5,1);
lcd.println((counter*3) ); 
delay(10000);
    metin();


}
                        //DHT11 AYAR YERİ
//////////////////////////////////////////////////////////////////////////
if(digitalRead(buton3)==1){
  milisayac=millis();
for(;millis() <(milisayac + 10000);){
float nem= nemsensor.readHumidity();
lcd.clear();
lcd.setCursor(0,0);
lcd.print("nem orani:");
lcd.setCursor(10,0);
lcd.println(nem);
lcd.setCursor(12,0);
lcd.println("%  ");
Serial.println(nem);
delay(100);
}
metin();
}
                       //isi sensoru ayar yeri
////////////////////////////////////////////////////////////////////////////////

if(digitalRead(buton4)==1){
  lcd.clear();
  milisayac=millis();
for(;millis() <(milisayac + 10000);){
  analogVal = analogRead(analogPin); 
  
  atessonuc=(5200/analogVal);  // degeri dereceye donusturme
  lcd.setCursor(0,0);
lcd.println("hastanin atesi: ");
  lcd.setCursor(0,1);
  lcd.println(atessonuc); 
  Serial.println(atessonuc);
  lcd.setCursor(2,1);
  lcd.println("c                ");
 
  delay(1000);
}
  metin();
}
                   //mx-135 ayar yeri(hava sensörü)
//////////////////////////////////////////////////////////////////////////////////
if(digitalRead(buton5)==1){
  lcd.clear();
  milisayac=millis();
for(;millis() <(milisayac + 10000);){
  havakirliligi=analogRead(havaPin);
  lcd.setCursor(0,0);
  lcd.print("Hava kirliligi: "); 
  lcd.setCursor(0,1); 
  lcd.print(havakirliligi); 
  Serial.println(havakirliligi);
  lcd.setCursor(4,1); 
  lcd.print("ppm");
  delay(200);
}
metin();
}
//////////////////////////ekg ayar yeri///////////////////////////////////////////
if(digitalRead(buton6)==1){
  lcd.clear();
  lcd.print("olculuyor");

  for(int a=0;a<1000;a++){
  Serial.begin(9600);
if((digitalRead(9)==1)||(digitalRead(8)==1)){
Serial.println("NIL");
}
else{
Serial.println(analogRead(A3));
}

Serial.end();
delay(30);
  }
  lcd.clear();
  lcd.print("olcum bitti");
  delay(100);
metin();
}
}

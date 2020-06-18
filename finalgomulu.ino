
/* Digital Saat UYGULAMASI gösterge uygulaması;
 * 
 */
int control = 0;
int manuel =0;
int x=0;
int y=0;
int z=0;
int t=0;
int alarmAktiveDominasyon = 0;
const byte BUTON = 2;
const byte BUTON_geri = 0;
const byte BUTON_mod = 1;

byte saat_H=0;
byte saat_L=7;
byte dk_H=0;
byte dk_L=0;
byte sn_H;
byte sn_L;


//-----------
byte on_saat_H=0;
byte on_saat_L=7;
byte on_dk_H=0;
byte on_dk_L=0;

//----------
byte off_saat_H=0;
byte off_saat_L=7;
byte off_dk_H=0;
byte off_dk_L=1;

//-----------
byte a;
byte b;
byte c;
byte d;
int buzzerState = LOW ; 
byte alarm=0;

unsigned long myTime = 0;
unsigned long lastTime = 0;    // Last time the LED changed state
float interval = 60000; // interval between the blinks in
                               //milliseconds



void setup() {

  // put your setup code here, to run once:

 pinMode(13,OUTPUT);  // a segmenti çıkış
 pinMode(12,OUTPUT);  // b segmenti çıkış
 pinMode(11,OUTPUT);  // c segmenti çıkış
 pinMode(10,OUTPUT);  // d segmenti çıkış
 pinMode(9,OUTPUT);  // e segmenti çıkış
 pinMode(8,OUTPUT);  // f segmenti çıkış
 pinMode(7,OUTPUT);  // g segmenti çıkış
 pinMode(6,OUTPUT);  // Anod saat_H 
 pinMode(5,OUTPUT);  // Anod saat_L 
 pinMode(4,OUTPUT);  // Anod dk_H
 pinMode(3,OUTPUT);  // Anod dk_L
 
pinMode(BUTON, INPUT);   // BUTON pini giriş olarak atandı
pinMode(BUTON_mod, INPUT); // BUTON_mod pini saat/alarm baş/alarm bitiş için


 pinMode (A5,OUTPUT);  ///////// ÇALIŞTIRILACAL SİSTEM /ALARM   çıkış
 pinMode (A4,INPUT);  ///////// ALARM ON/OFF SEÇİMİ

 pinMode (A0,INPUT);  ////////// MANUEL OLARAK SİSTEM AÇMA/KAPAMA BUTONU
 pinMode (A1,OUTPUT);  /////////  NOKTA GÖSTERGESİ saatle - dakika arasındaki
 pinMode (A2,OUTPUT);  ////////// led alarm off ayarı göstergesi
 pinMode (A3,OUTPUT);  ////////// BUZZER


digitalWrite(A0, HIGH);  // ORTAK ANOT  OFF durumunda //yorum satırı idi
digitalWrite(A1, LOW);  // NOKTA  OFF durumunda
digitalWrite(A2, LOW);  // ORTAK ANOT  KIRMIZI ON durumunda
digitalWrite(A3, LOW);   // BUZZER kapalı
digitalWrite(A5, HIGH);

 
 Serial.begin (9600); ////////
   
}




void loop() {
//////////////////LOOP BAŞI
   
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if(control == 0){
        digitalWrite(6, HIGH); 
        digitalWrite(5, LOW);
        digitalWrite(4, LOW);
        digitalWrite(3, LOW);
        SevenSegment(saat_H);
        digitalWrite(A1,HIGH);
        delay(5);
      
        digitalWrite(6, LOW);
        digitalWrite(5, HIGH);
        digitalWrite(4, LOW);
        digitalWrite(3, LOW);
        SevenSegment(saat_L);
        digitalWrite(A1,LOW);
        delay(5);
      
        digitalWrite(6, LOW);
        digitalWrite(5, LOW);
        digitalWrite(4, HIGH);
        digitalWrite(3, LOW);
        digitalWrite(A1,HIGH);
        SevenSegment(dk_H);
        delay(5);
      
        digitalWrite(6, LOW);
        digitalWrite(5, LOW);
        digitalWrite(4, LOW);
        digitalWrite(3, HIGH);
        digitalWrite(A1,HIGH);
        SevenSegment(dk_L);
        delay(5);
    }
    else if(control == 1){
        digitalWrite(6, HIGH); 
        digitalWrite(5, LOW);
        digitalWrite(4, LOW);
        digitalWrite(3, LOW);
        digitalWrite(A1,HIGH);
        SevenSegment(on_saat_H);
        delay(5);
      
        digitalWrite(6, LOW);
        digitalWrite(5, HIGH);
        digitalWrite(4, LOW);
        digitalWrite(3, LOW);
        digitalWrite(A1,LOW);
        SevenSegment(on_saat_L);
        delay(5);
      
        digitalWrite(6, LOW);
        digitalWrite(5, LOW);
        digitalWrite(4, HIGH);
        digitalWrite(3, LOW);
        digitalWrite(A1,HIGH);
        SevenSegment(on_dk_H);
        delay(5);
      
        digitalWrite(6, LOW);
        digitalWrite(5, LOW);
        digitalWrite(4, LOW);
        digitalWrite(3, HIGH);
        digitalWrite(A1,HIGH);
        SevenSegment(on_dk_L);
        delay(5);
    }
    else if(control == 2){
        digitalWrite(6, HIGH); 
        digitalWrite(5, LOW);
        digitalWrite(4, LOW);
        digitalWrite(3, LOW);
        digitalWrite(A1,HIGH);
        SevenSegment(off_saat_H);
        delay(5);
      
        digitalWrite(6, LOW);
        digitalWrite(5, HIGH);
        digitalWrite(4, LOW);
        digitalWrite(3, LOW);
        digitalWrite(A1,LOW);
        SevenSegment(off_saat_L);
        delay(5);
      
        digitalWrite(6, LOW);
        digitalWrite(5, LOW);
        digitalWrite(4, HIGH);
        digitalWrite(3, LOW);
        digitalWrite(A1,HIGH);
        SevenSegment(off_dk_H);
        delay(5);
      
        digitalWrite(6, LOW);
        digitalWrite(5, LOW);
        digitalWrite(4, LOW);
        digitalWrite(3, HIGH);
        digitalWrite(A1,HIGH);
        SevenSegment(off_dk_L);
        delay(5);
    }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

// A5 RÖLE
// A0 RÖLE BUTONU
// Z DENETÇİ
// MANUEL 

  if(digitalRead(A0)==LOW){ // RÖLEYİ TETİKLEMEK İÇİN
    if(z == 0){
      while(digitalRead(A0)==LOW){digitalWrite(A5,LOW); alarmAktiveDominasyon = 1; z=1; if(digitalRead(A5)==LOW){digitalWrite(A2,LOW); alarm = 0;} }
    }
    else if(z == 1){
      while(digitalRead(A0)==LOW){digitalWrite(A5,HIGH); z=0; alarmAktiveDominasyon = 0; }
    }
  }

  
  if(digitalRead(A5) == LOW){ // RÖLENİN DOMİNANTLIĞINI SAĞLAMAK İÇİN
    manuel = 1;
  }
  else{
    manuel = 0;
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

if(manuel == 0){
    if(digitalRead(BUTON_mod)==LOW){ // MOD DEĞİŞTİRME BUTONU
        if(control == 0){
          while(digitalRead(BUTON_mod)==LOW){
            control = 1;
            digitalWrite(6, LOW);
            digitalWrite(5, HIGH);
            digitalWrite(4, HIGH);
            digitalWrite(3, HIGH);
            SevenSegment(0);
            delay(5);

            digitalWrite(6, HIGH);
            digitalWrite(5, LOW);
            digitalWrite(4, HIGH);
            digitalWrite(3, HIGH);
            digitalWrite(13,HIGH);
            digitalWrite(12,HIGH);
            digitalWrite(11,HIGH);
            digitalWrite(10,LOW);
            digitalWrite(9,HIGH);
            digitalWrite(8,HIGH);
            delay(5);

            digitalWrite(6, HIGH);
            digitalWrite(5, HIGH);
            digitalWrite(4, LOW);
            digitalWrite(3, HIGH);
            digitalWrite(13,HIGH);
            digitalWrite(12,HIGH);
            digitalWrite(11,HIGH);
            digitalWrite(10,LOW);
            digitalWrite(9,HIGH);
            digitalWrite(8,HIGH);
            delay(5);
            
            }
        }
        else if(control == 1){
          while(digitalRead(BUTON_mod)==LOW){
            control = 2;
            digitalWrite(6, HIGH);
            digitalWrite(5, HIGH);
            digitalWrite(4, HIGH);
            digitalWrite(3, HIGH);
            SevenSegment(0);
            delay(5);

            digitalWrite(6, HIGH);
            digitalWrite(5, LOW);
            digitalWrite(4, HIGH);
            digitalWrite(3, HIGH);
            digitalWrite(13,HIGH); 
            digitalWrite(12,LOW);
            digitalWrite(11,LOW);
            digitalWrite(10,LOW);
            digitalWrite(9,HIGH);  
            digitalWrite(8,HIGH);  
            digitalWrite(7,HIGH);   
            delay(5);

            digitalWrite(6, HIGH);
            digitalWrite(5, HIGH);
            digitalWrite(4, LOW);
            digitalWrite(3, HIGH);
            digitalWrite(13,HIGH); 
            digitalWrite(12,LOW);
            digitalWrite(11,LOW);
            digitalWrite(10,LOW);
            digitalWrite(9,HIGH);
            digitalWrite(8,HIGH);
            digitalWrite(7,HIGH);
            delay(5);
            }
        }
        else if(control == 2){
          while(digitalRead(BUTON_mod)==LOW){
            control = 0;
            if( x == 2 ){
            digitalWrite(6, LOW);
            digitalWrite(5, HIGH);
            digitalWrite(4, HIGH);
            digitalWrite(3, HIGH);
            SevenSegment(0);
            tone(A3,4000,1000);
            delay(1000);
          x = 0;
      }
            }
        }
      } // MOD DEĞİŞTİRME BUTONU
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
if(alarmAktiveDominasyon == 0){    
    if(digitalRead(A4)==LOW){ //////////////////// ALARM AKTİVE BUTONU
        if( alarm == 0){
          while(digitalRead(A4)==LOW){
            digitalWrite(A2,HIGH);
            alarm = 1;

            digitalWrite(6, LOW);
            digitalWrite(5, HIGH);
            digitalWrite(4, HIGH);
            digitalWrite(3, HIGH);
            SevenSegment(0);
            delay(5);

            digitalWrite(6, HIGH);
            digitalWrite(5, LOW);
            digitalWrite(4, HIGH);
            digitalWrite(3, HIGH);
            digitalWrite(13,HIGH);
            digitalWrite(12,HIGH);
            digitalWrite(11,HIGH);
            digitalWrite(10,LOW);
            digitalWrite(9,HIGH);
            digitalWrite(8,HIGH);
            delay(5);

            digitalWrite(6, HIGH);
            digitalWrite(5, HIGH);
            digitalWrite(4, LOW);
            digitalWrite(3, HIGH);
            digitalWrite(13,HIGH);
            digitalWrite(12,HIGH);
            digitalWrite(11,HIGH);
            digitalWrite(10,LOW);
            digitalWrite(9,HIGH);
            digitalWrite(8,HIGH);
            delay(5);
            
            
            }
        }
        else if(alarm == 1) {
          while(digitalRead(A4) == LOW){ 
            digitalWrite(A2,LOW);
            digitalWrite(A5,HIGH);
            alarm = 0;

            digitalWrite(6, LOW);
            digitalWrite(5, HIGH);
            digitalWrite(4, HIGH);
            digitalWrite(3, HIGH);
            SevenSegment(0);
            delay(5);

            digitalWrite(6, HIGH);
            digitalWrite(5, LOW);
            digitalWrite(4, HIGH);
            digitalWrite(3, HIGH);
            digitalWrite(13,HIGH); 
            digitalWrite(12,LOW);
            digitalWrite(11,LOW);
            digitalWrite(10,LOW);
            digitalWrite(9,HIGH);  
            digitalWrite(8,HIGH);  
            digitalWrite(7,HIGH);   
            delay(5);

            digitalWrite(6, HIGH);
            digitalWrite(5, HIGH);
            digitalWrite(4, LOW);
            digitalWrite(3, HIGH);
            digitalWrite(13,HIGH); 
            digitalWrite(12,LOW);
            digitalWrite(11,LOW);
            digitalWrite(10,LOW);
            digitalWrite(9,HIGH);
            digitalWrite(8,HIGH);
            digitalWrite(7,HIGH);
            delay(5);
            }
        }
      } ////////////// ALARM AKTİVE BUTONU
}
 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
if(manuel == 0 || alarm == 1){
     if( alarm==1){ // ALARM AKTİVE EDİLİNCE // ALARM BAŞLANGIÇ ANINDA MANUEL KESİLİP SONRA AÇILIRSA KAPANIS SAATİNDE RÖLE ATIYOR AMA GERİ KAPANMIYOR ONU HALLET

          
         if( y == 0){ //  60 saniyede dönülen looplarda buraya sürekli girmemesi için
          if(saat_H == on_saat_H && saat_L == on_saat_L && dk_H == on_dk_H && dk_L == on_dk_L){ // AÇILIS SAATİ SAYAN SAATE EŞİT OLUNCA // bir dakika içinde buraya sürekli girdiği için buzzer susmuyor olabilir.
             digitalWrite(A5,LOW);
             tone(A3,2000,5000);
             y = 1;
          }
         }
         if( t == 0){//  60 saniye dönülen looplarda buraya sürekli girmemesi için
          if(saat_H == off_saat_H && saat_L == off_saat_L && dk_H == off_dk_H && dk_L == off_dk_L){   // KAPANIS SAATİ SAYAN SAATE EŞİT OLUNCA // MUHTEMEL ÇÖZÜM BURDA 
              tone(A3,2000,5000); 
              if(digitalRead(A2)==HIGH){digitalWrite(A2,LOW);}
              digitalWrite(A5,HIGH);
              t = 1 ; // kapanışın manuel olmadıgını belirtiyor.
              alarm = 0 ;
            }
          }
        }
     else if(alarm==0 && t == 0){  // SİSTEME MANUEL OLARAK MOD BUTONUNDAN MÜDAHALE OLUNCA
        digitalWrite(A2,LOW);
        digitalWrite(A5,HIGH);
        noTone(A3);
        }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
    unsigned long currentTime = millis();
    if(currentTime - lastTime >= interval && control == 0){ ////////// SAAT AKIŞI ve ALARM AKTİF Mİ ALANI          ------------- 60 saniye interval yapınca alarmı aktif etme butonuna basınca da 60 saniye sonra okuyacak onu direk yapmak lazım
      

      lastTime = currentTime;
      
      dk_L++;
      if(dk_L == 10){dk_L = 0; dk_H++;}
      if(dk_H == 6){dk_H = 0; saat_L++;}
      if(saat_L == 10){saat_L = 0; saat_H++;}
      if(saat_H ==2 && saat_L ==4 ){saat_L = 0; saat_H = 0;}

    } ////////// SAAT AKIŞI ve ALARM AKTİF Mİ ALANI
 if(manuel == 0 ){   
    
    if(control==1){  //////////ALARM BAŞLANGIÇ
      if( x == 0 ){
          tone(A3,3000,500);
          x = 1;
      }
     if(digitalRead(BUTON) == LOW){ // DAKİKA ARTTIR
        t = 0;
        y = 0;
        on_dk_L ++;
        sn_H=0;
        sn_L=0;
        
        
        if (on_dk_L==10) {on_dk_L=0; on_dk_H ++;}
        if (on_dk_H==6) {on_dk_H=0; on_saat_L ++;}
        if (on_saat_L==10) {on_saat_L=0; on_saat_H ++;}
        
        
        if (on_saat_H==2) {
                         if (on_saat_L==4) {on_saat_L=0; on_saat_H=0;}
                       }
        
        
        while (digitalRead(BUTON)==LOW)      // HALA BASILI MI?????    
          {
        digitalWrite(6, LOW);
        digitalWrite(5, HIGH);
        digitalWrite(4, HIGH);
        digitalWrite(3, HIGH);
        SevenSegment(on_saat_H);
        delay(5);
        
        digitalWrite(6, HIGH);
        digitalWrite(5, LOW);
        digitalWrite(4, HIGH);
        digitalWrite(3, HIGH);
        SevenSegment(on_saat_L);
        delay(5);
      
        digitalWrite(6, HIGH);
        digitalWrite(5, HIGH);
        digitalWrite(4, LOW);
        digitalWrite(3, HIGH);
        SevenSegment(on_dk_H);
        delay(5);
      
        digitalWrite(6, HIGH);
        digitalWrite(5, HIGH);
        digitalWrite(4, HIGH);
        digitalWrite(3, LOW);
        SevenSegment(on_dk_L);
        delay(5);
                 }  
        } // DAKİKA ARTTIR
     
    if(digitalRead(BUTON_geri) == LOW){ // DAKİKA AZALT
        t = 0;
        y = 0;
        on_dk_L --;
        sn_H=0;
        sn_L=0;
        
        if (on_dk_L==255) {on_dk_L=9; on_dk_H --;   //Geri saydırmada byte 
        // değişkeninin 0'dan 255'e geçerken 9'a set edilir.
        
                        if (on_dk_H==255) {on_dk_H=5; on_saat_L --;}
        
                        }
        
        if (on_saat_L==255) {on_saat_L=9; on_saat_H --;
        
                          if (on_saat_H==255) {on_saat_H=2; on_saat_L=3; }
        
                         }
        
          while (digitalRead(BUTON_geri)==LOW)      // HALA BASILI MI?????    
            {
          digitalWrite(6, LOW);
          digitalWrite(5, HIGH);
          digitalWrite(4, HIGH);
          digitalWrite(3, HIGH);
          SevenSegment(on_saat_H);
          delay(5);
          
          digitalWrite(6, HIGH);
          digitalWrite(5, LOW);
          digitalWrite(4, HIGH);
          digitalWrite(3, HIGH);
          SevenSegment(on_saat_L);
          delay(5);
        
          digitalWrite(6, HIGH);
          digitalWrite(5, HIGH);
          digitalWrite(4, LOW);
          digitalWrite(3, HIGH);
          SevenSegment(on_dk_H);
          delay(5);
        
          digitalWrite(6, HIGH);
          digitalWrite(5, HIGH);
          digitalWrite(4, HIGH);
          digitalWrite(3, LOW);
          SevenSegment(on_dk_L);
          delay(5);
                   }  
      }      // DAKİKA AZALT
      
}  //ALARM BAŞLANGIÇ

    
    if(control==2){//ALARM BİTİŞ
      if( x == 1 ){
          tone(A3,3000,500);
          x = 2;
      }
     
     if(digitalRead(BUTON) == LOW){ // DAKİKA ARTTIR
        t = 0;
        y = 0;
        off_dk_L ++;
        sn_H=0;
        sn_L=0;
        
        
        if (off_dk_L==10) {off_dk_L=0; off_dk_H ++;}
        if (off_dk_H==6) {off_dk_H=0; off_saat_L ++;}
        if (off_saat_L==10) {off_saat_L=0; off_saat_H ++;}
        
        
        if (off_saat_H==2) {
                         if (off_saat_L==4) {off_saat_L=0; off_saat_H=0;}
                       }
        
         
        
      
        while (digitalRead(BUTON)==LOW)      // HALA BASILI MI?????    
          {
        digitalWrite(6, LOW);
        digitalWrite(5, HIGH);
        digitalWrite(4, HIGH);
        digitalWrite(3, HIGH);
        SevenSegment(off_saat_H);
        delay(5);
        
        digitalWrite(6, HIGH);
        digitalWrite(5, LOW);
        digitalWrite(4, HIGH);
        digitalWrite(3, HIGH);
        SevenSegment(off_saat_L);
        delay(5);
      
        digitalWrite(6, HIGH);
        digitalWrite(5, HIGH);
        digitalWrite(4, LOW);
        digitalWrite(3, HIGH);
        SevenSegment(off_dk_H);
        delay(5);
      
        digitalWrite(6, HIGH);
        digitalWrite(5, HIGH);
        digitalWrite(4, HIGH);
        digitalWrite(3, LOW);
        SevenSegment(off_dk_L);
        delay(5);
                 }  
          } // DAKİKA ARTTIR      
      if(digitalRead(BUTON_geri) == LOW){
        t = 0;
        y = 0;
        off_dk_L --;
        sn_H=0;
        sn_L=0;
        
        if (off_dk_L==255) {off_dk_L=9; off_dk_H --;   //Geri saydırmada byte 
        // değişkeninin 0'dan 255'e geçerken 9'a set edilir.
        
                        if (off_dk_H==255) {off_dk_H=5; off_saat_L --;}
        
                        }
        
        if (off_saat_L==255) {off_saat_L=9; off_saat_H --;
        
                          if (off_saat_H==255) {off_saat_H=2; off_saat_L=3; }
        
                         }
        
          while (digitalRead(BUTON_geri)==LOW)      // HALA BASILI MI?????    
            {
          digitalWrite(6, LOW);
          digitalWrite(5, HIGH);
          digitalWrite(4, HIGH);
          digitalWrite(3, HIGH);
          SevenSegment(off_saat_H);
          delay(5);
          
          digitalWrite(6, HIGH);
          digitalWrite(5, LOW);
          digitalWrite(4, HIGH);
          digitalWrite(3, HIGH);
          SevenSegment(off_saat_L);
          delay(5);
        
          digitalWrite(6, HIGH);
          digitalWrite(5, HIGH);
          digitalWrite(4, LOW);
          digitalWrite(3, HIGH);
          SevenSegment(off_dk_H);
          delay(5);
        
          digitalWrite(6, HIGH);
          digitalWrite(5, HIGH);
          digitalWrite(4, HIGH);
          digitalWrite(3, LOW);
          SevenSegment(off_dk_L);
          delay(5);
                   }  
      }
    
    }//ALARM BİTİŞ
 }



}/////////////////// LOOP SON






void SevenSegment(int rakam) 
   {
    switch(rakam)
    {
     case 0:
      digitalWrite(13, HIGH);
      digitalWrite(12, HIGH);
      digitalWrite(11, HIGH);
      digitalWrite(10, HIGH);
      digitalWrite(9, HIGH); 
      digitalWrite(8, HIGH);
      digitalWrite(7, LOW);
      break;


     case 1:
      digitalWrite(13, LOW);
      digitalWrite(12, HIGH); 
      digitalWrite(11, HIGH);
      digitalWrite(10, LOW);
      digitalWrite(9, LOW);
      digitalWrite(8, LOW);
      digitalWrite(7, LOW);
      break;



     case 2:
      digitalWrite(13, HIGH);
      digitalWrite(12, HIGH);
      digitalWrite(11, LOW);
      digitalWrite(10, HIGH);
      digitalWrite(9, HIGH);
      digitalWrite(8, LOW);
      digitalWrite(7, HIGH);
      break;

     case 3:
      digitalWrite(13, HIGH);
      digitalWrite(12, HIGH);
      digitalWrite(11, HIGH);
      digitalWrite(10, HIGH);
      digitalWrite(9, LOW);
      digitalWrite(8, LOW);
      digitalWrite(7, HIGH);
      break;


    case 4:
      digitalWrite(13, LOW);
      digitalWrite(12, HIGH);
      digitalWrite(11, HIGH);
      digitalWrite(10, LOW);
      digitalWrite(9, LOW);
      digitalWrite(8, HIGH);
      digitalWrite(7, HIGH);
      break;


    case 5:
      digitalWrite(13, HIGH);
      digitalWrite(12, LOW);
      digitalWrite(11, HIGH);
      digitalWrite(10, HIGH);
      digitalWrite(9, LOW);
      digitalWrite(8, HIGH);
      digitalWrite(7, HIGH);
      break;


    case 6:
      digitalWrite(13, LOW);
      digitalWrite(12, LOW);
      digitalWrite(11, HIGH);
      digitalWrite(10, HIGH);
      digitalWrite(9, HIGH);
      digitalWrite(8, HIGH);
      digitalWrite(7, HIGH);
      break;

    case 7:
      digitalWrite(13, HIGH);
      digitalWrite(12, HIGH);
      digitalWrite(11, HIGH);
      digitalWrite(10, LOW);
      digitalWrite(9, LOW);
      digitalWrite(8, LOW);
      digitalWrite(7, LOW);
      break;

    case 8:
      digitalWrite(13, HIGH);
      digitalWrite(12, HIGH);
      digitalWrite(11, HIGH);
      digitalWrite(10, HIGH);
      digitalWrite(9, HIGH);
      digitalWrite(8, HIGH);
      digitalWrite(7, HIGH);
      break;

    case 9:
      digitalWrite(13, HIGH);
      digitalWrite(12, HIGH);
      digitalWrite(11, HIGH);
      digitalWrite(10, LOW);
      digitalWrite(9, LOW);
      digitalWrite(8, HIGH);
      digitalWrite(7, HIGH);
      break;

      
    }
   }  

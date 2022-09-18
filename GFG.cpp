//Variable pentru fiecare "PIN" iesit din Arduino.

int sens_1 = 2;     // Variabila pentru sensul 1 al motorului care ridica usa.
int sens_2 = 3;     // Variabila pentru sensul 2 al motorului care inchide usa.
int releu=4;        // Variabila pentru semnalul releului.
int senzorIR1 = 8;  // Variabila pentru senzorul de IR care detecteaza cand usa este inchisa. 
int senzorIR2 = 9;  // Variabila pentru senzorul de IR care detecteaza cand usa este deschisa.  
int detectare_1;    // Variabila pentru date SENZOR IR 1.
int detectare_2;    // Variabila pentru date SENZOR IR 2.
int stare=0;        // Variabila care receptioneaza semanlul( 1 sau 0) prin bluetooth . 1 = start , 0 = in asteptare.



void setup() {

// Codul din void este rulat o singura data.
  
  Serial.begin(9600);  // Setarea frecventei de comunicare dintre Computer si Arduino.
  
  //Functia pinMode(seteaza Pin-ul ca intrare sau iesire(Semnal intrare sau Semnal iesire).
  
  pinMode(sens_1,OUTPUT);
  pinMode(sens_2,OUTPUT);
  pinMode(sens_3,OUTPUT);
  pinMode(sens_4,OUTPUT);
  pinMode(senzorIR1,INPUT);
  pinMode(senzorIR2,INPUT);
  pinMode(releu,OUTPUT);


  
  digitalWrite(releu,HIGH); // "digitalWrite" este o comanda digitala care imi inchide releu(datorita montajului) din inainte sa inceapa progamul sa ruleza.
  
}

void loop() {
     
 

while(Serial.available() == 0 ){   // Este o bucla care ruleaza incontinuu pana cand se va da o comanda din telefon. Atat timp cat nu primeste un semnal "1" nu va face nimic.

 }
 stare = Serial.parseInt();     // Inregistreaza comanda din telefon(pentru a rula progamul).

  delay(2000); // o pauza de 2000 mili secunde(2 secunde)
  
 
    
    detectare_1=digitalRead(senzorIR1);  // Senzorul IR 1 inregistreaza 1 sau 0 , cand recepteaza un obiecit este 0 , iar in cand nu recepeteaza este 1.
    detectare_2=digitalRead(senzorIR2);  // -||-
    
    if(detectare_1 == 0 ) {    // cand senzorul IR 1 detecteaza 0 ruleaza comanda din paranteze.
       
     
     while(detectare_2 == 1 && stare == 1) {  // Atat timp cat senzorul IR 2 receptioneaza 1 si semnlul din telefon este 1 codul va rula.
      

        
            
        detectare_1=digitalRead(senzorIR1); //Recepteaza daca este usa inchisa sau nu.
        detectare_2=digitalRead(senzorIR2); //Recepteaza daca este usa inchisa sau nu.
      
        digitalWrite(sens_1,HIGH); // Motorul incepe sa ridice usa de la cuptor.
        digitalWrite(sens_2,LOW);
        delay(200);

      if(detectare_2 == 0){        // Când detectează senzorul ca este 0, motorul se oprește
        digitalWrite(sens_1,LOW);
        digitalWrite(sens_2,LOW);
     

      digitalWrite(releu,LOW);     // Releul porneste pentru a da un impuls electromagnetului, ce mai departe va da un impuls pistonului.
      delay(35);
      digitalWrite(releu,HIGH);   

      delay(5000);               // pauză 5 secunde 
        
        }
       }
      }

    


    detectare_1=digitalRead(senzorIR1);  // senzorii cu IR culeg informații.
    detectare_2=digitalRead(senzorIR2);
    
    if(detectare_2 == 0) {               // Dacă senzorul IR de deasupra cuptorului primește semnal rulează codul
       
     
     while(detectare_1 == 1){            // Atât timp cat senzorul cu IR 1 este egal cu 1 codul va rula.

       
            
        detectare_1=digitalRead(senzorIR1);    // senzorii IR culeg informații
        detectare_2=digitalRead(senzorIR2);
      
        digitalWrite(sens_1,LOW);              //motorul de la cuptor inchide ușa
        digitalWrite(sens_2,HIGH);
        delay(200);                            //o pauză de 0.2 secunde
    
      if(detectare_1 == 0){                    // dacă senzorul IR1 = 0 codul va rula.
        digitalWrite(sens_1,LOW);              //motorul de la usa se oprește
        digitalWrite(sens_2,LOW);
                     
      
        
        delay(2000);              //pauza 2 secunde.
        
        
        stare = 0;        // resetare
        
        }
       }
      }
}

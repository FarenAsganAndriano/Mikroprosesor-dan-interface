

const int led1 = 3;
const int led2 = 2;
const int led3 = 1;
const int button1 = 4;  
 

int buttonState1 = 0;  


void setup() {
  
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

 
  pinMode(button1, INPUT);
  

  // Awal status LED mati
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
}

void loop() {
  
  buttonState1 = digitalRead(button1);
  

  
  if (buttonState1 == HIGH) {
    digitalWrite(led1, HIGH);
    delay(300);
    digitalWrite(led1, LOW);

    digitalWrite(led2, HIGH);
    delay(300);
    digitalWrite(led2, LOW);

    digitalWrite(led3, HIGH);
    delay(300);
    digitalWrite(led3, LOW);
  }

  
}


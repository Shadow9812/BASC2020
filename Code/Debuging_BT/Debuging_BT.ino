// download "Android Bluetooth Control" to your android phone
// connect the device by BT


#define led1 4
#define led2 5
#define led3 6

char Val;

void setup() {
  Serial.begin(9600);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);

  digitalWrite(led1,LOW);
  digitalWrite(led2,LOW);
  digitalWrite(led3,LOW);
  // put your setup code here, to run once:

}

void loop() {
  if (Serial.available()){
    Val=Serial.read();
    Serial.print(Val);

    if (Val==1){
      digitalWrite(led1,HIGH);
      delay(1500);
      digitalWrite(led1,LOW);
      digitalWrite(led2,LOW);
      digitalWrite(led3,LOW);
      //(insert the 1st code section)
    }

    if (Val==2){
      digitalWrite(led1,HIGH);
      digitalWrite(led2,HIGH);
      delay(1500);
      digitalWrite(led1,LOW);
      digitalWrite(led2,LOW);
      digitalWrite(led3,LOW);
      //(insert the 2nd code section)
    }

    if (Val==3){
      digitalWrite(led1,HIGH);
      digitalWrite(led2,HIGH);
      digitalWrite(led3,HIGH);
      delay(1500);
      //(insert the 3rd code section)
    }

    if (Val==4){
      digitalWrite(led1,HIGH);
      digitalWrite(led2,HIGH);
      digitalWrite(led3,HIGH);
      delay(1500);
      digitalWrite(led1,LOW);
      digitalWrite(led2,LOW);
      digitalWrite(led3,LOW);
      delay(500);
      digitalWrite(led1,HIGH);
      delay(500);
      digitalWrite(led1,LOW);
      digitalWrite(led2,LOW);
      digitalWrite(led3,LOW);
      
      //(insert the 4th code section)
    }
  }
  // put your main code here, to run repeatedly:

}

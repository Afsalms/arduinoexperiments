String recieved_text;
void setup() {
  // put your setup code here, to run once:
  pinMode(13,OUTPUT);
  digitalWrite(13, LOW);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
 while (Serial.available())
  {
    recieved_text  = Serial.readString();
    recieved_text.replace("\n","");
    Serial.println(recieved_text); 
    if (recieved_text.equals("on")){
      
        digitalWrite(13, HIGH);
      }
    else{
      digitalWrite(13, LOW);
      }
  }

}

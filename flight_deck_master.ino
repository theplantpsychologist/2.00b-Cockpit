int failures = 0;
int successes = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(8,INPUT_PULLUP); //failure
  pinMode(9,INPUT_PULLUP); //success
  pinMode(10,INPUT_PULLUP); //failure
  pinMode(11,INPUT_PULLUP); //success  
  pinMode(4,OUTPUT); //green light, rocket up
  pinMode(5,OUTPUT); //red light, rocket down
  Serial.begin(9600);
}

void failure(){
  failures = failures + 1;
  Serial.print("Failures:");
  Serial.println(failures);
  digitalWrite(5,HIGH);
  delay(500);
  digitalWrite(5,LOW);
}
void success(){
  successes = successes + 1;
  Serial.print("Successes:");
  Serial.println(successes);
  digitalWrite(4,HIGH);
  delay(500);
  digitalWrite(4,LOW);
}
void loop() {
  if (digitalRead(8)==LOW || digitalRead(10)==LOW){
    success();
    while(digitalRead(8)==LOW || digitalRead(10)==LOW){}
  }
  if (digitalRead(9)==LOW || digitalRead(11)==LOW){
    failure();
    while(digitalRead(9)==LOW || digitalRead(11)==LOW){}
  }
}

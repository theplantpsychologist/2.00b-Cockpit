String incomingByte;
const char *commands[4] = {"green","blue","yellow","red"};
const char *consoles[4] = {'1','2','3','4'};
//list of all the commands used in the game, and all the consoles

void setup() {
  pinMode(2,INPUT_PULLUP);  
  pinMode(4,OUTPUT);
  Serial.begin(9600);
}

//int message(String text){
//  Serial.println(text);
//  digitalWrite(4,HIGH);
//  while(digitalRead(2)==LOW){
//    //low means there is an input/output, high means there is none
//  }
//  digitalWrite(4,LOW);
//  return 0;
//}


void giveCommand(char id){
  Serial.println(commands[random(0,4)].insert(0,id));
}
void rocketDown(){}

void payAttention(){
  if (Serial.available() > 0) {
    //Serial.println("Starting...");
    incomingByte = Serial.readString(); //this includes the newline (which is \r\n)
    char* output = incomingByte.c_str();
    //Serial.print(output);
    char first = output[0];
    
    if (first == 'C'){
      //C means a console is asking for a command
      giveCommand(output+1);
    } 
    if (strcmp(output,"FAILURE")==0){
      rocketDown();
    }
  }
}

void loop() {
  
  if(digitalRead(2)==LOW){
    Serial.println(commands[random(0,4)]);
  }
}

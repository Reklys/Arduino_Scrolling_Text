//define ST string as matrix and changing matrix

byte character[8]={0x0, 0xee, 0x84, 0xe4, 0x24, 0xe4, 0x0, 0x0};
byte charactertrans[8]={0x0, 0xee, 0x84, 0xe4, 0x24, 0xe4, 0x0, 0x0};
//define pins
uint8_t colPins[8]={ 2, 3, 4, 5, 6, 7, 8, 9};

int i;

#define SER_PIN 10
#define SCK_PIN 11
#define RCK_PIN 12
//Setup LED array byt turning off everything
void setup() {
  
  for(int i=0; i<8; i++) {
    pinMode(colPins[i],OUTPUT);
  }
  pinMode(SER_PIN, OUTPUT);
  pinMode(SCK_PIN, OUTPUT);
  pinMode(RCK_PIN, OUTPUT);
  Serial.begin(9600);

}


int counter=0;
void loop() { 
if(counter==20){
bool same = true;
for (int row = 0; row < 8; row++){
  if (charactertrans[row] != 0x00)
    same = false;  
}
if (same){
  for(int row = 0; row < 8; row++){
    charactertrans[row] = character[row];
      
  }
 
}
else {
  for (int row = 0; row < 8; row++){
    charactertrans[row] = charactertrans[row] << 1;
  }
}
counter=0;
}
else{
  counter++;
}
  // iterate each row
  int rowbits = 0x80;
//for(int repeat = 0; repeat<; repeat++){
  for(int row=0; row<8; row++) {
    for(int k=0; k<8; k++) 
      digitalWrite(colPins[k],HIGH); // Cleanup cols
    write595(rowbits); // prepare to write the row
    for(int col=0; col<8; col++)
      digitalWrite(colPins[7-col], charactertrans[row] & 1 << col ? LOW : HIGH);
    delay(1);
    write595(0);
    rowbits >>= 1; 

 
 // } 
}

  
}

void write595(byte data) {
  digitalWrite(RCK_PIN, LOW);
  shiftOut(SER_PIN, SCK_PIN, LSBFIRST, data);
  digitalWrite(RCK_PIN, HIGH);
}

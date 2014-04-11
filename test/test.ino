
uint8_t column = 0;
uint8_t row = 0;

byte smiley[8] = {
  0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f
};
void setup() {
  Serial1.begin(9600);
  delay(2);
  Serial1.write(159);
  Serial1.write(130);
  delay(1);
  Serial1.write(159);
  Serial1.write(131);
  delay(1);
  Serial1.write(165);
  while(1)
    {
        if (Serial1.available() > 0 &&Serial1.read()==170)
            break;
    }
   
}

void loop() {
  Serial1.write(159);
  Serial1.write(255);
  Serial1.write(column);
  Serial1.write(row);
  
  Serial1.write(159);
  Serial1.write(255);
  Serial1.write(column);
  Serial1.write(1);
  
  Serial.write(64);
  
  Serial1.write(254);
  Serial1.write("Hello, world!");
  while(1);
}

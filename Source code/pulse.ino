#define heartbeat 0

void setup()
{
  Serial.begin(115200);  
}


void loop() 
{
  
heartbeat = analogRead(A0);
Serial.println(String(heartbeat)+"?");

}
const long A = 1000;     //Resistencia en oscuridad KO
const int B = 15;        //Resistencia a la luz (10 Lux) KO
const int Rc1 = 13;       //Resistencia calibracion 1 KO
const int Rc2 = 10;       //Resistencia calibracion 2 KO
const int LDRPin1 = A0;   //Pin del LDR1
const int LDRPin2 = A1;   //Pin del LDR2
 
int V1, V2;
int ilum1, ilum2;
 
void setup() 
{
  Serial.begin(9600);
}
 
void loop()
{
  V1 = analogRead(LDRPin1);         
  V2 = analogRead(LDRPin2);
 
  //ilum = ((long)(1024-V)*A*10)/((long)B*Rc*V);    //usar si       
  ilum1 = ((long)V1*A*10)/((long)B*Rc1*(1024-V1));    //usar si 
  ilum2 = ((long)V2*A*10)/((long)B*Rc2*(1024-V2));    //usar si 
  
  Serial.print(ilum1);
  Serial.print("  ");
  Serial.print(ilum2); 
  Serial.println();
  
  delay(1000);
}

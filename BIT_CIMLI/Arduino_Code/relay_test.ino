// Operadores de mascaras de bit
#define TurnOnBit(var, pos)   ((var) |= (1 << pos))
#define TurnOffBit(var, pos)  ((var) &= (1 << pos))
#define IsOnBit(var, pos)     ((var) &  (1 << pos))
#define ToggleBit(var, pos)   ((var) ^= (1 << pos))

const int  A = 1000;     //Resistencia en oscuridad KO
const byte B = 15;        //Resistencia a la luz (10 Lux) KO
const byte Rc = 10;       //Resistencia calibracion KO
const byte LDRPin = A0;   //Pin del LDR
 
int V;
int ilum;
unsigned char relayPins[6] = {41, 42, 43, 44, 45, 46};

int MedirLuz()
{
    V = analogRead(LDRPin);         
 
    //ilum = ((long)(1024-V)*A*10)/((long)B*Rc*V);    //usar si       
    ilum = ((long)V*A*10)/((long)B*Rc*(1024-V));    //usar si

    return ilum;
}

void apagarLuces(int n)
{
  //Apago todas las luces
  for (int j=0; j<n; j++)
    digitalWrite(relayPins[j], HIGH);
}

// Combinaciones de N elementos
void Combinaciones(int n) {

int num=0;

apagarLuces(n);

for(int k = 1; k <= n; k++ ) 
{ 
  for( int i = 0; i < (1 << n); i++ ) 
  {
    // Caja negra para contar los bit activos (solo 32 bits)
    int c = i - ( ( i >> 1 ) & 0x55555555 );
    c = ( c & 0x33333333 ) + ( ( c >> 2 ) & 0x33333333 );
    c = ( ( c + ( c >> 4 ) & 0xF0F0F0F ) * 0x1010101 ) >> 24;

    //Conteo en O(n) mucho mas lento q la caja negra
    //for (j=0,c=0; j<32; j++) if (i & (1<<j)) c++;

    if( c == k ) 
    {
      // Usar combinación.
      Serial.print("Combination #"); Serial.print(++num); Serial.print(": \t");
      
      for (int j=0; j<n; j++) 
        if (IsOnBit(i,j)){
          //El elemento j+1 pertenece a la combinacion 
          digitalWrite(relayPins[j], LOW);
          Serial.print(j+1,DEC); //Serial.print(" ");
        }
        Serial.print("\tLux: ");
        
       //Aqui hago las mediciones (total 50 mediciones)
       int medition = 0;
       
       for (int i = 0; i < 50; i++) {
          medition += MedirLuz();
          delay(30);
       }
          
       //Hago un promedio a 50 mediciones para la misma combinacion
       medition /= 50;     

       Serial.println(ilum);  
              
       delay(1500); 
       
       //Apago todas las luces
       apagarLuces(n);      
    }
  }
}

}


void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < 6; i++)
    pinMode(relayPins[i], OUTPUT);
  pinMode(LDRPin, INPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  /*
  for (int i = 0; i < 6; i++){
    digitalWrite(relayPins[i], HIGH);
    delay(1000);    
  }

  for (int i = 0; i < 6; i++){
    digitalWrite(relayPins[i], LOW);
    delay(1000);    
  }
  
  apagarLuces(6);
  delay(5000);
  digitalWrite(relayPins[0], LOW);
  digitalWrite(relayPins[1], LOW);
  delay(10000);
  */
  
  Serial.println("Inicio del experimiento:");
  Serial.println("------------------------"); 
 Combinaciones(6);
  Serial.println("------------------------");
  Serial.println("Fin del experimiento:");
   
}

///Codigo Final Montaje

int ledPin_R1 = 13;  //declaramos 5 leds rojos(R) y 5 leds verdes(G)
int ledPin_G1 = 12;
int ledPin_R2 = 11;
int ledPin_G2 = 10;
int ledPin_R3 = 9;
int ledPin_G3 = 8;
int ledPin_R4 = 7;
int ledPin_G4 = 6;
int ledPin_R5 = 5;
int ledPin_G5 = 4;
int pinBuzzer = 3;
int threshold = 300; // threshold para los piezoeléctricos
int threshold_2 = 150;
int piezoState = 0;
int startState = 0; 
int roundCount = 1;
int rounds = 20;

const int Piezo_1 = A0; // Pines analogicos de los piezos
const int Piezo_2 = A1;
const int Piezo_3 = A2;
const int Piezo_4 = A3;
const int Piezo_5 = A4;

bool welcomeMsg = false;

bool gameOn = false; // indica juego activo
bool playerDone = false; // golpe exitoso 

long randomTime;
long startTime;
long endTime;

float scoreTotal; //promedio de tiempo de reacción por rounds
float scoreSum;   //sumatoria de tiempos de reacción en ms

void setup() {

  pinMode(Piezo_1, INPUT);   // definimos piezos de entrada
  pinMode(Piezo_2, INPUT);
  pinMode(Piezo_3, INPUT);
  pinMode(Piezo_4, INPUT);
  pinMode(Piezo_5, INPUT);
  pinMode(ledPin_R1, OUTPUT); // leds de salida
  pinMode(ledPin_R2, OUTPUT);
  pinMode(ledPin_R3, OUTPUT);
  pinMode(ledPin_R4, OUTPUT);
  pinMode(ledPin_R5, OUTPUT);
  pinMode(ledPin_G1, OUTPUT);
  pinMode(ledPin_G2, OUTPUT);
  pinMode(ledPin_G3, OUTPUT);
  pinMode(ledPin_G4, OUTPUT);
  pinMode(ledPin_G5, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  if (welcomeMsg == false) {
    digitalWrite(ledPin_R1, HIGH);  // Menú de inicio: Enciende el led principal (piezo1) en rojo y los demás en verde para indicar reinicio del juego
    digitalWrite(ledPin_G2, HIGH);
    digitalWrite(ledPin_G3, HIGH);
    digitalWrite(ledPin_G4, HIGH);
    digitalWrite(ledPin_G5, HIGH);
    Serial.println("      ");
    Serial.println("presione el botón 1 para iniciar");
    welcomeMsg = true;
  }

  startState = analogRead(Piezo_1);   // lee piezo principal para iniciar el juego

  if (startState >= threshold && gameOn== false ){  
    tone(pinBuzzer,1000);
    gameOn = true;
    digitalWrite(ledPin_R1, LOW);   //apaga todos los leds
    digitalWrite(ledPin_G2, LOW);
    digitalWrite(ledPin_G3, LOW);
    digitalWrite(ledPin_G4, LOW);
    digitalWrite(ledPin_G5, LOW);

    digitalWrite(ledPin_G1, HIGH);      // feedback con led verde para indicar golpe exitoso en piezo 1
    delay (200);
    digitalWrite(ledPin_G1, LOW);
    noTone(pinBuzzer);
    delay(1000);
    Serial.println("Preparate!");

    tone(pinBuzzer,600);
    digitalWrite(ledPin_R1, HIGH);  // Blink rojo en todos los piezos para indicar que inicia el juego
    digitalWrite(ledPin_R2, HIGH);
    digitalWrite(ledPin_R3, HIGH);
    digitalWrite(ledPin_R4, HIGH);
    digitalWrite(ledPin_R5, HIGH);
    delay(400);
    noTone(pinBuzzer);
    digitalWrite(ledPin_R1, LOW);
    digitalWrite(ledPin_R2, LOW);
    digitalWrite(ledPin_R3, LOW);
    digitalWrite(ledPin_R4, LOW);
    digitalWrite(ledPin_R5, LOW);
    delay(400);

    tone(pinBuzzer,600);
    digitalWrite(ledPin_R1, HIGH);
    digitalWrite(ledPin_R2, HIGH);
    digitalWrite(ledPin_R3, HIGH);
    digitalWrite(ledPin_R4, HIGH);
    digitalWrite(ledPin_R5, HIGH);
    delay(400);
    noTone(pinBuzzer);
    digitalWrite(ledPin_R1, LOW);
    digitalWrite(ledPin_R2, LOW);
    digitalWrite(ledPin_R3, LOW);
    digitalWrite(ledPin_R4, LOW);
    digitalWrite(ledPin_R5, LOW);
    delay(400);

    tone(pinBuzzer,1500);
    digitalWrite(ledPin_R1, HIGH);
    digitalWrite(ledPin_R2, HIGH);
    digitalWrite(ledPin_R3, HIGH);
    digitalWrite(ledPin_R4, HIGH);
    digitalWrite(ledPin_R5, HIGH);
    delay(400);
    digitalWrite(ledPin_R1, LOW);
    digitalWrite(ledPin_R2, LOW);
    digitalWrite(ledPin_R3, LOW);
    digitalWrite(ledPin_R4, LOW);
    digitalWrite(ledPin_R5, LOW);
    noTone(pinBuzzer);

    while ( gameOn == true && roundCount <= rounds) {    //checkea si hay juegos activos y el numero de rounds para iniciar los ciclos, al llegar al limite de rounds termina el juego
      startGame();  
      
    }
    endGame();
  }
}

void startGame() {
  scoreTotal = 0;                         //reinicia el puntaje total al iniciar nuevas rondas
  playerDone = false;                     // reinicia el indicador de cada round (golpe en el piezo)
  gameOn = true;                          // indica que el juego está en progreso
  randomTime = random(1,3);               // tiempo random entre 2 y 6 segundos (5 segundos maximo de espera entre rounds)
  randomTime = randomTime*1000;

  delay(randomTime);
   
  int rand_num = random(0, 5);            // genera numero aleatorio para encender leds
  startTime = millis();                   // lectura de tiempo inicial
              
  if (rand_num == 0) {
    digitalWrite(ledPin_R1, HIGH);   // enciende led rojo 1: listo para golpear piezo

    while (playerDone == false) {
      piezoState = analogRead(Piezo_1);   // lee piezo 1 

      if (piezoState >= threshold && playerDone == false) {
        tone(pinBuzzer,440);
        Serial.println();
        Serial.println("Knock!");         // registra golpe y muestra el valor de lectura del piezo
        Serial.print(piezoState);

        endTime = millis();               // lectura de tiempo final

        digitalWrite(ledPin_R1,LOW);      // apaga led rojo de piezo_1
        digitalWrite(ledPin_G1, HIGH);    // feedback, blink verde para indicar golpe exitoso
        delay (200);
        noTone(pinBuzzer);
        digitalWrite(ledPin_G1, LOW);

        playerDone = true;                
        piezoState = 0;
        roundCount++;                      // suma un nuevo round al contador
        scoreSum= scoreSum + (endTime - startTime); // suma tiempo de reacción al puntaje
      }
    }
}
  else if(rand_num == 1) {              // Repite lo anterior con piezo 2
    digitalWrite(ledPin_R2, HIGH);

    while (playerDone == false) {
      piezoState = analogRead(Piezo_2);

      if (piezoState >= threshold && playerDone == false) {
        tone(pinBuzzer,440);
        Serial.println();
        Serial.println("Knock!");
        Serial.print(piezoState);

        endTime = millis();

        digitalWrite(ledPin_R2,LOW);
        digitalWrite(ledPin_G2, HIGH);
        delay (200);
        noTone(pinBuzzer);
        digitalWrite(ledPin_G2, LOW);

        playerDone = true;
        piezoState = 0;
        roundCount++;
        scoreSum= scoreSum + (endTime - startTime);
      
  }
 }
}

  else if (rand_num == 2) {                // Repite lo anterior con piezo 3
    digitalWrite(ledPin_R3, HIGH);

    while (playerDone == false) {
      piezoState = analogRead(Piezo_3);

      if (piezoState >= threshold && playerDone == false) {
        tone(pinBuzzer,440);
        Serial.println();
        Serial.println("Knock!");
        Serial.print(piezoState);
        
        endTime = millis();

        digitalWrite(ledPin_R3,LOW);
        digitalWrite(ledPin_G3, HIGH);
        delay (200);
        noTone(pinBuzzer);
        digitalWrite(ledPin_G3, LOW);

        playerDone = true;
        piezoState = 0;
        roundCount++;
        scoreSum= scoreSum + (endTime - startTime);
        }
      }
    }
    else if (rand_num == 3) {                // Repite lo anterior con piezo 3
    digitalWrite(ledPin_R4, HIGH);

    while (playerDone == false) {
      piezoState = analogRead(Piezo_4);

      if (piezoState >= threshold && playerDone == false) {
        tone(pinBuzzer,440);
        Serial.println();
        Serial.println("Knock!");
        Serial.print(piezoState);
        
        endTime = millis();

        digitalWrite(ledPin_R4,LOW);
        digitalWrite(ledPin_G4, HIGH);
        delay (200);
        noTone(pinBuzzer);
        digitalWrite(ledPin_G4, LOW);

        playerDone = true;
        piezoState = 0;
        roundCount++;
        scoreSum= scoreSum + (endTime - startTime);
        }
      }
    }
    else if (rand_num == 4) {                // Repite lo anterior con piezo 3
    digitalWrite(ledPin_R5, HIGH);

    while (playerDone == false) {
      piezoState = analogRead(Piezo_5);

      if (piezoState >= threshold_2 && playerDone == false) {
        tone(pinBuzzer,440);
        Serial.println();
        Serial.println("Knock!");
        Serial.print(piezoState);
        
        endTime = millis();

        digitalWrite(ledPin_R5,LOW);
        digitalWrite(ledPin_G5, HIGH);
        delay (200);
        noTone(pinBuzzer);
        digitalWrite(ledPin_G5, LOW);

        playerDone = true;
        piezoState = 0;
        roundCount++;
        scoreSum= scoreSum + (endTime - startTime);
        }
      }
    }
}

void endGame() {
  delay(1000);
  tone(pinBuzzer,700);
  digitalWrite(ledPin_G1, HIGH);  // Blink verde en todos los piezos para indicar que acaba el juego
  digitalWrite(ledPin_G2, HIGH);
  digitalWrite(ledPin_G3, HIGH);
  digitalWrite(ledPin_G4, HIGH);
  digitalWrite(ledPin_G5, HIGH);
  delay(400);
  digitalWrite(ledPin_G1, LOW);
  digitalWrite(ledPin_G2, LOW);
  digitalWrite(ledPin_G3, LOW);
  digitalWrite(ledPin_G4, LOW);
  digitalWrite(ledPin_G5, LOW);
  delay(400);
  noTone(pinBuzzer);
  tone(pinBuzzer,650);
  digitalWrite(ledPin_G1, HIGH);
  digitalWrite(ledPin_G2, HIGH);
  digitalWrite(ledPin_G3, HIGH);
  digitalWrite(ledPin_G4, HIGH);
  digitalWrite(ledPin_G5, HIGH);
  delay(400);
  digitalWrite(ledPin_G1, LOW);
  digitalWrite(ledPin_G2, LOW);
  digitalWrite(ledPin_G3, LOW);
  digitalWrite(ledPin_G4, LOW);
  digitalWrite(ledPin_G5, LOW);
  delay(400);
  noTone(pinBuzzer);
  tone(pinBuzzer,580);
  digitalWrite(ledPin_G1, HIGH);
  digitalWrite(ledPin_G2, HIGH);
  digitalWrite(ledPin_G3, HIGH);
  digitalWrite(ledPin_G4, HIGH);
  digitalWrite(ledPin_G5, HIGH);
  delay(400);
  digitalWrite(ledPin_G1, LOW);
  digitalWrite(ledPin_G2, LOW);
  digitalWrite(ledPin_G3, LOW);
  digitalWrite(ledPin_G4, LOW);
  digitalWrite(ledPin_G5, LOW);
  noTone(pinBuzzer);

  scoreTotal = scoreSum/rounds;     // Promedio: sumatoria de tiempos de reacción dividido por el número de rounds. los mejores puntajes se acercan a cero.
  Serial.println();
  Serial.println("    ");
  Serial.println("Tiempo de reacción promedio fue de:");
  Serial.print(scoreTotal/1000);
  Serial.print(" segundos");
  Serial.println("   ");
  delay(3000);
  piezoState = 0;                   // regresa las variables al estado original para reiniciar el loop
  gameOn = false;
  playerDone = false;
  startState = 0;
  randomTime = 0;
  startTime = 0,
  endTime = 0;
  welcomeMsg = false;
  roundCount = 1;
  scoreTotal = 0;
  scoreSum = 0;
}
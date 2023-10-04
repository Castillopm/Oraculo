////////MIS VARIABLES//////

const int ledRojo = 9;   
const int ledVerde = 8;  
const int ledAmarillo = 7;

String miPregunta;
String s1 = "¡Claro que sí!";
String s2 = "¡Ni de broma!";
String s3 = "Eso no lo se, pero se te va a caer el pelo cuando llegues a casa";
String s4 = "Si te esperas un momento, lo busco en Google";

int Brillo = 0;
int fadeAmount = 3;

void setup() {
  Serial.begin(9600);

  pinMode(ledRojo, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarillo, OUTPUT);
  if (Serial) {
    Serial.println("Hola, hazme una pregunta.");
  }
}

void loop() {
  if (Serial.available() > 0) {
    miPregunta = Serial.readStringUntil('\n');
    Serial.print("Tu pregunta es: ");
    Serial.println(miPregunta);

    delay(100);

    // Comprueba si la pregunta contiene un signo de interrogación
    if (miPregunta.indexOf('?') != -1) {
      int numRandom = random(0, 4);

      if (numRandom == 0) {
        Serial.println(s1);
        digitalWrite(ledVerde, HIGH);
      } else if (numRandom == 1) {
        Serial.println(s2);
        digitalWrite(ledRojo, HIGH);
      } else if (numRandom == 2) {
        Serial.println(s3);
        digitalWrite(ledAmarillo, HIGH);
      } else if (numRandom == 3) {
        Serial.println(s4);
        digitalWrite(ledRojo, HIGH);
        digitalWrite(ledVerde, HIGH);
        digitalWrite(ledAmarillo, HIGH);
      }

      // Apaga los LEDs después de un tiempo
      delay(1000);
      digitalWrite(ledRojo, LOW);
      digitalWrite(ledVerde, LOW);
      digitalWrite(ledAmarillo, LOW);
    } else {
      // Si no se encuentra un signo de interrogación en la pregunta
      Serial.println("Eso no es una pregunta");

      // Enciende el LED rojo tres veces en secuencia
      for (int j = 0; j < 4; j++) {
        for (int i = 0; i <= 255; i += fadeAmount) {
          analogWrite(ledRojo, i);
          delay(10); // Velocidad de aumento de intensidad
        }
        digitalWrite(ledRojo, LOW);
        delay(500); // Pequeño retraso entre secuencias
      }

      // Apaga los LEDs después de las secuencias
      digitalWrite(ledVerde, LOW);
      digitalWrite(ledAmarillo, LOW);
    }
  }
}

// Alcoholímetro futurólogo.
const int sensorAlcohol = A0;

// las luces LED
const int ledVerde = 8;
const int ledRojo = 9;
const int ledAmarillo = 10;

// Umbral de tasa de alcohol en aire (en mg/l). float porque la tasa contiene decimales.
const float umbralAlcohol = 0.5;

// Respuestas
String s1 = "¡Claro que sí!";
String s2 = "Ni de broma";
String s3 = "Eso no lo sé, pero se te va a caer el pelo cuando llegues a casa";
String s4 = "Espera que lo busco en Google";
String s5 = "¡Vaya morao que llevas en lo alto!";

void setup() {
  Serial.begin(9600);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledRojo, OUTPUT);
  pinMode(ledAmarillo, OUTPUT);
}

void loop() {
  // leer tasa de alcohol en aire. 1023 es el valor máximo de lectura analógico y se multiplica por 5 que son los voltios de tensión del sensor. El resultado se almacena en la variable tasaAlcohol.
  float tasaAlcohol = analogRead(sensorAlcohol) * (5.0 / 1023.0);

  // Comprobar si la tasa de alcohol supera el umbral
  if (tasaAlcohol > umbralAlcohol) {
    // Si la tasa de alcohol es alta, mostrar un mensaje y parpadear la luz roja
    Serial.println("¡Vaya morao que llevas en lo alto!");
    parpadearLED(ledRojo);
  } else {
    // Si la tasa de alcohol es baja, permitir la pregunta
    Serial.println("Hazme una pregunta:");
    while (!Serial.available()) {
    }
    String pregunta = Serial.readStringUntil('\n');
    Serial.println("Tu pregunta es: " + pregunta);

    // Elegir una respuesta aleatoria
    int respuestaAleatoria = random(1, 5);

    // Mostrar la respuesta y encender la luz correspondiente
    switch (respuestaAleatoria) {
      case 1:
        Serial.println(s1);
        digitalWrite(ledVerde, HIGH);
        break;
      case 2:
        Serial.println(s2);
        digitalWrite(ledRojo, HIGH);
        break;
      case 3:
        Serial.println(s3);
        digitalWrite(ledAmarillo, HIGH);
        break;
      case 4:
        Serial.println(s4);
        intermitenciaLEDs();
        break;
      default:
        break;
    }
  }

  // Esperar un tiempo antes de apagar todas las luces
  delay(3000);
  apagarLEDs();
}

// Función para apagar todas las luces LED
void apagarLEDs() {
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledRojo, LOW);
  digitalWrite(ledAmarillo, LOW);
}

// Función para parpadear la luz roja
void parpadearLED(int pin) {
  for (int i = 0; i < 5; i++) {
    digitalWrite(pin, HIGH);
    delay(500);
    digitalWrite(pin, LOW);
    delay(500);
  }
}

// Función para la secuencia de intermitencia de las luces
void intermitenciaLEDs() {
  for (int j = 0; j < 3; j++) {
    digitalWrite(ledVerde, HIGH);
    delay(500);
    digitalWrite(ledVerde, LOW);

    digitalWrite(ledRojo, HIGH);
    delay(500);
    digitalWrite(ledRojo, LOW);

    digitalWrite(ledAmarillo, HIGH);
    delay(500);
    digitalWrite(ledAmarillo, LOW);
  }
}

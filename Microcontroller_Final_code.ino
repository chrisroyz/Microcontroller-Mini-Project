
const int MOISTURE_POWER_PIN = 8;
const int MOISTURE_PIN = A0;
const int RELAY_PIN = 7;

// Initial values based on your previous sensor readings
const int DRY_THRESHOLD = 700;
const int WET_THRESHOLD = 600;

const unsigned long SENSOR_SETTLE_MS = 500;
const unsigned long PUMP_DURATION_MS = 3000;
const unsigned long SOAK_DELAY_MS = 15000;
const unsigned long INSPECTION_DELAY_MS = 60000;

// Set false if your relay module is active-HIGH.
const bool RELAY_ACTIVE_LOW = true;

bool wateringNeeded = false;

void setPump(bool on) {
  digitalWrite(
    RELAY_PIN,
    (on == RELAY_ACTIVE_LOW) ? LOW : HIGH
  );
}

int readMoisture() {
  // Power sensor only when measuring
  digitalWrite(MOISTURE_POWER_PIN, HIGH);
  delay(SENSOR_SETTLE_MS);

  // Average several readings
  long total = 0;
  for (int i = 0; i < 5; i++) {
    total += analogRead(MOISTURE_PIN);
    delay(10);
  }

  // Turn sensor power off after measurement
  digitalWrite(MOISTURE_POWER_PIN, LOW);

  return total / 5;
}

void setup() {
  // Initialize relay OFF
  digitalWrite(RELAY_PIN, RELAY_ACTIVE_LOW ? HIGH : LOW);
  pinMode(RELAY_PIN, OUTPUT);
  setPump(false);

  // Sensor power starts OFF
  digitalWrite(MOISTURE_POWER_PIN, LOW);
  pinMode(MOISTURE_POWER_PIN, OUTPUT);

  Serial.begin(9600);
  Serial.println("Smart irrigation started");
}

void loop() {
  int moisture = readMoisture();

  Serial.print("Moisture reading: ");
  Serial.println(moisture);

  // Hysteresis prevents rapid relay switching
  if (moisture >= DRY_THRESHOLD) {
    wateringNeeded = true;
  } else if (moisture <= WET_THRESHOLD) {
    wateringNeeded = false;
  }

  if (wateringNeeded) {
    Serial.println("Soil dry: pump ON");
    setPump(true);
    delay(PUMP_DURATION_MS);

    setPump(false);
    Serial.println("Pump OFF: soaking period");

    delay(SOAK_DELAY_MS);
    // loop() measures moisture again
  } else {
    setPump(false);
    Serial.println("Soil sufficiently moist");

    delay(INSPECTION_DELAY_MS);
    // Measure again after 60 seconds
  }
}

/*
====================================================
SMART ROOM MONITORING SYSTEM
ESP32 DOIT DEVKIT V1

Komponen:
1. Wi-Fi Hotspot HP
2. Sensor DHT22
3. LED

KONFIGURASI GPIO:
DHT22 DATA = GPIO 4
LED        = GPIO 18

KONEKTIVITAS:
SSID     = Celestia Note 14 5G
BAUDRATE = 115200
====================================================
*/

#include <WiFi.h>
#include <DHT.h>

// ==================================================
// KONFIGURASI HOTSPOT
// ==================================================

const char* WIFI_SSID = "Celestia Note 14 5G";
const char* WIFI_PASSWORD = "12345678";

// ==================================================
// KONFIGURASI SENSOR
// ==================================================

#define DHT_PIN 4
#define DHT_TYPE DHT22

#define LED_PIN 18

#define BATAS_SUHU 30.0

DHT dht(DHT_PIN, DHT_TYPE);

// ==================================================
// TIMER
// ==================================================

unsigned long waktuSebelumnya = 0;
unsigned long waktuReconnect = 0;

const unsigned long INTERVAL_MONITOR = 2000;
const unsigned long INTERVAL_RECONNECT = 10000;

// ==================================================
// FUNGSI KONEKSI WIFI
// ==================================================

void koneksiWiFi() {

  Serial.println();
  Serial.println("[WIFI] Menghubungkan ke Hotspot HP...");

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  unsigned long waktuMulai = millis();

  while (WiFi.status() != WL_CONNECTED &&
         millis() - waktuMulai < 20000) {

    delay(500);
    Serial.print(".");
  }

  Serial.println();

  if (WiFi.status() == WL_CONNECTED) {

    Serial.println("[SUCCESS] HOTSPOT BERHASIL TERHUBUNG!");

    Serial.print("SSID       : ");
    Serial.println(WiFi.SSID());

    Serial.print("IP Address : 10.213.148.112");
    Serial.println(WiFi.localIP());

    Serial.print("Gateway    : 10.213.148.218");
    Serial.println(WiFi.gatewayIP());

    Serial.print("RSSI       : ");
    Serial.print(WiFi.RSSI());
    Serial.println(" dBm");

  } else {

    Serial.println("[ERROR] GAGAL TERHUBUNG KE HOTSPOT!");

  }
}

// ==================================================
// SETUP
// ==================================================

void setup() {

  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  dht.begin();

  Serial.println();
  Serial.println("========================================");
  Serial.println(" SMART ROOM MONITORING SYSTEM");
  Serial.println(" ESP32 DOIT DEVKIT V1");
  Serial.println("========================================");

  koneksiWiFi();

  Serial.println();
  Serial.println("[SYSTEM] Monitoring dimulai.");
}

// ==================================================
// LOOP
// ==================================================

void loop() {

  unsigned long sekarang = millis();

  // ----------------------------------------------
  // 1. AUTO RECONNECT WIFI
  // ----------------------------------------------

  if (WiFi.status() != WL_CONNECTED) {

  if (sekarang - waktuReconnect >= INTERVAL_RECONNECT) {

    waktuReconnect = sekarang;

    Serial.println("[WIFI] Koneksi terputus!");
    Serial.println("[WIFI] Mencoba reconnect...");

    WiFi.reconnect();
  }
}

  // ----------------------------------------------
  // 2. MONITORING SENSOR
  // ----------------------------------------------

  if (sekarang - waktuSebelumnya >= INTERVAL_MONITOR) {

    waktuSebelumnya = sekarang;

    float suhu = dht.readTemperature();
    float kelembapan = dht.readHumidity();

    Serial.println();
    Serial.println("========================================");
    Serial.println("          DATA MONITORING");
    Serial.println("========================================");

    // STATUS WIFI

    Serial.println("[WIFI]");

    if (WiFi.status() == WL_CONNECTED) {

      Serial.println("Status : TERHUBUNG");

      Serial.print("IP     : ");
      Serial.println(WiFi.localIP());

      Serial.print("RSSI   : ");
      Serial.print(WiFi.RSSI());
      Serial.println(" dBm");

    } else {

      Serial.println("Status : TERPUTUS");

    }

    // ------------------------------------------
    // 3. PEMBACAAN DHT22
    // ------------------------------------------

    Serial.println();
    Serial.println("[DHT22]");

    if (isnan(suhu) || isnan(kelembapan)) {

      Serial.println("[ERROR] Gagal membaca sensor DHT22!");

      digitalWrite(LED_PIN, LOW);

    } else {

      Serial.print("Suhu       : ");
      Serial.print(suhu);
      Serial.println(" C");

      Serial.print("Kelembapan : ");
      Serial.print(kelembapan);
      Serial.println(" %");

      // ----------------------------------------
      // 4. KONTROL LED
      // ----------------------------------------

      Serial.println();
      Serial.println("[LED]");

      if (suhu >= BATAS_SUHU) {

        digitalWrite(LED_PIN, HIGH);

        Serial.println("MENYALA - SUHU TINGGI");

      } else {

        digitalWrite(LED_PIN, LOW);

        Serial.println("MATI - SUHU NORMAL");

      }
    }

    Serial.println("========================================");
  }
}
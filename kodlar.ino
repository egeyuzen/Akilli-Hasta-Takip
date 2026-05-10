#include <WiFi.h>
#include "ThingSpeak.h"
#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

// --- AĞ VE BULUT AYARLARI ---
const char* ssid = "realme GT 2";       
const char* password = "tez12345";     

unsigned long myChannelNumber = 3373245;       
const char * myWriteAPIKey = "PDUOBNQL5OMY8858"; 

WiFiClient  client;
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
Adafruit_BME280 bme; 

void setup() {
  Serial.begin(115200);

  // --- FİZİKSEL I2C PİNLERİ ---
  Wire.begin(6, 7);
  Wire.setClock(50000);  
  Wire.setTimeout(1000); 

  // Sensörleri Başlat
  if (!mlx.begin()) {
    Serial.println("HATA: MLX90614 bulunamadi!");
    while (1);
  }
  if (!bme.begin(0x76)) { 
    Serial.println("HATA: BME280 bulunamadi!");
    while (1);
  }
  
  Serial.println("Sensorler hazir!");

  // Wi-Fi Bağlantısı
  Serial.print("WiFi Baglaniyor...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Baglandi!");

  // ThingSpeak Başlatma
  ThingSpeak.begin(client);
}

void loop() {
  // 1. Sensörleri Oku
  float vucutSicaklik = mlx.readObjectTempC();
  float ortamSicaklik = bme.readTemperature();
  float ortamNem = bme.readHumidity();
  float ortamBasinc = bme.readPressure() / 100.0F; 

  // 2. ThingSpeak Alanlarına Doldur
  ThingSpeak.setField(1, ortamSicaklik);
  ThingSpeak.setField(2, vucutSicaklik);
  ThingSpeak.setField(3, ortamNem);
  ThingSpeak.setField(4, ortamBasinc);

  // 3. Buluta Gönder
  Serial.println("ThingSpeak'e veri yollaniyor...");
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

  if(x == 200){
    Serial.println("Basarili! Veriler buluta ulasti.");
  } else {
    Serial.println("HATA! Iletisim kodu: " + String(x));
  }

  
  Serial.println("15 saniye bekleniyor...\n");
  delay(15000); 
}

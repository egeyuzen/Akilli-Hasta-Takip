#  IoT Tabanlı Akıllı Hasta Takip Sistemi


##  Proje Özeti
Bu proje, hastaların biyometrik (vücut sıcaklığı) ve çevresel (ortam ısısı, nem, basınç) verilerini eşzamanlı olarak takip etmek amacıyla tasarlanmış, **Nesnelerin İnterneti (IoT)** tabanlı akıllı bir telemetri istasyonudur. Sistem, donanım katmanında toplanan verileri bulut sunucularına aktarır ve MATLAB destekli otonom karar algoritmaları ile kritik durumlarda anlık acil durum bildirimleri (e-posta) üretir.

##  Donanım Mimarisi
Sistem, giyilebilir teknoloji standartlarına uygun olarak düşük güç tüketimi ve kompakt tasarım hedeflenerek inşa edilmiştir.
* **Mikrodenetleyici:** Seeed Studio XIAO ESP32-C3 (RISC-V 32-bit, Wi-Fi 2.4GHz)
* **Biyometrik Sensör:** MLX90614 (I2C) - Temassız Yüksek Hassasiyetli Kızılötesi Sıcaklık Ölçümü
* **Meteorolojik Sensör:** BME280 (I2C) - Ortam Isısı, Bağıl Nem ve Barometrik Basınç
* **Güç Yönetimi:** 3.7V 400mAh Li-Po Batarya

## ☁️ Yazılım ve Bulut Altyapısı
* ** (C/C++):** I2C haberleşme protokolü ile sensör verilerinin 15 saniyelik döngülerle okunması ve Wi-Fi üzerinden iletimi.
* **Cloud Katmanı (ThingSpeak):** Verilerin gerçek zamanlı grafiksel dashboard üzerinde görselleştirilmesi.
* **Karar Mekanizması (MATLAB):** `React` modülü ile tetiklenen analiz kodu sayesinde, vücut sıcaklığının **37.0°C** eşiğini aşması durumunda sistemin otonom `Alerts API` bildirimlerini başlatması.

  
**Geliştirici:** Ege Yüzen Enis Kaya Ali Bozkurt

# Smart Room Monitoring System

## Deskripsi Proyek

Smart Room Monitoring System merupakan proyek Internet of Things (IoT) berbasis ESP32 yang dirancang untuk memantau kondisi suhu dan kelembapan ruangan menggunakan sensor DHT22.

Sistem menggunakan LED sebagai indikator otomatis berdasarkan ambang batas suhu yang telah ditentukan.

## Komponen yang Digunakan

1. ESP32 DOIT DEVKIT V1
2. Sensor DHT22
3. LED
4. Resistor 220 Ohm
5. Breadboard dan kabel jumper

## Konfigurasi GPIO

| Komponen | GPIO |
|---|---|
| DHT22 DATA | GPIO 4 |
| LED | GPIO 18 |

## Fitur Sistem

- Monitoring suhu ruangan.
- Monitoring kelembapan udara.
- Koneksi Wi-Fi melalui hotspot HP.
- Auto-reconnect Wi-Fi.
- Indikator LED otomatis berdasarkan suhu.

## Teknologi

- Arduino IDE 2.3.10
- ESP32
- Bahasa pemrograman C/C++
- Library WiFi.h
- Library DHT.h

## Dokumentasi

Dokumentasi lengkap mengenai deskripsi komponen dan alur kerja sistem tersedia pada folder `documentation`.

## Pengembang

Mahasiswa Program Studi Teknologi Informasi  
Fakultas Sains dan Teknologi  
UNISA

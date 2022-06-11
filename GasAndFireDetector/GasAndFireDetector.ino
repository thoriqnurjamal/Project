/*
 Thoriq Nur Jamal
 06/2022

 Sistem Pendeteksi Kebakaran Berbasis ESP8266 Dan Blynk App

 NodeMCU ESP8266 <=> Sensor MQ2 dan Flame Sensor

 Platform:
 Arduino IDE

 Catatan:
 Hati-hati wiring.
 Jika didapatkan nilai tidak rasional, coba untuk dikalibrasi.

 Referensi:
 [1] Sritu Hobby, "How to make a IoT based gas leakage monitoring system With Nodemcu and Blynk," Sritu Hobby, 13 May 2021.
 [2] Sritu Hobby, "IoT based fire alarm system using Nodemcu ESP8266 and Blynk," Sritu Hobby, 21 April 2021.
 [3] IoT Starters, "IoT based Fire Security Alarm System using NodeMCU," IoT Starters, 04 May 2021.
*/
#define BLYNK_PRINT Serial //Untuk mendefinisi serial blynk 
#include <ESP8266WiFi.h> //Memanggil Library ESP8266
#include <BlynkSimpleEsp8266.h> //Memanggil Library Blynk App


char auth[] = "UnS-zWtetYc3xmsebBBKGYkHMlc_pXNc";//Masukkan auth token yang ada di blynk untuk mendeklarasikan dan menyambungkan ke template app blynk
char ssid[] = "HUAWEI-gn32";//Masukkan nama WIFI untuk mengkoneksikan esp8266 dengan wifi 
char pass[] = "4hrD4Rm5";//Masukkan WIFI password untuk mengkoneksikan esp8266 dengan wifi

BlynkTimer timer; //Mengirimkan waktu dan menentukan seberapa sering mengirim data ke app blynk


// Define component pins
#define Buzzer D1 //Untuk mendefinisikan pin untuk buzzer
#define MQ2 A0 //Untuk mendefinisikan pin untuk sensor MQ2
#define Flame D0 //Untuk mendefinisikan pin untuk flame sensor
#define LED D2 //Untuk mendefinisikan pin untuk LED


void setup() {
  Serial.begin(9600); //Menentukan kecepatan dan penerimaan data
  pinMode(Buzzer, OUTPUT); //Mengkonfigurasi pin buzzer sebagai output
  pinMode(Flame, INPUT); //Mengkonfigurasi pin flame sebagai input
  pinMode(LED, OUTPUT); //mengkonfigurasi pin LED sebagai output
  digitalWrite(LED, HIGH); //menyalakan led
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80); //menyambungkan ke blynk cloud

//Call the functions
  timer.setInterval(100L, gassensor); //Memanggil fungsi dari gas sensor tiap beberapa detik 
  timer.setInterval(100L, flame); //Memanggil fungsi dari gas sensor tiap beberapa detik
}



//Get the MQ2 sensor values
void gassensor() {
  int value = analogRead(MQ2); //Memasukkan nilai dan mengubah analog menjadi digital
  Serial.println(value);
  value = map(value, 0, 1024, 0, 100); //mengetahui berapa nilai dari sensor MQ2 
  if (value <= 50) {
    digitalWrite(Buzzer, LOW); //Mematikan buzzer saat keadaan low dan nilai gas kurang dari 50
    
  } else if (value > 50) {
    Blynk.notify("Bahaya! Gas Bocor"); //Menampilkan notifikasi
    digitalWrite(Buzzer, HIGH); { //Menyalakan buzzer saat keadaan high dan nilai gas lebih dari 50
    digitalWrite(LED, LOW); //mematikan led dengan delay 100 milisecond
      delay(100);
      digitalWrite(LED, HIGH); //menyalakan led dengan delay 100 milisecond
      delay(100);
    }
  }
  Blynk.virtualWrite(V1, value); //Inisialisasi virtual pin

}

//Get the Flame Sensor value
void flame() {
  int value = digitalRead(Flame); //Memasukkan nilai dan membaca pin dari flame sensor
    if (value == 0) { //memberi nilai 0
      digitalWrite(Buzzer, HIGH); { ///Menyalakan buzzer saat keadaan high dan nilai gas 0
      digitalWrite(LED, LOW); //mematikan led dengan delay 100 milisecond
      delay(100);
      digitalWrite(LED, HIGH); //menyalakan led dengan delay 100 milisecond
      delay(100);
      }
      Blynk.notify("Bahaya! Ada Api"); //Menampilkan notifikasi pada aplikasi blynk
    } else if (value == 1) {
      digitalWrite(Buzzer, LOW); //Mematikan buzzer saat keadaan low dan nilai gas 1
      
    }
  Blynk.virtualWrite(V2, value); //Inisialisasi virtual pin
}

void loop() {
  Blynk.run();//Run the Blynk library
  timer.run();//Run the Blynk timer
}

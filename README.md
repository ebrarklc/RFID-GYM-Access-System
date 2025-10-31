# 🏋️‍♀️ RFID Tabanlı Akıllı Spor Salonu Sistemi

Bu proje, **ESP32** tabanlı bir **RFID erişim sistemi** ile spor salonu girişlerini otomatik olarak kaydeden ve kullanıcıya anlık geri bildirim veren akıllı bir turnike prototipidir.  
Proje, hem **donanım** hem de **yazılım** bileşenlerinden oluşan kapsamlı bir sistemin parçasıdır.

---

## 🚀 Proje Özeti

Spor salonuna girişlerde RFID kart kullanılarak kullanıcı kimliği doğrulanır.  
Sisteme kayıtlı kullanıcıların kartları okutulduğunda:

- LCD ekranda **“Hoşgeldiniz [isim]”** mesajı görüntülenir 🖥️  
- **Yeşil LED** yanar 💡  
- **Buzzer** kısa bir bip sesi çıkarır 🔊  
- Giriş yetkisi olmayan kartlarda **Kırmızı LED** yanar ve “Erişim reddedildi!” mesajı görünür. 🚫  

Sistem, daha sonra web ve mobil uygulama ile entegre edilmek üzere tasarlanmıştır.  
(Backend: Spring Boot, Frontend: React, Mobil: React Native)

---

## ⚙️ Donanım Bileşenleri

| Bileşen | Açıklama |
|----------|----------|
| **ESP32** | Ana denetleyici (Wi-Fi + Bluetooth destekli) |
| **RFID RC522** | Kart UID okuma modülü |
| **LCD 16x2 (I2C modüllü)** | Kullanıcı ismi ve mesajların görüntülendiği ekran |
| **Buzzer (3 pinli)** | Sesli bildirim |
| **LED (Kırmızı & Yeşil)** | Görsel bildirim |
| **Breadboard + Jumper Kabloları** | Devre bağlantısı |

---

## 🔌 Devre Bağlantıları

### 🔹 RFID RC522 ↔️ ESP32
| RC522 | ESP32 Pin |
|-------|------------|
| SDA | GPIO 2 |
| SCK | GPIO 18 |
| MOSI | GPIO 23 |
| MISO | GPIO 19 |
| RST | GPIO 4 |
| 3.3V | 3.3V |
| GND | GND |

### 🔹 LCD (I2C) ↔️ ESP32
| LCD | ESP32 Pin |
|------|------------|
| SDA | GPIO 21 |
| SCL | GPIO 22 |
| VCC | 5V |
| GND | GND |

### 🔹 LED ve Buzzer
| Eleman | ESP32 Pin |
|---------|------------|
| Yeşil LED | GPIO 25 |
| Kırmızı LED | GPIO 26 |
| Buzzer | GPIO 27 |

---

## 💻 Arduino IDE Gerekli Kütüphaneler

Projeyi derlemeden önce aşağıdaki kütüphanelerin kurulu olduğundan emin olun:

- `MFRC522` — RFID kart okuyucu için  
- `LiquidCrystal_I2C` — LCD ekran kontrolü için  
- `Wire` — I2C haberleşmesi için  

Kurulum:  
Arduino IDE → **Sketch → Include Library → Manage Libraries…**  
ve bu kütüphaneleri aratıp kurun.

---

## 🔧 Kod Özeti

- Her RFID kartın kendine ait bir UID’si vardır.  
- Kodda her UID’ye karşılık gelen kullanıcı tanımlanmıştır.  
- Yetkisiz kart okutulursa sistem “Erişim reddedildi!” mesajı verir.  

Örnek:
```cpp
if (uid == "F0FD9A7C") isim = "Ebrar Kilic";
else if (uid == "873B5CED") isim = "Gulsum Sahin";

# NodeMCU - Web server s AP - načítání a zobrazování hodnot z meteostanice
![](https://github.com/lukastrkan/epo_esp8266/blob/master/img/index.png)

## Použité knihovny

 - Wire
 - Adafruit Senzor
 - Adafruit BME280
 - ESP8266 Wifi
 - ESP8266 Web server

## Popis aplikace
ESP spustí přístupový bod s názvem ESP8266 a přístupovým heslem 12345678. Uživatel musí pro připojení nastavit na zařízení statickou IP ze sítě 10.0.0.0/24. Adresu 10.0.0.1 používá ESP.
Pokud se uživatel připojí na webserver, zobrazí se mu tři hodnoty, které jsou periodicky aktualizovány(1s).

## Použité komponenty

 - Lolin new NodeMCU v3 (ESP8266)
 - BME/BMP280 (I2C)

## Zapojení
![](https://github.com/lukastrkan/epo_esp8266/blob/master/img/esp.jpg)



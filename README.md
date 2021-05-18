# PlantWeather
![Key Visual](https://raw.githubusercontent.com/nikcani/plant-weather/main/docs/key-visual/key-visual.png)

## Nie wieder Pflanzen vergessen
- Eine Messstation misst die Temperatur (evtl. auch Humidity) eine Ortes, an dem Pflanzen groß gezogen werden oder generell wachsen.
- Wenn die Temperatur einen (konfigurierbaren) Schwellwert unterschreitet werden die Bewohner im Innenraum informiert (LED & Notification am Handy) und können die Pflanzen an einen wärmeren Ort stellen.
- Außerdem können die Messdaten per Taster und Display erfragt werden bei Bedarf.
- Evtl. wird für die Messung im Außenbereich eine alte Radiosonde (Serial Interface über einen ESP8266) verwendet.

## Komponenten
### Short
- Sensoren
  - Temperatursensor
  - Taster
  - evtl. Feuchtigkeitssensor
- Aktoren
  - Display
  - verschiedene Endgeräte mit E-Mail Client

![Components](https://raw.githubusercontent.com/nikcani/plant-weather/main/docs/components/components.png)

### Long
- Messstation
  - Hardware
    - entweder ESP32 mit Sensordaten über das serielle Interface einer refurbished Radiosonde
    - oder ESP32 mit Temperatursensor und evlt. Feuchtigkeitssensor
  - sendet Messdaten regelmäßig via HTTP an die Indoor Station
- Indoor Station
  - Hardware
    - ESP32
    - Taster
      - stellt Schwellenwert ein
      - aktiviert Display
    - Display
      - Anzeige der aktuellen Messdaten
    - LED
      - blinkt bei aktiven Warnungen
  - Software
    - REST API: speichert erhaltene Messdaten
    - SMTP Client sendet Warnung an SMTP Relay
      - Warnung bei Unterschreitung des Schwellenwertes
      - Warnung wenn die Messstation zu lange keine Messdaten mehr gesendet hat
- Endgeräte der Nutzer
  - Hardware
    - Smartphone
    - Tablet
    - Heimcomputer
    - usw.
    - jedes Endgerät das Push Benachrichtigungen von empfangenen E-Mails anzeigen kann
  - Software
    - keine Implementierung auf unterschiedlichen Endgeräten notwendig
- Cloud E-Mail Relay
  - SMTP Relay Server
  - stellt zuverlässigen E-Mail Versand sicher
- Service: Registrierte Domain
  - SPF Eintrag mit IP des E-Mail Relays

## Mögliche Ausbaustufen
- Fenster/Tür im Gewächshaus öffnen/schließen
- Heizung einschalten im Gewächshaus

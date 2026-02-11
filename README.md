# SIMA 26 - Differential Robot Drive Control with Feedback Loop

Dieses Projekt implementiert eine streckenbasierte Fahrsteuerung für einen Differentialroboter mit zwei SCServo-Motoren.  
Der Roboter dient als Testobjekt zur Erprobung von Odometrie und automatischer Motorsynchronisation.

## Features

- Fahren definierter Strecken in Zentimetern
- Odometrie über Servo-Encoder (4096 Ticks/Umdrehung)
- Automatische Anpassung der Motorgeschwindigkeit
- Encoder-Wrap-Around-Korrektur
- Einfache Drehfunktion (zeitbasiert)

## Hardware

- Differentialroboter mit zwei angetriebenen Rädern
- SCServo-Motoren  
  - Rechter Motor: ID 4  
  - Linker Motor: ID 5  

## Automatische Motorsynchronisation

Während der Fahrt werden die Encoderpositionen beider Räder kontinuierlich ausgewertet.  
Aus der Differenz der zurückgelegten Encoder-Ticks wird ermittelt, welches Rad vorausläuft.

Ein proportionaler Regler passt die Geschwindigkeit der Motoren dynamisch an:

- Das vorauslaufende Rad wird verlangsamt
- Das zurückliegende Rad wird beschleunigt

Dadurch fährt der Roboter auch bei unterschiedlichen Motor- oder Lastbedingungen möglichst geradeaus.  
Die Regelung basiert auf realer Position (Encoder), nicht auf Zeit.

## Odometrie

Die zurückgelegte Strecke wird aus dem Raddurchmesser und der Encoderauflösung berechnet.  
Encoder-Überläufe (0–4095) werden automatisch korrigiert.

## Nutzung

```cpp
driveDistance(100, 1500); // fährt 100 cm
turn(true, 90);          // dreht ca. 90° nach rechts
```
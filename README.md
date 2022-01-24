# Synology-NAS-Switcher

Stand: 24.1.2022

24.1.2022\
Dies ist ein Webserver mit welchem es möglich ist eine NAS von Synology aus der Ferne ein- und auszuschalten. Dies wird mit einem Arduino Nano realisiert. Dieser wird über ein Ethernet-Kabel an das lokale Netzwerk angebunden. Über ein Relai am Arduino wird der Power-Schalter der Synology-NAS für zwei Sekunden betätigt. Es ist ein Bild des Schaltungsausbaus angehängt. Der Webserver schaltet Pin2 am Arduino, an welchem ein Relai verkabelt ist. Die Verkabelung zwischen Arduino und dem W5500 Ethernet-Shield ist unten gelistet. Der Code ist mit der Arduino-Entwicklungsumgebung geschrieben und als *.ino abgespeichert.

Webserver:\
Der Code hat eine feste IP-Konfig:
IP 192.168.0.250\
Gateway 192.168.0.253\
Subnet 255.255.255.0\

An das Netzwerk ist der Webserver angebunden mit einem W5500 Ethernet-Shield.
Elektronisch wird der Arduino und der W5500 wie folgt angebunden:\
Arduino - - - W5500\
3,3V        3,3V\
oder\
5,0V        5,0V\
\
GND   ---     GND\
13    ---     SCLK\
12    ---     MISO\
11    ---     MOSI\
10    ---     SCSn\
Reset ---     Reset\

Das Projekt basiert auf meinem älteren Projekt Zentralheizung-Webserver (https://github.com/quiddi-github/Zentralheizung-Webserver). Das Projekt Zentralheizung-Webserver ist entstanden aus dem Projekt von Salvatore Fancello, welches auf der Webseite http://progettiarduino.com zu finden ist.
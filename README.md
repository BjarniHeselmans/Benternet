# ZeroMQ Client - Send & Response

Dit project bevat een Client Send en Client Response applicatie die communiceren via ZeroMQ met de Benternet-server. De Client Send verstuurt verzoeken, en de Client Response verwerkt deze en stuurt een antwoord terug.

## Installatie van ZeroMQ en cppzmq

Voor **MSYS2** (MinGW):
```ssh
pacman -S mingw-w64-x86_64-zeromq mingw-w64-x86_64-cppzmq
````
Voor **Linux** (Ubuntu):
```ssh
sudo apt update
sudo apt install libzmq3-dev libczmq-dev
```
## Code compileren

Voor **Windows** (MinGW):
```ssh
g++ Service.cpp -o Service.exe -IC:\msys64\mingw64\include -LC:\msys64\mingw64\lib -lzmq
g++ client.cpp -o Service.exe -IC:\msys64\mingw64\include -LC:\msys64\mingw64\lib -lzmq
```
Voor **Linux:**
```ssh
g++ service.cpp -o service -lzmq
g++ client.cpp -o client -lzmq
```
## Uitvoeren

Eerst de **Client Response** starten:
```ssh
./Service
```
Daarna de **Client Send** met een topic en gebruikersnaam:
```ssh
./Client BjarniDobbelsteen Gebruiker123
```
De response wordt automatisch verwerkt en weergegeven in de console.

## Mogelijke fouten en oplossingen

1. zmq.hpp: No such file or directory→ Controleer of cppzmq correct is geïnstalleerd.→ Gebruik de juiste include path: -I/mingw64/include of /usr/include/cppzmq.

2. error while loading shared libraries: libzmq.dll not found→ Voeg mingw64/bin toe aan je PATH-variabele.→ Kopieer libzmq.dll naar de map met je uitvoerbare bestanden.

## Werking

1. Client Send verstuurt een bericht via PUSH naar benternet.pxl-ea-ict.be:24041.

2. Client Response luistert naar verzoeken en stuurt een willekeurig getal (1-6) terug.

3. Client Send ontvangt de response via SUB en print het resultaat.

Dit project maakt gebruik van Benternet, een ZeroMQ-gebaseerd netwerk voor berichtenverkeer.

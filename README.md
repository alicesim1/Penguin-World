# Penguin-World
Proyecto indie retro game: para SEGA Mega Drive/Genesis, creado con SGDK

Redes sociales:
https://twitter.com/Alice_Sim1
https://www.youtube.com/user/simulatorone/

Error desconocido al compilar:
```
out/src/zone-jugpri.o (symbol from plugin): In function `jugcontrol':
(.text+0x0): multiple definition of `randomInRangeU8'
out/src/main.o (symbol from plugin):(.text+0x0): first defined here
out/src/zone-jugpri.o (symbol from plugin): In function `jugcontrol':
(.text+0x0): multiple definition of `randU16'
out/src/main.o (symbol from plugin):(.text+0x0): first defined here
out/src/zone-jugpri.o (symbol from plugin): In function `jugcontrol':
(.text+0x0): multiple definition of `VDP_drawInt'
out/src/main.o (symbol from plugin):(.text+0x0): first defined here
out/src/zone-jugpri.o (symbol from plugin): In function `jugcontrol':
(.text+0x0): multiple definition of `inputHandler'
out/src/main.o (symbol from plugin):(.text+0x0): first defined here
```

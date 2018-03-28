Memory
======
Die Simulationsumgebung und der simulierte Mikroprozessor teilen sich einen Speicher mit dem Adressraum von 0x00000000 bis 0xFFFFFFFF.

In der nachstehenden Tabelle ist aufgeführt, wie der Speicher eingeteilt ist. Die Spalte "User" steht für den Simulierten Prozessor mitsamt dem vom User geschrieben Code. Die Spalte "SimulationCode" beschreibt, welches Modul der Simulation dort Speicher belegt.


User | Adresse | Size | SimulationCode
-- |            | -
                        | 0x00000000 ||
ROM (main.c)            | 0x08000000 | 0x00100000|
RAM                     | 0x20000000 | 0x00020000|
memorymapped Periph.    | 0x40000000 | 0x20000000|
                        | 0x90000000 | 0x000002f3 | TFT_DISPLAY
                        | 0x900002f4 | 0x00000100 | LED_DISPLAY
                        | 0x93000000 | 0x00000500 | TIMER
                        | 0x91000000 | 0x00000100 | ONEWIRE
FSMC                    | 0xA0000000 ||
DEBUGGING MCU           | 0xE0042000 ||

# SuperSimpleKeyLogger

Super Simple Key Logger is a minimal Windows application designed to capture and display keystrokes in real time using a low-level keyboard hook. It intercepts keyboard events via the Windows API, translates them into Unicode characters, and outputs them to the console. This project is provided as a simple demonstration of how to use Windows hooks to monitor keyboard input. Only tested on windows 10 and 11.

## Build Instructions

To build with Visual Studio:
1. Open the project/solution in Visual Studio 2022
2. Use `Ctrl + B` shortcut or Build -> Build SuperSimpleKeyLogger

To build with MSYS2 GCC:
```bash
gcc SuperSimpleKeyLogger.c -o SuperSimpleKeyLogger
```

To build with MSVC:
```bash
cl SuperSimpleKeyLogger.c
```

## Usage

Either double-click the executable or run the following in Command Prompt:
```bash
.\SuperSimpleKeyLogger.exe
```

## Disclaimer

This is intended for educational purposes only. I assume no responsibility for misuse of this software.
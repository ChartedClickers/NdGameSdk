# NdGameSdk
A ModSDK for NdGames, providing additional features and APIs for custom development and game engine control.
This project is currently in the alpha stage and under active development. Expect changes and experimental features. Work In Progress.

## Install

1. Download the latest release from the [Releases](https://github.com/ChartedClickers/NdGameSdk/releases/latest) page.
2. Choose the appropriate folder for your game version:
   - `T2R/` — for The Last of Us Part II Remastered
   - `T1X/` — for The Last of Us Part I
3. From the selected folder, copy the following files into the game directory:
   - `*.ModClient.asi` — the main injection entry point
   - `NdGameSdk.dll` — the core SDK runtime
4. Install the contents of the `ASI_Loader_x64/` folder into the same game root directory.  
   This is required to enable ASI plugin loading via [Ultimate ASI Loader](https://github.com/ThirteenAG/Ultimate-ASI-Loader).

## NdGameSdk

NdGameSdk is the core development kit that provides a unified and extensible API layer for interacting with NdGameEngine and SDK.

### Components & Features

- Includes:
  - T2RSDK — SDK layer for The Last of Us Part II Remastered
  - T1XSDK — SDK layer for The Last of Us Part I
- Core features:
  - ND DevMode — base developer menu
  - ExtendedDebugMenu — on allocated DebugMemory
  - PrimServer

## ND.ModClient

ND.ModClient is the RuntimeInjection layer that enables mod capabilities inside the game process.
- Includes:
  - T2R.ModClient — ModClient layer for The Last of Us Part II Remastered
  - T1X.ModClient — ModClient layer for The Last of Us Part I

Currently a work in progress and undergoing migration from [T1X.ModClient (Legacy)](https://github.com/ChartedClickers/T1X.ModClient) into a new, cleaner architecture and fresh modular design.
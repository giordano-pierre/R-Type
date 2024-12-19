# R-Type

## What is R-Type?

**R-Type** is an iconic arcade game developed by Irem in 1987. This **horizontal scrolling shoot 'em up** places the player in the cockpit of a spacecraft, the **R-9 Arrowhead**, to combat the extraterrestrial threat known as the **Bydo Empire**.

## Technologies Used

- **Programming Languages:** Python and C++
- **Graphics Library:** [SFML](https://www.sfml-dev.org/)
- **Audio Management:** Integrated via SFML

Feel free to check our [Technical and Comparative study](doc/TechnicalStudy)!

## Project Architecture
![Alt text](/doc/archi.png "project architecture")

## How to Play?

### Prerequisites

- **Install Python**
  - **Ubuntu**:
    ```bash
    sudo apt update && sudo apt install python3
    ```
  - **Fedora**:
    ```bash
    sudo dnf install python3
    ```
  - **Arch Linux**:
    ```bash
    sudo pacman -S python
    ```
  - **Windows**:
    - Visit the official [Python](https://www.python.org/) website and download the installer.

- **Install Make**
  - **Ubuntu**:
    ```bash
    sudo apt install make
    ```
  - **Fedora**:
    ```bash
    sudo dnf install make
    ```
  - **Arch Linux**:
    ```bash
    sudo pacman -S make
    ```
  - **Windows**:
    - Install [Make for Windows](http://gnuwin32.sourceforge.net/packages/make.htm) or use a platform like MinGW.

- **Install CMake**
  - **Ubuntu**:
    ```bash
    sudo apt install cmake
    ```
  - **Fedora**:
    ```bash
    sudo dnf install cmake
    ```
  - **Arch Linux**:
    ```bash
    sudo pacman -S cmake
    ```
  - **Windows**:
    - Download CMake from the official [CMake](https://cmake.org/download/) website and follow the installation instructions.

- **Install Boost:Asio**
  - **Ubuntu**:
    ```bash
    sudo apt install libboost-all-dev
    ```
  - **Fedora**:
    ```bash
    sudo dnf install boost-devel
    ```
  - **Arch Linux**:
    ```bash
    sudo pacman -S boost
    ```
  - **Windows**:
    - Download Boost from the official [Boost](https://www.boost.org/users/download/) website and follow the installation instructions.

### Installation and Launch

1. **Clone the repository:**
    ```bash
    git clone https://github.com/your-repo/rtype-remake.git
    ```

2. **Install dependencies:**
    ```bash
    python3 install.py
    ```

3. **Compilation (Linux only):**
    ```bash
    make
    ```
    - On Windows, the compiled file will be located directly at the root of the project.

4. **Run the server and client:**
    - **Server:**
      ```bash
      ./server
      ```
    - **Client:**
      ```bash
      ./client
      ```

    - If the server is on another PC, specify the server's IP address when launching the client.

### In-Game Commands

- **Arrow keys:** Move the spacecraft
- **Spacebar:** Fire
- **D key:** Toggle colorblind mode
- **Escape key:** Quit the game

The keys can be modified in the settings.

[Documentation for the Game Engine](doc/ECS.md)

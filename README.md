# R-Type

## Qu'est-ce que R-Type ?

Le **R-Type** est un jeu d'arcade emblématique développé par Irem en 1987. Ce **shoot 'em up à défilement horizontal** place le joueur dans le cockpit d'un vaisseau spatial, le **R-9 Arrowhead**, pour combattre la menace extraterrestre connue sous le nom de **Bydo Empire**.

## Technologies utilisées

- **Langages de programmation :** Python et C++
- **Bibliothèque graphique :** [SFML](https://www.sfml-dev.org/)
- **Gestion audio :** Intégrée via SFML

N'hésitez pas a consulter notre [Technical and Comparative study](doc/TechnicalStudy) !

## Architecture du projet
![Alt text](/doc/archi.png "project architecture")


## Comment jouer ?

### Pré-requis

- **Avoir Python installé**
  - **Ubuntu** :
    ```bash
    sudo apt update && sudo apt install python3
    ```
  - **Fedora** :
    ```bash
    sudo dnf install python3
    ```
  - **Arch Linux** :
    ```bash
    sudo pacman -S python
    ```
  - **Windows** :
    - Rendez-vous sur le site officiel [Python](https://www.python.org/) et téléchargez le programme d'installation.

- **Avoir Make installé**
  - **Ubuntu** :
    ```bash
    sudo apt install make
    ```
  - **Fedora** :
    ```bash
    sudo dnf install make
    ```
  - **Arch Linux** :
    ```bash
    sudo pacman -S make
    ```
  - **Windows** :
    - Installez [Make for Windows](http://gnuwin32.sourceforge.net/packages/make.htm) ou utilisez une plateforme comme MinGW.

- **Avoir CMake installé**
  - **Ubuntu** :
    ```bash
    sudo apt install cmake
    ```
  - **Fedora** :
    ```bash
    sudo dnf install cmake
    ```
  - **Arch Linux** :
    ```bash
    sudo pacman -S cmake
    ```
  - **Windows** :
    - Téléchargez CMake à partir du site officiel [CMake](https://cmake.org/download/) et suivez les instructions d'installation.

- **Avoir Boost:Asio installé**
  - **Ubuntu** :
    ```bash
    sudo apt install libboost-all-dev
    ```
  - **Fedora** :
    ```bash
    sudo dnf install boost-devel
    ```
  - **Arch Linux** :
    ```bash
    sudo pacman -S boost
    ```
  - **Windows** :
    - Téléchargez Boost à partir du site officiel [Boost](https://www.boost.org/users/download/) et suivez les instructions d'installation.

### Installation et lancement

1. **Clonez le dépôt :**
    ```bash
    git clone https://github.com/votre-repo/rtype-remake.git
    ```

2. **Installez les dépendances :**
    ```bash
    python3 install.py
    ```

3. **Compilation (Linux uniquement) :**
    ```bash
    make
    ```
    - Sur Windows, le fichier compilé se trouvera directement à la racine du projet.

4. **Exécutez le serveur et le client :**
    - **Serveur :**
      ```bash
      ./server
      ```
    - **Client :**
      ```bash
      ./client
      ```

    - Si le serveur est sur un autre PC, indiquez l'adresse IP du serveur lors du lancement du client.

### Commandes dans le jeu

- **Flèches directionnelles :** Déplacer le vaisseau
- **Barre d'espace :** Tirer
- **Touche D :** Activer/désactiver le mode pour daltoniens
- **Touche Échap :** Quitter le jeu

Les touches sont modifiables dans les paramètres.


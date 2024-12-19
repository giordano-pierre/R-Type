#!/usr/bin/python3

import os
import platform
import subprocess
import shutil

def get_os_system():
    os_system = platform.system()
    if os_system == "Linux":
        return "LINUX"
    elif os_system in ["Windows", "Microsoft"]:
        return "WINDOWS"
    else:
        return "NONE"

def install_linux_dependencies():
    """Installe les dépendances système requises pour SFML selon le gestionnaire de paquets."""
    print("Installation des dépendances système requises...")
    try:
        if shutil.which("apt"):
            print("Utilisation de apt pour installer les dépendances (Debian/Ubuntu).")
            subprocess.run([
                "sudo", "apt", "install", "-y",
                "libx11-dev", "libxrandr-dev", "libxcursor-dev", "libxi-dev",
                "libudev-dev", "libgl1-mesa-dev", "ninja-build",
                "autoconf", "automake", "libtool", "pkg-config"
            ], check=True)
        elif shutil.which("dnf"):
            print("Utilisation de dnf pour installer les dépendances (Fedora/RedHat).")
            subprocess.run(["sudo", "dnf", "install", "-y",
                            "libX11-devel", "libXrandr-devel", "libXcursor-devel",
                            "libXi-devel", "systemd-devel", "mesa-libGL-devel",
                            "ninja-build", "autoconf", "automake", "libtool", "pkgconf"
            ], check=True)
        elif shutil.which("pacman"):
            print("Utilisation de pacman pour installer les dépendances (Arch Linux).")
            subprocess.run(["sudo", "pacman", "-Syu", "--noconfirm"], check=True)
            subprocess.run([
                "sudo", "pacman", "-S", "--noconfirm",
                "libx11", "libxrandr", "libxcursor", "libxi",
                "libsystemd", "mesa", "ninja", "autoconf", "automake", "libtool", "pkgconf"
            ], check=True)
        else:
            print("Aucun gestionnaire de paquets compatible trouvé. Système non pris en charge.")
            exit(1)
    except subprocess.CalledProcessError as e:
        print(f"Erreur lors de l'installation des dépendances système : {e}")
        exit(1)

def run_vcpkg():
    """Clone et configure vcpkg pour SFML et autres bibliothèques."""
    if not os.path.exists("vcpkg"):
        print("Clonage de vcpkg...")
        subprocess.run(["git", "clone", "https://github.com/microsoft/vcpkg.git"], check=True)
        subprocess.run(["./vcpkg/bootstrap-vcpkg.sh"], check=True)
    else:
        print("vcpkg existe déjà. Mise à jour...")
        subprocess.run(["git", "-C", "vcpkg", "pull"], check=True)
        subprocess.run(["./vcpkg/bootstrap-vcpkg.sh"], check=True)

    os.chdir("vcpkg")
    subprocess.run([
        "./vcpkg", "install",
        "sfml", "nlohmann-json", "boost-asio", "boost-uuid"
    ], check=True)
    subprocess.run(["./vcpkg", "integrate", "install"], check=True)
    os.chdir("..")

def build_project():
    """Configure et construit le projet avec CMake."""
    subprocess.run([
        "cmake", "-B", "./build",
        "-DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake"
    ], check=True)
    subprocess.run(["cmake", "--build", "./build"], check=True)

def main():
    os_system = get_os_system()
    if os_system == "LINUX":
        if os.getenv("GITHUB_ACTIONS") == "true":
            print("Exécution dans un pipeline GitHub Actions.")
        else:
            print("Exécution sur une machine locale Linux.")
        install_linux_dependencies()
        run_vcpkg()
        build_project()
    elif os_system == "WINDOWS":
        run_vcpkg()
        build_project()
    else:
        print("Système d'exploitation inconnu. Abandon.")
        exit(1)

if __name__ == "__main__":
    main()

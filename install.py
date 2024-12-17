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

def add_nlohmann_to_cmake(cmake_file):
    """Ajoute find_package et target_link_libraries pour nlohmann-json"""
    with open(cmake_file, "r") as file:
        lines = file.readlines()

    if any("nlohmann_json" in line for line in lines):
        print("nlohmann-json déjà présent dans le CMakeLists.txt.")
        return

    for index, line in enumerate(lines):
        if "project(" in line:
            lines.insert(index + 1, "find_package(nlohmann_json CONFIG REQUIRED)\n")
            break

    for index, line in enumerate(lines):
        if "add_executable(r-type_server" in line or "target_link_libraries(" in line:
            lines.insert(index + 1, "target_link_libraries(r-type_server PRIVATE nlohmann_json::nlohmann_json)\n")
            break

    with open(cmake_file, "w") as file:
        file.writelines(lines)

    print("nlohmann-json ajouté dans le CMakeLists.txt.")

def run_vcpkg_linux():
    """Configure et installe vcpkg avec SFML et autres bibliothèques"""
    if not os.path.exists("vcpkg"):
        print("Clonage de vcpkg...")
        subprocess.run(["git", "clone", "https://github.com/microsoft/vcpkg.git"], check=True)
        subprocess.run(["./vcpkg/bootstrap-vcpkg.sh"], check=True)
    else:
        print("vcpkg existe déjà. Bootstrap vcpkg...")
        subprocess.run(["./vcpkg/bootstrap-vcpkg.sh"], check=True)

    os.chdir("vcpkg")
    subprocess.run([
        "./vcpkg", "install",
        "sfml:x64-linux",
        "nlohmann-json:x64-linux",
        "boost-asio:x64-linux",
        "boost-uuid:x64-linux"
    ], check=True)
    subprocess.run(["./vcpkg", "integrate", "install"], check=True)
    os.chdir("..")

find_os = get_os_system()

if find_os == "LINUX":
    run_vcpkg_linux()

    add_nlohmann_to_cmake("CMakeLists.txt")

    subprocess.run([
        "cmake", "-B", "./build",
        "-DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake",
        "-DVCPKG_TARGET_TRIPLET=x64-linux"
    ], check=True)
    subprocess.run(["cmake", "--build", "./build"], check=True)

elif find_os == "WINDOWS":
    if not os.path.exists("vcpkg"):
        subprocess.run(["git", "clone", "https://github.com/microsoft/vcpkg.git"], check=True)
    subprocess.run([".\\vcpkg\\bootstrap-vcpkg.bat"], shell=True, check=True)
    os.chdir("vcpkg")
    subprocess.run([
        "./vcpkg", "install",
        "sfml",
        "nlohmann-json",
        "boost-asio",
        "boost-uuid"
    ], check=True)
    subprocess.run(["./vcpkg", "integrate", "install"], check=True)
    os.chdir("..")

    add_nlohmann_to_cmake("CMakeLists.txt")

    subprocess.run([
        "cmake", "-B", "./build",
        "-DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake"
    ], check=True)
    subprocess.run(["cmake", "--build", "build", "--config", "Release"], check=True)

else:
    print("Unknown OS. Cannot proceed.")
    exit(1)

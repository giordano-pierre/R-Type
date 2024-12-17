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

find_os = get_os_system()

if find_os == "LINUX":
    subprocess.run(["git", "clone", "https://github.com/microsoft/vcpkg.git"])
    subprocess.run(["./vcpkg/bootstrap-vcpkg.sh"])
    os.chdir("vcpkg")
    subprocess.run(["./vcpkg", "install", "sfml"])
    subprocess.run(["./vcpkg", "install", "nlohmann-json"])
    subprocess.run(["./vcpkg", "install", "boost-asio"])
    subprocess.run(["./vcpkg", "install", "boost-uuid"])
    subprocess.run(["./vcpkg", "integrate", "install"])
    os.chdir("..")
    subprocess.run(["cmake", "-B", "./build"])


elif find_os == "WINDOWS":
    subprocess.run(["git", "clone", "https://github.com/microsoft/vcpkg.git"])
    subprocess.run([".\\vcpkg\\bootstrap-vcpkg.bat"], shell=True)
    os.chdir("vcpkg")
    subprocess.run(["./vcpkg", "install", "sfml"])
    subprocess.run(["./vcpkg", "integrate", "install"])
    os.chdir("..")
    subprocess.run(["cmake", "-B", "./build"])
    subprocess.run(["cmake", "--build", "build", "--config", "Release"])

    if subprocess.run(["cmake", "--build", "build"]).returncode != 0:
        print("Build error: try again later")
        exit(1)
    shutil.copy("build/r-type_client", ".")
    shutil.copy("build/r-type_server", ".")

else:
    print(f"Unknown os")
    exit(1)

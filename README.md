# Worksheet 1 part 1

## Overview
This project demonstrates how to implement safe and persistent data storage on the Raspberry Pi Pico using its onboard flash memory. It includes a command-line interface that allows users to interact with the Pico’s flash memory using three core commands: read, write, and erase. This part is divided into two tasks: Task 1 implements the basic functionality of these commands, while Task 2 extends the system by introducing structured data storage with additional metadata.

## Getting started
To get a copy of the project up and running on your local machine, follow these instructions.

## Essentials
* Raspberry Pi Pico SDK installed and configured
* CMake (to generate the build system)
* Make (to build the project)
* USB connection to the Pico (For uploading .uf2 file)
* A serial terminal program to interact with the Pico’s CLI (e.g Tera Term)


## Initisialing the project environment
1. Clone the repository:
~~~bash
    git clone https://gitlab.uwe.ac.uk/q2-alhendi/cap_template.git
~~~
2. To build and compile task 1 follow these steps:
~~~bash
    cd cap_template # Navigate into project directory
    mkdir build  # Create a build directory     
    cd build # navigate into build directory
    cmake .. # Generate build files 
    make # Compile project
~~~
3. To build and compile task 2 follow these steps:
~~~bash
    cd cap_template # Navigate into project directory
    cd 
    mkdir build  # Create a build directory     
    cd build # navigate into build directory
    cmake .. # Generate build files 
    make # Compile project
~~~
## Task 1: 

### Elements 

### Make 

### Output 

## Task 2:
This task demonstartes extending the code so that it can send messages back to the client. 
### Elements (other than the ones mentioned in task 1)
* Messages printed on the client side 
### Make
To build the application:
~~~bash
make /server #to build server
make /client #to build client
~~~
### Output
On every client run a message is printed showing the ip address of the server:
![alt text](image-4.png)
This indicates that the echoing is successful.

# Fast Robot Interface
The Fast Robot Interface library allows for hard real time communication to the KUKA LBR Med, see KUKA's [paper](http://www.best-of-robotics.org/pages/publications/KUKA_FRI_from_WS_Proceedings_ICRA2010.pdf). This folder contains the C++ client side library to setup the UDP connection to the LBR Med. However, hard real time is only supported if the FRI is compiled on a real time OS.

**TODO** Real time system support?
## Build and Installation
Other than what KUKA provides, our FRI comes with CMake support. This allows for cross-platform compatability. The build and installation steps for Linux, and Windows, are listed below.
### Linux and Windows
**TODO** explain prerequisites. 

**TODO** Windows: new windows terminal, choco, git, cmake

**TODO** Linux: git, cmake

Clone this repository
```shell
git clone https://github.com/KCL-BMEIS/FastRobotInterface.git
```
Build and install the FRI library
```shell
cd FastRobotInterface
mkdir build && cd build
cmake ..
cmake --build # builds the FRI library
cmake --install # installs the FRI library
```
## Usage
The FRI runs Java on the server side, which is the robot controller. 

### Prerequisites
Follow the Build and Installation instructions for your OS.

**TODO** installation of Sunrise Workbench

**TODO** build the apps

### Execute an App
**TODO** explain usage of SmartHMI

**TODO** explain how to run

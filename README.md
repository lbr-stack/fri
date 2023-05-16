# Fast Robot Interface
The Fast Robot Interface (FRI) library allows for hard real time communication to the KUKA LBRs, see KUKA's [paper](http://www.best-of-robotics.org/pages/publications/KUKA_FRI_from_WS_Proceedings_ICRA2010.pdf). This folder adds CMake support to KUKA's FRI.

## Build
To build, run

```shell
cmake -B build -DCMAKE_BUILD_TYPE=Release -DBUILD_FRI_APPS=ON
cmake --build build
```

## Run the Apps
To run the example applications, run

```shell
./build/LBRJointSineOverlayApp
```

On the `smartPAD`, run the `LBRJointSineOverlay` application. You should see the robot execute a sine wave.

## Contributing
Do you use a different FRI version?
- Fork this repository.
- Create a branch fri-major.minor (e.g. fri-1.15).
- Replace `FRI-Client-SDK_Cpp_v1.15.zip` with your client SDK as extracted from `KUKA Sunrise Workbench`.
- Open a pull request.

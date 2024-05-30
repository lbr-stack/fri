# fri
This folder adds CMake support to KUKA's Fast Robot Interface (FRI).

| FRI Version | Build Status |
| ----------- | ------------ |
| `1.11`      | [![Build status](https://github.com/lbr-stack/fri/actions/workflows/build.yaml/badge.svg?branch=fri-1.11)](https://github.com/lbr-stack/fri/actions/workflows/build.yaml) |
| `1.14`      | [![Build status](https://github.com/lbr-stack/fri/actions/workflows/build.yaml/badge.svg?branch=fri-1.14)](https://github.com/lbr-stack/fri/actions/workflows/build.yaml) |
| `1.15`      | [![Build status](https://github.com/lbr-stack/fri/actions/workflows/build.yaml/badge.svg?branch=fri-1.15)](https://github.com/lbr-stack/fri/actions/workflows/build.yaml) |
| `1.16`      | [![Build status](https://github.com/lbr-stack/fri/actions/workflows/build.yaml/badge.svg?branch=fri-1.16)](https://github.com/lbr-stack/fri/actions/workflows/build.yaml) |
| `2.5`       | [![Build status](https://github.com/lbr-stack/fri/actions/workflows/build.yaml/badge.svg?branch=fri-2.5)](https://github.com/lbr-stack/fri/actions/workflows/build.yaml)  |
| `2.7`       | [![Build status](https://github.com/lbr-stack/fri/actions/workflows/build.yaml/badge.svg?branch=fri-2.7)](https://github.com/lbr-stack/fri/actions/workflows/build.yaml)  |

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

1. Fork this repository.
2. Replace `FRI-Client-SDK_Cpp.zip` with your client SDK as extracted from `KUKA Sunrise Workbench`. Therefore (see images):
    * In the `Software` tab of `StationSetup.cat`, add `Fast Robot Interface Extension`.
    * Save via `ctrl+s`, click `Save and apply`.
    * Under `FastRobotInterface_Client_Source`, find `FRI-Client-SDK_Cpp.zip`.

  <figure>
    <p align="center"><img src="https://raw.githubusercontent.com/lbr-stack/fri/fri-1.15/img/00_extract_fri_client_sdk.png" width="25%" height="25%" hspace="20"><img   src="https://raw.githubusercontent.com/lbr-stack/fri/fri-1.15/img/01_extract_fri_client_sdk.png" width="25%" height="25%" hspace="20"><img src="https://raw.githubusercontent.com/lbr-stack/fri/fri-1.15/img/02_extract_fri_client_sdk.png" width="25%" height="25%" hspace="20"></p>
    <figcaption></figcaption>
  </figure>

3. Open an issue and ask for a branch named fri-major.minor (e.g. fri-1.15).
4. Open a pull request against this new branch.

## License
Please note that we distribute the CMake support under Apache-2.0 license. Please note that third party libraries under `FRI-Client-SDK_Cpp.zip` are distributed under their respective license. See [NOTICE](https://github.com/lbr-stack/fri/blob/fri-1.15/NOTICE).

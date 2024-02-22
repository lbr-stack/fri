# fri
[![Build status](https://github.com/lbr-stack/fri/actions/workflows/build.yaml/badge.svg?branch=fri-1.15)](https://github.com/lbr-stack/fri/actions/workflows/build.yaml)

This folder adds CMake support to KUKA's Fast Robot Interface (FRI).

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
    <p align="center"><img src="img/00_extract_fri_client_sdk.png" width="25%" height="25%" hspace="20"><img   src="img/01_extract_fri_client_sdk.png" width="25%" height="25%" hspace="20"><img src="img/02_extract_fri_client_sdk.png" width="25%" height="25%" hspace="20"></p>
    <figcaption></figcaption>
  </figure>

3. Open an issue and ask for a branch named fri-major.minor (e.g. fri-1.15).
4. Open a pull request against this new branch.

## License
Please note that we distribute the CMake support under Apache-2.0 license. Please note that third party libraries under `FRI-Client-SDK_Cpp.zip` are distributed under their respective license. See [NOTICE](NOTICE).

## Citation
If you enjoyed using this repository for your work, we would really appreciate ❤️ if you could cite it, as it helps us to continue offering support.

```
@misc{huber2023lbrstack,
      title={LBR-Stack: ROS 2 and Python Integration of KUKA FRI for Med and IIWA Robots}, 
      author={Martin Huber and Christopher E. Mower and Sebastien Ourselin and Tom Vercauteren and Christos Bergeles},
      year={2023},
      eprint={2311.12709},
      archivePrefix={arXiv},
      primaryClass={cs.RO}
}
```

## Acknowledgements
<img src="https://medicalengineering.org.uk/wp-content/themes/aalto-child/_assets/images/medicalengineering-logo.svg" alt="wellcome" height="45" width="65" align="left">

This work was supported by core and project funding from the Wellcome/EPSRC [WT203148/Z/16/Z; NS/A000049/1; WT101957; NS/A000027/1]. 

<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/b/b7/Flag_of_Europe.svg/1920px-Flag_of_Europe.svg.png" alt="eu_flag" height="45" width="65" align="left" >

This project has received funding from the European Union's Horizon 2020 research and innovation programme under grant agreement No 101016985 (FAROS project).

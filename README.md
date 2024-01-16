# GD-Hacks

Geometry Dash Cheat Menu

![Geometry Dash 16 01 2024 0_25_52](https://github.com/qwix456/gd-hacks/assets/104967297/06e91fad-2663-4e42-9b08-f696a329455d)

## How to Install and Inject

1. First, download the latest version of gd-hacks by visiting the [releases page](https://github.com/Skyue1/gd-hacks/releases).
2. Move the files `gd-hacks.dll` and `libExtensions.dll` to the folder where Geometry Dash is located. After completing this step, launch the game and press TAB.

## How to Compile (x32, CMake)

If you prefer to compile GD-Hacks from the source code, follow these steps:

1. Ensure you have CMake installed on your system.
2. Clone the GD-Hacks repository to your local machine.

   ```bash
   git clone https://github.com/Skyue1/gd-hacks.git
   ```

3. Navigate to the cloned repository.

   ```bash
   cd gd-hacks
   ```

4. Create a build directory.

   ```bash
   mkdir build
   cd build
   ```

5. Run CMake to generate build files.

   ```bash
   cmake ..
   ```

6. Compile the project.

   ```bash
   make
   ```

7. After a successful compilation, you will find the compiled `gd-hacks.dll` in the build directory. Move these files to the Geometry Dash folder, as mentioned in the "How to Install and Inject" section.

Now you have a freshly compiled version of GD-Hacks ready for use.

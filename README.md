<h1 align="center"> Haggle Mod SDK </h1>
<p align="center"> For Peggle Deluxe and Peggle Nights </p>

<p align="center">
  <img src="/../assets/images/example-mod.png">
</p>

## Haggle?
### Hack Peggle
Haggle exposes a bunch of SexyFramework and Peggle functions in a wrapper to be used from outside of the game to do whatever you want with it!

## Noteable Uses
- [CrowdControl](https://crowdcontrol.live/item-pricing/Peggle)

## Installing
To run a mod, you must perform the following steps:
- [Install the Mod Loader](#installing-the-mod-loader)
- [Install mods into the mods folder](#installing-mods-into-the-mods-folder)

### Installing the Mod Loader
When Haggle mods are used with Peggle, they are loaded into the Peggle executable code on startup.
The Mod Loader performs this operation. Follow these steps to install the Mod Loader.
1. Obtain the Mod Loader `dsound.dll` file:
   1. Download from the [Haggle Github releases page](https://github.com/PeggleCommunity/haggle/releases) or
   2. Compile from the [`mod-loader` project files](src/mod-loader/). Refer to the [Compiling](#compiling) section for details.
2. Copy the `dsound.dll` file into the directory that the Peggle executable is run from.
   1. For **Steam**, Peggle executes from a location like `C:\ProgramData\PopCap Games\Peggle` (drive letter may vary).
      Note that the install location for Steam games is not the same as this ProgramData location.
      The Mod Loader must be placed inside this ProgramData location due to Steam's DRM check.

      To easily find this location, follow these steps:

      <details>
        <summary><i>Steam Mod Loader Install Location - Image</i></summary>
        <p>
          <img src="/../assets/images/Steam_Loader_InstallLocation.png">
        </p>
      </details>

      1. Run Peggle from Steam
      2. Open the Task Manager (Ctrl+Shift+Esc; Right-click Taskbar or Start Menu->Task Manager; or Search "Task Manager" in the Start Menu)
      3. Find `popcapgame1.exe` on the "Processes" tab (sort by "Name" to easily find it)
      4. Right-click on `popcapgame1.exe`
      5. Click on "Open file location"
   2. For the **EA launcher**, Peggle executes from the install location of Peggle.
      To easily find this location, follow these steps:
      <details>
        <summary><i>EA Mod Loader Install Location - Image</i></summary>
        <p>
          <img src="/../assets/images/EA_InstallLocation.png">
        </p>
      </details>

      1. Open the EA app
      2. Go to "My Collection"
      3. Click on the "3 dots" menu for Peggle
      4. Click on "View Properties"
      5. Click on "Browse" under the "Install location" section.
3. Test that the Mod Loader has been installed correctly.
   1. Launch Peggle
   2. If a window titled "Haggle Mod Loader" opened along with Peggle, then the Mod Loader has been installed correctly!
      At this point, the Mod Loader will complain about not finding a mod folder if no mods have been installed yet.
      Refer to the section on [installing mods into the mod folder](#installing-mods-into-the-mods-folder).

*Note: you can temporarily disable mods by renaming the `dsound.dll` file (e.g. rename it to `_dsound.dll`).*

### Installing mods into the mods folder
1. Create a folder called "mods" in the Peggle installation directory.
   1. For **Steam**, you can find this location by right-clicking on Peggle in your Steam library, hover over "Manage", and click on "Browse local files".

      <details>
        <summary><i>Steam Mod Folder Install Location - Image</i></summary>
        <p>
          <img src="/../assets/images/Steam_Mods_InstallLocation.png">
        </p>
      </details>
   2. For the **EA launcher**, you can find this location by following the same steps in the [Installing the Mod Loader](#installing-the-mod-loader) section for the EA launcher.
2. Place the mod's file(s) into the created folder. A mod file will usually have a `.dll` or `.asi` extension.
3. Test that the mod has been installed correctly.
   1. Launch Peggle, having already completed the [Installing the Mod Loader](#installing-the-mod-loader) step.
   2. In the Haggle Mod Loader window, the Mod Loader identifies which mods it loads.
      Ensure that all of the mod files that were placed into the "mods" folder in the previous step have been loaded.

      <details>
        <summary><i>Haggle Mod Loader with mod loaded successfully - Image</i></summary>
        <p>
          <img src="/../assets/images/Haggle_Mod_Loader_with_Example_Mod_loaded.png">
        </p>
      </details>

## Compiling
### Requirements
- Visual Studio 2022 (or prefered version) with C++ modules installed

### Compile
- Run `generate.bat` for VS2022 generation
  - edit `generate.bat` if needed for other IDEs, check [premake](https://premake.github.io/docs/Using-Premake/) for more info
- Compile


## Contributing
Refere to the [contributing guide](https://github.com/PeggleCommunity/haggle/blob/master/CONTRIBUTING.md) for more information.

## Dependencies
For license information, please check the containing depedency folder in `./deps` or check their website and/or repository page
- [MinHook](https://github.com/TsudaKageyu/minhook) - Hooking library

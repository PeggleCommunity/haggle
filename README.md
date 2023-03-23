<h1 align="center"> Haggle Mod SDK </h1>
<p align="center"> For Peggle Deluxe (and Peggle Nights soon) </p>

<p align="center">
  <img src="/../assets/images/example-mod.png" width="400">
</p>

## Haggle?
### Hack Peggle
Haggle exposes a bunch of SexyFramework and Peggle functions in a wrapper to be used from outside of the game to do whatever you want with it!

## Notable Uses
- [CrowdControl](https://crowdcontrol.live/item-pricing/Peggle)

## Installing
To run a mod, you must perform the following steps:
- [Install the Mod Loader](#installing-the-mod-loader)
- [Install mods into the mods folder](#installing-mods-into-the-mods-folder)

### Installing the Mod Loader
When Haggle mods are used with Peggle, they are loaded into the Peggle executable code on startup.
The Mod Loader performs this operation. Follow these steps to install the Mod Loader.
1. Obtain the Mod Loader `Haggle.exe` file:
   1. Download from the [Haggle Mod Loader Github releases page](https://github.com/PeggleCommunity/haggle-mod-loader/releases) or
   2. Compile from the [`mod-loader` project files](https://github.com/PeggleCommunity/haggle-mod-loader/tree/main/src/). Refer to the [Compiling](#compiling) section for details.
2. Copy the `Haggle.exe` file into your game directory. For Steam, right click the game in your library, hover over "Manage", and click on "Browse local files".

<details>
	<summary><i>Steam Mod Folder Install Location - Image</i></summary>
	<p>
		<img src="/../assets/images/Steam_Mods_InstallLocation.png">
	</p>
</details>

4. Test that the Mod Loader has been installed correctly. 
	1. Launch Peggle
	2. If a window titled "Haggle Mod Loader" opened along with Peggle, then the Mod Loader has been installed correctly!
      	At this point, the Mod Loader will complain about not finding a mod folder if no mods have been installed yet.
      	Refer to the section on [installing mods into the mod folder](#installing-mods-into-the-mods-folder).

### Installing mods into the mods folder
1. Create a folder called "mods" in the Peggle installation directory.  
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

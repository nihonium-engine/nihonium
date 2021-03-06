# Nihonium - `source` Directory

The `source` directory holds the source code. It is organised into the following subdirectories:

* `filesystem` - Interface for loading files.
* `log` - Interface for logging information, warnings and errors.
* `main` - Code for initialising the engine for each platform. This is where the `main()` functions are found.
* `model` - Code for loading models and meshes, and initialising meshes for each platform.
* `object` - Code for representing objects in the game world, and also the world itself. Also contains code binding the scripting language to the rest of the engine.
* `renderer` - Code for setting up windows etc. and drawing meshes to the screen.
* `shader` - Code for loading and initialising shaders.
* `texture` - Code for loading and initialising textures.

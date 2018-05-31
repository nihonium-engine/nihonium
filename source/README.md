# Nihonium - `source` Directory

The `source` directory holds the source code. It is organised into the following subdirectories:

* `file_reader` - Temporary interface for loading files. It is currently in the process of being replaced with `filesystem`.
* `filesystem` - Interface for loading files.
* `main` - Code for initialising the engine for each platform. This is where the `main()` functions are found.
* `model` - Code for loading models and meshes, and initialising meshes for each platform.
* `renderer` - Code for setting up windows etc. and drawing meshes to the screen.
* `shader` - Code for loading and initialising shaders.
* `texture` - Code for loading and initialising textures.

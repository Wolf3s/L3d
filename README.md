
## L3D - Lampert's 3D Scene Editor

My tiny 3D scene editor.

To compile this project, you will need to install the Qt Framework in your machine,
which can be found [here](http://qt-project.org/downloads).

In the base folder there is a QtCreator project file (`.pro`) that can be opened
with QtCreator and be used to build the scene editor.

The project is cross platform and should compile for MacOS X, Linux and Windows.
Inside the `bin/` folder you will also find a pre-built Mac Application file that
should run in all recent MacOS versions.

Note: The project is set up to look for dependencies from the `bin/` folder.
When opening the `.pro` file for the first time in a platform different from
the one that generated it may cause QtCreator to reset some user settings,
such as the build output directory. It is recommended that the output directory
be set to the `bin/` folder, otherwise, you may have to manually edit the `.pro`
file to account for a custom directory.

**The Assimp Library:**

The only external dependency besides the Qt Framework is the Open Asset Import Library (Assimp).
Together with the scene editor project files is included a copy of the Assimp library version 2.0.863,
that can be compiled to use with the editor. However it should work with newer versions of the library as well.
To compile the accompanying Assimp library, you can make use of the provided `makefile` located in the
`code/` directory, that is, `assimp-2.0.863/code/`. Running the makefile with the flags
`static` and `NOBOOST=1` (the second flag is needed only if you don't have the Boost libraries installed)
will generate a static library suitable for your platform in the `assimp-2.0.863/bin/` directory.

So your `make` command for the Assimp library will look something like:

> `$ make static NOBOOST=1`

Once the make completes, the way I've set up the project, you're going to have to copy the
resulting library file to the `lib/` folder in the Assimp directory (`assimp-2.0.863/lib/`).
In there you will find a subdirectory for your operating system, like `assimp-2.0.863/lib/macosx/`
for example. Just copy the static library to the appropriate folder and you're done.

----

![l3d scene editor](https://bytebucket.org/glampert/l3d/raw/a475488f6d8f12b6cc06f810bf9149bd3b488df7/bin/screens/cover.jpg "l3d scene editor")

You can find other screenshots like the above in the `bin/screens/` directory.

## License:

This project's source code is released under the [MIT License](http://opensource.org/licenses/MIT).


# Teapot

This project is a simple ray-trace rendering application using the Qt framework. It simply renders an image and displays it in a GUI. 

Teapot began as an Objective-C++ Cocoa application for a project in Advanced Computer Graphics (CS 548) at Washington State University. I have since ported it to Qt and C++.

![Sample Render](sample1080.png)


## How to Build

1. Install Qt framework. This was built using Qt 6.5.
2. Open the project in Qt Creator.
3. Build the project.

## How to Use

The Teapot executable expects to find several support files in the parent directory of the build directory. After building, the directory structure on my machine looks like this:

```
CMakeLists.txt
README.md
build/                     - build directory
   \- [Teapot executable]  - the executable within the build directory
bunny_surface0.norm        - bunny surface normals
teapot_surface0.norm       - teapot surface normals
earth_2k.jpg               - earth texture
sample1080.png
[ more source files and directories: *.h and *.cpp, mainwindow.ui ]
```

If your build environment places the `build` directory somewhere else, you will need to copy or move the three files\* to the same directory as the build directory. This was the easier option rather than asking the user to locate the files every time the application is run.

\* The three files are: bunny_surface0.norm, teapot_surface0.norm, and earth_2k.jpg.

1. Press the "Begin" button to start rendering.
2. The rendered image will be displayed in the `RenderView` widget.
3. Press the "Cancel" button to cancel the rendering process.
4. After rendering has finished, you can click on the image to request debug rendering of a specific pixel, or:
5. Press the "Save" button to save the rendered image.

## License

This project is licensed under the MIT License.

## Acknowledgements

- [Professor Wayne Cochran](https://github.com/wcochran) (formerly at WSU) for instruction, knowledge, and inspiration.

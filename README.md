# Teapot

This project is a simple ray-trace rendering application using the Qt framework. It simply renders an image and displays it in a GUI. 

Teapot began as an Objective-C++ Cocoa application for a project in Advanced Computer Graphics (CS 548) at Washington State University. I have since ported it to Qt and C++.

![Sample Render](sample1080.png)


## How to Build

1. Install Qt framework. This was built using Qt 6.5.
2. Open the project in Qt Creator.
3. Build the project.

## How to Use

The Teapot executable expects to find three data files in the project directory.\* If the project directory is moved, the executable will need to be recompiled.

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

# Directory structure breakdown

1. core:
Contains the fundamental classes and functions that define the basic operations of ray tracing, such as ray generation, intersection tests, and color calculations.
Example files: Ray.h, Scene.h, Camera.h
2. materials:
Holds classes that define material properties, such as diffuse, specular, transparency, and texture mapping.
Example files: Material.h, Texture.h
3. math:
Dedicated to mathematical utilities and functions used across the raytracer, like vector operations, transformations, and geometric utilities.
Example files: Vector3.h, Matrix4x4.h
4. objects:
Contains definitions for various geometric objects that can be rendered, such as spheres, planes, and meshes.
Example files: Sphere.h, Mesh.h
5. lights:
Includes classes for different types of light sources in the scene, such as point lights, directional lights, and area lights.
Example files: Light.h, PointLight.h
6. utils:
For utility functions and classes that assist in operations like logging, debugging, file handling, or other helper functions.
Example files: Logger.h, FileLoader.h
7. shaders:
If implementing shader-like functionality or programmable aspects of the ray tracing process, this folder can contain such implementations.
Example files: Shader.h, PhongShader.h
tests:
Contains unit tests or other testing scripts specific to the ray tracing algorithms and functionalities.
Example files: RaytracerTests.cpp

```
Raytracer/
│
├── Core/
│   ├── Ray.h
│   ├── Scene.h
│   ├── Camera.h
│   └── ...
│
├── Materials/
│   ├── Material.h
│   ├── Texture.h
│   └── ...
│
├── Math/
│   ├── Vector3.h
│   ├── Matrix4x4.h
│   └── ...
│
├── Objects/
│   ├── Sphere.h
│   ├── Mesh.h
│   └── ...
│
├── Utils/
│   ├── Logger.h
│   ├── FileLoader.h
│   └── ...
│
├── Shaders/
│   ├── Shader.h
│   ├── PhongShader.h
│   ├── Light.h
│   └── ...
│
└── Tests/
    ├── RaytracerTests.cpp
    └── ...
```

# Jubi v0.1.6

**Version:** 0.1.6  
**License:** ALLPU or MIT  
**Copyright © 2025 Averi**  

Jubi is a single-file, public physics library written in pure C, for ease of use physics. Jubi is designed to be easily included in any project without external dependencies.

# Structure

Jubi follows any standard single-file library.
```C
#ifndef JUBI_H
#define JUBI_H
// Header code
#endif

#ifdef JUBI_IMPLEMENTATION_H
// Source code
#endif
```

Including & implementing Jubi in a project is as simple as:

```C
#define JUBI_IMPLEMENTATION_H
#include <Jubi.h>
```

# Core

## World

Jubi uses *worlds* to manage objects & bodies.
```C
JubiWorld2D 2DWorld = Jubi_CreateWorld2D();
JubiWorld3D 3DWorld = Jubi_CreateWorld3D();
```

## Bodies

Bodies are stored in a fixed-size array (`JUBI_MAX_BODIES`) and can be boxes or circles.
Bodies have 2 types `Static` & `Dynamic`, 2 shapes `Circle` & `Box`, `Position`, `Size`, `Velocity`, and a `Mass`. Example creation:
```C
// JBody2D_CreateBox(JubiWorld2D *WORLD, Vector2 Position, Vector2 Size, BodyType2D Type, float Mass)
Body2D Box = JBody2D_CreateBox(NULL, (Vector2D){5.0, 17.0}, (Vector2D){4.0, 4.0}, BODY_DYNAMIC, 1.0f);
```

There will be more advanced features later on, like custom collisions, but at the minute retain to `SHAPE_BOX` & `SHAPE_CIRCLE`.

## Vector2 Utilities

Jubi provides the user with a fully fledged list of vector math functions:

`Addition | Division | Subtraction | Multiplication` - Basic arithmic
`Dot | Cross | Scalar` - Scalar operations
`Normalize | Length | Distance | Direction` - Metrics

## Tests/Demos

Tests are designed to test & push the limits of what Jubi can do, and are placed under the `tests` folder. Each test has a detailed description on what their purpose is, the end result, alongside the creation/modification date. All tests are designed to be compiled in ***pure*** C, with no need of external libraries.

## Constants & Limits

Jubi uses fixed-size memory to stay leightweight & easy to use.

`JUBI_MAX_BODIES` - Max number of bodies in a world.
`GRAVITY` - World's set gravity.
`JUBI_VERSION_MAJOR/MINOR/PATCH` - Version Macros

# System Architecture

## System Dependencies

As previously stated, Jubi is made in pure C, with no use of external libraries. Jubi requires only a standard C compiler with C99 or later. The Jubi library has no current OS-dependent features or architecture within it.

## Current bugs & limitations

### Major

Jubi 0.1.6 >> 0.2.0
  - `JBody2D_CreateBox` function returns the copy version of the body, leading to you editing a fake/faulty body. To be fixed as of 0.2.1.

Jubi 0.1.4 >> 0.1.6 >> 0.2.0
  - `Jubi_IsWorldValid` function returned a fualty value (1), with all function(s) using said function checking for a **0** value.
  - `JBody2D_CreateBox` function recieved a faulty value from `Jubi_IsWorldValid`, leading to NULL (No) world values being treated as a world, leading to silent errors in the creation process.

### Minor

As of said version, Jubi has no *known* minor issues to its code.

### Limitations

As of said version, Jubi has no *known* limitations to its code.

## Versioning

Macros `JUBI_VERSION_MAJOR`, `JUBI_VERSION_MINOR`, and `JUBI_VERSION_PATCH` are defined in the header to match the release version.

# Future Features

- 3D Support
- Improved Architecture/Code Size
- Increased/Improved Memory Management

# API Reference

## World API

### Create / Destroy

```C
JubiWorld2D Jubi_CreateWorld2D(void);
void Jubi_ClearWorld2D(JubiWorld2D *WORLD);
```

> `Jubi_CreateWorld2D(void)` - Creates a new world with default gravity & an empty body list   
> `Jubi_ClearWorld2D(JubiWorld2D *WORLD)` - Resets all   

# License

Jubi is licensed under ALLPU / MIT, giving plenty of freedom to modify, & redistribute open-source versions of the project.

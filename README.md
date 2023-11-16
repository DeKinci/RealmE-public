# RealmE - Realm Engine public page
A voxel game (engine) with a build-in modding environment, not yet ready for a public release

Formerly known as a low-poly game library TilesGE. Realm Engine is being developed in a private repository, with this repo containing an overview and updates.
For nostalgic purposes code of one of the early versions of TilesGE is available.

Project goal - explore possibilities of voxel world representation, by implementing voxel physics and simulation engine. 

## Overview

![Editor overview](docs/Realme_editor.png)

Editor features:
- ECS entity viewer and editor
- Log tab with colors!
- Tracy profiler integration
- Debug gizmo drawing with groups
- Instrumented debugger and value watcher, aware of the game loop

## Tech stack
- C++ 20, CMake
- [BGFX](https://github.com/bkaradzic/bgfx) as a GPU abstraction
- [SDL](https://www.libsdl.org) as windows and input abstraction
- [EnTT](https://github.com/skypjack/entt) core entity component system
- [Dear ImGui](https://github.com/ocornut/imgui) developer tools UI
- [protobuf](https://github.com/protocolbuffers/protobuf) binary serialization
- [Valve GameNetworkingSockets](https://github.com/ValveSoftware/GameNetworkingSockets) UDP networking library
- [kompute](https://github.com/KomputeProject/kompute) Vulkan GPGPU abstraction
- [Tracy](https://github.com/wolfpld/tracy) frame profiler

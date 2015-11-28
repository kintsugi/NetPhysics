# NetPhysics
C++ ECS Multiplayer Game Engine Server
Uses RakNet for networking, BulletPhysics for server side physics, and Unreal Engine for client display.

**Note**: This is an old hobby project. This readme will list dependencies and general building instructions, but development on this has stalled for the time being. This is not intended for distribution or collaboration.

## Build Instructions

The NetPhysicsServer directory contains the Visual Studio project files and server code. It depends On Bullet physics and RakNet. Assuming those are properly linked and setup, the server will build.

The NetPhysicsClient contains the client source code and the unreal engine files. However, the client code depends on a symlink to the XSource directory in the NetPhysicsServer directory. The client relies on a properly working UE4 environment with visual studio, and also relies on RakNet being properly linked.

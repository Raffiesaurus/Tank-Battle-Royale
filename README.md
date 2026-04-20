# Tank Battle Royale

![Tank Battle Royale](BattleTank/BattleTank.png)

A **1v13 tank battle royale** built with Unreal Engine 4 using C++ and Blueprints. You're one player tank against 13 AI opponents on an open terrain map - use the landscape for cover, manage your ammo, and be the last tank standing.

---

## Gameplay

- **1 player vs 13 AI tanks** - last tank alive wins
- All tanks spawn at separate points on the map with identical stats and ammo for fair play
- Tanks have finite **health points** and **ammo** - choose your shots wisely
- Terrain can be used tactically to break line of sight and dodge incoming fire

---

## Architecture

The tank is built as a modular, component-driven system entirely in C++:

| Class | Responsibility |
|-------|---------------|
| `Tank` | Base tank actor - health, damage, death |
| `TankPlayerController` | Player input and cursor-based aiming |
| `TankAIController` | AI perception and target acquisition |
| `TankAimingComponent` | Barrel elevation and predictive projectile aiming |
| `TankMovementComponent` | Tank locomotion via left/right track throttle |
| `TankTrack` | Per-track physics force application |
| `SprungWheel` | Physics-based suspension per wheel |
| `TankBarrel` | Barrel elevation control |
| `TankTurret` | Turret yaw rotation |
| `Projectile` | Physics projectile with impact damage and effects |
| `SpawnPoint` | Distributed spawn logic for all 14 tanks |

---

## Tech

- **Engine:** Unreal Engine 4
- **Language:** C++ (gameplay systems) + Blueprints (assets, configuration)
- **Platform:** Windows Desktop
- **Physics:** UE4 PhysX - suspension, tracks, projectile ballistics

---

## Opening the Project

1. Install **Unreal Engine 4** via the Epic Games Launcher
2. Clone the repo
3. Right-click `BattleTank/BattleTank.uproject` → **Generate Visual Studio project files**
4. Open the `.sln` in Visual Studio and build
5. Launch via `BattleTank.uproject`

---

## Project Structure
```
BattleTank/
├── Source/BattleTank/
│ ├── Public/                           # C++ header files
│ ├── Private/                          # C++ implementation files
│ ├── Tank.cpp/h                        # Base tank actor
│ └── TankPlayerController.cpp/h
├── Content/                            # Blueprints, meshes, maps
└── BattleTank.uproject
```

---

## License

MIT

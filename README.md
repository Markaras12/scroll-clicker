# Scroll Clicker — Geode Mod
**GD Version:** 2.2081  
**Geode SDK:** 5.3.0  
**Mod Version:** 1.0.0

Lets you click/jump in Geometry Dash by scrolling your mouse wheel.

---

## Features
| Setting | Default | Description |
|---|---|---|
| Scroll Up Clicks | ✅ | Scrolling up triggers a jump |
| Scroll Down Clicks | ✅ | Scrolling down triggers a jump |
| Only In Level | ✅ | Scroll clicking only active while inside a level |
| Click Both Directions | ❌ | Both directions press without releasing on opposite scroll |

---

## Building

### Prerequisites
- CMake ≥ 3.21
- Geode SDK 5.3.0 (cloned & bootstrapped)
- MSVC (Windows), Clang (macOS), or Android NDK

### Steps

```bash
# 1. Clone / download this mod folder
cd scroll-clicker-mod

# 2. Configure (replace path with your Geode SDK location)
cmake -B build -DGEODE_SDK=/path/to/geode-sdk

# 3. Build
cmake --build build --config RelWithDebInfo
```

The output `.geode` file will appear in `build/` (or your Geode mods folder if you configured the loader path).

### Quick install (after building)
Copy `yourname.scroll-clicker.geode` into:
- **Windows:** `%LOCALAPPDATA%\GeometryDash\geode\mods\`
- **macOS:** `~/Library/Application Support/GeometryDash/geode/mods/`
- **Android:** `/sdcard/Android/data/com.robtopx.geometryjump/files/geode/mods/`

---

## How It Works

The mod hooks `CCDirector::scrollWheel`, which is the Cocos2d callback for all mouse-wheel input.  
When a scroll event arrives while `PlayLayer` is active, it calls `PlayLayer::handleButton(true, 1, true)` to simulate a jump press, then schedules a release on the next frame so it behaves like a tap rather than a held key.

---

## License
MIT — do whatever you want with it.

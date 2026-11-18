# The Godfather: The Game (Xbox 360) - Static Recompilation (ReXGlue)

Community static recompilation project for **The Godfather: The Game** (Xbox 360, USA, Title ID `454107E9`, Media ID `39C09F0B`, `default.xex` patched via XexTool to Title Update 1 ) built with **ReXGlue SDK v0.11.0**.

## Current Status
* **Working:** Boots into menus, Bink FMVs, and 3D gameplay via D3D12 (`allow_invalid_fetch_constants = true`, `readback_resolve = none`).
* **Custom Hooks (`src/godfather_recomp_hooks.cpp`):**
  * `sub_825709A8` (`XamContentGetDeviceData`): Reports 10 GB free HDD space so the save/storage check passes.
  * `sub_82A6D090` (`SaveManager`): Bypasses Xbox 360 STFS container verification when the 461,268-byte save payload exists on disk.
  * `sub_825712C8` / `sub_82571D40`: Linker stubs for unreferenced imports.

## Known Issues (Help Wanted!)
1. **Slow Frame Pacing & Audio Buzzing:** EA's 2006 RenderWare engine couples its 48 kHz XMA2 audio mixer (`XMASetInputBuffer0Valid` / `XMAGetOutputBufferWriteOffset`), Bink FMV playback, and fixed-timestep physics to `VdSwap` and hardware VBlank interrupts (`VdSetGraphicsInterruptCallback`). Frame times above 16.67 ms stretch the timestep and underflow the SDL3 audio buffer.
2. **Save Slot Persistence & Overwrites:** The title writes all 461,268 bytes to `user/B13EBABEBABEBABE/454107E9/00000001/The Godfather/The Godfather`, but `rexxam` STFS metadata checks and trailing whitespace in `XCONTENT_DATA` trigger damaged-save prompts on subsequent menu opens or overwrites.

## Mapped Guest Functions
* `sub_82570900`: `XamContentCreateEx` wrapper (passes `flags = 0x12` on initial save, `0x11` on overwrite).
* `sub_82A75370` - `sub_82A77E70`: C++ `SaveManager` state machine (state `21` = damaged save dialog).
* `0x82591458`: Main `VdSwap` presentation call.
* `0x8259C0E0`: `VdSetGraphicsInterruptCallback` registration.

## Build Instructions
1. Install **ReXGlue SDK v0.11.0** to `D:/rexglue-sdk` (or update `CMAKE_PREFIX_PATH` in `CMakePresets.json`).
2. Place your own legal dump of `default.xex` (patched via XexTool) and `godfath0.viv` through `godfath12.viv` into `assets/`.
3. Generate recompiled C++ sources: `rexglue.exe codegen godfather_recomp_manifest.toml`
4. Configure and build: `cmake --preset win-amd64 && cmake --build --preset win-amd64-release`
5. Copy `godfather_recomp.toml` and `assets/` into `out/build/win-amd64/Release/` and launch: `godfather_recomp.exe --game_data_root=assets`

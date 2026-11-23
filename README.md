# TrackMania Original Recomp

A [Recomp Toolkit](https://github.com/wraitii/recomp-toolkit) profile for running TrackMania Original on Linux and Android. The repository contains the integration, code map, launcher icon, and toolkit patch. Bring your own compatible game files.

## Game input

The tested input was the English **Win10 Community Repack** listed on [My Abandonware](https://www.myabandonware.com/game/trackmania-gcf#downloads). Use a local copy you are entitled to use. Select the folder containing `TMORIGINAL.EXE` and `GameData/`. The setup tool checks this executable SHA-256.

```text
75e129d769f4595ddde54a8ef484162915bc2bf998c1a2139cc963294fe8175e
```

## Prepare the toolkit and game

Install the [toolkit build prerequisites](https://github.com/wraitii/recomp-toolkit/blob/05392effc17c354a7315fd0102d2a304925be80d/CONTRIBUTING.md). From the repository root, run the commands below. Set `GAME_INSTALL` to the absolute path of your local installation.

```sh
git clone https://github.com/wraitii/recomp-toolkit.git recomp-toolkit
git -C recomp-toolkit checkout --detach 05392effc17c354a7315fd0102d2a304925be80d
git -C recomp-toolkit apply --check ../patches/recomp-toolkit-linux-android.patch
git -C recomp-toolkit apply ../patches/recomp-toolkit-linux-android.patch

python3 -m venv recomp-toolkit/.venv
py="$PWD/recomp-toolkit/.venv/bin/python"
"$py" -m pip install -r recomp-toolkit/requirements-dev.txt
profile="$PWD/games/tm-original"
build="$PWD/local/build/tm-original"
export CARGO_BUILD_JOBS=2 RAYON_NUM_THREADS=2

"$py" recomp-toolkit/tools/setup.py \
  --game-dir "$profile" --build-root "$build" --install "$GAME_INSTALL"
```

### Linux x86-64

```sh
"$py" recomp-toolkit/tools/build.py \
  --game-dir "$profile" --build-root "$build" --jobs 2 --regenerate --target app

RECOMP_EXE="$build/original/TMORIGINAL.EXE" \
  "$build/package/TmOriginalRecomp/TmOriginalRecomp"
```

### Android ARM64

The tested Android toolchain used JDK 21, SDK platform 36, build tools 37.0.0, NDK r27c, and Rust's `aarch64-linux-android` target. Set `JAVA_HOME`, `ANDROID_HOME`, and `ANDROID_NDK_HOME` to your toolchain paths. Install the Rust target with `rustup target add aarch64-linux-android`.

```sh
"$py" recomp-toolkit/tools/build.py \
  --game-dir "$profile" --build-root "$build" --jobs 2 --config Release \
  --regenerate --target android --no-install

"$ANDROID_HOME/platform-tools/adb" install -r \
  "$build/android/app/build/outputs/apk/debug/app-debug.apk"
```

The APK uses debug signing and native Release optimization. On first launch, use the launcher to import your local game folder or a ZIP of that folder. To change the keyboard, gamepad, or menu size later, tap during the startup countdown and open **Configure**. The menu size also applies to **Controller setup**.

## Verification

| Platform | Verified |
| --- | --- |
| Linux x86-64 | Main menu and RaceA1 |
| Android emulator | Main menu |
| Nothing A059P, ARM64 | Main menu, built-in replay benchmark, touch keyboard, and Controller setup |

On the Nothing A059P, the built-in replay averaged 46.9 FPS with native Release optimization and 15.3 FPS in the earlier native Debug build, at the same 1595 × 720 viewport and graphics settings. Live race performance varies by track.

## AI assistance and manual review

Most changes were made with Codex using GPT-6.2-Sol. The changes received partial manual review.

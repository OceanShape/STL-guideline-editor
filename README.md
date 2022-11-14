# STL-guideline-editor
`STL-guideline-editor` is `.csv` data exporter from X-ray image using guideline.

![image](https://user-images.githubusercontent.com/42532724/201208906-560b3758-e14e-47f5-87d4-b3c6e0d5db02.png)

## Environment
- OS: Windows 10
- Language: C++14/xml(Qt UI)
- Framework: Qt(Core/Gui/Widgets)
- IDE: Visual Studio 2019

## How to Build
1. Install `Visual Studio 2019`
2. Install `Qt` for `Windows`
    - Download and run [Qt installer](https://www.qt.io/download-thank-you?hsLang=en).
    - Create account and select `Custom installation`.
        - Install only `Qt 5.15.2`, `Qt designer`, `Qt debugging for windows`.
3. Add `Qt` to `Visual Studio`(use `Extensions`)
    - Search and install `Qt Visual Studio Tools` in `Manage Extensions`.
        <p align="center">
        <img src="https://user-images.githubusercontent.com/42532724/158069722-fc222891-0d31-4f7e-a4b1-90310c92b41f.png" width="50%" height="50%">
        </p>
    - Select `Extensions` → `QT VS Tools` → `Qt Versions`.
    - Add `qmake.exe`(find `bin` folder in installed qt directory) to list in `add new Qt version`.
4. Build and run

## How to Use
- Left screen is AP image, and Right screen is LAT image.
- After setting all the guidelines, you can save and create a `.csv` file.
- There are four menus, and four guideline types.
    - `New`/`Open`: Create new/different image set for data. Before setting a guideline, you must select two image(AP/LAT).
    - `Save`: Convert data to `.csv`. Before converting data, you must set all guidelines.
    - `Close`: Close current program.
    - `baseline`: Change baseline mode for world coordinates.
    - `spine`: Change spine mode for setting five spines per image. If you draw four dots, `guideline-editor` automatically creates a single bone.
    - `spinous-process`: Change spinous process mode.
    - `pelvis`: Change pelvis mode. This mode just for AP.
    - `tailbone`: Change tailbone mode. This mode just for LAT.
- You can add symptom/remarks by note in `Symptom`/`Remarks(proof)` 
- If you want sample, download this [images](https://drive.google.com/file/d/1bRhkr-I-3SykoCC3AVjhxrdFI-JFAYOT/view?usp=share_link).

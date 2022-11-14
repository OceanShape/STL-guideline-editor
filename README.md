# STL-guideline-editor
`STL-guideline-editor` is `.csv` data exporter from X-ray image using guideline.

![image](https://user-images.githubusercontent.com/42532724/201208906-560b3758-e14e-47f5-87d4-b3c6e0d5db02.png)

### Environment
- OS: Windows 10
- Language: C++14/xml(Qt UI)
- Framework: Qt(Core/Gui/Widgets)
- IDE: Visual Studio 2019

### How to Build
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

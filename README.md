# text-editor-from-scratch

A simple text editor (like notepad in windows), made from scratch, uses only one library ([liballeg](https://liballeg.org) ↗️) for input and rendering.
No GUI Libraries used 🙂

![](/screenshots/editor.png)

### Building from Source:
#### Dependencies: [liballeg](https://liballeg.org) ↗️
<details>
<summary>Installing on Linux</summary>

#### Ubuntu 18.04+ (or derivatives thereof)

First, add the Allegro PPA. This gives you up-to-date versions of Allegro; the base repos only provide 5.2.3 at the time of writing.

```bash
sudo add-apt-repository ppa:allegro/5.2
```

Then, install Allegro:

```bash
sudo apt-get install liballegro*5.2 liballegro*5-dev
```

#### Debian-based distributions (Debian, Mint, Ubuntu, etc..)

```bash
sudo apt-get install liballegro-ttf5-dev
```

#### Fedora

```bash
sudo dnf install allegro5*
```

#### Others

Binary packages may be available for your distro; feel free to add them here if so.

Otherwise, select "Something else" below.

</details>

<details>
<summary>Installing on macOS</summary>

#### Install with [Homebrew](https://brew.sh/)

```bash
brew install allegro
```

You will also need to install pkg-config, if it is not already installed.

```bash
brew install pkg-config
```

</details>

<details>
<summary>Installing on Windows</summary>

#### Visual Studio 2015+

Install per-project using [NuGet](https://www.nuget.org/) in PowerShell:

```ps1
cd MyProjectDir\
Install-Package Allegro
```

Or, just [[install from within Visual Studio|Allegro in Visual Studio#using-nuget-within-visual-studio]].

#### MinGW (via MSYS2)

* [Go to the Allegro releases page](https://github.com/liballeg/allegro5/releases) and find the most recent Allegro 5 version.
  * There are a few options for MinGW - but for those new to Allegro, we recommend downloading the **x86_64 dynamic** package.
  * This will be named - e.g. for v5.2.6 - **allegro-x86_64-w64-mingw32-gcc-9.2.0-posix-seh-dynamic-5.2.6.0.zip**.
* Extract the relevant directories into your MinGW install's include & library paths:
  * Find out where you installed MinGW (`C:\msys64` is the default).
  * The .zip contains three directories under `allegro\`: `bin\ include\ lib\`.
  * Extract the files from each to e.g. `C:\msys64\mingw64\bin`, `C:\msys64\mingw64\include`, `C:\msys64\mingw64\lib` respectively.

</details>

#### Building:
```bash
git clone https://github.com/Eessh/text-editor-from-scratch.git
cd text-editor-from-scratch/
make build
./main
```
- Windows users:
  - use `mingw32-make build` instead of `make build`
  - use `.\main.exe` instead of `./main`

#### TODO
- [x] Basic Features
- [ ] Taking input when a modifier key is active
- [ ] Tab Support
- [ ] File Read/Write
- [ ] Syntax Highliting
- [ ] StatusLine
- [ ] Maybe 🤔 Modal Editing (like [Vim](https://github.com/vim/vim), [Neovim](https://github.com/neovim/neovim), ... )
- [ ] Maybe 🤔 trying out differnet data structures for DocBuffer
    - [ ] Rope Data Structure (used by [Xi-Editor](https://github.com/xi-editor/xi-editor))
    - [ ] PieceTable Data Structure (currently used by [VSCode](https://github.com/microsoft/vscode))

# Matrix Rain Effect

A terminal-based Matrix rain effect implementation written in C using the ncurses library.

## Features

- Dynamic character rain effect with customizable colors
- Responsive to terminal window size
- Smooth animation with adjustable speed
- Transparent background support

## Requirements

- GCC compiler
- ncurses library

## Installation

### macOS
```bash
brew install ncurses
```

### Ubuntu/Debian
```bash
sudo apt-get install libncurses5-dev libncursesw5-dev
```

## Compilation

### Using Makefile (recommended)

```bash
make
```

### Manual compilation

```bash
gcc -o matrix matrix.c -lncurses
```

### Additional Makefile targets

```bash
make clean    # Remove compiled files
make install  # Install to /usr/local/bin (requires sudo)
make uninstall # Remove from /usr/local/bin (requires sudo)
```

## Usage

```bash
./matrix
```

### Controls

- Press `q`, `Q`, or `Esc` to exit gracefully
- Press `Ctrl+C` to force exit
- Resize terminal window - the effect will automatically adapt

## Demo

![Matrix Effect Demo](assets/matrix.gif)

# Console Snake Game in C 🐍

A classic, fully functional Snake game built entirely in C that runs directly in the Windows command prompt. 

## 🎮 Features
* **Classic Gameplay:** Eat the food to grow, but don't hit the walls or your own tail!
* **Multiple Difficulties:** Choose between Easy, Medium, and Hard to adjust the snake's speed.
* **Retro Terminal UI:** Custom ASCII art menu and borders.
* **Flicker-Free Rendering:** Optimized console output to prevent screen flickering during movement.
* **Input Handling:** Smooth controls using `conio.h` and collision/direction checks (prevents 180-degree self-collisions).

## 🛠️ Technologies Used
* **Language:** C
* **Libraries:** standard C libraries (`stdio.h`, `stdlib.h`), plus `<windows.h>` for console manipulation (colors, cursor positioning) and `<conio.h>` for asynchronous keyboard input.

## 🚀 How to Play

### Controls
* `W` - Move Up
* `S` - Move Down
* `A` - Move Left
* `D` - Move Right

### Compilation (Windows)
Since this project uses the Windows API, it needs to be compiled for a Windows environment. You can use **GCC (MinGW)** to compile the game from your terminal:

```bash
gcc main.c -o snake.exe

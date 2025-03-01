# MiniRT
Maryna and Stephanie's MiniRT, a 42 school project written in C language that uses the ray tracing technique for CGI.

The goal of this program is to generate images using the Raytracing protocol.Those computer-generated images will each represent a scene, as seen from a specific angle and position, defined by simple geometric objects, and each with its own lighting system.

Ray tracing is a technique for modeling light transport to generate digital images.

Our first RayTracer with miniLibX
miniLibX is [explanation].

## Function Return Value Conventions

This project utilizes distinct return value conventions to enhance clarity and maintainability.

For functions indicating the success or failure of an operation, standard practice is followed: `SUCCESS` is defined as `0`, and `FAILURE` as `1`. This aligns with common C programming conventions.

For functions representing boolean "yes/no" or "true/false" conditions, the `stdbool.h` library is included to enable the use of `true` and `false`. To improve readability, boolean checks are explicitly written in the form `if (is_empty_file(filename) == true)`, emphasizing the intended condition.

## Window Creation

The program utilizes the MiniLibX (MLX) library to create a graphical window. This window serves as the primary display for the rendered scene.

**Function: `mlx_new_window()`**

The core function responsible for window creation is `mlx_new_window()`, which is provided by the MiniLibX library.

**Implementation:**

In our program, the window is instantiated within the `setup_mlx()` function. The following code snippet demonstrates its usage:

`mlx_new_window(rt->cf.mlx, 800, 600, "42 MinilibX Window");`

In this example, a default size of 800 pixels wide and 600 pixels high is used. However, these values can be adjusted to create windows of different sizes as needed.

**Operating System Compatibility:**

* **Ubuntu (Linux):** As students at 42Berlin, we primarily develop and test our programs on Ubuntu Linux. In this environment, MiniLibX is readily available, and the window creation process should function seamlessly without requiring any additional software installations.
* **Windows 10 (WSL2):** It is also possible to run our program on Windows 10 using Windows Subsystem for Linux 2 (WSL2). However, to display the graphical window, you will need to install an X server, such as "Xming X Server for Windows". For detailed instructions on setting up an X server on Windows 10 (WSL2), please refer to the following tutorial: [Getting a screen on Windows 10 (WSL2)](https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html#getting-a-screen-on-windows-10-wsl2).

---
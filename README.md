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

## Viewport Definition

In our 3D raytracing scene, the viewport acts as the 2D window through which we visualize the 3D world. Unlike objects within the scene, the viewport's parameters are derived from the camera's properties.

Think of the viewport as the "canvas" we'll later display using minilibx. It mirrors the aspect ratio of our output window, and the width of this canvas is determined by the FOV.

In 3D space, the viewport is a rectangular plane defined by:

* **A center point:** This anchors the viewport's position.
* **two vectors:** ??????
* **Width and height:** These dimensions are crucial for determining which points fall within the viewport's boundaries, distinguishing them from the infinite expanse of a general 3D plane.
* **Field of View (FOV):** This angle determines the horizontal extent of the visible scene, directly influencing the viewport's width.

Essentially, the viewport acts as a bridge between the 3D scene and the 2D image we render.

## Set Up the Viewport

Key Components:
* Camera Position (C): The location of the camera in 3D space.
* Orientation Vector (o): A normalized vector (length of 1) that indicates the direction the camera is facing.
* Field of View (FOV): The angle that defines the extent of the camera's view. A wider FOV means a broader view.

**Calculate the Center of the Viewport**

VPc = C + o

This finds the point directly in front of the camera, at a distance of 1 unit in the direction of the orientation vector. This point is the center of the viewport plane.

**Determine the Viewport Planee**
The viewport plane is perpendicular to the orientation vector (o) and passes through the Viewport Center (VPc).

**Calculate Viewport Dimensions (Width and Height in 3D Space)**

Key Components:
* M_PI is a constant that represents the mathematical value of π (pi).
* Radians are a unit of angular measurement. Many programming languages and graphics libraries use radians for their trigonometric functions.

[ ... ]

**Find the Upper-Left Corner of the Viewport**

To find the corners of the viewport, you need to create two orthogonal vectors that are perpendicular to the orientation vector. These vectors will define the "up" and "right" directions of the viewport.

[ ... ]

## How to use the Viewport

Now that we have the Viewport and its Total width and height, we can calculate the position of each individual Pixel in this 3D space by dividing the width with the total number of Pixels in a row and the height with those in a column. 

Instead of fixed positions, you can also calculate each vector to move horizontally and vertically to access each pixel by scaling the vectors with full numbers. 
---
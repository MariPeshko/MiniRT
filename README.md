# MiniRT

<p align="center"> 
  Let's ray-trace some light into this project! ✨
</p>

<p align="center">
 <img src = "https://github.com/user-attachments/assets/3a9d4014-fd86-4f75-9b15-1b53f83714a8" />
</p>

MiniRT is a _raytracing project_ developed by Maryna Peshko and Stephanie Patricia Gramsch as part of the 42 Berlin school curriculum in 2025. It is written in C and generates basic computer graphics using ray tracing techniques.

[LinkedIn Maryna Peshko](https://www.linkedin.com/in/maryna-peshko/)

The goal of this program is to generate images using the raytracing protocol. Ray tracing is a technique for modeling light transport to generate digital images. Those computer-generated images will each represent a scene, as seen from a specific angle and position, defined by simple geometric objects, and each with its own lighting system.
<br />
<br />
# Compilation and Usage

***System Requirements***

* A Unix-like system (Linux or macOS)
* A C compiler (e.g., gcc or clang)
* make utility
* miniLibX library (provided as a submodule)

## How to Compile

Command-line usage

`make` to compile a project

`make re` to recompile

`make clean` to delete object files

`make fclean` to delete object files and executable file

## How to Run

Command-line usage as well

```
./miniRT [name_of_scene].rt
```

**Operating System Compatibility:**

* **Ubuntu (Linux):** As students at 42Berlin, we primarily develop and test our programs on Ubuntu Linux. In this environment, MiniLibX is readily available, and the window creation process should function seamlessly without requiring any additional software installations.
* **Windows 10 (WSL2):** It is also possible to run our program on Windows 10 using Windows Subsystem for Linux 2 (WSL2). However, to display the graphical window, you will need to install an X server, such as "Xming X Server for Windows". For detailed instructions on setting up an X server on Windows 10 (WSL2), please refer to the following tutorial: [Getting a screen on Windows 10 (WSL2)](https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html#getting-a-screen-on-windows-10-wsl2).

# Configuration files

You can find them in `/rt_files` folder.

Keywords in rt_file
Feature: despite that fact that vectors must be in a range from 0 to 1, there is no need to set a normilized vector in config file. Our miniRT normilize all the vectors in a parsing part.

* **A — ambient light**, intensity, and R,G,B colors
* **C — camera**, position, direction, field of view (rotation is not available)
* **L — light**, position, intensity, R,G,B colors (light is treated as _omnidirectional_ — it does not have a specific direction but instead radiates equally in all directions from its source.)
* **sp — sphere**, position of the center, size, R,G,B colors
* **pl — plane**, position, normal vector (perpendicular to the entire plane), R,G,B colors
* **cy — cylinder**, position of the center, a vector of axis, diameter, height, R,G,B colors

# Examples

Our raytracer supports multiple spheres, planes, and cylinders, one ambient light, and colored lighting, shadows.

![Brightness_Light_sideways_000 rt](https://github.com/user-attachments/assets/2304c896-08ed-4c28-b313-ba417f57f8cd)
<br />
<br />
![Brightness_Light_sideways](https://github.com/user-attachments/assets/58cc552c-f737-4b41-862f-41c65aae1d95)
<br />
<br />
![Screenshot from 2025-04-28 19-43-12](https://github.com/user-attachments/assets/6a2f851a-a0aa-41c3-8364-6d864a864898)
<br />
## Colored light

![Colored_light](https://github.com/user-attachments/assets/6c3824e6-e2b0-46ed-a709-40ba31aa014a)
## Two cylinders
![Screenshot from 2025-04-28 19-43-12](https://github.com/user-attachments/assets/217f6966-85d0-40a1-8428-8acbf31fecfd)
## Marbles 
![marbles0_8](https://github.com/user-attachments/assets/bdbe0a5e-a802-4856-8839-dfbf4e6387a9)

## Snowman
![snowman](https://github.com/user-attachments/assets/d9077693-5644-4620-b5e3-9c25ddfe403e)

Our first RayTracer with miniLibX
miniLibX is [explanation].

# Function Return Value Conventions

This project utilizes distinct return value conventions to enhance clarity and maintainability.

For functions indicating the success or failure of an operation, standard practice is followed: `SUCCESS` is defined as `0`, and `FAILURE` as `1`. This aligns with common C programming conventions.

For functions representing boolean "yes/no" or "true/false" conditions, the `stdbool.h` library is included to enable the use of `true` and `false`. To improve readability, boolean checks are explicitly written in the form `if (is_empty_file(filename) == true)`, emphasizing the intended condition.

# Window Creation

The program utilizes the MiniLibX (MLX) library to create a graphical window. This window serves as the primary display for the rendered scene.

**Function: `mlx_new_window()`**

The core function responsible for window creation is `mlx_new_window()`, which is provided by the MiniLibX library.

**Implementation:**

In our program, the window is instantiated within the `setup_mlx()` function. The following code snippet demonstrates its usage:

`mlx_new_window(rt->cf.mlx, 800, 600, "42 MinilibX Window");`

In this example, a default size of 800 pixels wide and 600 pixels high is used. However, these values can be adjusted to create windows of different sizes as needed.

# Viewport Definition

In our 3D raytracing scene, the viewport acts as the 2D window through which we visualize the 3D world.

Think of the viewport as the "canvas" we'll later display using minilibx. It mirrors the aspect ratio of our output window, and the width of this canvas is determined by the FOV.

Essentially, the viewport acts as a bridge between the 3D scene and the 2D image we render.

In 3D space, the viewport is a rectangular plane defined by:

* Camera Position (C): The location of the camera in 3D space.
* Orientation Vector (o): A normalized vector (length of 1) that indicates the direction the camera is facing.
* **Field of View (FOV):** This angle determines the horizontal extent of the visible scene, directly influencing the viewport's width.

# Set Up the Viewport

* **A center point:** This anchors the viewport's position.
* **Width and height:** These dimensions are crucial for determining which points fall within the viewport's boundaries, distinguishing them from the infinite expanse of a general 3D plane.
* **Two vectors:** Two perpendicular vectors that define the viewport’s plane. 

**Calculate the Center of the Viewport**

`VPc = C + o`

This finds the point directly in front of the camera, at a distance of 1 unit in the direction of the orientation vector. This point is the center of the viewport plane.

**Determine the Viewport Plane**

The viewport plane is perpendicular to the orientation vector (o) and passes through the Viewport Center (VPc).

**Calculate Viewport Dimensions (Width and Height in 3D Space)**

Key Components:
* `M_PI` is a constant that represents the mathematical value of π (pi).
* `Radians` are a unit of angular measurement. Many programming languages and graphics libraries use radians for their trigonometric functions.
* `isnan` - floating-point classification macro. It checks whether a floating-point number (width in case of calculating width) is NaN (Not a Number). In C, NaN (Not a Number) is a special floating-point value that represents an invalid or undefined mathematical result.
* `Radian_FOV` - The camera’s horizontal field of view in degrees (converted to radians).

The viewport size depends on the horizontal field of view (FOV) and the chosen distance:

`Viewport_Width = 2 * (Viewport_Distance * tan(Radian_FOV / 2))`

To maintain the correct aspect ratio, the viewport height is calculated as:

`Viewport_Height = Viewport_Width / Aspect_Ratio`

**Basis Vectors (right and up) for Viewport Orientation**

When we say "basis vectors", we are referring to a special set of vectors that define the orientation and coordinate system for the viewport in 3D space.

To correctly place the viewport, we need two perpendicular vectors that define the viewport’s plane. The magnitude of the VPs Horizontal and Vertical vectors are the difference between two pixels in that direction.

Why Do We Need Basis Vectors for the Viewport?

Your camera doesn’t necessarily align with the world’s x, y, and z axes. Instead, we need a local coordinate system for the viewport, defined by three new basis vectors:

* Forward vector (camera direction) → "z-axis"

This is the normalized direction the camera is looking at.

* Right vector (horizontal axis) → "x-axis"

This is perpendicular to the forward vector and is usually computed using the cross product.

* Up vector (vertical axis) → "y-axis"

This is perpendicular to both the forward and right vectors.

These three vectors together form a new basis for the viewport's orientation.

Key Components:
* `world up vector` is a fixed reference vector that defines the upward direction in the global (world) coordinate system. In most cases we use `Z axis` as a world up vector.

**Calculate the Horizontal and Vertical Step Vectors for Pixels**

Each pixel in the final image corresponds to a small area in the viewport. We need to know how much to move in the horizontal and vertical directions when tracing rays.

To determine the position of each pixel, we calculate step vectors for horizontal and vertical movement:

`Pixel_Step_Horizontal = (Viewport_Width / Image_Width) * Right_Vector`
`Pixel_Step_Vertical = (Viewport_Height / Image_Height) * (-Up_Vector)`

(The negative sign in the vertical step ensures the image is oriented correctly.)

**Find the Upper-Left Corner of the Viewport**

The viewport corners are calculated based on the viewport center, width, height, and the basis vectors.

# How to use the Viewport

Now that we have the Viewport and its Total width and height, we can calculate the position of each individual Pixel in this 3D space by dividing the width by the total number of Pixels in a row and the height with those in a column. 

Instead of fixed positions, you can also calculate each vector to move horizontally and vertically to access each pixel by scaling the vectors with full numbers. 

# Ray Generation (Rendering Phase)

**Pixel Position Calculation**

For a pixel at row i, column j, its position in 3D space is:

`Pixel_Position = Top_Left_Corner + j * Pixel_Step_Horizontal + i * Pixel_Step_Vertical`

**Ray Direction Calculation**

"In the real world, light comes from a light source (the Sun, a light bulb, and so on), bounces off several objects, and then finally reaches our eyes.
Instead, we’ll consider the rays of light “in reverse”; we’ll start with a ray originating from the camera, going through a point in the viewport, and tracing its path until it hits some object in the scene. This object is what the camera “sees” through that point of the viewport." 
(c) https://www.gabrielgambetta.com/computer-graphics-from-scratch/02-basic-raytracing.html

Each ray starts from the camera position and points toward the pixel. Normalization ensures all rays have the same step size.
Note: We’ve already normalized the basis vectors when setting up the viewport; you don't need to normalize the ray direction again when calculating each ray.

`Ray direction = (Pixel position - Camera position)`

# The Ray Equation

Key Components:
* O - the origin point (the camera position).
* V - the point on the viewport (the representation of the pixel).
* t  - is any real number.

We can express any point P in the ray as:

`P = O + t(V−O)`

# Edge cases that we handled

1. Error: Camera is embedded in the plane.
File: camera_on_plane.rt

2. Error: Camera is embedded in the plane.
Error: Warning! The camera's direction is exactly in the plane.
File: camera_dir_on_plane.rt

3. Message: Camera inside a sphere
File: inside_sphere.rt

4. Camera inside a cylinder
Error: "Camera inside a Cylinder."

Error and exit when the configuration file is misconfigured or the filename doesn't end with the `.rt` extention. Also the program displays proper message in case there is no read permission or no such file or directory.

Files for these tests in `rt_files/invalid_config/`

And more.

# The almost last but not least
### EPSILON Macro instead of zero in calculation

Floating-point numbers can be very slightly off, even when they’re theoretically zero. We use an epsilon.

Otherwise, it may fail to detect the camera on the plane due to tiny floating-point errors.

We use EPSILON in light-shadow calculations. It helped to avoid artifacts such as shadow acne, which occurs when a surface incorrectly shadows itself due to floating-point inaccuracies. By offsetting the hit point slightly along the surface normal, we ensured that secondary rays (like shadow rays) don't falsely detect intersections with the surface they originated.

# # Fun issues we had during implementation
First picture without light calculations
![Screenshot from 2025-04-12 16-49-01](https://github.com/user-attachments/assets/03a9a374-7c75-41ee-8378-504d12725278)
Shadow acne
![Spheres_acne](https://github.com/user-attachments/assets/af93e159-be41-413e-ab86-a115598e1cea)
Weird shadows of the cylinder
![Screenshot from 2025-05-01 20-23-19](https://github.com/user-attachments/assets/52e6026e-2758-4379-8bfb-b6e81524ae92)
A cylinder without a bottom
![Screenshot from 2025-04-28 15-04-52](https://github.com/user-attachments/assets/79ca331a-aff3-433a-8033-074cfa6f9ebb)

# 🧊 Bonus
If you're still reading this, try running my favorite scene:
```
./miniRT scenes/snowman_nice.rt
```
He's chill. Literally.


(c) Maryna Peshko and Stephanie Patricia Gramsch, 2025, Berlin


---

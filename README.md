# MiniRT
Maryna and Stephanie's MiniRT.<br />
A 42 school project written in C language that uses the ray tracing technique for CGI.

The goal of this program is to generate images using the Raytracing protocol.Those computer-generated images will each represent a scene, as seen from a specific angle and position, defined by simple geometric objects, and each with its own lighting system.

Ray tracing is a technique for modeling light transport to generate digital images.

Our first RayTracer with miniLibX
miniLibX is [explanation].

## Function Return Value Conventions

This project utilizes distinct return value conventions to enhance clarity and maintainability.<br />
For functions indicating the success or failure of an operation, standard practice is followed: `SUCCESS` is defined as `0`, and `FAILURE` as `1`. This aligns with common C programming conventions.<br />
For functions representing boolean "yes/no" or "true/false" conditions, the `stdbool.h` library is included to enable the use of `true` and `false`. To improve readability, boolean checks are explicitly written in the form `if (is_empty_file(filename) == true)`, emphasizing the intended condition.

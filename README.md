# Simple 3D Rendering with Raylib

Rendering 3D objects using projection.

![Screenshot of spnning donut!](/assets/donut.png)


## Methodology

A concise 3D rendering was done by using the equation below:

$$
x' = x / z \\
y' = y / z
$$

Coordinates for the torus was generated using the equation below:
$$
x = (R + r\cos\phi)\cos\theta \\
y = (r\sin\phi) \\
z = (R + r\cos\phi)\sin\theta
$$

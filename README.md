# Simple 3D Rendering with Raylib

Rendering 3D objects using projection.

![Screenshot of spnning donut!](/assets/donut.png)


## Methodology

A concise 3D rendering was done by using the equation below:

$$
\begin{aligned}
x' &= x / z \\
y' &= y / z
\end{aligned}
$$

Coordinates for the torus was generated using the equation below:

$$
\begin{aligned}
x &= (R + r\cos(\phi)) \cdot \cos(\theta) \\
y &= (r\sin(\phi)) \\
z &= (R + r\cos(\phi)) \cdot \sin(\theta)
\end{aligned}
$$

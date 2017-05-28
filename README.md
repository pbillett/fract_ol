# fractol
This project consist to create graphically some nices fractals


Compile both on Mac and Linux without any problem. (with X11)

# How to launch :

- git clone http://github.com/pbillett/fractol.git && cd fractol
- make re && ./fractol [with name of fractal: mandelbrot, julia, burningship, triangle_sierpinski]

# Shortcut :

<h3>Mouse:</h3>

- Scroll wheels: Zoom inside fractal
- Left click (used on Julia): Play/pause motion
- Right click: Reinitialize fractal(when changing fractal, or not seeing anything)

<h3>Keyboard:</h3>

- Arrow keys (R/L/Up/Dwn): Move inside fractal
- Tab: Random Color
- Numpad 1/2/3/4: change to other fractal (mandelbrot/julia/triangle_sierpinski/burningship) (use right click to reinitialize)
- Numpad +/-: Incremente fratacal details (Warning increase could make rendering slower)
- 1/2/3/4/5 numbers : Predefined julia fractal set. (after Pausing Motion with mouse left click)
- Adjust Color:
        min/-/+/max
  - R:  z/e/r/t
  - G:  d/f/g/h
  - B:  c/v/b/n
- Escape: Quit

Ps: Warning, this project are not currently using openCL to accelerate rendering.
On some processors(ex: on linux config), a good way to accelate the rendering is simply to 
reduce the size from 1000x1000 to 540x480 in fractol.h and recompile with make re.

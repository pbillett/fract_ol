![Alt text](img/fractol_scrot_1.png?raw=true "Fractol")
![Alt text](img/fractol_scrot_2.png?raw=true "Fractol")
![Alt text](img/fractol_scrot_3.png?raw=true "Fractol")
![Alt text](img/fractol_scrot_4.png?raw=true "Fractol")
![Alt text](img/fractol_scrot_5.png?raw=true "Fractol")
![Alt text](img/fractol_scrot_7.png?raw=true "Fractol")
![Alt text](img/fractol_scrot_8.png?raw=true "Fractol")
![Alt text](img/fractol_scrot_9.png?raw=true "Fractol")
![Alt text](img/fractol_scrot_10.png?raw=true "Fractol")
![Alt text](img/fractol_scrot_11.png?raw=true "Fractol")
![Alt text](img/fractol_scrot_12.png?raw=true "Fractol")
![Alt text](img/fractol_scrot_13.png?raw=true "Fractol")
![Alt text](img/fractol_scrot_14.png?raw=true "Fractol")
![Alt text](img/fractol_scrot_15.png?raw=true "Fractol")
![Alt text](img/fractol_scrot_16.png?raw=true "Fractol")
![Alt text](img/fractol_scrot_17.png?raw=true "Fractol")
![Alt text](img/fractol_scrot_18.png?raw=true "Fractol")
![Alt text](img/fractol_scrot_6.png?raw=true "Fractol")
![Alt text](img/fractol_scrot_19.png?raw=true "Fractol")
![Alt text](img/fractol_scrot_21.png?raw=true "Fractol")
![Alt text](img/fractol_scrot_22.png?raw=true "Fractol")
![Alt text](img/fractol_scrot_23.png?raw=true "Fractol")

# fractol
This project consist to create graphically some nices fractals

Compile both on Mac and Linux without any problem. (with X11)

# How to launch :

- git clone http://github.com/pbillett/fractol.git && cd fractol
- make re && ./fractol [with name of fractal: mandelbrot, julia, triangle_sierpinski, burningship]
<code>

      example : ./fractol mandelbrot -> launch Mandelbrot
      
                ./fractol julia -> launch Julia
                
                ./fractol triangle_sierpinski -> launch Triangle Sierpinski
                
                ./fractol burningship -> launch Burningship  
</code>

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


<i>Ps: Warning, this project are not currently using openCL to accelerate rendering.
On some processors(ex: linux), a good way to accelate the rendering is to reduce the
windows size from 1000x1000 to 540x480 in fractol.h and recompile with make re.</i>

# Compilation possible issues

<h3>Linux</h3>

- Compilation of the Minilibx under Linux needs X11 and Xext dependencies, to install them simply enter this command:
- sudo apt-get install libx11-dev && sudo apt-get install libxext-dev (You should now found all the file under /usr/include/X11/).
- for an eventual problem of use of strlcpy, just comment the line in the file ./minilibx/mlx_xpm.c and uncomment the line just over it that use strcpy.

<h3>Mac</h3>

- Compiltation on Mac should not have any pb issue. As framework OpenGl and framework appKit should be installed by default,
- But if not just use this command line instead of classic make re.
- gcc -o fdf *.c -lm -L libft -lft -L minilibx_macos -L/usr/local/lib/ -I/usr/local/include -lmlx -framework OpenGL -framework AppKit</br>

That's it !
You should now be able to run this project on Mac and Linux.
Enjoy !

# miniRT  
Basic raytracing engine on C using MiniLibX.  

#### Build it yourself

- **sudo apt-get install gcc make xorg libxext-dev libbsd-dev**  
- **(Only using WSL) Install [XMing](https://sourceforge.net/projects/xming/) on your Windows 10 (just click next, it's ok)**  
- **make all**  

#### .rt file syntax

- **R [int] [int]** *// display resolution (at the moment only 1:1)*  
- **A [float] [int],[int],[int]** *// ambient lighting: intensity, color RGB*  
- **c [int],[int],[int] [int],[int],[int] [int]** *// camera: position, rotation angle as normalized vector, fov*  
- **sp [int],[int],[int] [float] [int],[int],[int] [float] [int]** *// sphere: position, radius, color RGB, reflection rate, specular rate*  

#### Usage

- **./miniRT map.rt --save // --save: save render as bmp file**  
- **Relish**  

#### Example

![Beautiful render](https://github.com/awend0/miniRT/blob/master/screenshots/image.jpg?raw=true)

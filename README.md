# miniRT  
Basic raytracing engine on C using MiniLibX.  

#### Build it yourself

- sudo apt-get install gcc make xorg libxext-dev libbsd-dev  
- (Only using WSL) Install [XMing](https://sourceforge.net/projects/xming/) on your Windows 10 (just click next, it's ok)  
- make all  

#### .rt file syntax

- R [width] [height] *// display resolution (at the moment only 1:1)*  
- c [x],[y],[z] [rotation x],[rotation y],[rotation z] [FOV] *// camera*  
- A [intensity] [R],[G],[B] *// ambient lighting
- l [x],[y],[z] [intensity] [R],[G],[B] *// point lighting*
- sp [x],[y],[z] [radius] [R],[G],[B] [reflection rate] [specular rate] *// sphere*
- tr [x],[y],[z] [x],[y],[z] [x],[y],[z] [R],[G],[B] [reflection rate] [specular rate] *// triangle*
#### Usage

- ./miniRT map.rt --save *// --save: save render as bmp file*  
- Relish  

#### Example

![Beautiful render](https://github.com/awend0/miniRT/blob/master/screenshots/image.jpg?raw=true)

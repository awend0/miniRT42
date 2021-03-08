# miniRT  
Basic raytracing engine on C using MiniLibX.  

#### Build it yourself

- sudo apt-get install gcc make xorg libxext-dev libbsd-dev  
- (Only using WSL) Install [XMing](https://sourceforge.net/projects/xming/) on your Windows 10 (just click next, it's ok)  
- make all  

#### .rt file syntax

- R [width] [height] *// display resolution*  
- c [X],[Y],[Y] [rotation X],[rotation Y],[rotation Z] [FOV] *// camera (rotation as normalized vector)*  
- A [intensity] [R],[G],[B] *// ambient lighting  
- l [X],[Y],[Z] [intensity] [R],[G],[B] *// point lighting*  
- sp [X],[Y],[Z] [radius] [R],[G],[B] [reflection rate] [specular rate] *// sphere*  
- tr [X],[Y],[Z] [X],[Y],[Z] [X],[Y],[Z] [R],[G],[B] [reflection rate] [specular rate] *// triangle*  
- cy [X],[Y],[Z] [X],[Y],[Z] [R],[G],[B] [diameter] [height] [caps, 0 or 1] [reflection rate] [specular rate] *// cylinder*  
- ds [X],[Y],[Z] [X],[Y],[Z] [radius] [reflection rate] [specular rate] *// disc* 
- sq [X],[Y],[Z] [X],[Y],[Z] [side size] [R],[G],[B] [reflection rate] [specular rate] *// square*

#### Usage

- export DISPLAY=$(cat /etc/resolv.conf | grep nameserver | awk '{print $2}'):0.0 *// WSL only*  
- export DISPLAY=localhost:0.0 *// WSL(1) only*  
- ./miniRT map.rt --save *// --save: save render as bmp file*  
- Relish  

#### Examples

![Beautiful render](https://git.chokemachine.ru/awend0/test/-/blob/master/screenshots/room.jpg)  
![Another render](https://git.chokemachine.ru/awend0/test/-/blob/master/screenshots/simple.jpg)

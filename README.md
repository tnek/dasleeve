# Da Sleeve

[![](http://s3-ap-southeast-1.amazonaws.com/ima-wp/wp-content/uploads/sites/5/2018/03/23204139/IMG_1252-300x225.jpg)](http://s3-ap-southeast-1.amazonaws.com/ima-wp/wp-content/uploads/sites/5/2018/03/23204139/IMG_1252.jpg)

Kent Ma & Leon Chou

Da Sleeve is a fabric gauntlet that uses bluetooth and accelerometer data to remotely control a computer's mouse based on motion. It moves the mouse up when the user's arm is raised, down when they're lowered, and left or right when they twist it left or right.  


## Physical Design

With Marcela's donation of velcro and instruction with the sewing machine, we sewed together the main sleeve to be attached by velcro.         

[![](http://s3-ap-southeast-1.amazonaws.com/ima-wp/wp-content/uploads/sites/5/2018/03/25153626/IMG_1218-300x225.jpg)](http://s3-ap-southeast-1.amazonaws.com/ima-wp/wp-content/uploads/sites/5/2018/03/25153626/IMG_1218.jpg) 

The accelerometer is on top of the sleeve, roughly where the top of the hand is. 

[![](http://s3-ap-southeast-1.amazonaws.com/ima-wp/wp-content/uploads/sites/5/2018/03/25154328/IMG_8255-300x225.jpg)](http://s3-ap-southeast-1.amazonaws.com/ima-wp/wp-content/uploads/sites/5/2018/03/25154328/IMG_8255.jpg) 

While testing, we noticed the sleeve kept slipping from it's own weight, preventing the accelerometer itself from moving when the user moves their arm. So, we cut a thumb hole to help keep the sleeve in place.

[![](http://s3-ap-southeast-1.amazonaws.com/ima-wp/wp-content/uploads/sites/5/2018/03/25154741/IMG_0511-268x300.jpg)](http://s3-ap-southeast-1.amazonaws.com/ima-wp/wp-content/uploads/sites/5/2018/03/25154741/IMG_0511.jpg)


#### Future Physical Sleeve Improvements:

**Buttons should be on the palm of the sleeve****.** When testing, we noticed people had difficulty reaching the buttons with their other hand while controlling or stabilizing the sleeve. Putting the button on the palm makes it entirely controllable with one hand, and also makes it more accessible. 

**Wrist component of the sleeve should be separate**. This allows the accelerometer to always align with the back of the hand for a consistent and correct experience. We had problems fitting the sleeve on people with significantly larger or smaller arms while maintaining the correct position for the accelerometer. 

**Less velcro.** It was difficult to take the sleeve off since the velcro extended far into the bottom of it. 

**Flap to remove the battery**. We sewed the battery into the sleeve, but without an easy way to remove it. However, the battery pack itself broke prior to demo day and we didn't have any way to replace it without cutting the sleeve open. 

**Storage for wires**. The battery comes with two wires: one to plug into the arduino and one to charge the battery. There was nowhere to keep the charging port when not charging, so it awkwardly hung out of the sleeve. Similarly, the electronic components were velcroed on to the sleeve instead of a proper storage compartment. 

**More intuitive thumb hole**. It isn't apparent without instruction which finger to put through the thumb hole, and the accelerometer doesn't properly align to the palm with other fingers on the thumb hole. 

**More comfortable/softer fabric.** The sleeve's kinda itchy.  


## Electrical

Components:

*   1 3-Axis Accelerometer ±16g
*   1 HC-06 Bluetooth Serial Module
*   1 Arduino Uno
*   1 DFRobot Prototyping shield
*   2 Buttons
*   2 10k resistors

Initially, we planned on the sleeve having the ability to dead reckon with the screen. That is, an exact 2D position of the arm determines the position of the mouse cursor. However, the equipment room doesn't have a gyroscope - it only had an accelerometer. As a result, there isn't a way to determine that the accelerometer's coordinate system has been rotated with respect to another coordinate system (necessary for double integration from acceleration into position). So we switched to it being just general mouse control using only the accelerometer. 

[![](http://s3-ap-southeast-1.amazonaws.com/ima-wp/wp-content/uploads/sites/5/2018/03/25153420/28946540_1743552932350835_1542100521_o-225x300.jpg)](http://s3-ap-southeast-1.amazonaws.com/ima-wp/wp-content/uploads/sites/5/2018/03/25153420/28946540_1743552932350835_1542100521_o.jpg) 

Additionally, a mouse needs to be able to click, so we used two buttons included in our kit to make mouse buttons. As usual, buttons wired to Arduino digital pins require the two 10k ohm resistors. 

[![](http://s3-ap-southeast-1.amazonaws.com/ima-wp/wp-content/uploads/sites/5/2018/03/23232011/IMG_0393-300x225.jpg)](http://s3-ap-southeast-1.amazonaws.com/ima-wp/wp-content/uploads/sites/5/2018/03/23232011/IMG_0393.jpg)  


#### Future Electrical Improvements:

**Use a smaller microcontroller & smaller battery: **Arduino Nanos or Minis are drastically smaller, making it a less cumbersome sleeve. Or, we could print our own PCB with an atmega chip to go even smaller. 

**Use an HID class bluetooth module**: This eliminates a lot of future low level programming, since the device would be able to directly register as a mouse device by the OS. 

**Alternatively, use a gyroscope for dead reckoning**. Basically, do what we originally wanted to do.  


#### Future Programming Improvements:

**Mouse motions should be interpolated.** Currently, the mouse slightly teleports to move - this is because it is doing rapid linear motion between points per-update instead of being properly interpolated like a real mouse.  

**Dynamically timing exact mouse movement events for S_PER_UPDATE. **Instead of trial-and-error to come about the value of 0.3 on my laptop, it should try to time how long it takes for a mouse movement function to complete so that it can adapt to any computer.

# Flair 58 EVA Mod
### EVA (Espresso Via Actuator)

Off the Shelf Hardware: 
- ESP32: [Amazon](https://www.amazon.com/dp/B089F6BY3C?psc=1&ref=ppx_yo2ov_dt_b_product_details)
    - Should work.
- Linear Actuators: [RobotDigg](https://robotdigg.com/product/1815/9-36VDC-stepper-motor-gear-drive-linear-actuator)
    - Two needed to achieve the pressure and maintain actuator speed.
- TMC2209 Driver: [Amazon](https://www.amazon.com/dp/B08DFV4QQ1?psc=1&ref=ppx_yo2ov_dt_b_product_details)
    - To be tested still. 
- 24v to 5v Converter:  [Amazon](https://www.amazon.com/dp/B08NZV88MC?psc=1&ref=ppx_yo2ov_dt_b_product_details)
    - To power the ESP32 from the PSU if not using another source.
- 150w 24v PSU:  [Amazon](https://www.amazon.com/dp/B077B7DHYL?psc=1&ref=ppx_yo2ov_dt_b_product_details)
    - Provides 24v to drive the steppers/actuators. 

Custom Hardware:
- Custom lever hinges.
    - Currently 3D Printed for testing purposes. 
- Custom lever hinge pins. 
    - TBD.


All in, off the shelf parts should be about $175, varying based on shipping. 

Custom hardware, estimating $20 to $100 depending on process and finish. 

**The (long term) plan:** ESP32-Hosted webserver, serving a page via localhost to control the actuators and enable automated pressure profiling. 
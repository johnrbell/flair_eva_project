# Flair 58 EVA 
#### EVA (Espresso Via Actuator)

Hardware: 
- ESP32: https://www.amazon.com/dp/B089F6BY3C?psc=1&ref=ppx_yo2ov_dt_b_product_details
    - I think any should work? 
- Linear Actuators: https://robotdigg.com/product/1815/9-36VDC-stepper-motor-gear-drive-linear-actuator
    - Two needed to achieve the pressure and maintain actuator speed.
- TMC2209 Driver: https://www.amazon.com/dp/B08DFV4QQ1?psc=1&ref=ppx_yo2ov_dt_b_product_details
    - To be tested still. 
- 24v to 5v Converter: https://www.amazon.com/dp/B08NZV88MC?psc=1&ref=ppx_yo2ov_dt_b_product_details
    - To power the ESP32 from the PSU if not using another source.
- 150w 24v PSU: https://www.amazon.com/dp/B077B7DHYL?psc=1&ref=ppx_yo2ov_dt_b_product_details
    - Provides 24v to drive the steppers/actuators. 

All in, should be about $175. 

The (long term) plan: ESP32-Hosted webserver, serving a page via localhost to control the actuators and enable automated pressure profiling. 
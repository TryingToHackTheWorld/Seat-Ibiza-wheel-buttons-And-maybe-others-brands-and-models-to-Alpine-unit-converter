# Seat-Ibiza-buttons-to-Alpine-unit-converter
Arduino code to convert digital Seat Ibiza 6l steering wheel buttons signals to analog Alpine unit

All the codes has been tested in an arduino nano clone.

 - Simply program Arduino board with code "" and connect cables following the schema

If you're not sure if code is valid or you want to try to adapt it to another car, those are the steps I followed to develop the final code:
 - Load "_First_step_-Simply_Voltage_Reader" in the Ardunio board
 - Connect positive signal of the wheel buttons to pin analog 5
 - Connect negative signal of the wheel buttons to GND pin
 - Open serial monitor (230400 baud) and press one wheel buttons a couple of times to obtain maximum and minimum voltage
 - Add the maximum voltage as "MaxVol" in "_Second_step_-Digital_RAW_Read"
 - Load "_Second_step_-Digital_RAW_Read" in the Arduino board
 - Open serial monitor (230400 baud) and press different buttons several times
 - Search the lowest time (In my case around 550)
 - Add the lowest time as "LowTime" in "_Third_step_-Specific_Button_Read"
 - Add the maximum voltage as "MaxVol" in "_Third_step_-Specific_Button_Read"
 - Load "_Third_step_-Specific_Button_Read" in the Arduino board
 - Open serial monitor (230400 baud) and press each button
 *********************************************************
 - At this point you can see the digital signal received in Arduino. You must identify the changes between the buttons to continue with the last part
 *********************************************************

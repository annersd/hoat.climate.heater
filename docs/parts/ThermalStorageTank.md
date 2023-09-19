# Thermal Storage Tank
The "Thermal storage Tank" stores heat in water. 
It uses differnt heat exhanger to store or expose heat. It also has thermometers which give the current temperature at differnet positions in the water stack.

Properties:
Heat Capacity: The Storage has a maximum of kWH it can store.

Temperatures:
from lower to hicher areas in the stack
- temp_1
- temp_2
- temp_3
- temp_4

## Events

### Current Status
The Storage reports its temperatures and approximal current used capacity 

Payload
``` json
{
  "chargeLevel": 2.51,
  "stackTemperatures": [12.5, 40.3, 58.9, 70.23]
}
```

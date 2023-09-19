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
The storage emits a status event

### Current Status
The Storage reports its temperatures and approximal current used capacity 

|property|type|description|
|--------|----|-----------|
| chargeLevel | float | The current charging Level of the complete Storage in watt/hour. This Level is an estamtion over all temperature zones. This means heat charger may not charge the storage, when the charging zone has a higher temperature.|

Payload
``` json
{
  "chargeLevel": 2.51,
  "stackTemperatures": [12.5, 40.3, 58.9, 70.23]
}
```
## Commands
The Storage has no commands

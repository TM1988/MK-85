# MK-85 Iron Man Helmet

This project is my take on the Iron Man MK-85 helmet.
Note: I am not very good at CAD, so some of the files may have issues

## Planned Features
- Motorized opening and closing mechanism controlled by a switch
- Voice assistant control for hands-free operation
- 3D-printed helmet design

## Pictures

<details>
<summary>Click to show!</summary>

### Wiring Diagram
<img src="https://github.com/TM1988/MK-85/blob/master/Images/Wiring%20Diagram.png?raw=true" width="500">

### Helmet Dome
<img src="https://github.com/TM1988/MK-85/blob/master/Images/Helmet%20Dome.png?raw=true" width="300">

### Faceplate
<img src="https://github.com/TM1988/MK-85/blob/master/Images/Faceplate.png?raw=true" width="300">

### Jaw
<img src="https://github.com/TM1988/MK-85/blob/master/Images/Jaw.png?raw=true" width="300">

### Lower Lip
<img src="https://github.com/TM1988/MK-85/blob/master/Images/Lower%20Lip.png?raw=true" width="300">

</details>

## Changelog

<details>
<summary> Click to show! </summary>

### Commit 1:
- Added 3D files for the outer helmet shell

### Commit 2:
- Updated Dome.3mf to include a missing mounting hole 
(This commit got deleted while trying to remove wrong files from history)

### Commit 3:
- Created faceplate.3mf for the faceplate
- Updated dome.3mf to smooth out some issues

### Commit 4:
- Created jaw.3mf for the jaw
- Fixed typo in the faceplate commit

### Commit 5:
- Created lowerlip.3mf

### Commit 6:
- Created Utility.3mf (Kit from https://www.thingiverse.com/thing:4607836)
- Created "Eye_Inside.3mf" and "Gold Jaw.3mf"

### Commit 7:
- Added "Code" folder containing my WOKWI project testing the code. Code is located inside src/main.cpp.

### Commit 8:
- Added Wiring Diagram to Pictures
- Added Assembly Instructions

</details>

## How to use

### Assembly Instructions
1. Press and glue 10x2mm magnets into the indents on both sides of the dome.
2. Repeat for the lower jaw. Make sure the jaw magnets attract the dome magnets.
3. Attach the lower jaw to the dome by aligning the magnets.
4. Glue the lower lip onto the top edge of the lower jaw.
5. Install the servos into the widow's peak area of the dome using the large casing from the Utility.3mf file.
6. Glue the small circular parts into the indents on the inside of the dome, then repeat for the corresponding indents on the faceplate.
7. Position the helper arms onto the installed circular parts and secure with M3 bolts.
8. Glue the piece from the Gold Jaw file onto the front face of the lower lip.
9. Following the included wiring diagram, install the remaining electronics and fasten them in available spaces. Placement may vary depending on your head size variant.

#### Large Casing:
<img src="https://github.com/TM1988/MK-85/blob/master/Images/Large%20Casing.png?raw=true" width="300">

#### Circular Parts:
<img src="https://github.com/TM1988/MK-85/blob/master/Images/Circular%20Parts.png?raw=true" width="300">

#### Helper Arms:
<img src="https://github.com/TM1988/MK-85/blob/master/Images/Helper%20Arms.png?raw=true" width="300">

### To run the simulation:
- Download VSCode (Unless you already have it)
- Download the WOKWI Extension and get a license
- Download the PlatformIO extension
- Clone the Repo
- Open PlatformIO from your sidebar and click "Pick a folder". Select the folder "MK-85 Helmet" inside the "Code" folder
- Click the checkmark at the bottom toolbar to build.
- Navigate to dragram.json
- If WOKWI is configured properly, it should show a simulation
- Press the start button and test.
- Video is available [here](https://drive.google.com/file/d/12uJFzC7YU4sSf6sAD5Qnprwmo6rfiqkf/view)

# B.O.M (Bill of Materials)

| Item # | Product | Qty | Total Price (USD)|
|---|---|---|---:|
| 1 | [Flexible Helmet LED Eyes](https://amoz.onl/55l) | 1 |13.98 (Business Account)|
| 2 | [DFROBOT Gravity Voice Recognition Module](https://www.amazon.com/gp/product/B0C5XG3BXW?smid=A2EH5PO307BR7O&psc=1)|1|16.40|
| 3 | MG90S Servos| 2 |6.8|
| 4 | M to F Dupont Cables| 1 |3.75|
| 5 | KW12-3 250V 5A limit switch (With NO, NC, Common) | 1 |2.49|
| 6 | 10mmx2mm Magnets | 1 |1.73|
| 7 | Sand Paper (Assorted) | 1 |0|
| 8 | M3 Screws (Assorted)| 1 |2.89|
| 9 | Arduino Nano | 1 |0.99|
| 10 | 3D Printed Helmet + Utility | 1 |--|
|11|[Spray Paint + Primer](https://docs.google.com/document/d/1boXkLBG06-nQ8r04DcoNFZOWzf_QpciWl75cyl6Dty0/edit?usp=sharing) |3|19.74|
|12|Hot Glue Gun|1|8.53|
|13|ScrewDriver Set|1|3.45|
|14|Wire Stripper + Gold Paint|1 ea|1.30 (Total)|

For Number 14, I have Amazon credit on stuff sold and shipped by them. So now it's just the tax. Also, the BOM does not account for Tax on parts.

Note: Each of these quantities is based on the Amazon listings; it's more like 1 of the listing.

Note 2: Unlinked parts are ordered from AliExpress for much better pricing, but direct links can't be provided due to fast-changing deals and inventory.

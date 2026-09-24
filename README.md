Petal - A Bionic Butterfly

<img width="1080" height="1350" alt="WhatsApp Image 2026-09-22 at 06 52 32 (1)" src="https://github.com/user-attachments/assets/2960924e-8996-4d87-91b1-f501c68fcd67" />

A small RC-controlled bionic butterfly built around an Arduino pro micro, two micro servos, and a FlySky receiver.

The project explores how a simple mechanical system can reproduce the flapping motion of a butterfly using coordinated servo movement. The firmware uses mathematical waveforms, including sine and triangular waves, to generate the wing motion.

The project is designed to be lightweight, reproducible, and easy to modify.

---

What Makes This Project Different?

Instead of simply reproducing an existing bionic butterfly build, this project focuses on understanding, modifying, and documenting the complete system, which provides guides for troubleshooting:

- Customised CAD design

<img width="1920" height="1080" alt="Screenshot 2026-09-22 003007" src="https://github.com/user-attachments/assets/d1a3f234-6187-4529-8838-9de488f11567" />


- Personalised mechanical components
- Two-servo wing actuation

<img width="1600" height="1204" alt="WhatsApp Image 2026-09-19 at 07 02 00 (2)" src="https://github.com/user-attachments/assets/c96029bd-7316-47a6-b29e-dd099ac26ad2" />


- Arduino pro micro or nano control
- FlySky RC control
- Sine-wave based wing motion
- Triangular-wave based wing motion
- Adjustable flapping parameters
- Documented electronics and wiring
- Reproducible build instructions
- Development and testing documentation

The project was developed iteratively, starting with individual servo tests and progressing toward the complete butterfly system.

---

Why I Made It

The idea for the Bionic Butterfly came to me after I saw some children in a park playing with butterflies and trying to catch them. It made me curious about whether I could recreate the movement of a butterfly using engineering rather than trying to replicate the entire animal. Later that same day, I came across mechanical design ideas and projects on GitHub, which inspired me to start designing my own version.
I wanted to understand how biological motion could be recreated using relatively simple electronics and mechanical components.
A butterfly is an interesting engineering problem because its wings require coordinated, repeated motion while remaining lightweight.
This project is also an experiment in learning engineering through building, documenting failures, and improving the design.

Inspiration:
Ken Jhonson's first butterfly design
<img width="557" height="547" alt="Screenshot 2026-09-22 073030" src="https://github.com/user-attachments/assets/d732cf80-aa55-4103-93b2-cf032548f6c2" />

Kazuhiko Kakuta - Butterfly and Ornitohopter designs.

Festo robotics company - Bionic blue butterfly
<img width="822" height="507" alt="Screenshot 2026-09-22 073316" src="https://github.com/user-attachments/assets/f2d12cf9-9c88-46b6-bdc9-cd2c7cb2cf66" />

S-Diy and Ctorque tech youtube channel's modern design.

---
 How It Works

The butterfly uses two micro servos to drive the wings.
The Arduino Nano receives control input from a FlySky receiver and generates the corresponding servo positions.
The firmware can generate different motion profiles, like a sine wave,
a sinusoidal function is used to create smooth periodic wing movement.
servo_position = center + amplitude × sin(phase) (kinda like this, check the diary section for more info and also the firmware)
This produces relatively smooth acceleration and deceleration throughout the wing stroke.


---

Hardware

Component| Quantity

Arduino pro micro | 1

Micro servos (PTK 7465MG) | 2

FlySky receiver (FS - A8S) | 1

Flysky transmitter (flysky fsi6) | 1

2S battery (lipo, 180 or 220 or even 350 mAh, but should be lightweight, under 11-12g) (25c or 30c or higher) | 1

Butterfly mechanical structure| 1

See ""BOM.csv"" (BOM.csv) for the complete bill of materials, links, and total cost.

---

Electronics

The Arduino pro micro acts as the main controller.
The FlySky receiver provides the control input, while the two micro servos provide the mechanical actuation.
The complete wiring diagram is available here:
"Wiring Diagram" (Electronics/wiring_diagram.png)

For detailed wiring and connection information, see:
- ""Electronics/wiring_notes.md"" (Electronics/wiring_notes.md)

---

 CAD

The project contains the editable CAD source files, exported STEP files, and STL files required for fabrication.

CAD files

- "CAD/STL/" — printable STL files

---

Firmware

The firmware is written for the Arduino pro micro.

Main firmware:
The firmware controls the two servos and implements the wing-motion algorithms.

Current motion modes include:
- Sine wave
- Triangular wave (to be done)

The firmware is intentionally documented so that parameters such as amplitude, frequency, center position, and control response can be modified.

Development & Testing

The project was developed incrementally rather than assembling everything at once.

The development process included:

1. Testing individual servos 
2. Testing servo range and direction 
3. Testing Arduino control 
4. Testing receiver input ( to be done )
5. Developing the wing-motion algorithm 
6. Comparing motion profiles ( to be done )
7. Integrating the mechanical system ( to be done )
8. Testing the complete butterfly ( to be done )
9. Recording problems and modifications ( to be done )
10. Preparing the final reproducible design ( to be done )

Early experiments and test code are available in:

""Initial_Test/"" (Initial_Test/)

Development photographs and screenshots are available in:

""Images/"" (Images/)

---
 Development Diary (Highly recommend checking it to understand the workflow)

I maintained notes during the research and development process.
this is like a design history file, research to modification to questions, everything is there.
Scanned/photographed diary pages are available in:
"" Diary/ "" (Diary/)

The diary documents the development process, research, decisions, experiments, and iterations behind the project.

---

---

References & Credits

This project was developed while studying existing open-source bionic butterfly projects and related designs.
Existing work was used as reference and inspiration rather than being presented as original work.
Where an existing design was modified or incorporated, the original creator and source are credited in:
""Documentation/references.md"" (Documentation/references.md)
S-DiY Bionic Butterfly
The S-DiY bionic butterfly project was studied as a reference for the general mechanical/electronic concept.
Ctorque CAD Model
A CTorque model was used as a starting or perhaps as reference point for part of the CAD development. The modified or personalised version in this repository is identified in the CAD documentation.

All third-party work remains credited to its respective creators.

---

License

See ""LICENSE"" (LICENSE) for the licensing information applicable to the original work in this repository.

Third-party designs and references remain subject to their respective original licenses.

---

Project Status

Current status: Functional prototype / final design in development
The project has progressed from individual component testing to an integrated bionic butterfly system.
In the repository there are a few ( to be done ) marks present, as that is a future goal and will be completed as soon as possible to completely finish the build.

---

Author

Rythm Raj
Student / independent maker
This project was built as a personal engineering project to learn mechanical design, electronics, embedded programming, and iterative prototyping.

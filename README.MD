#Requirements
The purpose of this project is to design and implement an embedded electronic system based stop watch.

The following minimum features are required:

- A button prompted stop watch 'reset' command. 
- A button prompted stop watch 'stop' and 'start' command.
- A bubble display that shows elapsed time in 1/100 seconds.

The following conditions must be satisfied:
- Precision of 10 ms max deviation within a 10 s timespan.
- Proof of button debouncing functionality.
- No delay() function used.
- Use of external interrupts.
- Use of MOSFETS to compensate for the microcontrollers' lmited current source and sink capability.

#System Design

#Implementation

##Single Digit Display
|Number          |Active Segments                |
|----------------|-------------------------------|
|0|abcdef   |
|1|bc       |
|2|abged    |
|3|abgcd    |
|4|fbgc     |
|5|afgcd    |
|6|afgecd   |
|7|abc      |
|8|afbgecd  |
|9|afbgc    |

#Integration and Testing

#Deployment of System

#Maintenance



# Requirements

The purpose of this project is to design and implement an embedded electronic system based stop watch.

The following minimum features are required:

- A button prompted stop watch 'reset' command. 
- A button prompted stop watch 'stop' and 'start' command.
- A bubble display that shows elapsed time in increments of 1/100 s (10 ms).

The following conditions must be satisfied:
- Precision of 10 ms (1/100 s) max deviation within a 10 s timespan.
- Proof of button debouncing functionality.
- No delay() function used.
- Use of external interrupts.
- Use of MOSFETS to compensate for the microcontroller's lmited current source and sink capability.

# System Design


# Implementation


## Single Digit Display

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

# Integration and Testing


# Deployment of System


# Maintenance

# References

https://arduino.stackexchange.com/questions/28092/how-do-i-split-a-number-into-individual-digits




# Lissajous Figures (C / SFML)

Lissajous shape simulator that draws a shape with a given frequency and amplitude

Over time, the accuracy of calculations and, as a result, the quality of rendering decreases. Therefore, after 5 thousand displayed
periods of the function, the period counter is reset. This effect is particularly noticeable when ...
Freq X = 40
Freq Y = 60
...especially if you stretch the amplitude by X across the entire width of the window.

By the way, during development, I accidentally discovered that when ...
Freq X = 19.99
Freq Y = 59.95
...the animation in 5 thousand periods is beautifully closed and there is no frame break when switching from the 5 thousandth value to
0 (or it is almost not noticeable).

## Controls
Keys                          |Description
------------------------------|-------------------------------------------------------
Up / Down                     |Slow changing of the oscillation frequency on Y-axis
Right / Left                  |Slowchanging of the oscillation frequency on X-axis
Ctrl + (Up / Down)            |Quickly changing of the oscillation frequency on Y-axis
Ctrl + (Right / Left)         |Quickly changing of the oscillation frequency on X-axis
Shift + (Up / Down)           |Slow changing of the oscillation amplitude on Y-axis
Shift + (Right / Left)        |Slow changing of the oscillation amplitude on X-axis
Shift + Ctrl + (Up / Down)    |Quickly changing of the oscillation amplitude on Y-axis
Shift + Ctrl + (Right / Left) |Quickly changing of the oscillation amplitude X-axis

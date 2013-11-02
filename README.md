ships_war
=========

Game in OpenGL using C when two ships fight using left and cannons

Assumptions:
1. The ship will not rotate until there is acceleration(i.e. until up button is held). But if the up button is release and all the movement buttons are released, the ship will stall but very slowly.
2. To read the code in proper structured manner open it in 90x45 terminal.
3. There are no boundaries for water, but the water is showed only in small area, so if the ship is moved outside the boundaries of displayed water, it will still behave like it is moving on water.
4. Ship is white in colour, negative axes is dotted line.

COMMANDS:
1. Compile  : make
2. Run      : make run
3. Clean    : make clean
4. Archive  : make archive

FUNCTIONALITY:
keyboard
    1. 'a'/'A'  : Axes toggle
    2. 'w'/'W'  : wireframe toggle
    3. '>'      : Increases speed of wave
    4. '<'      : Decreases speed of wave
    5. '-'      : halve water tessellation
    6. '+'      : double water tessellation
    7. 'n'/'N'  : normal lines toggle
    8. 'o'/'O'  : enable/disable shadows and lighting
    9. 'p'/'P'  : Emergency brake of ship
    10. esc     : quits the application
    11. up      : accelerate ship
    12. down    : decelerate ship
    13. left    : rotate ship left
    14. right   : rotate ship right
    15. 'd'     : increases the height of the waves
    16. 'f'     : decreases the height of the waves

mouse
    1. leftclick    : click and drag rotates the world
    2. rightclick   : click and drag up/down, zooms in/out


OTHERS:
1. There are two make files. 'makefile' for sutherland lab and 'makefile_mac' for mac computers(NOTE: If you are running on mac computer, change the name of makefile).

2. fps code is reference from this website
http://mycodelog.com/2010/04/16/fps/



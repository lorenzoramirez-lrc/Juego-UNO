UNO Game
===============
**Authors:** Lorenzo Ramírez Calderón, Danna Valentina Cano, Juan Pablo Vanegas, Laura Lesmes Ocampo

## General Description
Traditional UNO game programmed in the C++ programming language.
## User's Manual

**Compilation and Execution:** Insert the file in an integrated C++ development environment either web or local and compile the code. The game is developed in the terminal.


**Controls:** All controls are keyboard controls, all text entries are designed to enter whole numbers except for choosing the color and entering player names.


**Caution:** Entering an entry that is not an integer without counting exceptions will lead to program corruption and will have to be restarted.

**Rules:** The original rules of UNO are followed, in the variation of scoring in which at the end of each round the points of the remaining cards are added up for each player. At the end of the game the player with the lowest score is the definitive winner. 
The following table is followed for the scores:
<div align="center">
All cards with number (0-9) ................................Number value

Draw two......................................................................20 points 

Reverse........................................................................20 points

Skip................................................................................20 point 

Wild Card ....................................................................50 points 

Wild Draw Four Card ..................................................50 points 
</div>
 
**Card codes:** The cards follow a two character structure, the first one indicating the number (0 to 9) and the second one the color Blue (A), Gold(D), Red(R), Green(V), this structure is maintained except for the action cards that follow the following structure first character (B) skip, (S) draw 2, (R) reverse, second character respective color, and for the Wild cards draw four (4S) and color change (CC).
Example: 0A(Blue zero), RV (Reverse green), 8R (Red eight), SD(Draw 2 gold)


# Bubble

One class representing the bubble as a set of vertices (simple circle) that handle the random movement and bounces at the edges of the screen

# Board

a class called board which handle multiple bubbles and used to simplify the harder level as the number of balls get higher

# Game

a class called game which handle the score, death, timer, board and level
# Gameplay loop

infinite loop until flag "Is_Alive" isn't true, when players die, you display the score and offer the possibility to restart. Each level correspond to a difficulty

| Level | Difficulty |
| ----- | ---------- |
| 1     | 1          |
| 2     | 2          |
| 3     | 3          |
| ...   | ...        |
| X     | X          |


# Classes

| Name          | Description                                                                                                                                                                                     | Atributes                                                                                                                                                                |
| ------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| Ball (bubble) | a bubble the player can pop  <br>(random movement is handle  <br>by choosing a random direction  <br>(0 -> 360) and random speed,  <br>then calculating the corresponding  <br>X and Y Speeds ) | - Float : Size<br>- Float : X_Speed<br>- Float : Y_Speed<br>- Float : Max_Speed<br>- Float : Min_Speed<br>- Int : Direction<br>- Float : Speed                           |
| Board         | Handle multiple bubble                                                                                                                                                                          | - Int : Number<br>- Vector<"Ball"> : balls                                                                                                                               |
| Game          | Handle the gameplay                                                                                                                                                                             | - Bool : Is_Alive<br>- Bool : Win<br>- Int : Score<br>- Int : Combo<br>- Int : Current_Level<br>- Float : Time_Left<br>- sf::clock : Timer<br>- Board : Game_Board<br>-  |



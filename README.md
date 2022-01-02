# iCarrom

Group Number : 12

#### Library Used: SDL 2.0 

A Carrom game simulator made using C++ and SDL 2.0.

#### System Requirements : 

Works on Ubuntu (tested on 20.04 LTS) only due to library constraints of SDL 2.0 for various operating system   

## Team Members :

1. IMT2020502 : Monjoy Narayan Choudhury 
2. IMT2020034: Ankrutee Arora
3. IMT2020542: Sashank Reddy Budideti 
4. IMT2020006: Harsh Shah 
5. IMT2020509: Hardik Khandelwal 



## Contribution :

1.IMT2020502 - Monjoy Narayan Choudhury: 

1. Provided Starter code / object oriented structure for game design 
2. Implemented mouse movements and click events 
3. Integrated physics (independently made by other member) with graphics element 
4. Smoothened screen transitions between menu and help + game end to menu 
5. Testing and debugging.

2.IMT2020034 - Ankrutee Arora :

1. Added Main menu 
2. Rendered text for play and exit options
3. Transition from menu to game. 
4. Dealt with game loop conditions

3.IMT2020542: Sashank Reddy Budideti :

 



4.IMT2020006: Harsh Shah :

1. Arranged all coins on board 
2. Implemented friction on coins 
3. Rendered Texts using SDL_ttf
4. Added tracer on striker to enumerate trajectory  



5.IMT2020509: Hardik Khandelwal 
1. Created Physics engine: Resolving collision between coins, boards and net and handling collision penetration.
2. Integrated different game states and console events.
3. Contributed in algorithm for computer moves.
4. Created a few classes like Coin, Board, Vector etc. 



## Features of Game:

1. Realistic physics collisions between coins as well as between board and coins which obey the concepts involving impulse, penetration resolution and coefficient of restitution.
2. Leaderboard feature to keep track of high scores so that a user can find motivation to improve in the game.
3. Tracer facility when the striker is pulled to get trajectory estimates for precise shots.
4. Human like CPU player which adapts to the location of the coins during the game to simulate in-person game.

## Screenshots:

<img src="https://github.com/hardik5k/iCarrom/blob/main/Screenshot%20from%202022-01-01%2020-39-17.png" alt="Screenshot from 2022-01-01 20-39-17" style="zoom:50%;" />

<img src="https://github.com/hardik5k/iCarrom/blob/main/Screenshot%20from%202022-01-01%2021-05-54.png" alt="Screenshot from 2022-01-01 21-05-54" style="zoom:50%;" />

<img src="https://github.com/hardik5k/iCarrom/blob/main/Screenshot%20from%202022-01-01%2021-06-38.png" alt="Screenshot from 2022-01-01 21-06-38" style="zoom:50%;" />

## Instructions to Run: 

1) Clone this repository 

2. Open terminal and type the following command to compile

   `make iCarrom`

3. Run the game using command 

   `./iCarrom`

## Controls:

1. Set the striker in place using arrow keys (left and right)
2. Press enter to confirm the position
3. Now hover your mouse on the striker. When the pointer is on the striker, hold the mouse and pull it back in the direction of preference. Take help of the tracer to estimate the trajectory. Leave the button when satisfied 
4. Now wait till the computer make its move.  

## Demo :

A demo video highlighting the controls can be found at https://www.youtube.com/watch?v=whBVOhUi14Q


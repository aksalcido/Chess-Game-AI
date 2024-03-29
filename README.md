# Chess-Chess-AI
Console Version of Chess with Incorporation of:
  - Simple AI: relies on a random source of entropy for moves
  - Smarter AI: relies on the Minmax algorithm with Alpha-beta pruning

# Instructions
  Use the makefile to compile out and run the program
  
  #### Players
   - **White** is represented in **lowercase** characters.
   - **Black** is represented in **uppercase** characters.
  
  #### Pieces
   - King  : **K** or **k** 
   - Queen : **Q** or **q**
   - Rook  : **R** or **r**
   - Bishop: **B** or **b**
   - Knight: **H** or **h**
   - Pawn  : **P** or **p**
   
  #### Moves 
   - Moves are made in the following format: **row** **column** **destinationRow** **destinationColumn**
  
  ##### Example)
  <img src='images/Move Instructions.png'>

  
# Simple AI
Random Moves are made accordingly to a random source of entropy using the standard random library.

  #### Sample Play and Checkmate)
   <img src='images/Checkmate.png'>
    
# Slightly Smarter AI
Moves are made following the Minmax algorithm with Alpha-beta Pruning. Evaluation function is not perfect currently and needs to be updated to better score positions on the board.
 
 #### Sample Play)

### Future Updates:
  - Evaluation function not properly complete accordingly to best position in all cases
  - GUI?

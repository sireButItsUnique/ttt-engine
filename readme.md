## Inspiration
Engine to solve "Pokemon Tic Tac Toe" (a game introduced by my highschool physics teacher), as with some pruning it seemed very possible to solve, with an absolute maximum of just 27^12 possible lines

#### The rules are as follows
- There are two players: Team Squirtle (p1) and Team Charmander (p2)
- Each player has two cards of each pokemon in its evolution tree, that is:
    - p1 has
        - 2x Squirtle (a)
        - 2x Wartortle (b)
        - 2x Blastoise (c)
    - p2 has
        - 2x Charmander (A)
        - 2x Charmeleon (B)
        - 2x Charizard (C)
- Players take turns playing their Pokemon into a 3x3 tic tac toe grid
- Any evolution can be placed on top of an empty square or a weaker Pokemon, that is:
    - A cell is available for play if it is currently empty
    - A cell is available for play if it is occupied by something lexicographically smaller than the character to be played
    - This includes playing in a cell occupied by a player's own character
- A player wins when there exists 3 cells in a row occupied by their Pokemon
- Team Squirtle (p1) plays first because "type advantage"

## Findings
Unless there's a bug somewhere, proves the game can be drawn with optimal play (i.e. there is no winning strategy for either player)

Planning to add evaluation such that it will play move with highest chance of winning in the case of an expected draw. It should play some more sensical moves as, against a human, optimal play is not expected

## Usage
#### Position Commands:
```
position startpos
```
*Sets the board to the starting position*

```
position pos [position string]
```
*Sets the board to the position represented by [position string]:*

```
d
```
*Prints the currently set board*

#### Position Strings
Some inspiration was taken from FEN in the design of this format.
The initial position can be represented as
```
xxx/xxx/xxx 222222 1
```
Where: 
```
xxx/xxx/xxx
```
Represents the current board, as an empty space is represented by 'x'

```
222222
```
Represents how many of each piece is left. Specifically, each number in '222222' corresponds to 'aAbBcC'

```
1
```
Represents who is playing this turn

#### Searching
Note that there is no max ply for the search since there is at max 12 moves. It will search until a definitive evaluation for the current position (assuming optimal play from both sides) is found
```
go
```
*Finds the best move in the current position. Positive score means the player whose turn it is to play is winning, negative is losing, 0 means tie*

```
go d
```
*Finds the best move in the current position, and shows the PV line's progression*

#### Examples
Some interesting positions that don't just result in a draw:
```
position pos xxx/xcB/xxx 222112 1
position pos xxx/xcc/xxx 222102 2
position pos axx/Bcc/xxx 122002 2
position pos cCb/AcB/xxC 011000 1
position pos axx/xCx/xxC 121220 1
position pos Cxx/xcx/xxx 222211 1
```

The following position was analyzed IRL and was thought to be winning for p2, but, according to the engine, it's actually losing
```
position pos xxx/xcB/xxx 222112 1 
Setting position with: xxx/xcB/xxx 222112 1
d
+---+---+---+
|   |   |   | 
+---+---+---+
|   | c | B | 
+---+---+---+
|   |   |   | 
+---+---+---+
Pieces left: 
Player 1: a: 2 b: 2 c: 1
Player 2: A: 2 B: 1 C: 2
Turn: Player 1
Pos: xxx/xcB/xxx 222112 1
go 
bestmove (a:0, 0) score 991
go d
Score: 991
Moves:
1. (a:0, 0)
+---+---+---+
| a |   |   | 
+---+---+---+
|   | c | B | 
+---+---+---+
|   |   |   | 
+---+---+---+
Pieces left: 
Player 1: a: 1 b: 2 c: 1
Player 2: A: 2 B: 1 C: 2
Turn: Player 2
Pos: axx/xcB/xxx 122112 2
2. (B:0, 0)
+---+---+---+
| B |   |   | 
+---+---+---+
|   | c | B | 
+---+---+---+
|   |   |   | 
+---+---+---+
Pieces left: 
Player 1: a: 1 b: 2 c: 1
Player 2: A: 2 B: 0 C: 2
Turn: Player 1
Pos: Bxx/xcB/xxx 122012 1

...

9. (b:2, 0)
+---+---+---+
| c | C | b | 
+---+---+---+
| A | c | B | 
+---+---+---+
| b |   | C | 
+---+---+---+
Pieces left: 
Player 1: a: 0 b: 0 c: 0
Player 2: A: 1 B: 0 C: 0
Turn: Player 2
Pos: cCb/AcB/bxC 010000 2
```
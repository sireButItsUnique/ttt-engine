### Goal
Engine to solve "pokemon tic tac toe" (a game introduced by my highschool physics teacher)

The rules are as follows:
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
- p1 plays first 

### Findings
Unless there's a bug somewhere, proves game can be drawn with optimal play (i.e. there is no winning strategy for either player)

Planning to add eval to play move with highest chance of winning in the case of an expected draw, as against a human, optimal play is not expected  
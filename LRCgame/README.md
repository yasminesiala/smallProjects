# LCR — Left/Center/Right Game

Simulates the dice game Left, Center, Right in C. The game is entirely chance-based: players roll dice and pass chips according to the roll.  

## How It Works
- Players start with 3 chips and sit in a circle.  
- Dice rolls (0–5) are mapped to symbols: DOT (0–2), LEFT (3), CENTER (4), RIGHT (5).  
- Each turn, a player rolls one die per chip (max 3) and updates chips:
  - **DOT:** do nothing  
  - **LEFT:** pass one chip to the next player  
  - **CENTER:** place one chip in the pot  
  - **RIGHT:** pass one chip to the previous player  
- Players with zero chips skip rolling but can rejoin if given chips.  
- The game ends when only one player has chips—the winner.  

## Implementation
- Uses enums and arrays to map rolls to symbols.  
- PRNG ensures reproducible dice rolls via `randi_seed()` and `randi()`.  
- Main functions: `play_game()`, `letter_of_symbol()`, `min()`, `rand_roll()`, `left_of()`, `right_of()`, `print_scores()`.  
- Multiple C files (`lcr.c`, `game.c`, `randi.c`) compiled using a Makefile.  

## Running the Game
```bash
$ make        # compile the executable
$ ./lcr       # run the game

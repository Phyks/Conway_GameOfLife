Conway Game of Life
===================

An implementation of the famous Game Of Life from Conway ( https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life ) in C. 

It uses ncurses to display a randomly generated view that follows the rules of the Game Of Life.

## Usage

Just compile it using gcc with -ncurses argument :

<code>gcc -ncurses main.c</code>

Then, you can launch it with an argument giving the initial percentage of alive cells :

<code>./a.out density</code> (where density is in [|0,100|])

# LICENSE

### TLDR;
	I don't give a damn to anything you can do using this code. It would just be nice to
	quote where the original code comes from.


--------------------------------------------------------------------------------
  	"THE NO-ALCOHOL BEER-WARE LICENSE" (Revision 42):
  
  	Phyks (phyks@phyks.me) wrote this file. As long as you retain this notice you
 	 can do whatever you want with this stuff (and you can also do whatever you want
 	 with this stuff without retaining it, but that's not cool... :/ ). If we meet some 
 	 day, and you think this stuff is worth it, you can buy me a <del>beer</del> soda 
 	 in return.
  																			Phyks
---------------------------------------------------------------------------------

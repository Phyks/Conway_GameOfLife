#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <ncurses.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

//TODO !!!!
// Inverser X et Y cf. Le retour
int kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;
 
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
 
  ch = getchar();
 
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
 
  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }
 
  return 0;
}

int main(int argc, char **argv)
{
	// Defines the 2*X*Y matrice
	// i, j, k for counters
	// count, density
	// o (=old), n(=new) for switching between the two matrices X*Y
	//Nbre_iterations = number of iterations
	int **m[2];
	int i, j, k;
	int count = 0, density = 50, o = 0, n, Y, X, nbre_iterations=0;
	int carac = 64; //@
	
	initscr();
	getmaxyx(stdscr, X, Y);
	
	Y -= 1;
	X -= 1;
	
	// If there's not enough args, give a short How-To
	if(argc < 1)
	{
		printw("Usage : %s [density in %] \n", argv[0]);
		refresh();
		return 0;
	}

	// Put the 2nd (if exists) into density
	if (argv[2] != NULL) density = atoi(argv[2]);

	// Initialize random generator
  	srand(time(NULL));

	// Dynamically allocate memory for both matrices
 	for (o = 0; o < 2; o++)
 	{
 		if((m[o] = malloc(sizeof(*m[o]) * X)) == NULL)
  		{
		  	perror("malloc:");
		  	exit(-1);
	 	}
 	 	for(i = 0; i < X; i++)
	 	{
   		 	if((m[o][i] = malloc(sizeof(**m[o]) * Y)) == NULL)
   		 	{
				perror("malloc:");
				exit(-1);
			}
   		}
	}

	// Fill the matrix 0 with random number between 1 and 0
	for(i = 0; i < X; i++)
	{
		for(j = 0; j < Y; j++)
		{
			// We put 1 if the number token is > density
			m[0][i][j] = (rand() % 100 > density) ? 1 : 0;
		}
	}
	// Clear the screen and print the matrice 0
	clear();

	for(i = 0; i < X; i++)
	{
		for(j = 0; j < Y; j++)
		{
			(m[0][i][j] == 1) ? addch(carac) : addch(32);
		}
		printw("\n");
		refresh();
	}

	// Reset o to 0
	o = 0;
	
 	while(!kbhit())
 	{
		n = 1-o; // If the old indice o = 0, then n = 1
		
		move(0,0);
		
  		for(i = 0; i < X; i++)
  		{
	  		for(j = 0; j < Y; j++)
	  		{
				// Add 1 to count for each neighbour
	  			count += (i < X-1 && 	j > 0 && 	m[o][i+1][j-1] == 1) 	? 1 : 0;
	 			count += (i < X-1 && 			m[o][i+1][j] == 1) 	? 1 : 0;
	 			count += (i < X-1 && 	j < Y-1 && 	m[o][i+1][j+1] == 1) 	? 1 : 0;
	 			count += (		j < Y-1	&& 	m[o][i][j+1] == 1) 	? 1 : 0;
	 			count += (		j > 0 && 	m[o][i][j-1] == 1) 	? 1 : 0;
	 			count += (i > 0 &&	j > 0 && 	m[o][i-1][j-1] == 1) 	? 1 : 0;
	 			count += (i > 0 && 			m[o][i-1][j] == 1)	? 1 : 0;
	 			count += (i > 0 && 	j < Y-1 && 	m[o][i-1][j+1] == 1) 	? 1 : 0;

				// Determine whether or not the cellular dies
				if(count < 2 || count > 3)
					m[n][i][j] = 0;
				else if(count == 3)
					m[n][i][j] = 1;
				else
					m[n][i][j] = m[o][i][j];
	  			
	  			(m[n][i][j] == 1) ? addch(carac) : addch(32);
	  			count = 0;
	  		}
	  		printw("\n");
		}
		nbre_iterations++;
		printw("%d", nbre_iterations);
		refresh();
		
		usleep(100000);
		
		//Exchange n and o -> New 'old' is old 'new' :)
		o = n;
	}
	endwin();
	return 0;
}

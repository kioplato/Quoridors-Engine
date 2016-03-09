/******************************************************
File implementation : command.c
Authors             : P. N. Kiorpelidis & G. Koryllos
Purpose             : command functions definitions
Date                : 28-1-2015
*******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../misc/misc.h"
#include "../command/command.h"

void inputCommand(unsigned* quit_game)
{
  char* inputCommand = get_line();

  char replaceChars[2] = {9, ' '};
  replaceStringChars(inputCommand, replaceChars, 2);
  removeChar(inputCommand, 13);
  removeExtraSpaces(inputCommand);

  char* command = NULL;
  command = commandDecode(inputCommand, command);

  unsigned n_arguments;
  char** arguments = NULL;
  arguments = argumentsDecode(inputCommand, &n_arguments);

  static ArraySize grid_size;
  static Walls available_walls;
  static unsigned is_set_walls;
  static int** grid = NULL;


  if(strcmp(command, "name") == 0)
  {
    name(); /*NAME FUNCTION CALL*/
  }
  else if(strcmp(command, "known_command") == 0)
  {
    if(n_arguments == 1)
    {
      known_command(arguments[0]);  /*KNOWN_COMMAND FUNCTION CALL*/
    }
    else
    {
      printf("= false\n\n");
    }
  }
  else if(strcmp(command, "list_commands") == 0)
  {
    list_commands();  /*LIST_COMMANDS FUNCTION CALL*/
  }
  else if(strcmp(command, "quit") == 0)
  {
    quit(quit_game);  /*QUIT FUNCTION CALL*/
  }
  else if(strcmp(command, "boardsize") == 0)
  {
    if(n_arguments == 1)
    {
      grid_size.size = atoi(arguments[0]);
      grid = boardsize(grid, grid_size);
    }
    else
    {
      printf("? Error: you need to give one(1) argument (ex. boardsize 9)\n\n");
    }
  }
  else if(strcmp(command, "clear_board") == 0)
  {
    //clear_board(grid);
  }
  else if(strcmp(command, "walls") == 0)
  {
    if(n_arguments == 1)
    {
      walls(&n_walls, atoi(arguments[0]));
    }
    else
    {
      printf("? Error: you need to give one(1) argument (ex. walls 10)\n\n");
    }
  }
  else if(strcmp(command, "playmove") == 0)
  {
    if(grid != NULL && n_arguments == 2)
    {
      //playmove(grid, arguments[0], arguments[1]); /*PLAYMOVE FUNCTION CALL*/
    }
    else if(grid == NULL)
    {
      printf("? Error: you need to create a board first\n\n");
    }
    else if(n_arguments != 2)
    {
      printf("? Error: you need to give two(2) arguments (ex. playmove w a1)\n\n");
    }
  }
  else if(strcmp(command, "playwall") == 0)
  {
    if(n_arguments == 3)
    {
      //playwall(grid, &n_walls, arguments[0], arguments[1], arguments[2]); /*PLAYWALL FUNCTION CALL*/
    }
    else
    {
      printf("? Error: you need to give 3 arguments (ex. playwall w a5 v)\n\n");
    }
  }
  else if(strcmp(command, "genmove") == 0)
  {
    if(n_arguments == 1)
    {
      //genmove(grid, grid_size, arguments[0]); /*GENMOVE FUNCTION CALL*/
    }
    else
    {
      printf("? Error: you need to give one(1) argument (ex. genmove w)\n\n");
    }
  }
  else if(strcmp(command, "undo") == 0)
  {
    if(n_arguments == 1)
    {
      //undo(grid, arguments[0]); /*UNDO FUNCTION CALL*/
    }
    else
    {
      printf("? Error: you need to give one(1) argument (ex. undo 4)\n\n");
    }
  }
  else if(strcmp(command, "winner") == 0)
  {
    //winner(grid, grid_size);  /*WINNER FUNCTION CALL*/
  }
  else if(strcmp(command, "showboard") == 0)
  {
    //showboard(grid, gridSize_v, gridSize_h);
  }
  else
  {
    printf("? Error: unknown command (run: list_commands)\n\n");
  }
}

/*********************************************************
-------------------------COMMANDS-------------------------
*********************************************************/

void name()
{
  char* engineName = "Deep Orange";
  printf("= %s\n\n", engineName);
}

void known_command(char* command)
{
  static unsigned n_elems = 13;
  static char* allCommands[] = {"name", "known_command", "list_commands", "quit", "boardsize", "clear_board", "walls", "playmove", "playwall", "genmove", "undo", "winner", "showboard"};

  unsigned n_rows = 0;
  for(n_rows = 0; n_rows < n_elems; n_rows++)
  {
    if(strcmp(command, allCommands[n_rows]) == 0)
    {
      printf("= true\n\n");
      return;
    }
  }
  printf("= false\n\n");
}

void list_commands()
{
  static unsigned n_elems = 13;
  static char* allCommands[] = {"name", "known_command", "list_commands", "quit", "boardsize", "clear_board", "walls", "playmove", "playwall", "genmove", "undo", "winner", "showboard"};

  printf("=\n");
  unsigned counter;
  for(counter = 0; counter < n_elems; counter++)
  {
    printf("%s\n", allCommands[counter]);
  }
  printf("\n");
}

void quit(unsigned* quit_game)
{
  *quit_game = 1;
  printf("= quitting game\n");
}

int** boardsize(int** grid, ArraySize grid_size)
{

}

void clear_board(int** grid, ArraySize grid_size)
{

}

void walls(unsigned int* n_walls, unsigned int input_n_walls)
{
  *n_walls = input_n_walls;
  printf("= walls set to %d.\n\n", *n_walls);
}

void playmove(int** grid, ArraySize grid_size, char player, Vertex move_coordinates)
{
  //FIXME: Add functionality to this function.
}

void playwall(int** grid, ArraySize grid_size, unsigned* n_walls, char player, Vertex wall_coordinates, unsigned orientation)
{
  //FIXME: Add functionality to this function.
}

void genmove()
{
  //FIXME: Add functionality to this function.
}

void undo(int** grid)
{
  //FIXME: Add functionality to this function.
}

void winner(int** grid, ArraySize grid_size)
{
  //FIXME: Add functionality to this function.
}

void showboard(int** grid, Walls available_walls, ArraySize grid_size)
{
  unsigned n_rows = grid_size.v_size;
  unsigned n_cols = grid_size.h_size;
  unsigned counter_rows = 0;
  unsigned counter_cols = 0;

  printf("=\n");

  /*print letters at the bottom*/
  char letters = 'A';
  counter_cols = 0;
  printf("  ");
  while(counter_cols < (n_cols - 1) / 4)
  {
    printf("   %c", letters++);
    counter_cols++;
  }
  printf("\n");
  /*end of print letters at the bottom*/

  for(counter_rows = 0; counter_rows < n_rows; counter_rows++)
  {
    /*print left side row numbers*/
    if(counter_rows % 2 == 1)
    {
      if((((n_rows - 1) / 2) - (counter_rows + 1) / 2) + 1 >= 10)
      {
        printf("%d ", (((n_rows - 1) / 2) - (counter_rows + 1) / 2) + 1);
      }
      else if((((n_rows - 1) / 2) - (counter_rows + 1) / 2) < 10)
      {
        printf(" %d ", (((n_rows - 1) / 2) - (counter_rows + 1) / 2) + 1);
      }
    }
    else if(counter_rows % 2 == 0)
    {
      printf("   ");
    }
    /*end of print left side row numbers*/

    /*print array content*/
    for(counter_cols = 0; counter_cols < n_cols; counter_cols++)
    {
      printf("%c", grid[counter_rows][counter_cols]);
    }
    /*print array content*/

    /*print right side row numbers*/
    if(counter_rows % 2 == 1)
    {
      printf(" %d", (((n_rows - 1) / 2) - (counter_rows + 1) / 2) + 1);
    }
    /*end of print right side row numbers*/

    /*print available walls for each player on the right*/
    if(counter_rows == 1)
    {
      printf("  black walls: %d", available_walls.black_walls);
    }
    else if(counter_rows == 3)
    {
      printf("  white walls: %d", available_walls.white_walls);
    }
    /*end of print available walls for each player on the right*/

    printf("\n");
  }

  /*print letters at the bottom*/
  letters = 'A';
  counter_cols = 0;
  printf("  ");
  while(counter_cols < (n_cols - 1) / 4)
  {
    printf("   %c", letters++);
    counter_cols++;
  }
  printf("\n\n");
  /*end of print letters at the bottom*/
}

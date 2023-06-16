//Vincent Phillip Rodriguez CPSC120-19
#include <chrono>
#include <ctime>
#include <curses.h>
#include <iostream>
#include <stdlib.h>
#include <thread>
using namespace std;

const int ROWS = 100;
const int COLUMNS = 150;


void InitializeCurses() {
  // Initialize curses to control where to output to the terminal. No need to
  // modify this function, but make sure it is called in main at the beginning.
  initscr();
  cbreak();
  noecho();
  clear();
}


void PrintExitInstructions() {
  // Prints instructions near the bottom of the screen for how to exit. No need
  // to modify this function.
  mvaddstr(ROWS + 1, 0, "Press ctrl+c to quit ");
  refresh();
}


void PrintRow(string row_to_print, int row) {
  mvaddstr(row, 0, row_to_print.c_str());
  refresh();

  this_thread::sleep_for(chrono::milliseconds(100));
}

//Determines the state of the cell based off of the current state and the total
//amount of cells that surround it.
int AliveOrDead(int cell_state, int cell_count) {

  //Cell is alive.
  if (cell_state == 1) {

    //Stays alive if there are 2 or three cells surrounding it.
    if (cell_count == 2 || cell_count == 3) {
      return 1;

    //Dies if there are less than 2 because of under-population.
    //Dies if there are more than 3 because of overpopulation.
    } else {
      return 0;
    }

    //Cell is dead.
  } else if (cell_state == 0) {

    //Cell becomes alive if there are exactly 3 cells surrounding it because of
    //reproduction.
    if (cell_count == 3) {
      return 1;

    //Cell remains dead if there a not exactly 3 cells surrounding it.
    } else {
      return 0;
    }
  }

  //Return 2 means something went wrong.
  return 2;
}


int main(int argc, char* argv[]) {
  InitializeCurses();
  PrintExitInstructions();

  //This array is read from.
  int main_world[ROWS][COLUMNS] = {};

  //Initialize the world with dead cells.
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      main_world[i][j] = 0;
    }
  }

  //This array is written to and copied to the main_world.
  int updated_world[ROWS][COLUMNS] = {};

  //Initialize the updated_world with dead cells.
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      updated_world[i][j] = 0;
    }
  }

  //The placement of these alive cells create a Light Weight Spaceship.
  main_world[1][3] = 1;
  main_world[1][4] = 1;
  main_world[2][1] = 1;
  main_world[2][2] = 1;
  main_world[2][4] = 1;
  main_world[2][5] = 1;
  main_world[3][1] = 1;
  main_world[3][2] = 1;
  main_world[3][3] = 1;
  main_world[3][4] = 1;
  main_world[4][2] = 1;
  main_world[4][3] = 1;

  //Conway's Game of Life.
  while (true) {

    string array_string = "";

    //Converts the array into a string by concatenating each space in every row
    //to array_string.
    //Dead cells are " " and alive cells are "*".
    for (int i = 0; i < ROWS; i++) {
      for (int j = 0; j < COLUMNS; j++) {
        if (main_world[i][j] == 0) {
          array_string += " ";
        } else if (main_world[i][j] == 1) {
          array_string += "*";
        }
      }
      array_string += "\n";
    }

    //Prints the main world.
    PrintRow(array_string, 0);

    for (int i = 0; i < ROWS; i++) {
      for (int j = 0; j < COLUMNS; j++) {
        int surrounding_cell_count = 0;
        int cell_state;

        //Determine if the cell is alive or dead.
        if (main_world[i][j] == 1) {
          cell_state = 1;
        } else if (main_world[i][j] == 0) {
          cell_state = 0;
        }

        //Checks the type of cell.
        //This is a left edge cell----------------------------------------------
        if ((i - 1) >= -1 && (i + 1) <= ROWS && j == 0) {

          //Check the cell to the right.
          if (main_world[i][j + 1] == 1) {
            surrounding_cell_count += 1;
          }

          //Check the cell at the top right corner.
          if (main_world[i - 1][j + 1] == 1) {
            surrounding_cell_count += 1;
          }

          //Check the cell at the top.
          if (main_world[i - 1][j] == 1) {
            surrounding_cell_count += 1;
          }

          //Check the cell at the top left corner.
          if (main_world[i - 1][COLUMNS - 1] == 1) {
            surrounding_cell_count += 1;
          }

          //Check the cell to the left.
          if (main_world[i][COLUMNS - 1] == 1) {
            surrounding_cell_count += 1;
          }

          //Check the cell at the bottom left corner.
          if (main_world[i + 1][COLUMNS - 1] == 1) {
            surrounding_cell_count += 1;
          }

          //Check the cell at the bottom.
          if (main_world[i + 1][j] == 1) {
            surrounding_cell_count += 1;
          }

          //Check the cell at the bottom right corner.
          if (main_world[i + 1][j + 1] == 1) {
            surrounding_cell_count += 1;
          }

          //Based on the surrounding cells, determines whether the cell is alive
          //or dead.
          updated_world[i][j] = AliveOrDead(cell_state, surrounding_cell_count);

        } else if ((i - 1) >= -1 && (i + 1) <= ROWS && j == COLUMNS - 1) {
          //This is a right edge cell-------------------------------------------
          //Check the cell to the right.
          if (main_world[i][0] == 1) {
            surrounding_cell_count += 1;
          }

          //Check the cell at the top right corner.
          if (main_world[i - 1][0] == 1) {
            surrounding_cell_count += 1;
          }

          //Check the cell at the top.
          if (main_world[i - 1][j] == 1) {
            surrounding_cell_count += 1;
          }

          //Check the cell at the top left corner.
          if (main_world[i - 1][j - 1] == 1) {
            surrounding_cell_count += 1;
          }

          //Check the cell to the left.
          if (main_world[i][j - 1] == 1) {
            surrounding_cell_count += 1;
          }

          //Check the cell at the bottom left corner.
          if (main_world[i + 1][j - 1] == 1) {
            surrounding_cell_count += 1;
          }

          //Check the cell at the bottom.
          if (main_world[i + 1][j] == 1) {
            surrounding_cell_count += 1;
          }

          //Check the cell at the bottom right corner.
          if (main_world[i + 1][0] == 1) {
            surrounding_cell_count += 1;
          }

          //Based on the surrounding cells, determines whether the cell is alive
          //or dead.
          updated_world[i][j] = AliveOrDead(cell_state, surrounding_cell_count);

        } else if ((j - 1) >= -1 && (j + 1) <= COLUMNS && i == 0) {
          //This is a top edge cell---------------------------------------------
          //Check the cell to the right.
          if (main_world[i][j + 1] == 1) {
            surrounding_cell_count += 1;
          }

          //Check the cell at the top right corner.
          if (main_world[ROWS - 1][j + 1] == 1) {
            surrounding_cell_count += 1;
          }

          //Check the cell at the top.
          if (main_world[ROWS - 1][j] == 1) {
            surrounding_cell_count += 1;
          }

          //Check the cell at the top left corner.
          if (main_world[ROWS - 1][j - 1] == 1) {
            surrounding_cell_count += 1;
          }

          //Check the cell to the left.
          if (main_world[i][j - 1] == 1) {
            surrounding_cell_count += 1;
          }

          //Check the cell at the bottom left corner.
          if (main_world[i + 1][j - 1] == 1) {
            surrounding_cell_count += 1;
          }

          //Check the cell at the bottom.
          if (main_world[i + 1][j] == 1) {
            surrounding_cell_count += 1;
          }

          //Check the cell at the bottom right corner.
          if (main_world[i + 1][j + 1] == 1) {
            surrounding_cell_count += 1;
          }

          //Based on the surrounding cells, determines whether the cell is alive
          //or dead.
          updated_world[i][j] = AliveOrDead(cell_state, surrounding_cell_count);

        } else if ((j - 1) >= -1 && (j + 1) <= COLUMNS && i == ROWS - 1) {
          //This is a bottom edge cell------------------------------------------
          //Check the cell to the right.
          if (main_world[i][j + 1] == 1) {
            surrounding_cell_count += 1;
          }

          //Check the cell at the top right corner.
          if (main_world[i - 1][j + 1] == 1) {
            surrounding_cell_count += 1;
          }

          //Check the cell at the top.
          if (main_world[i - 1][j] == 1) {
            surrounding_cell_count += 1;
          }

          //Check the cell at the top left corner.
          if (main_world[i - 1][j - 1] == 1) {
            surrounding_cell_count += 1;
          }

          //Check the cell to the left.
          if (main_world[i][j - 1] == 1) {
            surrounding_cell_count += 1;
          }

          //Check the cell at the bottom left corner.
          if (main_world[0][j - 1] == 1) {
            surrounding_cell_count += 1;
          }

          //Check the cell at the bottom.
          if (main_world[0][j] == 1) {
            surrounding_cell_count += 1;
          }

          //Check the cell at the bottom right corner.
          if (main_world[0][j + 1] == 1) {
            surrounding_cell_count += 1;
          }

          //Based on the surrounding cells, determines whether the cell is alive
          //or dead.
          updated_world[i][j] = AliveOrDead(cell_state, surrounding_cell_count);

        } else {
          //The cell is a regular cell------------------------------------------
          //Check the cell to the right.
          if (main_world[i][j + 1] == 1) {
            surrounding_cell_count += 1;
          }

          //Check the cell at the top right corner.
          if (main_world[i - 1][j + 1] == 1) {
            surrounding_cell_count += 1;
          }

          //Check the cell at the top.
          if (main_world[i - 1][j] == 1) {
            surrounding_cell_count += 1;
          }

          //Check the cell at the top left corner.
          if (main_world[i - 1][j - 1] == 1) {
            surrounding_cell_count += 1;
          }

          //Check the cell to the left.
          if (main_world[i][j - 1] == 1) {
            surrounding_cell_count += 1;
          }

          //Check the cell at the bottom left corner.
          if (main_world[i + 1][j - 1] == 1) {
            surrounding_cell_count += 1;
          }

          //Check the cell at the bottom.
          if (main_world[i + 1][j] == 1) {
            surrounding_cell_count += 1;
          }

          //Check the cell at the bottom right corner.
          if (main_world[i + 1][j + 1] == 1) {
            surrounding_cell_count += 1;
          }
        }

        //Based on the surrounding cells, determines whether the cell is alive
        //or dead.
        updated_world[i][j] = AliveOrDead(cell_state, surrounding_cell_count);
      }
    }

    //Updates the main world by copying the updated world to the main world.
    for (int i = 0; i < ROWS; i++) {
      for (int j = 0; j < COLUMNS; j++) {
        main_world[i][j] = updated_world[i][j];
      }
    }
  }

  endwin();
  return 0;
}

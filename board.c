#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Board Struct
struct Board {
  int pieces[8][8];
  int turn;
};
struct Board board;


// Player struct
struct Player {
  int score;
  char name[20];
};
struct Player player_1;
struct Player player_2;

int has_valid_move(int player);

// Function initializes board and player scores
void init_board() {
  player_1.score = 2;
  player_2.score = 2;
  board.turn = 1;

  for(int y=0; y<8; ++y) {
    for(int x=0; x<8; ++x) {
      board.pieces[y][x] = 0;
    }
  }
  board.pieces[3][3] = 2;
  board.pieces[4][4] = 2;
  board.pieces[3][4] = 1;
  board.pieces[4][3] = 1;
}

// Outputs board
void output_board() {
  printf("  ");
  for(int i=0; i<8; ++i) {
    printf("%c ", 'a'+i);
  }
  printf("\n");

  for(int y=0; y<8; ++y) {
    printf("%d ", y+1);
    for(int x=0; x<8; ++x) {
      if(board.pieces[y][x] == 1) {
        printf("B "); // Black is player 1
      }
      if(board.pieces[y][x] == 2) {
        printf("W "); // White is player 2
      }
      if(board.pieces[y][x] == 0) {
        printf("- ");
      }
    }
    printf("\n");
  }
}

int make_move(char move[2], int player, int change_board) {
  if(move[0] == 'p') { // Checks if player wants to pass
    if(has_valid_move(player)) { // Doesn't allow player to pass unless there are no available moves
      printf("You can't pass unless you have no valid moves.\n");
      return 0;
    } else {
      return 1;
    }
  } else {
    // Convert move from 'a1' format
    int x = move[0]-'a';
    int y = move[1]-'1';

    int lines_changed = 0;
    int pieces_changed = 0;

    if(board.pieces[y][x] == 0) { // Make sure desired square is empty
      int dirs[8][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1} }; // All valid directions matches can be found in

      for(int i=0; i<8; ++i) { // Loop through every dir
        int y_track = y+dirs[i][0]; // Temporary y that lets us loop through line to see if it's valid
        int x_track = x+dirs[i][1]; // Temporary x that lets us loop through line to see if it's valid
        int valid = 0;

        if(board.pieces[y_track][x_track] != player && board.pieces[y_track][x_track] != 0) { // Ensure piece at temp y/x is opponents piece
          while(y_track>=0&&y_track<8&&x_track>=0&&x_track<8) {
            if(board.pieces[y_track][x_track] == player) { // If you encounter your own piece line is valid and finished
              valid = 1;
              break;
            }
            if(board.pieces[y_track][x_track] == 0) {
              break;
            }
            y_track += dirs[i][0]; // Increment temp y by dir in y direction
            x_track += dirs[i][1]; // Increment temp x by dir in x direction
          }
        }

        int y1 = y; // Temp y to change pieces
        int x1 = x; // Temp x to change pieces
        if(valid) {
          lines_changed += 1; // Keeps track of lines changed
          if(change_board) { // Checks if function is called by player and not has_valid_move function
            while(y1!=y_track || x1!=x_track) { // Ensures end of line isn't reached past
              if(board.pieces[y1][x1] != player) { // If piece isn't already changed increment the pieces_changed var
                pieces_changed += 1;
              }
              board.pieces[y1][x1] = player; // Change piece
              y1+=dirs[i][0]; // Inc/dec y dir
              x1+=dirs[i][1]; // Inc/dec x dir
            }
          }
        }
      }
    }
    if(lines_changed) {
      // Change scores based on turn
      if(board.turn == 1) {
        player_1.score += pieces_changed;
        player_2.score -= pieces_changed-1;
      } else {
        player_2.score += pieces_changed;
        player_1.score -= pieces_changed-1;
      }
    }

    return lines_changed;
  }

}

// Returns 1 if current player has a possible move to make
// Brute forces every position on board
int has_valid_move(int player) {
  char move[2];
  for(int y=0; y<8; ++y) {
    for(int x=0; x<8; ++x) {
      move[0] = 'a'+x;
      move[1] = '1'+y;
      if(make_move(move, player, 0)) {
        return 1;
      }
    }
  }
  return 0;
}

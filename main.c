#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_output.c"
#include "board.c"


int main() {
  init_board();

  printf("Welcome to Othello\n\n");
  // Take names as input
  printf("Player 1 please enter your name : ");
  scanf("%s", player_1.name);
  printf("Player 2 please enter your name : ");
  scanf("%s", player_2.name);

  int invalid_streak = 0;
  while(1) {
    output_board();

    char move[2];
    printf("%s : %d  %s : %d \n", player_1.name, player_1.score, player_2.name, player_2.score); // Output scores
    // Output whose turn it is
    if(board.turn == 1) {
      printf("%s's turn\n", player_1.name);
    } else {
      printf("%s's turn\n", player_2.name);
    }
    printf("Make your move : ");
    scanf("%s", move);

    while(!(make_move(move, board.turn, 1))) { // Until valid move is made keep prompting for input
      printf("Invalid move\n");
      printf("Make your move : ");
      scanf("%s", move);
    }
    if(move[0] == 'p') { // If player passed update invalid_streak
      invalid_streak += 1;
    } else {
      invalid_streak = 0;
    }
    if(player_1.score + player_2.score == 64 || invalid_streak == 2) { // If board is full or 2 turns in a row had no valid moves end the game
      break;
    }

    board.turn = (board.turn%2)+1; // Switch player turn
  }

  printf("\nGAME OVER\n");
  output_board();
  // Output winner and scores
  if(player_1.score == player_2.score) {
    printf("\n%s : %d  %s : %d \n", player_1.name, player_1.score, player_2.name, player_2.score);
    printf("\nDRAW");
  } else if(player_1.score > player_2.score) {
    printf("\n%s : %d  %s : %d \n", player_1.name, player_1.score, player_2.name, player_2.score);
    printf("\%s wins!", player_1.name);
  } else {
    printf("\n%s : %d  %s : %d \n", player_1.name, player_1.score, player_2.name, player_2.score);
    printf("\%s wins!", player_2.name);
  }
  update_result_file(player_1.name, player_1.score, player_2.name, player_2.score); // Append results to file
}

#include <stdio.h>
#include <time.h>

// This function appends date/time/game results to file
void update_result_file(char player_1_name[20], int player_1_score, char player_2_name[20], int player_2_score) {
  FILE *fp;
  fp = fopen("othello-results.txt", "a");

  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  fprintf(fp, "\n%d-%02d-%02d %02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min);
  if(player_1_score == player_2_score) {
    fprintf(fp, "%s : %d  %s : %d \n", player_1_name, player_1_score, player_2_name, player_2_score);
    fprintf(fp, "\nDRAW\n");
  } else if(player_1_score > player_2_score) {
    fprintf(fp, "%s : %d  %s : %d \n", player_1_name, player_1_score, player_2_name, player_2_score);
    fprintf(fp, "\%s won\n", player_1_name);
  } else {
    fprintf(fp, "%s : %d  %s : %d \n", player_1_name, player_1_score, player_2_name, player_2_score);
    fprintf(fp, "\%s won\n", player_2_name);
  }

  fclose(fp);
}

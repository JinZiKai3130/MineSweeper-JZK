#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <utility>
#include <ctime>
#include <random>

extern int rows;         // The count of rows of the game map.
extern int columns;      // The count of columns of the game map.
extern int total_mines;  // The count of mines of the game map.

// You MUST NOT use any other external variables except for rows, columns and total_mines.

char client_map[105][105];

/**
 * @brief The definition of function Execute(int, int, bool)
 *
 * @details This function is designed to take a step when player the client's (or player's) role, and the implementation
 * of it has been finished by TA. (I hope my comments in code would be easy to understand T_T) If you do not understand
 * the contents, please ask TA for help immediately!!!
 *
 * @param r The row coordinate (0-based) of the block to be visited.
 * @param c The column coordinate (0-based) of the block to be visited.
 * @param type The type of operation to a certain block.
 * If type == 0, we'll execute VisitBlock(row, column).
 * If type == 1, we'll execute MarkMine(row, column).
 * If type == 2, we'll execute AutoExplore(row, column).
 * You should not call this function with other type values.
 */
void Execute(int r, int c, int type);

/**
 * @brief The definition of function InitGame()
 *
 * @details This function is designed to initialize the game. It should be called at the beginning of the game, which
 * will read the scale of the game map and the first step taken by the server (see README).
 */
void InitGame() {
  // TODO (student): Initialize all your global variables!
  int first_row, first_column;
  std::cin >> first_row >> first_column;
  Execute(first_row, first_column, 0);
}

/**
 * @brief The definition of function ReadMap()
 *
 * @details This function is designed to read the game map from stdin when playing the client's (or player's) role.
 * Since the client (or player) can only get the limited information of the game map, so if there is a 3 * 3 map as
 * above and only the block (2, 0) has been visited, the stdin would be
 *     ???
 *     12?
 *     01?
 */
void ReadMap() {
  // TODO (student): Implement me!
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      std::cin >> client_map[i][j];
    }
  }
}

/**
 * @brief The definition of function Decide()
 *
 * @details This function is designed to decide the next step when playing the client's (or player's) role. Open up your
 * mind and make your decision here! Caution: you can only execute once in this function.
 */
void Decide() {
  // TODO (student): Implement me!
  // while (true) {
  //   Execute(0, 0);
  // }
  int dx[15] = {-1, 0, 1, -1, 0, 
                1, -1, 0, 1};
  int dy[15] = {-1, -1, -1, 0, 0, 
                0, 1, 1, 1};
  bool flag = 0;
  // std::cout << "start to decide" << std::endl;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      if (client_map[i][j] == '?') continue ;
      int mine_blocks = 0, unknown_blocks = 0, next_r, next_c;
      bool visited = 1;
      for (int k = 0; k < 9; k++) {
        if (client_map[i + dx[k]][j + dy[k]] == '@') mine_blocks++;
        if (client_map[i + dx[k]][j + dy[k]] == '?') {
          unknown_blocks++;
          visited = 0;
          next_r = i + dx[k];
          next_c = j + dy[k];
        }
      }
      if (visited) continue;
      if (mine_blocks == int(client_map[i][j] - '0')) { // auto explore available
        Execute(i, j, 2);
        flag = 1;
      }
      else if (mine_blocks + unknown_blocks == int(client_map[i][j] - '0')) { // marking available
        Execute(next_r, next_c, 1);
        flag = 1;
      }
    }
  }
  int d0x[5] = {0, 0 , -1, 1}, d0y[5] = {1, -1 , 0, 0};
  for (int i = 0; i < rows - 1; i++) { // minus formula
    for (int j = 0; j < columns - 1; j++) {
      if (client_map[i][j] == '?' || client_map[i][j] == '@') continue;
      for (int k = 0; k < 5; k++) {
        int mine_blocks_1 = 0, unknown_blocks_1 = 0;
        int mine_blocks_2 = 0, unknown_blocks_2 = 0;
        if (client_map[i + d0x[k]][j + d0y[k]] == '?' || client_map[i + d0x[k]][j + d0y[k]] == '@')
        continue; // unable to use minus formula
        if (k > 1) { // row
          if (client_map[i - d0x[k]][j - d0y[k] + 1] == '?') unknown_blocks_1++;
          if (client_map[i - d0x[k]][j - d0y[k]] == '?') unknown_blocks_1++;
          if (client_map[i - d0x[k]][j - d0y[k] - 1] == '?') unknown_blocks_1++;
          if (client_map[i - d0x[k]][j - d0y[k] + 1] == '@') mine_blocks_1++;
          if (client_map[i - d0x[k]][j - d0y[k]] == '@') unknown_blocks_1++;
          if (client_map[i - d0x[k]][j - d0y[k] - 1] == '@') mine_blocks_1++;
          if (client_map[i + 2 * d0x[k]][j - d0y[k] + 1] == '?') unknown_blocks_2++;
          if (client_map[i + 2 * d0x[k]][j - d0y[k]] == '?') unknown_blocks_2++;
          if (client_map[i + 2 * d0x[k]][j - d0y[k] - 1] == '?') unknown_blocks_2++;
          if (client_map[i + 2 * d0x[k]][j - d0y[k] + 1] == '@') mine_blocks_2++;
          if (client_map[i + 2 * d0x[k]][j - d0y[k]] == '@') unknown_blocks_2++;
          if (client_map[i + 2 * d0x[k]][j - d0y[k] - 1] == '@') mine_blocks_2++;
        }
        else { // column
          if (client_map[i - d0x[k] + 1][j - d0y[k]] == '?') unknown_blocks_1++;
          if (client_map[i - d0x[k]][j - d0y[k]] == '?') unknown_blocks_1++;
          if (client_map[i - d0x[k] - 1][j - d0y[k]] == '?') unknown_blocks_1++;
          if (client_map[i - d0x[k] + 1][j - d0y[k]] == '@') mine_blocks_1++;
          if (client_map[i - d0x[k]][j - d0y[k]] == '@') unknown_blocks_1++;
          if (client_map[i - d0x[k] - 1][j - d0y[k]] == '@') mine_blocks_1++;
          if (client_map[i + d0x[k] + 1][j + 2 * d0y[k]] == '?') unknown_blocks_2++;
          if (client_map[i - d0x[k]][j + 2 * d0y[k]] == '?') unknown_blocks_2++;
          if (client_map[i + d0x[k] - 1][j + 2 * d0y[k]] == '?') unknown_blocks_2++;
          if (client_map[i + d0x[k] + 1][j + 2 * d0y[k]] == '@') mine_blocks_2++;
          if (client_map[i + d0x[k]][j + 2 * d0y[k]] == '@') mine_blocks_2++;
          if (client_map[i + d0x[k] - 1][j + 2 * d0y[k]] == '@') mine_blocks_2++;
        }
        if (client_map[i][j] == client_map[i + d0x[k]][j + d0y[k]]) { // the two sides are the same
          if (mine_blocks_1 == mine_blocks_2) {

          }
        }
        else if (client_map[i][j] >= client_map[i + d0x[k]][j + d0y[k]]) {

        }
        else {

        }
      }
    }
  }


  std::srand(std::time(0)); // random
  while (!flag) { // random block
    int random_r = std::rand() % rows;
    int random_c = std::rand() % columns;
    if (client_map[random_r][random_c] == '?') {
      flag = 1;
      Execute(random_r, random_c, 0);
    }
  }
}

#endif
#include "sqlite_query.h"

#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <curses.h>
#include <menu.h>


int main(int argc, char *argv[])
{
  if (argc < 2) {
    std::cout << "Usage: ./run [db_filepath] [table_name] [col1,col2]\n";
    return 0;
  }

  int rc = 0;
  int i = 0;
  int exit_flag = 0;
  int input_key;

  std::vector<Record> records;

  MENU *pCursesMenu = NULL;
  ITEM **ppCursesItems;
  ITEM *pCurrItem = NULL;
  const char *currItemDescription;

  const std::string db_filename = argv[1];
  const std::string table_name = argv[2];
  const std::string cols = argv[3];

  rc = sqlite_query(db_filename, table_name, cols, records);
  if (rc != 0) {
    std::cerr << "sqlite_query err: " << rc << '\n';
    return rc;
  }

  // initialize curses
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);

  ppCursesItems = (ITEM **)calloc(records.size() + 1, sizeof(ITEM *));

  for (i = 0; i < records.size(); i++)
    ppCursesItems[i] = new_item(records[i].key.c_str(), records[i].description.c_str());
  ppCursesItems[records.size()] = NULL;

  pCursesMenu = new_menu(ppCursesItems);
  post_menu(pCursesMenu);
  refresh();

  while (1) {
    input_key = getch();
    switch(input_key) {
      case 033: // ESCAPE
        exit_flag = 1;
        break;
      case 10: // ENTER
        pCurrItem = current_item(pCursesMenu);
        currItemDescription = item_description(pCurrItem);
        exit_flag = 1;
        break;
      case KEY_DOWN:
        menu_driver(pCursesMenu, REQ_DOWN_ITEM);
        break;
      case KEY_UP:
        menu_driver(pCursesMenu, REQ_UP_ITEM);
        break;
    }
    if (exit_flag != 0) {
      break;
    }
  }

  unpost_menu(pCursesMenu);
  free_menu(pCursesMenu);
  for (i = 0; i < records.size(); i++)
    free_item(ppCursesItems[i]);
  endwin();

  std::cout << currItemDescription << '\n';

  return 0;
}


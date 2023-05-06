#include <ncurses.h>
#include <vector>
#include <string>
#include <fstream>
#include <menu.h>

void printLoad(WINDOW * &window);
void printLeaderboard(WINDOW * &window);
void printAbout(WINDOW * &window);

// Print the logo
void printLogo(WINDOW * &window) {
    std::ifstream fin;
    // open logo bitmap
    fin.open("logo.txt");
    std::string line;
    // print line by line
    int i=0;
    start_color();
    while (getline(fin, line) && i<9){
        mvwprintw(window, i, 0, line.c_str());
        i++;
        }
        wrefresh(window);
    // close the file
    fin.close();
}

// Print background
void printBackground(WINDOW * &window) {
    std::ifstream fin;
    // open logo bitmap
    fin.open("background.txt");
    std::string line;
    // print line by line
    int i=0;
    start_color();
    init_pair(1, COLOR_RED, COLOR_MAGENTA);
    wattron(window, COLOR_PAIR(1));
    while (getline(fin, line) && i<15){
        mvwprintw(window, i, 0, line.c_str());
        i++;
        }
        wrefresh(window);
    wattroff(window,COLOR_PAIR(1));
    // close the file
    fin.close();
}

// Print the menu
void printMenu(WINDOW * &window) {

    #define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
    #define CTRLD 	4

    char *choices[] = {
                        "    Start     ",
                        "    Load     ",
                        " Leaderboard     ",
                        "    About     ",
                        "    Quit     ",
                  };
    char *choices2[] = {
                        " ",
                        " ",
                        " ",
                        " ",
                        " ",
                  };
    ITEM **my_items;
	int c;				
	MENU *my_menu;
        int n_choices, i;
	
	/* Initialize curses */
	start_color();
        cbreak();
        noecho();
	keypad(stdscr, TRUE);
	init_pair(1, COLOR_RED, COLOR_BLACK);
    mvprintw(LINES - 2, 1, "ENGG1340 Project");
    wrefresh(window);
	/* Create items */
        n_choices = ARRAY_SIZE(choices);
        my_items = (ITEM **)calloc(n_choices, sizeof(ITEM *));
        for(i = 0; i < n_choices; ++i)
                my_items[i] = new_item(choices2[i], choices[i]);

	/* Crate menu */
	my_menu = new_menu((ITEM **)my_items);

	/* Create the window to be associated with the menu */
        keypad(window, TRUE);
     
	/* Set main window and sub window */
        set_menu_win(my_menu, window);
        set_menu_spacing(my_menu, 3, 2, 5);
        set_menu_format(my_menu, 5, 1);
        set_menu_sub(my_menu, derwin(window, 12, 38, 3, 1));

	/* Set menu mark to the string " * " */
        set_menu_mark(my_menu, "   ");

	/* Print a border around the main window and print a title */
        //box(window, 0, 0);
	//print_in_middle(window, 1, 0, 40, "My Menu", COLOR_PAIR(1));
	//mvwaddch(window, 2, 0, ACS_LTEE);
	//mvwhline(window, 2, 1, ACS_HLINE, 38);
	//mvwaddch(window, 2, 39, ACS_RTEE);
	wrefresh(window);
        
	/* Post the menu */
	post_menu(my_menu);
	wrefresh(window);

    int userInput=0;
	while((c = wgetch(window)) != KEY_END)
	{       switch(c)
	        {	case KEY_DOWN:
				menu_driver(my_menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(my_menu, REQ_UP_ITEM);
				break;
            case KEY_ENTER: {
                int userInput=item_index(my_menu->curitem);
            if (userInput==0)
                return;    
            if (userInput==1) {
                // load
                // clear the screen
                wclear(window);
                // print the background
                printLoad(window);
                // refresh the screen
                wrefresh(window);
            }
            else if (userInput==2) {
                // leaderboard
                // clear the screen
                wclear(window);
                // print the menu
                printLeaderboard(window);
                // refresh the screen
                wrefresh(window);
            }
            else if (userInput==3) {
                // about
                // clear the screen
                wclear(window);
                // print the menu
                printAbout(window);
                // refresh the screen
                wrefresh(window);
            }
            else if (userInput==4) {
                // quit
                // clear the screen
                unpost_menu(my_menu);
                free_menu(my_menu);
                for(int i = 0; i < n_choices; ++i)
                    free_item(my_items[i]);
                werase(window);
                wclear(window);
                wrefresh(window);
                delwin(window);
	            endwin();
                refresh();
                erase();
                clear();
                exit(0);
            }
        }
    }
}
	/* Unpost and free all the memory taken up */
        unpost_menu(my_menu);
        free_menu(my_menu);
        for(i = 0; i < n_choices; ++i)
                free_item(my_items[i]);
	endwin();
}

// Print the difficulty menu
int printDifficulty(WINDOW * &window){
    #define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
    #define CTRLD 	4

    char *choices[] = {
                        "    Easy        ",
                        "   Medium        ",
                        "    Hard        ",
                        "   Expert        ",
                        "    Back        ",
                  };
    char *choices2[] = {
                        " ",
                        " ",
                        " ",
                        " ",
                        " ",
                  };
    ITEM **my_items;
	int c;				
	MENU *my_menu;
        int n_choices, i;
	
	start_color();
        cbreak();
        noecho();
	keypad(stdscr, TRUE);
        n_choices = ARRAY_SIZE(choices);
        my_items = (ITEM **)calloc(n_choices, sizeof(ITEM *));
        for(i = 0; i < n_choices; ++i)
                my_items[i] = new_item(choices2[i], choices[i]);
	my_menu = new_menu((ITEM **)my_items);
        keypad(window, TRUE);
        set_menu_win(my_menu, window);
        set_menu_spacing(my_menu, 3, 2, 5);
        set_menu_format(my_menu, 5, 1);
        set_menu_sub(my_menu, derwin(window, 12, 38, 3, 1));
        set_menu_mark(my_menu, "   ");
	mvprintw(LINES - 2, 1, "ENGG1340 Project");
	refresh();
	post_menu(my_menu);
	wrefresh(window);

    int userInput=0;
	while((c = wgetch(window)) != KEY_END)
	{       switch(c)
	        {	case KEY_DOWN:
				menu_driver(my_menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(my_menu, REQ_UP_ITEM);
				break;
            case KEY_ENTER:{
            int userInput=item_index(my_menu->curitem);
            
            unpost_menu(my_menu);
            free_menu(my_menu);
            for(i = 0; i < n_choices; ++i)
                free_item(my_items[i]);
	        endwin();
            return userInput;	       
            }
        }
    }
}

// Print the save/load menu
void printLoad(WINDOW * &window) {
    // Print a menu with save and load buttons aligned vertically
    std::string menu[2] = {"Save", "Load"};
    int y = 15;
    for (int i = 0; i < 2; ++i) {
        mvwprintw(window, y, 0, menu[i].c_str());
        y += 3;
        wrefresh(window);
    }
    wrefresh(window);
}

// Print the leaderboard
void printLeaderboard(WINDOW * &window) {
    std::ifstream fin;
    fin.open("leaderboard.txt");
    std::string line;
    // print line by line
    int i=0;
    start_color();
    while (getline(fin, line) && i<15){
        mvwprintw(window, i, 0, line.c_str());
        i++;
        }
        wrefresh(window);
    // close the file
    fin.close();
}

void printAbout(WINDOW * &window) {
    // Print the about page
    std::ifstream fin;
    fin.open("about.txt");
    std::string line;
    // print line by line
    int i=0;
    start_color();
    while (getline(fin, line) && i<15){
        mvwprintw(window, i, 0, line.c_str());
        i++;
        }
        wrefresh(window);
    // close the file
    fin.close();
}
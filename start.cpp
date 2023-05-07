#include <ncurses.h>
#include <vector>
#include <string>
#include <fstream>

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
    init_pair(1, COLOR_RED, COLOR_BLACK);
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
    start_color();
	init_pair(2, COLOR_RED, COLOR_WHITE);
    refresh();
    wrefresh(window);
    keypad(window, TRUE);
    // char to store choices
    char *choices[] = {
                        "        Start        ",
                        "        Load         ",
                        "     Leaderboard     ",
                        "        About        ",
                        "        Quit         ",
                  };
    // initializing variables
    int choice;
    int highlight = 0;
    int userInput=0;
    // main menu loop
    while(1) {
        mvprintw(LINES - 2, 1, "ENGG1340 Group 69 Project ");
        refresh();
        for(int i = 0; i < 5; ++i) {
            // highlights the present choice
            if (i == highlight) {
                wattron(window, A_REVERSE);
            }
            // prints the choices
            mvwprintw(window, i*2+1, 3, choices[i]);
            wattroff(window, A_REVERSE);
        }
        // read the choice
        choice = wgetch(window);
        switch(choice) {
            case KEY_UP:
                highlight--;
                if (highlight == -1) {
                    highlight = 0;
                }
                break;
            case KEY_DOWN:
                highlight++;
                if (highlight == 5) {
                    highlight = 4;
                }
                break;
            default:
                break;
        }
        if (choice == 10) {
            userInput=highlight;
            // do actions based on user input
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
    
	endwin();
}

// Print the difficulty menu
int printDifficulty(WINDOW * &window){
    refresh();
    wrefresh(window);
    keypad(window, TRUE);

    char *choices[] = {
                        "        Easy         ",
                        "       Medium        ",
                        "        Hard         ",
                        "       Expert        ",
                        "        Back         ",
                  };
    // initializing variables
    int choice;
    int highlight = 0;
    int userInput=0;
    // main menu loop
    while(1) {
        for(int i = 0; i < 5; ++i) {
            // highlights the present choice
            if (i == highlight) {
                wattron(window, A_REVERSE);
            }
            // prints the choices
            mvwprintw(window, i*2+1, 3, choices[i]);
            wattroff(window, A_REVERSE);
        }
        // read the choice
        choice = wgetch(window);
        switch(choice) {
            case KEY_UP:
                highlight--;
                if (highlight == -1) {
                    highlight = 0;
                }
                break;
            case KEY_DOWN:
                highlight++;
                if (highlight == 5) {
                    highlight = 4;
                }
                break;
            default:
                break;
        }
        if (choice == 10) {
            userInput=highlight;
            break;
        }
    }
    // do actions based on user input
	return userInput;	       
}


// Print the save/load menu
/*
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
    wgetch(window);
}
*/
void printLoad(WINDOW * &window) {
    std::ifstream fin;
    fin.open("load.txt");
    std::string line;
    // print line by line
    int i=0;
    start_color();
    while (getline(fin, line) && i<15){
        mvwprintw(window, i, 0, line.c_str());
        i++;
        }
        wrefresh(window);
    // print return message and refresh
    mvprintw(LINES - 2, 1, "Press any key to return...");
    refresh();
    // close the file
    fin.close();
    // hold the screen
    wgetch(window);
    // clear the screen
    wclear(window);
    // refresh the screen
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
    // print return message and refresh
    mvprintw(LINES - 2, 1, "Press any key to return...");
    refresh();
    // close the file
    fin.close();
    // hold the screen
    wgetch(window);
    // clear the screen
    wclear(window);
    // refresh the screen
    wrefresh(window);
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
    // print return message and refresh
    mvprintw(LINES - 2, 1, "Press any key to return...");
    refresh();
    // close the file
    fin.close();
    // hold the screen
    wgetch(window);
    // clear the screen
    wclear(window);
    // refresh the screen
    wrefresh(window);
}
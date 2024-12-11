#include "node.h"
#include <iostream>
#include <conio.h>
#include <chrono>
#include <windows.h>
#include <string>
#include <thread>
#include <mutex>
#include <atomic>
#include <fstream>
using namespace std;

mutex console_mutex;
atomic<bool> stopGame(false);

node* newnode = new node(0, 0);
node* temp;
node* head = nullptr;


void node::insert_nodes(node*** candy) {
    try {



        if (head == nullptr) {
            head = newnode;
        }
        else {
            temp = head;
            while (temp->address_node != nullptr) {
                temp = temp->address_node;
            }
            newnode->prev = temp;
            temp->address_node = newnode;
        }

        string colors[] = {
            "\033[31m",
            "\033[32m",
            "\033[33m",
            "\033[34m",
            "\033[35m",
            "\033[36m",
            "\033[37m"
        };

        COORD gridStartPos = { 0, 1 };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), gridStartPos);

        for (int i = 0; i < 30; i++) {
            for (int j = 0; j < 30; j++) {
                string color = colors[rand() % 7];
                cout << color << '[' << candy[i][j]->data << ']' << "";
            }
            cout << "\n";
        }

        cout << "\033[0m";
    }
    catch (exception& er) {
        cout << er.what();
    }
}

void node::delay() {
    Sleep(200);
}


void node::Timer(int minutes, int seconds) {
    int totalseconds = minutes * 60 + seconds;
    /*int backuptime = minutes * 60 + seconds;*/

    while (totalseconds >= 0 && !stopGame) {
        int remainingminutes = totalseconds / 60;
        int remainingseconds = totalseconds % 60;

        {
            lock_guard<mutex> lock(console_mutex);
            COORD timerPos = { 100, 0 };
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), timerPos);
            cout << "timer : "
                << (remainingminutes < 10 ? "0" : "") << remainingminutes << ":"
                << (remainingseconds < 10 ? "0" : "") << remainingseconds << "  ";
        }

        delay();
        totalseconds--;
    }

    stopGame = true;
    
}



int ca;


    void node::insert_candy() {
        int i, j;

        srand(time(NULL));

        node*** mynodes = new node * *[30];
        for (i = 0; i < 30; i++) {
            mynodes[i] = new node * [30];
            cout << "\n";

            for (j = 0; j < 30; j++) {
                int randomValue = rand() % 10;
                mynodes[i][j] = new node(randomValue);
            }
        }
       /* Timer(10, 9);*/
        insert_nodes(mynodes);
        player_position(mynodes);
        swapping_Candy(mynodes);

       

       

        if (stopGame) {
            system("cls");
            COORD messagePos = { 0, 0 };
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), messagePos);
            cout << "Time's up! Exiting the game..." << endl;
        }
    }

    




node* node::sethead(node* first_node)
{
    head = first_node;
    return head;
}



void node::swapWithPrev() {
    if (!this->prev) {
        cout << "No previous node to swap with!" << endl;
        return;
    }

    node* current = this;           
    node* prevNode = current->prev; 
    node* prevPrev = prevNode->prev; 
    node* nextNode = current->address_node; 
    if (prevPrev) {
        prevPrev->address_node = current;
    }

    if (nextNode) {
        nextNode->prev = prevNode;
    }

    current->prev = prevPrev;
    current->address_node = prevNode;

    prevNode->prev = current;
    prevNode->address_node = nextNode;

    if (head == prevNode) {
        head = current;
    }

    cout << "Swapped " << prevNode->data << " with " << current->data << endl;
}




int  first_candy = -1;
int target_candy = -1;
node* firstNode;  
node* targetNode;
int node::player_position(node** *& candy) {
    try {
        string colors[] = {
            "\033[31m", "\033[32m", "\033[33m",
            "\033[34m", "\033[35m", "\033[36m", "\033[37m"
        };

        while (true) {

            COORD gridStartPos = { 0, 1 };
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), gridStartPos);

            for (int i = 0; i < 30; i++) {
                for (int j = 0; j < 30; j++) {
                    if (i == newnode->pos_y && j == newnode->pos_x) {
                        cout << '[' << " " << ']';
                    }
                    else {
                        string color = colors[candy[i][j]->data % 7];
                        cout << color << '[' << candy[i][j]->data << ']' << "\033[0m";
                    }
                }
                cout << "\n";
            }
            // 0 224
            int ch = _getch();
            if (ch == 224) {
                ch = _getch();
                switch (ch) {
                case 72: if (newnode->pos_y > 0) newnode->pos_y--; break;
                case 80: if (newnode->pos_y < 29) newnode->pos_y++; break;
                case 75: if (newnode->pos_x > 0) newnode->pos_x--; break;
                case 77: if (newnode->pos_x < 29) newnode->pos_x++; break;
                }

                cout << "coridinate y : " << " " << newnode->pos_y << " cordinate x : " << newnode->pos_x;
            }
            else if (ch == 13) {
                int current_x = newnode->pos_x;
                int current_y = newnode->pos_y;

                if (first_candy == -1) {
                    first_candy = candy[current_y][current_x]->data;
                    firstNode = candy[current_y][current_x];
                }
                else {
                    target_candy = candy[current_y][current_x]->data;
                    targetNode = candy[current_y][current_x];

                    swapping_Candy(candy);
                    deleteMatchesAndRegenerate(candy);
                }
            }
        }
    }
    catch (const exception& ex) {
        cout << "Error: " << ex.what() << endl;
    }
    return newnode->pos_y;
}





void node::game_main_menu() {
    char user_choice;

    cout << "Hello to our candy crush game , We hope you will have a nice time with us and enjoy your time."
        << "\n"
        << "-------------------------------------------------------------------------------------------------"
        << "\n"
        << "1) Play game\n2) Show your history\n3) Levels\n\n: ";
    cin >> user_choice;

    switch (user_choice) {
    case '1':
        loading_page();
        Sleep(200);
        system("cls");
        insert_candy();
        break;

    default:
        break;
    }
}

int node::getTerminalWidth() {
    return 110;
}

void node::loading_page() {
      int i;

      cout << "LOADING : "
          << "\n\n";

      for (i = 0; i <= 70; i++) {
          cout << "-";
          Sleep(30);

          if (i == 70) {
              cout << "\n";
              for (int k = 0; k <= 70; k++) {
                  cout << '*';
                  Sleep(30);

                  if (k == 70) {
                      cout << "\n";
                      for (int j = 0; j <= k; j++) {
                          cout << '-';
                          Sleep(30);
                      }
                  }
              }
          }
      }




}

void node::history_of_the_game()
{

    


    try {

        ofstream historyfile("history_file.txt");




        historyfile << "the time the player has taken to end the game is : " << 1 / 60 << "menuits" << " " << 1 % 60 << "seconds" << endl;


        historyfile.close();
    }
    catch (exception er) {
        cout << er.what();
    }


}

int   node::get_pos_x()
{







    return newnode->pos_x;
}

int node::get_pos_y()
{
    return newnode->pos_y;
}

void node::swapping_Candy(node*** candy) {
    try {
        if (first_candy == -1 || target_candy == -1) {
            cout << "No candies selected for swapping." << endl;
            return;
        }

        int tempData = firstNode->data;
        firstNode->data = targetNode->data;
        targetNode->data = tempData;

        cout << "Swapped candies: " << first_candy << " with " << target_candy << endl;

        first_candy = -1;
        target_candy = -1;
        firstNode = nullptr;
        targetNode = nullptr;

        COORD gridStartPos = { 0, 1 };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), gridStartPos);
        for (int i = 0; i < 30; i++) {
            for (int j = 0; j < 30; j++) {
                string colors[] = {
                    "\033[31m", "\033[32m", "\033[33m",
                    "\033[34m", "\033[35m", "\033[36m", "\033[37m"
                };
                string color = colors[candy[i][j]->data % 7];
                cout << color << '[' << candy[i][j]->data << ']' << "\033[0m";
            }
            cout << "\n";
        }
    }
    catch (const exception& ex) {
        cout << "Error during swapping: " << ex.what() << endl;
    }
}



void node::deleteMatchesAndRegenerate(node*** candy) {
    try {
      
        bool toDelete[30][30] = { false };

      
        for (int i = 0; i < 30; i++) {
            for (int j = 0; j < 28; j++) { 
                if (candy[i][j]->data == candy[i][j + 1]->data &&
                    candy[i][j]->data == candy[i][j + 2]->data) {
                    toDelete[i][j] = toDelete[i][j + 1] = toDelete[i][j + 2] = true;
                }
            }
        }

      
        for (int j = 0; j < 30; j++) {
            for (int i = 0; i < 28; i++) { // Ensure we don't go out of bounds
                if (candy[i][j]->data == candy[i + 1][j]->data &&
                    candy[i][j]->data == candy[i + 2][j]->data) {
                    toDelete[i][j] = toDelete[i + 1][j] = toDelete[i + 2][j] = true;
                }
            }
        }

     
        for (int i = 0; i < 30; i++) {
            for (int j = 0; j < 30; j++) {
                if (toDelete[i][j]) {
                    candy[i][j]->data = rand() % 10; 
                }
            }
        }

       
        COORD gridStartPos = { 0, 1 };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), gridStartPos);

        string colors[] = {
            "\033[31m", "\033[32m", "\033[33m",
            "\033[34m", "\033[35m", "\033[36m", "\033[37m"
        };

        for (int i = 0; i < 30; i++) {
            for (int j = 0; j < 30; j++) {
                string color = colors[candy[i][j]->data % 7];
                cout << color << '[' << candy[i][j]->data << ']' << "\033[0m";
            }
            cout << "\n";
        }
    }
    catch (const exception& ex) {
        cout << "Error during deletion and regeneration: " << ex.what() << endl;
    }
}





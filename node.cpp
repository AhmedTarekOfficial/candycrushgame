#include "node.h"
#include <iostream>
#include <conio.h> 


using namespace std;
#include <windows.h>



void node::insert_nodes(int candy[30][30])
{


    try
    {

        node* newnode = new node();
        node* temp;
        node* head = nullptr;

        if (head == nullptr)
        {
            head = newnode;
        }
        else
        {
            temp = head;
            while (temp->address_node != nullptr)
            {
                temp = temp->address_node;
            }

            newnode->prev = temp;
            temp->address_node = newnode;
        }


        string colors[] = {
    "\033[31m", // Red
    "\033[32m", // Green
    "\033[33m", // Yellow
    "\033[34m", // Blue
    "\033[35m", // Magenta
    "\033[36m", // Cyan
    "\033[37m"  // White
        };



        for (int i = 0; i < 30; i++)
        {
            cout << "\n";
            for (int j = 0; j < 30; j++)
            {


                string color = colors[rand() % 7];
                cout << color << '[' << candy[i][j] << ']' << "";
            }
        }
    }
    catch (exception& er)
    {
        cout << er.what();
    }
}

void node::insert_candy()
{

    srand(time(NULL));

    int candy[30][30];
    for (int i = 0; i < 30; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            candy[i][j] = rand() % 10;
        }
    }
    insert_nodes(candy);
    player_position(candy);


}

void node::player_position(int candy[30][30]) {
    try {
        int pos_X = 0;
        int pos_Y = 0;

        string colors[] = {
            "\033[31m",
            "\033[32m",
            "\033[33m",
            "\033[34m",
            "\033[35m",
            "\033[36m",
            "\033[37m"
        };

        while (true) {
            system("cls");

            for (int i = 0; i < 30; i++) {
                for (int j = 0; j < 30; j++) {
                    if (i == pos_Y && j == pos_X) {
                        cout << '[' << " " << ']';
                    }
                    else {
                        string color = colors[candy[i][j] % 7];
                        cout << color << '[' << candy[i][j] << ']' << "\033[0m";
                    }
                }
                cout << "\n";
            }

            int ch = _getch();
            if (ch == 224) {
                ch = _getch();
                switch (ch) {
                case 72:
                    if (pos_Y > 0) --pos_Y;
                    break;
                case 80:
                    if (pos_Y < 29) ++pos_Y;
                    break;
                case 75:
                    if (pos_X > 0) {
                   
                        --pos_X;
                    }
                    break;

                case 77:
                    if (pos_X < 29) ++pos_X;
                    break;
                }
            }

            Sleep(100);
        }
    }
    catch (const exception& er) {
        cout << "Error: " << er.what() << endl;
    }
}



void node::delete_candy()
{

}

void node::game_main_menu()
{
}


#pragma once 


class node
{

public:

	int data;
	node* address_node;
	node* prev = nullptr;

	

	int pos_x   ; 
	int pos_y ; 

	

	

	
	node(int value = 0 , int pos_x_x = 0, int pos_y_y = 0) :  data(value), pos_x(pos_x_x), pos_y(pos_y_y) {};

	/*~node();*/


	void insert_nodes(node ***candy);
	void insert_candy();

	
	
	int player_position( node ***& candy);
	void  swapping_Candy(node*** candy );
	void game_main_menu();
	void Timer(int minutes, int seconds);
	

	void delay();
	int getTerminalWidth();
	void loading_page();

	void history_of_the_game();
	
	int get_pos_x();
	int get_pos_y();
	node* sethead(node* first_node = nullptr);
	void swapWithPrev();
	void  deleteMatchesAndRegenerate(node*** candy);
};


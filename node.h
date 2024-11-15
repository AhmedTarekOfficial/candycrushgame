#pragma once 


class node
{

public:

	int data;
	node* address_node;
	node* prev = nullptr;




	void insert_nodes(int candy[30][30]);
	void insert_candy();
	
	void player_position(int candy[30][30]);
	void delete_candy();
	void game_main_menu();

};


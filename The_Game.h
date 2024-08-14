#pragma once
#include "Table.h"
#include <thread>

using namespace std;



void source(AssetManager& asset, Texture& t, Texture& t1)
{
	t.loadFromFile("C:/Users/ukran/OneDrive/Изображения/R.JPG");
	t1.loadFromFile("C:/Users/ukran/OneDrive/Изображения/b.PNG");

	asset.createManager(t, 344, 0, 69, 100); // 1
	asset.createManager(t, 413, 0, 69, 100); // 2
	asset.createManager(t, 482, 0, 69, 100); // 3 
	asset.createManager(t, 551, 0, 69, 100); // 4
	asset.createManager(t, 620, 0, 69, 100); // 5
	asset.createManager(t, 689, 0, 69, 100); // 6
	asset.createManager(t, 758, 0, 69, 100); // 7
	asset.createManager(t, 827, 0, 69, 100); // 8
	asset.createManager(t, 0, 0, 69, 100); //9
	////////////////////////////////////////////////  
	asset.createManager(t, 344, 100, 69, 100); // 10
	asset.createManager(t, 413, 100, 69, 100); // 11
	asset.createManager(t, 482, 100, 69, 100); // 12
	asset.createManager(t, 551, 100, 69, 100); // 13
	asset.createManager(t, 620, 100, 69, 100); // 14
	asset.createManager(t, 689, 100, 69, 100); // 15
	asset.createManager(t, 758, 100, 69, 100); // 16
	asset.createManager(t, 827, 100, 69, 100); //17
	asset.createManager(t, 0, 100, 69, 100); // 18
	///////////////////////////////////////////// 
	asset.createManager(t, 344, 200, 69, 100); // 19
	asset.createManager(t, 413, 200, 69, 100); // 20
	asset.createManager(t, 482, 200, 69, 100); // 21
	asset.createManager(t, 551, 200, 69, 100); // 22
	asset.createManager(t, 620, 200, 69, 100); // 23
	asset.createManager(t, 689, 200, 69, 100); // 24
	asset.createManager(t, 758, 200, 69, 100); // 25
	asset.createManager(t, 827, 200, 69, 100); // 26
	asset.createManager(t, 0, 200, 69, 100); // 27
	//////////////////////////////////////////////  
	asset.createManager(t, 344, 300, 69, 100); // 28
	asset.createManager(t, 413, 300, 69, 100); // 29
	asset.createManager(t, 482, 300, 69, 100); // 30
	asset.createManager(t, 551, 300, 69, 100); // 31
	asset.createManager(t, 620, 300, 69, 100); // 32
	asset.createManager(t, 689, 300, 69, 100); // 33
	asset.createManager(t, 758, 300, 69, 100); // 34
	asset.createManager(t, 827, 300, 69, 100); // 35
	asset.createManager(t, 0, 300, 69, 100); // 36
	////////////////////////////////////////////////
	asset.createManager(t1, 0, 0, 168, 250); //  37 rubashka

}

void MyTurn(RenderWindow& window, Event& _event, Table& table, Player& player)
{
	Vector2i pos = Mouse::getPosition(window);
	player.game_button(pos.x, pos.y);

	if (player.hand.size() > 0)
	{
		if (_event.type == Event::MouseButtonPressed)
		{
			if (table.cards_on_table.size() == 6)
			{
				player.turn = false;
				table.Round = false;
			}
			else if (player.getglobalbounds_button(pos.x, pos.y))
			{
				player.turn = false;
			}
			else if (_event.key.code == Mouse::Left)
			{
				if (player.getglobalbounds_bool(pos.x, pos.y))
				{
					if (player.card_selected && player.index_card == player.getglobalbounds_int(pos.x, pos.y))
					{
						if (player.Attack == Player::Attack)
						{
							if (table.cards_on_table.size() == 0)
							{
								table.add_card_1(player.Put_the_card(player.index_card));
							}
							else if (table.find_equals_X(player.hand[player.index_card]) && table.cards_on_table.size() < 6)
							{
								table.add_card_1(player.Put_the_card(player.index_card));
							}
						}
						if (player.Wait == Player::Wait) ///////////////////nedodelano
						{
							if (table.find_equals_XY(player.hand[player.index_card]))
							{
								table.add_card_1(player.Put_the_card(player.index_card));
							}
						}
						if (player.Deff == Player::Deff) ///////////////////nedodelano
						{
							if (table.find_greater(player.hand[player.index_card]))
							{
								table.add_card_2(player.hand[player.index_card]);
							}
						}
					}
					else
					{
						player.card_selected = true;
					}
					player.index_card = player.getglobalbounds_int(pos.x, pos.y);
				}
			}
			if (_event.key.code == Mouse::Right)
			{
				player.card_selected = false;
			}
		}
		_event.type = Event::MouseButtonReleased;
	}
	else
	{
		player.turn = false;
	}
}

void queue_obj(RenderWindow& window, Event& _event, Table& table, Player& player)
{
	if (table.Round)
	{
		if (table.players.get_current_obj().turn)
		{
			player.rect_coodinat_butons();
			MyTurn(window, _event, table, player);
			std::this_thread::sleep_for(std::chrono::milliseconds(50));///////////////
			window.clear();
			table.draw_players(window);
			table.draw_table_cards(window);
			window.display();
		}
		else
		{
			table.players.next_object();
			table.turn();
		}
	}
	else if (!player.turn)
	{
		table.round_STATES();
	}
}


int the_Game()
{
	RenderWindow window(VideoMode::getDesktopMode(), "Durak", Style::Fullscreen);
	Event _event;
	AssetManager asset;


	Texture t;
	Texture t1;
	source(asset, t, t1);

	float width = VideoMode::getDesktopMode().width;
	float height = VideoMode::getDesktopMode().height;

	Table table(asset, width, height);

	table.set_value_seats(6);
	table.create_table();
	table.round_STATES();
	table.turn();

	for (int i = 0; i < table.players.get_sise(); i++)
	{
		table.players.get_current_obj().draw(window);
		table.players.next_object();
	}

	while (window.isOpen())
	{
		while (window.pollEvent(_event))
		{
			if (table.players.get_sise() == 1 || _event.type == Event::Closed)
				window.close();

			queue_obj(window, _event, table, table.players.get_current_obj());
		}
	}

	return 0;
}

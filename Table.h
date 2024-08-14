#pragma once
//#ifndef _TABLE_H_
//#define _TABLE_H_

#include "circlelist.h"
#include "Cards_Deck_of_cards.h"
#include "Asset_manager.h"
#include "Player.h"
#include <list>


class Table
{
	struct Pair_cards { Card x, y; };

public:

	std::list<Pair_cards> cards_on_table;
	Deck_of_cards deck; /// колода создается\тусуется по умолчанию
	circle_list<Player> players;
	bool Round = true;

	Table(AssetManager& asset, float width, float heigth)
	{
		this->asset = asset;
		this->width = width;
		this->height = heigth;
	}

	void create_table()
	{
		for (int i = 0; i < value_players; i++)
		{
			Player pl(asset, width, height);
			players.push_front(pl);
		}
		distribute_cards_STARTgame();
		first_turn();
		for (int i = 0; i < value_players; i++)
		{
			players.get_current_obj().points_players();
			players.next_object();
		}
	}

	void round_STATES() /// определить емуны в начале раунда
	{
		for (int i = 0; i < players.get_sise(); i++)
		{
			if (i == 0)
			{
				players.get_current_obj().set_STATE(Player::STATE::Attack);
			}
			else if (i == 1)
			{
				players.get_current_obj().set_STATE(Player::STATE::Deff);
			}
			else
			{
				players.get_current_obj().set_STATE(Player::STATE::Wait);
			}
			players.next_object();
		}
	}

	void turn()
	{
		for (int i = 0; i < players.get_sise(); i++)
		{
			if (i == 0)
			{
				players.get_current_obj().turn = true;
			}
			else if (i == 1)
			{
				players.get_current_obj().turn = false;
			}
			else
			{
				players.get_current_obj().turn = false;
			}
			players.next_object();
		}
		Round = true;
	}

	void add_card_1(Card card)
	{
		Pair_cards pair;
		pair.x = card;
		cards_on_table.push_back(pair);
	}

	void add_card_2(Card card)///////////////// недоделано
	{
		Pair_cards pair;

	}

	bool find_equals_X(Card& card)
	{
		for (auto& it : cards_on_table)
		{
			if (it.x == card)
			{
				return true;
			}
		}
		return false;
	}

	bool find_equals_XY(Card& card)
	{
		for (auto& it : cards_on_table)
		{
			if (it.x == card)
			{
				return true;
			}
			if (it.y == card)
			{
				return true;
			}
		}
		return false;
	}

	bool find_greater(Card& card)
	{
		for (auto& it : cards_on_table)
		{
			if (card > it.x)
			{
				return true;
			}
		}
		return false;
	}

	void draw_players(RenderWindow& window)
	{
		for (int i = 0; i < value_players; i++)
		{
			players.get_current_obj().draw(window);
			players.next_object();
		}
		players.get_current_obj().draw_button(window);
	}

	void draw_table_cards(RenderWindow& window)
	{
		float pointX = width / 2;
		float pointY = height / 2;
		int value_pairs = cards_on_table.size();
		float point = value_pairs * (width / 15); //некое значение, блягодаря которому будут спратится карты друг от друга пропрционально количеству

		int i = 0;
		for (auto& it : cards_on_table)
		{
			asset.set(it.x.get_key());
			asset.setPos(pointX + point / value_pairs * i++ - point / 2, pointY);
			asset.draw(window);

			if (it.y.get_key() != 0) /// проверка на бланковую карту (он же конструктор по умолчанию)
			{
				asset.set(it.y.get_key());
				asset.setPos((pointX + point / value_pairs * i - point / 2) + 15, pointY - 50);
				asset.draw(window);
			}
		}
	}

	void set_value_seats(int sits) // задать кол-во игроков, от мин до максимального
	{
		if (sits <= 2)
			value_players = 2;
		if (sits > 2 && sits < 6)
			value_players = sits;
		if (sits >= 6)
			value_players = 6;
	}


private:

	int value_players;/////////////
	AssetManager asset;
	float width;
	float height;

	void distribute_cards_STARTgame() /// раздача по одной карте по кругу. до фула
	{
		while (!players.get_current_obj().full_hand())
		{
			players.get_current_obj().Take_card(deck.get_card());
			players.next_object();
		}
	}

	void distribute_cards_INgame() /// раздает одному игроку карты пока фулханд = фолс
	{
		while (!deck.empty() && !players.get_current_obj().full_hand())
		{
			players.get_current_obj().Take_card(deck.get_card());
		}
	}

	void distribute_cards_player_check() /// 
	{
		for (int i = 0; i < players.get_sise(); i++)
		{
			players.next_object();
			distribute_cards_INgame();
		}
	}

	void first_turn() // определяет у кого младший козырь и кто будет ходить первым
	{
		Card trump_card;

		if (value_players < 6)
		{
			trump_card = deck.trump_suit_check();
		}
		else
		{
			trump_card = players.get_current_obj().hand[5];
		}

		int rank_card = 9;

		for (int i = 0; i < players.get_sise(); i++)
		{
			for (auto current_card : players.get_current_obj().hand)
			{
				if (trump_card.get_trump() == current_card.get_trump() && current_card.get_rank() < rank_card)
				{
					rank_card = current_card.get_rank();
				}
			}
			players.next_object();
		}

		for (int i = 0; i < players.get_sise(); i++)
		{
			for (int j = 0; j < players.get_current_obj().hand.size(); j++)
			{
				if (players.get_current_obj().hand[j].get_rank() == rank_card)
				{
					round_STATES();
					turn();
					break;
				}
			}
		}
	}

	friend Card Deck_of_cards::trump_suit_check();

	void find_STATE_obj(Player::STATE state)
	{
		while (players.get_current_obj().get_STATE() == state)
		{
			players.get_current_obj();
		}
	}
};

//#endif



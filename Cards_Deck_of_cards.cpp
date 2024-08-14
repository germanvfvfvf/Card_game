#include "Cards_Deck_of_cards.h"
//#include <algorithm>

Deck_of_cards::Deck_of_cards()
{
	Shuffling();
}

void Deck_of_cards::Shuffling()
{
	for (int i = 0; i < valueCards; )
	{
		Card card(rand() % 4 + 1, rand() % 9 + 1);

		bool alredy_there = false;

		for (int j = 0; j < i; j++)
		{
			if (deck[j].get_key() == card.get_key())
			{
				alredy_there = true;
				break;
			}
		}
		if (!alredy_there)
		{
			deck.push_back(card);
			i++;
		}
	}

	/*for (int i = 1; i < 10; i++)
	{
		for (int j = 1; j < 5; j++)
		{
			Card card(j, i);
			deck.push_back(card);
		}
	}
	std::random_shuffle(deck.begin(), deck.end());*/
	////////////////////////

	Determine_the_trump_cards();
}


Card Deck_of_cards::trump_suit_check()
{
	return deck[0];
}

Card Deck_of_cards::get_card()
{
	Card card = deck[valueCards - 1];
	deck.pop_back();
	valueCards--;
	return card;
}

bool Deck_of_cards::empty()
{
	return deck.empty();
}

int Deck_of_cards::Sise()
{
	return valueCards;
}

void Deck_of_cards::Determine_the_trump_cards()
{
	auto suit = deck[0].get_suit();

	for (auto& it : deck)
		if (it.get_suit() == suit)
			it.set_trump();
}

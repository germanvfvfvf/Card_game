#pragma once
#include <vector>

class Card
{
public:

	Card() :
		suit(0),
		rank(0),
		key(0),
		trump(false)
	{};

	Card(int suit, int rank) :
		suit(suit),
		rank(rank),
		key((suit - 1) * 9 + rank)
	{};

	bool operator > (const Card& card)
	{
		if (card.suit == suit &&
			card.rank > rank ||
			card.trump == trump &&
			card.rank > rank ||
			card.trump == true && trump == false)
			return true;
		return false;
	}

	bool operator < (const Card& card)
	{
		if (card.suit == suit &&
			card.rank < rank ||
			card.trump == trump &&
			card.rank < rank ||
			card.trump == false && trump == true)
			return true;
		return false;
	}

	bool operator == (const Card& card)
	{
		if (card.rank == rank)
			return true;
		return false;
	}

	int get_rank() { return rank; }

	int get_suit() { return suit; }

	int get_key() { return key; }

	bool get_trump() { return trump; }

	void set_trump() { trump = true; }

private:

	int rank;
	int suit;
	int key; //// for asset manager and other checks
	bool trump = false;

};


class Deck_of_cards
{
public:

	Deck_of_cards();
	void Shuffling();
	Card trump_suit_check();
	Card get_card();
	bool empty();
	int Sise();

private:

	int valueCards = 36;
	std::vector<Card>  deck;

	void Determine_the_trump_cards();
};


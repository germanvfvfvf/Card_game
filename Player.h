#pragma once
//#ifndef _Player_H_
//#define _Player_H_
#include "Table.h"
#include <iostream>


class Player
{
	AssetManager asset;
	RectangleShape button;


public:

	bool card_selected = false;
	int index_card;
	bool turn = false;
	std::vector<Card> hand;
	enum STATE { Attack, Deff, Wait };

	Player() {}

	Player(AssetManager& asset, float width, float heigth)
	{
		numberPlayer = value_players;
		value_players++;
		this->asset = asset;
		this->width = width;
		this->height = heigth;
	}

	void Take_card(Card card)
	{
		value_hand_cards++;
		hand.push_back(card);
	}

	Card Put_the_card(int index)
	{
		Card card = hand[index];
		auto it = hand.begin();
		hand.erase(it + index);
		value_hand_cards--;
		return card;
	}

	bool full_hand()
	{
		if (hand.size() != 6)
		{
			return false;
		}
		return true;
	}

	void draw(RenderWindow& window)
	{
		float point = value_hand_cards * (width / 40 - value_hand_cards * 2);// некое значение, блягодаря которому будут спратится карты друг от друга пропрционально количеству

		for (int i = 0; i < value_hand_cards; i++)
		{
			asset.set(hand[i].get_key());

			if (i == index_card && card_selected)
			{
				asset.setPos(pointX + point / value_hand_cards * i - point / 2, pointY - 15);
			}
			else
			{
				asset.setPos(pointX + point / value_hand_cards * i - point / 2, pointY);
			}
			asset.draw(window);
		}
	}

	void rect_coodinat_butons()
	{
		float point = value_hand_cards * (width / 40 - value_hand_cards * 2);// некое значение, блягодаря которому будут спратится карты друг от друга пропрционально количеству
		arr_coorditane_buttons.clear();
		arr_coorditane_buttons.reserve(value_hand_cards);

		for (int i = 0; i < value_hand_cards; i++)
		{
			arr_coorditane_buttons.push_back(FloatRect());
			arr_coorditane_buttons[i].top = pointY;
			arr_coorditane_buttons[i].left = pointX + point / value_hand_cards * i - point / 2;
			arr_coorditane_buttons[i].height = pointY + 100;

			float w = (pointX + point / value_hand_cards * 1 - point / 2) - (pointX + point / value_hand_cards * 0 - point / 2);
			if (i == value_hand_cards - 1)
			{
				arr_coorditane_buttons[i].width = 69 + (pointX + point / value_hand_cards * i - point / 2);
			}
			else
			{
				arr_coorditane_buttons[i].width = w + (pointX + point / value_hand_cards * i - point / 2);
			}
		}
	}

	void game_button(float x, float y) {

		if (turn && button.getGlobalBounds().contains(x, y))
		{
			button.setSize(Vector2f(60, 40));
			button.setPosition(Vector2f(width / 11 * 10, height / 8 * 7));
			button.setFillColor(sf::Color::Yellow);
		}
		else if (turn)
		{
			button.setSize(Vector2f(60, 40));
			button.setPosition(Vector2f(width / 11 * 10, height / 8 * 7));
			button.setFillColor(sf::Color::Green);
		}
		else
		{
			button.setSize(Vector2f(60, 40));
			button.setPosition(Vector2f(width / 11 * 10, height / 8 * 7));
			button.setFillColor(sf::Color::Red);
		}

	}

	void draw_button(RenderWindow& window) { window.draw(button); }

	int getglobalbounds_int(float x, float y)
	{
		for (int i = 0; i < value_hand_cards; i++)
		{
			if (arr_coorditane_buttons[i].left <= x &&
				arr_coorditane_buttons[i].width > x &&
				arr_coorditane_buttons[i].top <= y &&
				arr_coorditane_buttons[i].height > y)
				return i;
		}
	}

	bool getglobalbounds_bool(float x, float y)
	{
		for (int i = 0; i < value_hand_cards; i++)
		{
			if (arr_coorditane_buttons[i].left <= x &&
				arr_coorditane_buttons[i].width > x &&
				arr_coorditane_buttons[i].top <= y &&
				arr_coorditane_buttons[i].height > y)
				return true;
		}
		return false;
	}

	bool getglobalbounds_button(float x, float y) { return button.getGlobalBounds().contains(x, y); }

	int return_id() { return numberPlayer; }

	void set_STATE(STATE State) { this->State = State; }

	STATE get_STATE() { return State; }

	void points_players()
	{
		if (numberPlayer == 0) {
			pointX = width / 2;
			pointY = height / 7 * 6;
		}
		if (value_players == 2) {
			if (numberPlayer == 1) {
				pointX = width / 2;
				pointY = height / 6;
			}
		}
		if (value_players == 3) {
			if (numberPlayer == 1) {
				pointX = width / 6;
				pointY = height / 5;
			}
			if (numberPlayer == 2) {
				pointX = width / 6 * 5;
				pointY = height / 5;
			}
		}
		if (value_players == 4) {
			if (numberPlayer == 1) {
				pointX = width / 6;
				pointY = height / 2;
			}
			if (numberPlayer == 2) {
				pointX = width / 2;
				pointY = height / 6;
			}
			if (numberPlayer == 3) {
				pointX = width / 6 * 5;
				pointY = height / 2;
			}
		}
		if (value_players == 5) {
			if (numberPlayer == 1) {
				pointX = width / 6;
				pointY = height / 4 * 3;
			}
			if (numberPlayer == 2) {
				pointX = width / 5;
				pointY = height / 4;
			}
			if (numberPlayer == 3) {
				pointX = width / 5 * 4;
				pointY = height / 4;
			}
			if (numberPlayer == 4) {
				pointX = width / 6 * 5;
				pointY = height / 4 * 3;
			}
		}
		if (value_players == 6) {
			if (numberPlayer == 1) {
				pointX = width / 6;
				pointY = height / 3;
			}
			if (numberPlayer == 2) {
				pointX = width / 6;
				pointY = height / 3 * 2;
			}
			if (numberPlayer == 3) {
				pointX = width / 2;
				pointY = height / 6;
			}
			if (numberPlayer == 4) {
				pointX = width / 6 * 5;
				pointY = height / 3;
			}
			if (numberPlayer == 5) {
				pointX = width / 6 * 5;
				pointY = height / 3 * 2;
			}
		}
	}

private:

	float width; //деление по экрану
	float height;//
	STATE State;
	///////////////
	float pointX;//координаты посадки
	float pointY;//
	int numberPlayer;
	static int value_players;
	int value_hand_cards = 0; // использую инт, вместно "hand_array.size()" для уменьшения бесполезного вызова метода
	std::vector<FloatRect> arr_coorditane_buttons; // массив содержащий в себе координаты спрайтов карт , с целью взаимодействия с ними курсором

};

int Player::value_players = 0;

//#endif 
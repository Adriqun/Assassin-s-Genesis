#pragma once
#include "eeentity.h"

namespace ee
{
	class Tile : public Entity
	{
		char** array;

	public:
		Tile();
		virtual ~Tile();
		void free();
		void reset();

		bool checkCollision(sf::Vector2i &mouse);

		void load(sf::Vector2f &screen, int amount);
		void draw(sf::RenderWindow* &window, sf::Vector2i &add);
		bool add(Item &data);
		bool remove(sf::Vector2i &mouse);
	};

	//class UnvisibleTile final : public Tile {};
}
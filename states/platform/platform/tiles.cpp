#include "tiles.h"
#include "loading.h"
#include <boost/lexical_cast.hpp>

Tiles::Tiles()
{
	free();
}

Tiles::~Tiles()
{
	free();
}

void Tiles::free()
{
	width = 32;
	screen_w = 0;
	screen_h = 0;

	if (tiles)
	{
		for (int i = 0; i < max; ++i)
		{
			delete[] tiles[i];
			tiles[i] = nullptr;
		}

		delete[] tiles;
	}

	if (untiles)
	{
		for (int i = 0; i < max; ++i)
		{
			delete[] untiles[i];
			untiles[i] = nullptr;
		}

		delete[] untiles;
	}

	max = 0;

	if (!sprites.empty())
	{
		for (auto &it : sprites)
		{
			delete it;
			it = nullptr;
		}

		sprites.clear();
	}

	reset();
}

void Tiles::reset()
{
	border_x = 0;
	border_y = 0;

	collision = false;
}

void Tiles::load(const float &screen_w, const float &screen_h)
{
	free();

	this->screen_w = screen_w;
	this->screen_h = screen_h;

	rect.setSize(sf::Vector2f(static_cast<float>(width * 2), static_cast<float>(width * 2)));
	rect.setFillColor(sf::Color(0x99, 0x99, 0x00, 0x99));

	for (unsigned i = 0; i < 17; ++i)
	{
		sprites.push_back(new cmm::Sprite());
		Loading::add(sprites[i]->load("images/platform/tiles/" + std::to_string(i) + ".png"));
		if (Loading::isError())	return;
		sprites[i]->setScale	(0.51, 0.51);
	}

	// Init only once!
	if (!tiles && !untiles)
	{
		max = 3000;
		tiles = new char*[max];
		untiles = new char*[max];
		for (int i = 0; i < max; ++i)
		{
			tiles[i] = new char[max];
			untiles[i] = new char[max];
			for (int j = 0; j < max; ++j)
			{
				tiles[i][j] = -1;
				untiles[i][j] = -1;
			}
		}
	}
}

void Tiles::draw(sf::RenderWindow* &window/*, sf::Shader &shader*/)
{
	int l = static_cast <int> (border_x / width);
	int r = static_cast <int> ((border_x + screen_w) / width);
	int b = static_cast <int> (border_y / width);
	int t = static_cast <int> (border_y + screen_h) / width;

	for (int i = l; i < r; ++i)
	{
		for (int j = b; j < t; ++j)
		{
			if (tiles[i][j] != -1)
			{
				sprites[tiles[i][j]]->setPosition(i * width, -(j * width) + screen_h - width);
				// shader.setUniform("addAlpha", alphas[i][j] / 0xFF);
				window->draw(*sprites[tiles[i][j]]/*, &shader*/);
			}
			else if (untiles[i][j] != -1)
			{
				sprites[untiles[i][j]]->setPosition(i * width, -(j * width) + screen_h - width);
				// shader.setUniform("addAlpha", alphas[i][j] / 0xFF);
				window->draw(*sprites[untiles[i][j]]/*, &shader*/);
			}
		}
	}

	// shader.setUniform("addAlpha", 1);

	if (collision)
	{
		window->draw(rect/*, &shader*/);
		rect.setPosition(-rect.getSize().x, -rect.getSize().y);	// put rect outside of window are
	}
}

void Tiles::read(std::vector<std::string> &vec)
{
	int x = -1, y = -1, c = -1;
	if (!vec.empty())
	{
		char** pointer = nullptr;
		if (vec[0].find("t:1") != std::string::npos)
			pointer = tiles;
		else
			pointer = untiles;

		for (auto &it : vec)
		{
			c = boost::lexical_cast<int>(it.substr(it.find("c:") + 2, it.find(" x:") - (it.find("c:") + 2)));
			x = boost::lexical_cast<int>(it.substr(it.find("x:") + 2, it.find(" y:") - (it.find("x:") + 2))) / width;
			y = boost::lexical_cast<int>(it.substr(it.find("y:") + 2, it.find(" id:") - (it.find("y:") + 2))) / width;
			pointer[x][y] = c;
		}
	}
}



void Tiles::setBorderX(float& x)
{
	border_x = x;
}

void Tiles::setBorderY(float& y)
{
	border_y = y;
}

const float& Tiles::getBorderX() const
{
	return border_x;
}

const float& Tiles::getBorderY() const
{
	return border_y;
}

const float& Tiles::getScreenWidth() const
{
	return screen_w;
}

const float& Tiles::getScreenHeight() const
{
	return screen_h;
}



void Tiles::switchCollision(bool collision)
{
	this->collision = collision;
}

bool Tiles::checkCollisionV(sf::Rect<int> &rect, const char add)
{
	int l = static_cast<int> (border_x / width);
	int r = static_cast<int> (border_x + screen_w) / width;
	int b = static_cast<int> (border_y / width);
	int t = static_cast<int> ((border_y + screen_h) / width);
	rect.top -= add;

	for (int i = l; i < r; ++i)
	{
		for (int j = b; j < t; ++j)
		{
			if (tiles[i][j] != -1)
			{
				sprites[tiles[i][j]]->setPosition(i * width, -(j * width) + screen_h - width);
				if (sprites[tiles[i][j]]->checkCollisionRect(rect))
				{
					if (collision)
					{
						this->rect.setSize(sf::Vector2f(sprites[tiles[i][j]]->getWidth(), sprites[tiles[i][j]]->getHeight()));
						this->rect.setPosition(sprites[tiles[i][j]]->getX(), sprites[tiles[i][j]]->getY());
					}

					rect.top += add;
					return true;
				}
			}
			else if (untiles[i][j] != -1)
			{
				sprites[tiles[i][j]]->setPosition(i * width, -(j * width) + screen_h - width);
				if (sprites[tiles[i][j]]->checkCollisionRect(rect))
				{
					if (collision)
					{
						this->rect.setSize(sf::Vector2f(sprites[tiles[i][j]]->getWidth(), sprites[tiles[i][j]]->getHeight()));
						this->rect.setPosition(sprites[tiles[i][j]]->getX(), sprites[tiles[i][j]]->getY());
					}

					rect.top += add;
					return true;
				}
			}
		}
	}

	rect.top += add;
	return false;
}

bool Tiles::checkCollisionH(sf::Rect<int> &rect, const char add)
{
	int l = static_cast<int> (border_x / width);
	int r = static_cast<int> (border_x + screen_w) / width;
	int b = static_cast<int> (border_y / width);
	int t = static_cast<int> ((border_y + screen_h) / width);
	rect.left -= add;

	for (int i = l; i < r; ++i)
	{
		for (int j = b; j < t; ++j)
		{
			if (tiles[i][j] != -1)
			{
				sprites[tiles[i][j]]->setPosition(i * width, -(j * width) + screen_h - width);
				if (sprites[tiles[i][j]]->checkCollisionRect(rect))
				{
					if (collision)
					{
						this->rect.setSize(sf::Vector2f(sprites[tiles[i][j]]->getWidth(), sprites[tiles[i][j]]->getHeight()));
						this->rect.setPosition(sprites[tiles[i][j]]->getX(), sprites[tiles[i][j]]->getY());
					}
						
					rect.left += add;
					return true;
				}
			}
			else if (untiles[i][j] != -1)
			{
				sprites[tiles[i][j]]->setPosition(i * width, -(j * width) + screen_h - width);
				if (sprites[tiles[i][j]]->checkCollisionRect(rect))
				{
					if (collision)
					{
						this->rect.setSize(sf::Vector2f(sprites[tiles[i][j]]->getWidth(), sprites[tiles[i][j]]->getHeight()));
						this->rect.setPosition(sprites[tiles[i][j]]->getX(), sprites[tiles[i][j]]->getY());
					}

					rect.left += add;
					return true;
				}
			}
		}
	}

	rect.left += add;
	return false;
}
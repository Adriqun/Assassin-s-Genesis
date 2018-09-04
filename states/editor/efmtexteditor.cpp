#include "efmtexteditor.h"

EFMTextEditor::EFMTextEditor()
{
	free();
}

EFMTextEditor::~EFMTextEditor()
{
	free();
}

void EFMTextEditor::free()
{
	screen_w = 0;
	screen_h = 0;

	arrow_counter = 0;
	arrow_line = 0.5;

	msg = "";

	reset();
	clear();
}

void EFMTextEditor::reset()
{
	decision = EMPTY;
}

void EFMTextEditor::clear()
{
	active = false;
}



void EFMTextEditor::load(const float &screen_w, const float &screen_h)
{
	free();

	this->screen_w = screen_w;
	this->screen_h = screen_h;

	float scale_x = screen_w / 1920;	if (scale_x > 1.0f)	scale_x = 1;
	float scale_y = screen_h / 1080;	if (scale_y > 1.0f)	scale_y = 1;

	board.load("images/other/plank2.png");
	board.setScale(scale_x, scale_y);
	board.center(screen_w / 2, screen_h / 2);

	const char* pathToFont = "fonts/Jaapokki-Regular.otf";
	infoText.setFont(pathToFont);
	formText.setFont(pathToFont);
	writtenText.setFont(pathToFont);
	arrowText.setFont(pathToFont);
	cancelText.setFont(pathToFont);
	proceedText.setFont(pathToFont);
	
	infoText.setSize(screen_w / 50);
	formText.setSize(screen_w / 60);
	writtenText.setSize(screen_w / 60);
	arrowText.setSize(screen_w / 60);
	cancelText.setSize(screen_w / 60);
	proceedText.setSize(screen_w / 60);

	infoText.setAlpha(0xFF);
	formText.setAlpha(0xFF);
	writtenText.setAlpha(0xFF);
	arrowText.setAlpha(0xFF);
	cancelText.setAlpha(0xFF);
	proceedText.setAlpha(0xFF);

	arrowText.setText("|");
	proceedText.setText("proceed");
	cancelText.setText("cancel");
	float off = screen_w / 200;
	proceedText.setPosition(board.getRight() - proceedText.getWidth() - off, board.getBot() - proceedText.getHeight() * 1.25 - off);
	cancelText.setPosition(board.getLeft() + off, proceedText.getTop());
	proceedRect = sf::FloatRect(proceedText.getX(), proceedText.getY(), proceedText.getWidth() * 2, proceedText.getHeight() * 2);
	cancelRect = sf::FloatRect(cancelText.getX(), cancelText.getY(), cancelText.getWidth() * 2, cancelText.getHeight() * 2);
}

void EFMTextEditor::handle(const sf::Event &event)
{
	if (!isActive())
		return;

	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			float x = (float)event.mouseButton.x;
			float y = (float)event.mouseButton.y;

			if (proceedRect.contains(x, y))		decision = PROCEED;
			else if (cancelRect.contains(x, y))	decision = CANCEL;
		}
	}

	if (event.type == sf::Event::TextEntered)
	{
		if (isPossibleKey(event.text.unicode))
		{
			if (writtenText.get().getString().getSize() < 19)
			{
				std::string temp = writtenText.get().getString();
				temp += event.text.unicode;
				writtenText.setText(temp);
				setWrittenText();
			}
		}
	}

	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::BackSpace)	// Delete last one.
		{
			if (writtenText.get().getString().getSize() >= 1)
			{
				std::string temp = writtenText.get().getString();
				temp.pop_back();
				writtenText.setText(temp);
				setWrittenText();
			}
		}
		else if (event.key.code == sf::Keyboard::Return)
		{
			decision = PROCEED;
		}
		else if (event.key.code == sf::Keyboard::Escape)
		{
			decision = CANCEL;
		}
	}
}

void EFMTextEditor::draw(sf::RenderWindow* &window)
{
	if (active)
	{
		window->draw(board.get());
		window->draw(infoText.get());
		window->draw(formText.get());
		window->draw(writtenText.get());

		if (arrow_counter < arrow_line)
			window->draw(arrowText.get());

		window->draw(cancelText.get());
		window->draw(proceedText.get());
	}
}

void EFMTextEditor::mechanics(const double &elapsedTime)
{
	arrow_counter += static_cast<float>(elapsedTime);
	if (arrow_counter > arrow_line * 2)
	{
		arrow_counter = 0;
	}
}



void EFMTextEditor::setActive()
{
	active = true;
}

const bool& EFMTextEditor::isActive() const
{
	return active;
}

bool EFMTextEditor::isDecision() const
{
	return decision != EMPTY;
}

bool EFMTextEditor::isCancel()
{
	if (decision == CANCEL)
	{
		decision = EMPTY;
		return true;
	}

	return false;
}

bool EFMTextEditor::isProceed()
{
	if (decision == PROCEED)
	{
		decision = EMPTY;
		return true;
	}

	return false;
}



void EFMTextEditor::set(std::string info, std::string form, std::string written)
{
	infoText.setText(info);
	formText.setText(form);
	writtenText.setText(written);

	infoText.center(board.getX() + board.getWidth() / 2, board.getY() + board.getHeight() / 15);
	formText.setPosition(cancelText.getLeft(), board.getY() + board.getHeight() / 3);
	setWrittenText();
}

std::string EFMTextEditor::get()
{
	return writtenText.get().getString() + ".chw";
}

bool EFMTextEditor::isMistake()
{
	std::string temp = writtenText.get().getString();

	if (temp.size() == 0)
	{
		msg = "File name should contain\nat least 1 character.";
		return true;
	}

	return false;
}

const std::string& EFMTextEditor::getMsg() const
{
	return msg;
}



void EFMTextEditor::setWrittenText()
{
	writtenText.setPosition(formText.getRight() + screen_w / 200.0f, formText.getY());
	arrowText.setPosition(writtenText.getRight() + screen_w / 600.0f, formText.getY());
}

bool EFMTextEditor::isPossibleKey(const sf::Uint8 &code) const
{
	if (code >= 48 && code <= 57)	// 0 .. 9
	{
		return true;
	}
	else if (code >= 65 && code <= 90)	// A .. Z
	{
		return true;
	}
	else if (code >= 97 && code <= 122) // a .. z
	{
		return true;
	}

	return false;
}
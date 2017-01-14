/**
    link_button.h
    Purpose: class Link_button - for buttons, after click open website with special url.

    @author Adrian Michalek
    @version 2016.10.16
	@email adrmic98@gmail.com
*/

#pragma once

#include "drawable/sprite.h"
#include "click.h"

class Link_button :public Click
{
    string url;
	
protected:
	
	bool locked;	// if true then we can not click on the button
    MySprite button;

public:
	
    Link_button( string url, bool locked = false );
    ~Link_button();

    void load( string path, int screen_w, int bot = 10 );
    void draw( sf::RenderWindow &window );
	void handle( sf::Event &event );
	
	void fadein( int i = 1, int max = 255 );
	void fadeout( int i = 1, int min = 0 );
	
	int getBot();	// getter
};
/**
    menu.h
    Purpose: class Menu is a huge container with buttons in menu state.

    @author Adrian Michalek
    @version 2016.11.20
	@email adrmic98@gmail.com
*/

#pragma once

#include "sound/sound.h"
#include "title/title.h"
#include "sound_button/sound_button.h"
#include "volume_button/volume_button.h"
#include "link_button/link_button.h"
#include "play_button/play_button.h"
#include "log/log.h"
#include "play_button/exit_log.h"
#include "sound/music.h"
#include "keyboard/information.h"
#include "keyboard/keyboard.h"
#include "development/development.h"
#include "reset_button/reset_button.h"

class Menu
{
	int state;
	
	// Menu objects
	Sound sound;
	
	Title* title;
	
	Sound_button* music_button;
	Sound_button* chunk_button;
	
	Volume_button* music_volume;
	Volume_button* chunk_volume;
	
	Link_button* git_button;
	Link_button* google_button;
	Link_button* twitter_button;
	Link_button* facebook_button;
	Link_button* scores_button;
	
	MySprite* background;
	
	Play_button* play_button;
	
	Log* author_log;
	Log* game_log;
	Log* settings_log;
	Log* skill_log;
	
	Exit_log* exit;
	
	Music* music;
	
	MyText* version;
	
	Information* information;
	Keyboard* keyboard;
	
	Development* development;
	
	Reset_button* reset_button;
	
public:
	
	Menu();
    ~Menu();
    void free();
	
    void load( int screen_w, int screen_h );
    void handle( sf::Event &event );
    void draw( sf::RenderWindow* &window );
	
	bool isQuit();
	bool nextState();
	void reloadMusic();
};
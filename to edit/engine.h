#pragma once

#include "core.h"
#include "loading/loading.h"
#include "intro/intro.h"
#include "menu/menu.h"
#include "level/levelmenu.h"

class Engine
{
    Core* core;
	Loading* loading;
	Intro* intro;
	Menu* menu;
	Level_menu* level_menu;

public:

    Engine();
    ~Engine();

    void free();
    void load();

    void events();
    void states();

    void loop();
};

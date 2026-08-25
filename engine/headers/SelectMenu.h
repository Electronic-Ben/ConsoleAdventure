#pragma once

#include <string>
#include <vector>
#include <utility>
#include <functional>
#include <unordered_map>


struct menuOption
{
	std::function<void()> callback;
	std::string label;

	menuOption(std::function<void()> func, std::string name)
		: callback(std::move(func)), label(std::move(name))
	{
	}
};


class SelectMenu
{
public:
	bool isOpen = false;
private:
	std::vector<menuOption> options;
	std::string display;
	int displayWidth;
	int selection = 0;
public:
	SelectMenu(int displayW);
	std::string getDisplay();
	void moveSelection(int dx, int dy);
	void select();
	void update();
	void addOption(std::function<void()> callback, std::string name);
	void close();
	void open();
private:
	std::string toString();
};


class Menu
{
public:
private:
	int displayWidth;
	std::unordered_map<std::string, SelectMenu> menus;
public:
	SelectMenu& addMenu(std::string name);
	SelectMenu* getMenu(std::string& name);
};
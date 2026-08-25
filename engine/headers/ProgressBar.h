#pragma once

#include <string>
#include <utility>
#include <functional>

class ProgressBar
{
private:
	int start = 0;
	int length = 0;
	std::string txt;
	std::string display;
	std::function<void()> onEnd;
	int ticks = 0;
public:
	ProgressBar();
	ProgressBar(int len, int endAt, std::string barText);

	bool tick();
	bool active();
	void reset();
	void setCallback(std::function<void()> callback);
	void set(int len, int endAt, std::string barText);
	std::string getDisplay();
private:
	char cap(char c);
	std::string toString();
};
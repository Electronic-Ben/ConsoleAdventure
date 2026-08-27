#include "engine/headers/ProgressBar.h"

ProgressBar::ProgressBar() : ticks(0), length(0), txt("") {}

ProgressBar::ProgressBar(int len, int endAfter, std::string barText)
    : ticks(endAfter), start(endAfter), length(len), txt(std::move(barText))
{
}

void ProgressBar::setCallback(std::function<void()> callback) { onEnd = std::move(callback); }

void ProgressBar::set(int len, int endAfter, std::string barText)
{
    ticks = endAfter;
    start = endAfter;
    length = len;
    txt = std::move(barText);
}

bool ProgressBar::tick()
{
    if (ticks < 0)
    {
        display = toString();
        return false;
    }

    if (ticks == 0)
    {
        if (onEnd)
        {
            onEnd();
        }
        ticks = -1;
        display = toString();
        return true;
    }

    display = toString();
    ticks--;
    return false;
}

std::string ProgressBar::toString()
{
    if (length <= 2 || ticks < 0)
    {
        return std::string(length, ' ');
    }

    double progress = 1.0 - (static_cast<double>(ticks) / start);
    if (progress < 0.0)
        progress = 0.0;
    if (progress > 1.0)
        progress = 1.0;

    int barLength = length - 2;
    int filledLength = static_cast<int>(progress * barLength + 0.5);

    std::string content;
    content.reserve(length);

    int wordStart = (barLength - static_cast<int>(txt.length())) / 2;
    int wordEnd = wordStart + static_cast<int>(txt.length());

    for (int i = 0; i < length - 2; i++)
    {
        if (i >= wordStart && i < wordEnd)
        {
            char c = txt[i - wordStart];
            if (i < filledLength)
            {
                content += cap(c);
            }
            else
            {
                content += c;
            }
        }
        else
        {
            if (i < filledLength)
            {
                content += '=';
            }
            else
            {
                content += '-';
            }
        }
    }

    return "[" + content + "]";
}

void ProgressBar::reset()
{
    start = 0;
    ticks = -1;
    txt.clear();
    display.clear();
    onEnd = nullptr;
}

std::string ProgressBar::getDisplay() { return display; }

bool ProgressBar::active() { return ticks >= 0; }

char ProgressBar::cap(char c)
{
    if (c >= 97 && c <= 122)
    {
        return c - 32;
    }
    return c;
}

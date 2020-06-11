//
// Created by Leonardo Oliveira on 29/04/2020.
//


#pragma once

#include <functional>

typedef enum {
    NORMAL = 's',
    MULTIPLE = 'm',
} EnumChoices;

typedef enum {
    AUTO,
    MANUAL,
} EnumGenerateMode;

typedef struct {
    int numCards;
    EnumChoices mode;
} MenuData;

class Menu {

private:
    int AskCards();

public:
    Menu();
    MenuData SelectMode();
    static EnumGenerateMode AskGenerateMode();
};
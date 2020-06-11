#include <iostream>
#include "Menu.h"
#include "Machine.h"

int main()
{
    Menu menu;
    MenuData data = menu.SelectMode();

    Machine machine(data);
}
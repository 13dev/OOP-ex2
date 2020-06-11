//
// Created by Leonardo Oliveira on 29/04/2020.
//

#include "Menu.h"
#include <iostream>
#include <limits>
#include "Machine.h"

Menu::Menu()
{
    std::cout << "Bem-vindo ao Euromilhoes " << std::endl;
    std::cout << "Escolha o tipo de aposta que deseja realizar: " << std::endl;
}

MenuData Menu::SelectMode()
{
    char choice = '\0';

    do {
        std::cout << "Aposta Simples (carregue 'S') Aposta Multipla (carregue 'M') - " << std::endl;
        std::cin >> choice;

        switch(tolower(choice))
        {
            case EnumChoices::NORMAL:
                std::cout << "-----------Escolheu a Aposta Simples----------- \n";
                std::clog << "Normal mode\n";

                return MenuData
                {
                    .numCards = AskCards(),
                    .generateMode = AskGenerateMode(),
                    .mode = EnumChoices::NORMAL,
                };

            case EnumChoices::MULTIPLE:
                std::cout << "-----------Escolheu a Aposta Multipla----------- \n";
                std::clog << "Multiple mode\n";

                return MenuData
                {
                    .numCards = AskCards(),
                    .generateMode = AskGenerateMode(),
                    .mode = EnumChoices::MULTIPLE,
                };

            default:
                continue;
        }

    } while(true);

}

EnumGenerateMode Menu::AskGenerateMode()
{
    char choice = '\n';

    do {
        std::cout << " Aposta Gerada Automaticamente (Carregue ‘A’) ou pelo Próprio (Carregue ‘P’) ?" << std::endl;
        std::cin >> choice;

        switch(tolower(choice))
        {
            case 'a':
                return EnumGenerateMode::AUTO;
            case 'p':
                return EnumGenerateMode::MANUAL;

            default:
                continue;
        }

    } while(true);


}


bool Menu::ParseIntInput(int& value)
{
    std::cin >> value;

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return std::cin.fail();
}

int Menu::AskCards()
{
    int t_Buffer;

    do {
        std::cout << "Quantas chaves pretende apostar? \n";

        if(Menu::ParseIntInput(t_Buffer)) {
            continue;
        }

        if(t_Buffer < 1 || t_Buffer > MAX_CARDS) {
            printf("Escolha numero entre 1 e %i!\n", MAX_CARDS);
            continue;
        }

       break;

    } while(true);

    return t_Buffer;
}


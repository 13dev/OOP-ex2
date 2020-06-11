//
// Created by Leonardo Oliveira on 29/04/2020.
//

#include "Menu.h"
#include <iostream>
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
                    .mode = EnumChoices::NORMAL,
                };

            case EnumChoices::MULTIPLE:
                std::cout << "-----------Escolheu a Aposta Multipla----------- \n";
                std::clog << "Multiple mode\n";

                return MenuData
                {
                    .numCards = AskCards(),
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

int Menu::AskCards()
{
    int t_numCards = 1;

    do {
        std::cout << "Quantas chaves pretende apostar? \n";
        std::cin >> t_numCards;

        if(t_numCards <= MAX_CARDS && t_numCards >= 1) {
            break;
        }

        printf("Escolha numero entre 1 e %i!\n", MAX_CARDS);

    } while(true);


    return t_numCards;
}


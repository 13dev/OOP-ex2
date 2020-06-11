//
// Created by Leonardo Oliveira on 29/04/2020.
//

#include "Machine.h"
#include <algorithm>
#include <ctime>
#include <iostream>
#include <regex>

int Machine::ParseInput(const std::string& t_Identifier, const ValidateInputCallback& t_Callback)
{
    std::regex regexInt("^0$|^[1-9][0-9]*$");
    std::string t_Buffer;

    do {
        std::cout << t_Identifier;
        std::cin >> t_Buffer;

        // Verificar se buffer faz match com regex
        if(!regex_match(t_Buffer, regexInt))
        {
            std::cout << "Insira um valor valido.\n";
            continue;
        }

        //Chamar callback passando o valor inteiro e excutar as condições particulares.
        if(!t_Callback(stoi(t_Buffer)))
        {
            continue;
        }

        break;

    }while(true);

    // Retornar o valor valido caso necessario.
    return stoi(t_Buffer);
}

int Machine::GenerateInt(int min = 0, int max = 0)
{
    int num = std::rand() % (max - min + 1) + min;

    return num;
}

Card Machine::InsertCard(Card& t_Card, int t_Index)
{
    data[t_Index] = t_Card;
    return t_Card;
}


Machine::Machine(MenuData t_menuData)
{
    srand(time(nullptr));

    for (int i = 0; i < t_menuData.numCards; ++i)
    {
        //Criar novo cartao inicializado tudo a zero para evitar garbage nums.
        Card t_Card = {0};

        const EnumGenerateMode t_GenerateMode = Menu::AskGenerateMode();

        printf("----- Apostando no (%i) Cartão -----\n", i + 1);

        switch (t_menuData.mode)
        {
            case EnumChoices::MULTIPLE:
            {
                // Perguntar numero de chaves e estrelas a apostar.
                const int t_NumKeys = AskNumberBetween(EnumContext::KEY, MIN_KEYS, MAX_KEYS);
                const int t_NumStars = AskNumberBetween(EnumContext::STAR, MIN_STARS, MAX_STARS);

                //Inserir estrelas
                InsertStars(t_Card, t_NumStars, t_GenerateMode);

                std::cout << "\n Estrelas: ";
                std::cout << PrintArray(t_Card.stars) << std::endl;

                // Inserir chaves
                InsertKeys(t_Card, t_NumKeys, t_GenerateMode);

                std::cout << "\n Chaves: ";
                std::cout << PrintArray(t_Card.keys) << std::endl;

                break;
            }
            case EnumChoices::NORMAL:

                //Inserir estrelas
                InsertStars(t_Card, MAX_NORMAL_STARS, t_GenerateMode);

                std::cout << "\n Estrelas: ";
                std::cout << PrintArray(t_Card.stars) << std::endl;


                // Inserir chaves
                InsertKeys(t_Card, MAX_NORMAL_KEYS, t_GenerateMode);

                std::cout << "\n Chaves: ";
                std::cout << PrintArray(t_Card.keys) << std::endl;

                break;
        }

        InsertCard(t_Card, i);
    }
}


void Machine::InsertKeys(Card& t_Card, int t_NumKeys, const EnumGenerateMode &t_GenerateMode)
{
    for (int index = 0; index < t_NumKeys; index++)
    {
        switch (t_GenerateMode)
        {
            case EnumGenerateMode::AUTO:
            {
                //Generate int until not exists in keys.
                int t_RandomInt;

                do {
                    t_RandomInt = GenerateInt(MIN_VALUE_KEYS, MAX_VALUE_KEYS);

                } while(std::find(t_Card.keys.begin(), t_Card.keys.end(), t_RandomInt) != t_Card.keys.end());

                t_Card.keys[index] = t_RandomInt;

                break;
            }
            case EnumGenerateMode::MANUAL:
                AskInsertContext(t_Card.keys, index, EnumContext::KEY, MIN_VALUE_KEYS, MAX_VALUE_KEYS);
                break;
        }

    }
}


void Machine::InsertStars(Card& t_Card, int t_NumStars, const EnumGenerateMode &t_GenerateMode)
{
    for (int index = 0; index < t_NumStars; index++)
    {
        switch (t_GenerateMode)
        {
            case EnumGenerateMode::AUTO:
            {
                //Generate int until not exists in stars.
                int t_RandomInt;

                do {
                    t_RandomInt = GenerateInt(MIN_VALUE_STARS, MAX_VALUE_STARS);

                } while(std::find(t_Card.stars.begin(), t_Card.stars.end(), t_RandomInt) != t_Card.stars.end());

                t_Card.stars[index] = t_RandomInt;

                break;
            }
            case EnumGenerateMode::MANUAL:
                AskInsertContext(t_Card.stars, index, EnumContext::STAR, MIN_VALUE_STARS, MAX_VALUE_STARS);
                break;
        }

    }

}

int Machine::AskNumberBetween(const EnumContext& t_Context, int t_Min, int t_Max)
{
    char buffer[200];
    sprintf(buffer, "Escolha nº de %ss entre %i e %i: ", STR_CONTEXT(t_Context), t_Min, t_Max);

//    std::stringstream buffer;
//    buffer << "Escolha nº de " << t_Identifier << " entre " << t_Min << " e " << t_Max << ": ";

    return Machine::ParseInput(buffer, [&](int input) {
        //Verificar limites do input
        return !(input > t_Max || input < t_Min);
    });

}

template<size_t N>
void Machine::AskInsertContext(std::array<int, N> &t_Data, int t_Index, const EnumContext& t_Context, int t_Min, int t_Max)
{
    char buffer[100];
    sprintf(buffer, "Insira a [%i] %s: " , t_Index + 1, STR_CONTEXT(t_Context));

    Machine::ParseInput(buffer, [&](int input) {

        // verificar se esta entre os limites.
        if(input > t_Max || input < t_Min)
        {
            printf("Insira uma %s entre %i e %i\n", STR_CONTEXT(t_Context), t_Min, t_Max);
            return false;
        }

        // verificar se já existe no array stars
        if(std::find(t_Data.begin(), t_Data.end(), input) != t_Data.end())
        {
            printf("Esta %s já foi votada tenta outra.\n",  STR_CONTEXT(t_Context));
            return false;
        }

        t_Data[t_Index] = input;

        return true;

    });

}

template<size_t N>
std::string Machine::PrintArray(const std::array<int, N> &t_Data)
{
    //Encontrar ultimo index not zero.
    int t_LastIndexNotZero = 0;
    for (int i = t_Data.size() - 1; i >= 0; --i)
    {
        if (t_Data.at(i) != 0)
        {
            t_LastIndexNotZero = i;
            break;
        }
    }

    std::string buffer;
    for (int j = 0; j < t_LastIndexNotZero + 1; ++j)
    {
        buffer += std::to_string(t_Data[j]);

        if(t_LastIndexNotZero == j)
        {
            buffer += ".";
            break;
        }

        buffer += ", ";
    }

    return buffer;
}





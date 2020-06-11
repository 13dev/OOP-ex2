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

int Machine::GetNumContext(const EnumContext& t_Context, const EnumChoices& t_Mode)
{
    const int maxValue = EnumContext::STAR == t_Context ? MAX_STARS : MAX_KEYS;
    const int minValue = EnumContext::STAR == t_Context ? MIN_STARS : MIN_KEYS;

    switch (t_Mode)
    {
        case EnumChoices::MULTIPLE:
            return AskNumberBetween(t_Context, minValue, maxValue);
        case EnumChoices::NORMAL:
            return EnumContext::STAR == t_Context ? MAX_NORMAL_STARS : MAX_NORMAL_KEYS;

    }
}

Machine::Machine(MenuData t_menuData)
{
    srand(time(nullptr));

    for (int i = 0; i < t_menuData.numCards; ++i)
    {
        //Criar novo cartao inicializado tudo a zero para evitar garbage nums.
        Card t_Card = {0};

        if(t_menuData.generateMode == MANUAL) {
            printf("----- Apostando no (%i) Cartão -----\n", i + 1);
        }

        //Inserir estrelas
        InsertContext(EnumContext::STAR, t_Card.stars, t_menuData);

        // Inserir numeros
        InsertContext(EnumContext::KEY, t_Card.keys, t_menuData);

        // Inserir cartão
        InsertCard(t_Card, i);
    }

    for (int i = 0; i < t_menuData.numCards; ++i) {

        printf("\n\n----- Cartão (%i) -----", i + 1);

        std::cout << "\n Estrelas: ";
        std::cout << PrintArray(data[i].stars);

        std::cout << "\n Chave: ";
        std::cout << PrintArray(data[i].keys) << std::endl;

    }
}

template<size_t N>
void Machine::InsertContext(const EnumContext& t_Context, std::array<int, N> &t_Data, const MenuData &t_MenuData)
{
    const int minValue = EnumContext::KEY == t_Context ? MIN_VALUE_KEYS : MIN_VALUE_STARS;
    const int maxValue = EnumContext::KEY == t_Context ? MAX_VALUE_KEYS : MAX_VALUE_STARS;

    const int numContext = GetNumContext(t_Context, t_MenuData.mode);

    for (int index = 0; index < numContext; index++)
    {
        switch (t_MenuData.generateMode)
        {
            case EnumGenerateMode::AUTO:
            {
                //Generate int until not exists in stars or keys.
                int t_RandomInt;

                do {
                    t_RandomInt = GenerateInt(minValue, maxValue);

                } while(std::find(t_Data.begin(), t_Data.end(), t_RandomInt) != t_Data.end());

                t_Data[index] = t_RandomInt;

                break;
            }
            case EnumGenerateMode::MANUAL:
                AskInsertContext(t_Data, index, t_Context, minValue, maxValue);
                break;
        }

    }

}

int Machine::AskNumberBetween(const EnumContext& t_Context, int t_Min, int t_Max)
{
    char buffer[200];
    sprintf(buffer, "Quantidade de %ss a inserir entre %i e %i: ", STR_CONTEXT(t_Context), t_Min, t_Max);

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
    sprintf(buffer, "Insira %iº %s: " , t_Index + 1, STR_CONTEXT(t_Context));

    Machine::ParseInput(buffer, [&](int input) {

        // verificar se esta entre os limites.
        if(input > t_Max || input < t_Min)
        {
            printf("Insira %s entre %i e %i\n", STR_CONTEXT(t_Context), t_Min, t_Max);
            return false;
        }

        // verificar se já existe no array stars
        if(std::find(t_Data.begin(), t_Data.end(), input) != t_Data.end())
        {
            printf("%s já existe!, tente novamente.\n", STR_CONTEXT(t_Context));
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
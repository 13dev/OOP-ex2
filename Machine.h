//
// Created by Leonardo Oliveira on 29/04/2020.
//
#pragma once

#include <array>
#include "Menu.h"

#define MAX_CARDS 5

#define MAX_STARS 9
#define MIN_STARS 2

#define MIN_KEYS 5
#define MAX_KEYS 11

#define MAX_VALUE_STARS 9
#define MIN_VALUE_STARS 1

#define MAX_VALUE_KEYS 50
#define MIN_VALUE_KEYS 1

//Macro para GenerateMode "Normal"
#define MAX_NORMAL_KEYS 5
#define MAX_NORMAL_STARS 2

#define STR_CONTEXT(context) (context == EnumContext::KEY ? "numero" : "estrela")

typedef std::function<bool(float)> ValidateInputCallback;

typedef enum {
    KEY,
    STAR
} EnumContext;

// Criar um tipo de dados para cada boletim.
typedef struct {
    std::array<int, MAX_KEYS> keys;
    std::array<int, MAX_STARS> stars;
} Card;

class Machine {

public:
    //Constructor recebe um tipo de dados MenuData.
    Machine(MenuData t_menuData);

private:

    //Guardar informação geral do tipo Card
    std::array<Card, MAX_CARDS> data;

    //Gerar int num especifico range.
    static int GenerateInt(int, int);

    //Inserir cartão.
    Card InsertCard(Card&, int);

    // uso de template para gerar automaticamente uma função compativel com N size.
    template<size_t N>
    void AskInsertContext(std::array<int, N> &t_Data, int t_Index, const EnumContext& t_Context, int t_Min, int t_Max);

    //Perguntar utilizador um numero entre min-max com contexto como "chave" ou "estrela".
    int AskNumberBetween(const EnumContext& t_Context, int t_Min, int t_Max);

    //Inserir estrelas baseado no generateMode.
    void InsertStars(Card& t_Card, int t_NumStars, const EnumGenerateMode &t_GenerateMode);

    //Inserir chaves baseado no generateMode.
    void InsertKeys(Card& t_Card, int t_NumKeys, const EnumGenerateMode &t_GenerateMode);

    //Mostrar um array em forma de string.
    template<size_t N>
    std::string PrintArray(const std::array<int, N> &t_Data);

    // Validate input, pedir enquanto valor não for valido.
    static int ParseInput(const std::string& t_Identifier, const ValidateInputCallback& t_Callback);
};

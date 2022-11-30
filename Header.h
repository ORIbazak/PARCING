#pragma once
#include <iostream>
#include <vector>
#include <string>
using std::cout;
using std::endl;
using std::vector;
using std::string;
//enums to label the chars in the equation
enum op_t {
    num,
    plus,
    minus,
    multiply,
    divide,
    par_open,
    par_close
};
enum token_type {
    operator_type = 0,
    int_type = 1, float_type,
};
struct token {
    op_t op_type;
    token_type t_type;
    int inte;
};

//side function, tokenizes the valid equtaion and labels it
std::vector<token> tokenize(const std::string& str);

//calculating functions
std::vector<token> Solve(const std::vector<token>& exp);

std::vector<token> CalcKefekHiluk(const std::vector<token>& exp);

token CalcPlusMinus(const std::vector<token>& exp);

//entry function, check if equation is valid
bool checkvalid(string& exp);

//side function to help determine whether the equation is valid
bool sign(const char& c);
bool ispar(const char& c);
bool valid(const char& c);







#include <iostream>
#include "Lexer.h"

std::vector<Token> Lexer::tokenize()
{
    std::vector<Token> vec;
    while (has_more_token()) {
        vec.push_back(next_token());
    }
    return vec;
}

Token Lexer::next_token()
{
    Token tok;

    // the default token is the ENDTOK
    tok.type = ENDTOK;
    tok.value = "";

    size_t last_pos = cur_pos;
    if (has_more_token()) {
        while (cur_pos < input_str.length() &&
               separators.find(input_str[cur_pos]) == separators.end() &&
               input_str[cur_pos] != ',')
            cur_pos++;
        tok.type  = IDENT;
        tok.value = input_str.substr(last_pos, cur_pos-last_pos);
    }
    return tok;
}

void Lexer::set_input(std::string str)
{
    cur_pos   = 0;
    input_str = str;
}

bool Lexer::has_more_token()
{
    // advance cursor to the next non-separator character or to end of string
    while (cur_pos < input_str.length() && separators.find(input_str[cur_pos]) != separators.end())
        cur_pos++;

    return (cur_pos < input_str.length());
}



//Lexical Analyzer
#include <iostream>
#ifndef _LEXER_H
#define _LEXER_H

#include <set>
#include <string>
#include <vector>

enum token_types_t
{
    IDENT,  // a sequence of characters with spaces
    ENDTOK  // end of string/file, no more token
};

struct Token
{
    token_types_t type;
    std::string value;
    // constructor for Token
    Token(token_types_t tt=ENDTOK, std::string val="") : type(tt), value(val) {}
};

/**
 * -----------------------------------------------------------------------------
 * the Lexer class:
 * - take a string to be scanned
 * - scan for tokens and return one at a time
 * -----------------------------------------------------------------------------
 */
class Lexer
{
    public:
    Lexer(std::string str="") : cur_pos(0), input_str(str)
    {
        separators.insert(' ');
        separators.insert('\t');
        separators.insert('\r');
        separators.insert('\n') ;
    }

    // a couple of modifiers
    void set_input(std::string); // set a new input,
 // scan and return the next token
    // cur_pos then points to one position right past the token
    Token next_token();

    std::vector<Token> tokenize();

    // are there more token(s)? move the cursor to the next non-separator char
    bool has_more_token();

    private:
    size_t      cur_pos;       // current position in the input string
    std::string input_str;     // the input string to be scanned
    std::set<char> separators; // set of characters that separate tokens
};

#endif
                                                            
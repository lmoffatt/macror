#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include <istream>
#include <map>

namespace Markov_Console
{

bool isNumberChar(char ch);
bool isNameChar(char ch);
bool isPathChar(char ch);


class Token
{
public:
    Token();

    enum Value {
        IDENTIFIER,
        STRING,
        NUMBER,

        EOL='\n',
        PLUS='+',
        MINUS='-',
        MUL='*',
        DIV='/',
        EXPONENT='^',

        DOT='.',
        COLON=':',
        COMMA=',',
        SEMICOLON=';',
        ASSIGN='=',

        LP='(',
        RP=')',
        LSB='[',
        RSB=']',

        NOT='~',
        AND='&',
        OR='|',
        LSS='<',
        GTR='>',

        LEQ,// <=
        EQ, //==
        NEQ, //~=
        GEQ, // >=

        WHILE, //while
        DO,  //do
        IF, //if
        THEN, // then
        BEGIN, //begin
        END, // end
        ELSE, // else
        SWITCH, //switch
        CASE,   // case
        INVALID
    };



    std::string get_tokenString()const;

    std::istream& get(std::istream& stream);

    const std::string& Name()const;

    double Number()const;

    const std::string& Path()const;

    Value get_token()const;

    Value toKeyword(std::string identifier)const;

private:
    Value curr_tok;
    double number_value;
    std::string identifier_value;
    std::string path_value;
    std::string emptyString_;

    std::map<std::string,Value> keywords_;
};

std::istream& operator>>(std::istream& stream,Token& token);
}

#endif // TOKEN_H

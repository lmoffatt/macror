#include "Markov_Console/Token.h"


namespace Markov_Console
{

bool isNumberChar(char ch)
{
    const std::string NumberChar="0123456789.eE-+";
    return NumberChar.find_first_of(ch)!=std::string::npos;
}


bool isNameChar(char ch)
{
    const std::string NameChar="abcdefghijklmnopqrstuvwxyz"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ" "1234567890_"; return
            NameChar.find_first_of(ch)!=std::string::npos;

}

std::istream& operator>>(std::istream& stream,Token& token)
{
    return token.get(stream);
}

Token::Token():
    curr_tok(END),
    number_value(0),
    identifier_value(""),
    path_value(""),
    emptyString_(){}


const std::string& Token::Name()const{
    switch(get_token())
    {
    case IDENTIFIER:
        return identifier_value;
    case STRING:
        return path_value;
    default:
        return emptyString_;

    }
}

std::string Token::get_tokenString()const
{
    switch (get_token())
    {
    case IDENTIFIER:
        return identifier_value;
    case STRING:
        return path_value;
    default:
        std::string result;
        result.push_back(get_token());
        return result;

    }
}


double Token::Number()const{return number_value;}
const std::string& Token::Path()const{return Name();}
Token::Value Token::get_token()const{return curr_tok;}




std::istream& Token::get(std::istream& stream)
{
    char ch;

    do {	// skip whitespace except '\en'
        if(!stream.get(ch))
        {
            curr_tok = END;
            return stream;
        }
    } while (isspace(ch));

    switch (ch) {
    case '\n':
        curr_tok=EOL;
        return stream;
    case '+':
    case '-':
    case '*':
    case '/':
    case '^':

    case ':':
    case '.':
    case ';':

    case '(':
    case ')':
    case '[':
    case ']':
    case '&':
    case '|':
        curr_tok=Value(ch);
        return stream;

    case '=':
        stream.get(ch);
        if (ch=='=')
        {
            curr_tok=EQ;
            return stream;
        }
        else
        {
            stream.putback(ch);
            curr_tok=ASSIGN;
            return stream;
        }
    case '~':
        stream.get(ch);
        if (ch=='=')
        {
            curr_tok=NEQ;
            return stream;
        }
        else
        {
            stream.putback(ch);
            curr_tok=NOT;
            return stream;
        }
    case '<':
        stream.get(ch);
        if (ch=='=')
        {
            curr_tok=LEQ;
            return stream;
        }
        else
        {
            stream.putback(ch);
            curr_tok=LSS;
            return stream;
        }
    case '>':
        stream.get(ch);
        if (ch=='=')
        {
            curr_tok=GEQ;
            return stream;
        }
        else
        {
            stream.putback(ch);
            curr_tok=GTR;
            return stream;
        }

    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
        stream.putback(ch);
        stream >> number_value;
        curr_tok=NUMBER;
        return stream;

    case '"':
        path_value.clear();
        while (stream.get(ch)&& (ch!='"'))
            path_value.push_back(ch);
        if (ch!='"')
        {
            //error("missing `""` ");
            curr_tok=STRING;
            stream.setstate(stream.rdstate() | std::ios_base::failbit);
            return stream;
        }
        else
            curr_tok=STRING;
        return stream;

    default:			// NAME, NAME=, or error
        if (isalpha(ch))
        {
            identifier_value = ch;
            while (stream.get(ch) && isNameChar(ch))
                identifier_value.push_back(ch);
            if (!isNameChar(ch))
                stream.putback(ch);

            curr_tok=toKeyword(identifier_value);
            stream.clear();
            return stream;
        }
        //error("bad token");
        curr_tok=INVALID;
        stream.setstate(stream.rdstate() | std::ios_base::failbit);
        return stream;

    }
}
Token::Value Token::toKeyword(std::string identifier) const
{

    if(identifier=="do")
    {
        return DO;
    }
    else if(identifier=="then")
    {
        return THEN;
    }
    else if(identifier=="while")
    {
        return WHILE;
    }
    else if(identifier=="if")
    {
        return IF;
    }
    else if(identifier=="else")
    {
        return ELSE;
    }
    else if(identifier=="begin")
    {
        return BEGIN;
    }
    else if(identifier=="end")
    {
        return END;
    }
    else if(identifier=="switch")
    {
        return SWITCH;
    }
    else if(identifier=="case")
    {
        return CASE;
    }

    else return IDENTIFIER;

}
}

#pragma once
#include "commands.h"
#include <string>
#include <cwctype>

namespace utl
{
    long long error_last_pos = 0;
    std::string error_where = "";

    void return_error(error type)
    {
        std::cout<<"error type:"<<type<<" in "<<error_where<<" at position "<<error_last_pos<<std::endl;
        exit(type);
    }

    command find_command(std::string sentence)
    {
        if(sentence.find("let ") != std::string::npos)
        {
            return let;
        }
        if(sentence.find("set ") != std::string::npos)
        {
            return set;
        }
        if(sentence.find("print ") != std::string::npos)
        {
            return print;
        }
        if(sentence.find("if ") != std::string::npos)
        {
            return condif;
        }
        if(sentence.find("while ") != std::string::npos)
        {
            return conwhile;
        }

        return_error(inv_command);
        return noop;
    }

    std::string remove_spaces(std::string sentence)
    {
        std::string next = "";
        for(int i=0;i<sentence.size();i++) // add characters to 'next' only if they are not ' '
        {
            if(sentence[i] != ' ')
            {
                next += sentence[i];
            }
        }
        return next;
    }

    std::string remove_sentence_level(std::string lev_sentence)
    {
        int h = 0;
        while(lev_sentence[h] == ' ' && h < lev_sentence.size())
        {
            h++;
        }
        return lev_sentence.substr( h, lev_sentence.size() );
    }

    std::string get_argumens(std::string sentence) // unfinished DO NOT USE
    {
        int h = 0;
        while(sentence[h] != ' ')
        {
            h++;
        }
        sentence = sentence.substr(h + 1,sentence.size());

        sentence = utl::remove_spaces(sentence);

        if(h < 1)
        {
            utl::return_error(inv_command);
        }

        return sentence; // h + 1 because h is a ' ' character
    }

    int get_sentence_level(std::string lev_sentence)
    {
        int h = 0;
        while(lev_sentence[h] == ' ' && h < lev_sentence.size())
        {
            h++;
        }
        return h;
    }

    std::string find_first(std::string sentence)
    {
        int h = 0;
        while(sentence[h] != ' ')
        {
            h++;
        }
        return sentence.substr( 0, h );
    }

    std::string find_rest(std::string sentence)
    {
        int h = 0;
        while(sentence[h] != ' ')
        {
            h++;
        }
        return sentence.substr( h+1, sentence.size() );
    }

}

#pragma once
#include <stack>
#include "utl.h"
#include <map>
#include "let.h"

struct func
{
    int longnes;
    std::string *content;
    std::string name;
    std::stack<int> callbacks;
    func(int totalsize)
    {
        longnes = totalsize;
        content = new std::string[longnes];
    }

    ~func()
    {
        delete[] content;
    }
};

struct var
{
    char type;
    union
    {
        bool b;
        char c;
        double f;
        long long l;
        var* p;
    };
};

class Mem_block //testing mode
{
public:
    std::map<std::string, int> variables;
    var *storage;
    int total_size = 1;
    int level = 0;

    Mem_block(const func &source,int mem_level)
    {
        level = mem_level;

        utl::error_where = "variable allocation in function " + source.name;

        for(int i=0;i<source.longnes;i++) //finds all occurrences of command let in that level
        {
            utl::error_last_pos = i;
            if(utl::find_command(source.content[i]) == let && utl::get_sentence_level( source.content[i] ) == level )
            {
                std::string name = let_command::find_variable_name( utl::remove_sentence_level( source.content[i] ) );
                if(variables[name] != 0)
                {
                    utl::return_error(name_def_pre);
                }
                variables[name] = total_size;
                total_size++;
            }

            storage = new var[total_size];

        }
    }

    ~Mem_block()
    {

    }
};




#pragma once
#include "utl.h"

namespace let_command
{
    std::string find_variable_name(std::string sentence)
    {
        std::string arg = utl::get_argumens(sentence);
        std::string name;
        if(isalpha(arg[0]))
        {
            int h = 0;
            while(isalnum(arg[h]) && h < arg.size())
            {
                h++;
            }

            name = arg.substr(0,h);

            if(h < arg.size()) // there is something after the actual name
            {
                utl::return_error(inv_name);
            }
        }
        else
        {
            utl::return_error(inv_name);
        }

        return name;
    }
}

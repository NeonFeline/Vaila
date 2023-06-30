#pragma once
#include "var_cha.h"

namespace cond
{
    void skip_higher_levels(const func &source, std::list<Mem_block> &memory, int &i, int &lev)
    {
        while(utl::get_sentence_level(source.content[i]) >= lev)
        {
            i++;
        }
        i--;
    }

    bool check_sentence_and_skip_if_needed(bool save_callback,func &source, std::string sentence, int &lev, int &i, std::list<Mem_block> &memory)
    {
        sentence = utl::get_argumens(sentence);
        sentence = utl::remove_spaces(sentence);
        var check = varia::evaluate_expression(sentence,memory);

        if(check.type != 'b')
        {
            utl::return_error(inv_data_type);
        }

        if(check.b == true)
        {
            if(save_callback == true)
            {
                source.callbacks.push(i);
            }
            else
            {
                source.callbacks.push(-1);
            }
        }
        else
        {

            i++;
            lev++;
            skip_higher_levels(source, memory, i, lev);
            lev--;
        }
    }


}

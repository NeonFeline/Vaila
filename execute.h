#pragma once
#include "if.h"

namespace exe
{
    var execute(func &source, std::list<Mem_block> &memory)
    {
        int lastlevel = 0;
        for(int i = 0; i < source.longnes; i++)
        {
            //separate sentence level
            int lev = utl::get_sentence_level(source.content[i]);
            std::string sentence = utl::remove_sentence_level(source.content[i]);

            command task = utl::find_command(sentence);

            utl::error_last_pos = i;
            utl::error_where = "function execution in "+source.name;
            if(lev < lastlevel)
            {
                if(source.callbacks.top() != -1)
                {

                    i = source.callbacks.top();
                    lastlevel = lev;
                    i--; //becouse for loop will add 1 to it
                    source.callbacks.pop();
                    continue;
                }
                source.callbacks.pop();


            }

            //std::cout<<source.content[i]<<std::endl;

            if(task == set)
            {
                varia::change_variable(sentence, memory);
            }
            else if(task == print)
            {
                varia::print_value(sentence, memory);
            }
            else if(task == condif)
            {
                cond::check_sentence_and_skip_if_needed(false, source, sentence, lev, i, memory);
            }
            else if(task == conwhile)
            {
                cond::check_sentence_and_skip_if_needed(true, source, sentence, lev, i, memory);
            }



            lastlevel = lev;
        }
    }
}

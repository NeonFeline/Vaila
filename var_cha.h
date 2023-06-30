#pragma once
#include <list>
#include <algorithm>
#include "let.h"

namespace varia
{

    var get_constant_value(std::string expression)
    {
        if( expression.size() < 2 )
        {
            utl::return_error(inv_constant);
        }

        if(isalpha(expression[1]))
        {
            var con;
            con.c = expression[1];
            con.type = 'c';
            return con;
        }
        else
        {
            var con;
            if(expression.find('.') == std::string::npos)
            {
                con.l = std::stoi(expression.substr(1,expression.size()));
                con.type = 'l';
                return con;
            }
            else
            {
                con.f = std::stod(expression.substr(1,expression.size()));
                con.type = 'f';
                return con;
            }
        }
        utl::return_error(inv_constant);
    }

    var* get_var_pointer(std::string expression, std::list<Mem_block> &memory)
    {
        for(std::list<Mem_block>::iterator it = memory.begin(); it != memory.end(); ++it)
        {
            if(it->variables[expression] != 0)
            {
                   return &it->storage[it->variables[expression]];
            }
        }
    }


    var get_value(std::string expression, std::list<Mem_block> &memory)
    {
        if(expression[0] == '@')
        {
            return get_constant_value(expression);
        }

        if(expression[0] == '$')
        {
            var point;
            point.type = 'p';
            point.p = get_var_pointer(expression,memory);
            return point;
        }

        //return a variable value (or a pointer i don't know, it is unsafe for now)
        return *get_var_pointer(expression,memory);
    }



    var evaluate_expression(std::string expression, std::list<Mem_block> &memory) //curently only operations on two arguments are allowed
    {

        int h = 0;
        while(isalnum(expression[h]) || expression[h] == '@' || expression[h] == '$' || expression[h] == '-' || expression[h] == '.')
        {
            h++;
        }

        if(expression.size() == h)
        {
            return get_value(expression,memory);
        }

        var first = get_value( expression.substr( 0, h ), memory );

        std::string operand = "";

        while(!(isalnum(expression[h]) || expression[h] == '@' || expression[h] == '$' || expression[h] == '-' || expression[h] == '.'))
        {
            operand += expression[h];
            h++;
        }

        var second = get_value( expression.substr( (h), expression.size() ), memory );
        var ans;


        if(operand == "+")
        {
            if(first.type == 'l' && second.type == 'l')
            {
                ans.type = 'l';
                ans.l = first.l + second.l;
                return ans;
            }
            else if(first.type == 'f' && second.type == 'f')
            {
                ans.type = 'f';
                ans.f = first.f + second.f;
                return ans;
            }
            else if(first.type == 'p' && second.type == 'p')
            {
                ans.type = 'p';
                ans.p = first.p + second.l;
                return ans;
            }
            else
            {
                utl::error_where = "value expression in data type";
                utl::return_error(inv_data_type);
            }
        }
        else if(operand == "-")
        {
            if(first.type == 'l' && second.type == 'l')
            {
                ans.type = 'l';
                ans.l = first.l - second.l;
                return ans;
            }
            else if(first.type == 'f' && second.type == 'f')
            {
                ans.type = 'f';
                ans.f = first.f - second.f;
                return ans;
            }
            else if(first.type == 'p' && second.type == 'p')
            {
                ans.type = 'p';
                ans.p = first.p - second.l;
                return ans;
            }
            else
            {
                utl::error_where = "value expression in data type";
                utl::return_error(inv_data_type);
            }
        }
        else if(operand == "*")
        {
            if(first.type == 'l' && second.type == 'l')
            {
                ans.type = 'l';
                ans.l = first.l * second.l;
                return ans;
            }
            else if(first.type == 'f' && second.type == 'f')
            {
                ans.type = 'f';
                ans.f = first.f * second.f;
                return ans;
            }
            else
            {
                utl::error_where = "value expression in data type";
                utl::return_error(inv_data_type);
            }
        }
        else if(operand == "/")
        {
            if(first.type == 'l' && second.type == 'l')
            {
                ans.type = 'l';
                ans.l = first.l / second.l;
                return ans;
            }
            else if(first.type == 'f' && second.type == 'f')
            {
                ans.type = 'f';
                ans.f = first.f / second.f;
                return ans;
            }
            else
            {
                utl::error_where = "value expression in data type";
                utl::return_error(inv_data_type);
            }
        }
        else if(operand == "%")
        {
            if(first.type == 'l' && second.type == 'l')
            {
                ans.type = 'l';
                ans.l = first.l % second.l;
                return ans;
            }
            else if(first.type == 'f' && second.type == 'f')
            {
                utl::error_where = "value expression in data type";
                utl::return_error(inv_data_type);
            }
            else
            {
                utl::error_where = "value expression in data type";
                utl::return_error(inv_data_type);
            }
        }
        else if(operand == "&") //TO DO
        {

        }
        else if(operand == "^") //TO DO
        {

        }
        else if(operand == "|") //TO DO
        {

        }
        else if(operand == "<<") //TO DO
        {

        }
        else if(operand == ">>") //TO DO
        {

        }
        else if(operand == "<") //TO DO
        {
            if(first.type == 'l' && second.type == 'l')
            {
                ans.type = 'b';
                if(first.f < second.f)
                {
                    ans.b = true;
                }
                else
                {
                    ans.b = false;
                }
                return ans;
            }
            else if(first.type == 'f' && second.type == 'f')
            {
                ans.type = 'b';
                if(first.f < second.f)
                {
                    ans.b = true;
                }
                else
                {
                    ans.b = false;
                }
                return ans;
            }
            else if(first.type == 'b' && second.type == 'b')
            {
                utl::return_error(inv_data_type);
            }
            else if(first.type == 'p' && second.type == 'p')
            {
                ans.type = 'b';
                if(first.p < second.p)
                {
                    ans.b = true;
                }
                else
                {
                    ans.b = false;
                }
                return ans;
            }
            else
            {
                utl::error_where = "value expression in data type";
                utl::return_error(inv_data_type);
            }
        }
        else if(operand == ">")
        {
            if(first.type == 'l' && second.type == 'l')
            {
                ans.type = 'b';
                if(first.f > second.f)
                {
                    ans.b = true;
                }
                else
                {
                    ans.b = false;
                }
                return ans;
            }
            else if(first.type == 'f' && second.type == 'f')
            {
                ans.type = 'b';
                if(first.f > second.f)
                {
                    ans.b = true;
                }
                else
                {
                    ans.b = false;
                }
                return ans;
            }
            else if(first.type == 'b' && second.type == 'b')
            {
                utl::return_error(inv_data_type);
            }
            else if(first.type == 'p' && second.type == 'p')
            {
                ans.type = 'b';
                if(first.p > second.p)
                {
                    ans.b = true;
                }
                else
                {
                    ans.b = false;
                }
                return ans;
            }
            else
            {
                utl::error_where = "value expression in data type";
                utl::return_error(inv_data_type);
            }
        }
        else if(operand == "<=")
        {
            if(first.type == 'l' && second.type == 'l')
            {
                ans.type = 'b';
                if(first.f <= second.f)
                {
                    ans.b = true;
                }
                else
                {
                    ans.b = false;
                }
                return ans;
            }
            else if(first.type == 'f' && second.type == 'f')
            {
                ans.type = 'b';
                if(first.f <= second.f)
                {
                    ans.b = true;
                }
                else
                {
                    ans.b = false;
                }
                return ans;
            }
            else if(first.type == 'b' && second.type == 'b')
            {
                utl::return_error(inv_data_type);
            }
            else if(first.type == 'p' && second.type == 'p')
            {
                ans.type = 'b';
                if(first.p <= second.p)
                {
                    ans.b = true;
                }
                else
                {
                    ans.b = false;
                }
                return ans;
            }
            else
            {
                utl::error_where = "value expression in data type";
                utl::return_error(inv_data_type);
            }
        }
        else if(operand == ">=")
        {
            if(first.type == 'l' && second.type == 'l')
            {
                ans.type = 'b';
                if(first.f >= second.f)
                {
                    ans.b = true;
                }
                else
                {
                    ans.b = false;
                }
                return ans;
            }
            else if(first.type == 'f' && second.type == 'f')
            {
                ans.type = 'b';
                if(first.f >= second.f)
                {
                    ans.b = true;
                }
                else
                {
                    ans.b = false;
                }
                return ans;
            }
            else if(first.type == 'b' && second.type == 'b')
            {
                utl::return_error(inv_data_type);
            }
            else if(first.type == 'p' && second.type == 'p')
            {
                ans.type = 'b';
                if(first.p >= second.p)
                {
                    ans.b = true;
                }
                else
                {
                    ans.b = false;
                }
                return ans;
            }
            else
            {
                utl::error_where = "value expression in data type";
                utl::return_error(inv_data_type);
            }
        }
        else if(operand == "==")
        {
            if(first.type == 'l' && second.type == 'l')
            {
                ans.type = 'b';
                if(first.l == second.l)
                {
                    ans.b = true;
                }
                else
                {
                    ans.b = false;
                }
                return ans;
            }
            else if(first.type == 'f' && second.type == 'f')
            {
                ans.type = 'b';
                if(first.f == second.f)
                {
                    ans.b = true;
                }
                else
                {
                    ans.b = false;
                }
                return ans;
            }
            else if(first.type == 'b' && second.type == 'b')
            {
                ans.type = 'b';
                if(first.b == second.b)
                {
                    ans.b = true;
                }
                else
                {
                    ans.b = false;
                }
                return ans;
            }
            else if(first.type == 'p' && second.type == 'p')
            {
                ans.type = 'b';
                if(first.p == second.p)
                {
                    ans.b = true;
                }
                else
                {
                    ans.b = false;
                }
                return ans;
            }
            else
            {
                utl::error_where = "value expression in data type";
                utl::return_error(inv_data_type);
            }
        }
        else if(operand == "!=")
        {
            if(first.type == 'l' && second.type == 'l')
            {
                ans.type = 'b';
                if(first.l != second.l)
                {
                    ans.b = true;
                }
                else
                {
                    ans.b = false;
                }
                return ans;
            }
            else if(first.type == 'f' && second.type == 'f')
            {
                ans.type = 'b';
                if(first.f != second.f)
                {
                    ans.b = true;
                }
                else
                {
                    ans.b = false;
                }
                return ans;
            }
            else if(first.type == 'b' && second.type == 'b')
            {
                ans.type = 'b';
                if(first.b != second.b)
                {
                    ans.b = true;
                }
                else
                {
                    ans.b = false;
                }
                return ans;
            }
            else if(first.type == 'p' && second.type == 'p')
            {
                ans.type = 'b';
                if(first.p != second.p)
                {
                    ans.b = true;
                }
                else
                {
                    ans.b = false;
                }
                return ans;
            }
            else
            {
                utl::error_where = "value expression in data type";
                utl::return_error(inv_data_type);
            }
        }







    }

    void change_variable(std::string sentence, std::list<Mem_block> &memory)
    {
        sentence = utl::find_rest(sentence);

        std::string dest = utl::find_first(sentence);

        sentence = utl::get_argumens(sentence);

        std::string value = sentence.substr(1,sentence.size());

        for(std::list<Mem_block>::iterator it = memory.begin(); it != memory.end(); ++it)
        {

            if(it->variables[dest] != 0)
            {

                it->storage[it->variables[dest]] = evaluate_expression(value,memory);
                return;
            }

        }

        utl::return_error(inv_name);
    }

    void print_value(std::string sentence, std::list<Mem_block> &memory)
    {
        sentence = utl::get_argumens(sentence);

        std::string value = sentence.substr(0,sentence.size());

        var what = evaluate_expression(value,memory);

        if(what.type == 'c')
        {
            std::cout<<what.c;
        }
        else if(what.type == 'l')
        {
            std::cout<<what.l;
        }
        else if(what.type == 'f')
        {
            std::cout<<what.f;
        }
        else if(what.type == 'p')
        {
            std::cout<<what.p;
        }
        else if(what.type == 'b')
        {
            if(what.b == true)
            {
                std::cout<<"True";
            }
            else if(what.b == false)
            {
                std::cout<<"False";
            }
            else
            {
                utl::return_error(inv_data_type);
            }
        }

        std::cout<<std::endl;

    }

}

#pragma once

enum command
{
    noop, let, set, print, condif, conwhile, close
};

enum error
{
    inv_name = 1, name_def_pre, inv_command, inv_constant, inv_pointer, inv_data_type
};

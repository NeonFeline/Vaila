#include <iostream>
#include "sub_pro.h"
#include "commands.h"
#include "execute.h"
#include <fstream>

using namespace std;

int main()
{

    fstream file;
    file.open("pro.vai",ios::in);
    int how = -1;
    while(!file.eof())
    {
        how++;
        file.ignore(256,'\n');
    }

    func fun(how);
    file.seekg (0, file.beg);

    int i = 0;

    while(i < how)
    {
        getline(file,fun.content[i]);
        i++;
    }



    fun.name = "test";

    list<Mem_block> m1;
    m1.push_front(Mem_block(fun,0));

    exe::execute(fun,m1);

    return 0;
}

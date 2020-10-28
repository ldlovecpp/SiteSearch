#pragma once
#include<string>
#include<fstream>
using namespace std;
class Util
{
public:
static bool Read(const string& file_path,string& html)
{
   ifstream ifs(file_path);
   if(!ifs.is_open())
     return false;
   string tmp;
   while(getline(ifs,tmp))
   {
    html+=tmp;
    tmp.clear();
   }
   ifs.close();
   return true;
}
};

#pragma once
#include<vector>
#include<string>
#include<fstream>
#include<boost/algorithm/string.hpp>
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
static void Splite(const string& input,const string& delimit,vector<string>& output)
{
   boost::split(output,input,boost::is_any_of(delimit),boost::token_compress_off);
}
};

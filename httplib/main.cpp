#include<iostream>
#include<fstream>
#include<jsoncpp/json/json.h>
using namespace std;
int main()
{
  Json::Value root;
  Json::Reader rd;
  ifstream in("./t.json",ios::binary);
  if(rd.parse(in,root))
  {
   string name=root["age"].asString();
   cout << name <<endl;
  }
}

#include"../httplib/httplib.h"
#include<iostream>
#include<vector>
using namespace std;
int main()
{
  using namespace httplib;
  Server server;
  server.Get("/server",[](const Request& req,Response& resp)
   {
      (void)req;
      resp.set_content("hello","/text/html");
   });
  server.listen("0.0.0.0",10001);
  return 0;
}

#include"../httplib/httplib.h"
#include"../searcher/search.h"
#include<iostream>
#include<vector>
using namespace std;
int main()
{
  using namespace httplib;
  searcher::Searcher searcher;
  searcher.init("../data/tmp/raw_input");
  Server server;
  server.Get("/searcher",[&searcher](const Request& req,Response& resp)
  {
   if(!req.has_param("query"))
   {
    resp.set_content("您发送的请求格式有误","text/plain; charset=utf-8");
    return;
   }
   string query= req.get_param_value("query");
   string results;
   searcher.search(query,results);
   resp.set_content(results,"application/jsoncpp; charset=utf-8");
  });
  server.set_base_dir("./wwwroot");
  server.listen("0.0.0.0",8888);
  return 0;
}

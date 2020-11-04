#include"./search.h"
int main()
{
  searcher::Searcher sh;
  sh.init("../data/tmp/raw_input");
  while(true)
  {
    std::cout<<"searcher: " <<std::flush;
    string query;
    std::cin>>query;
    if(!cin.good())
    {
      cout<<"good"<<endl;
      break;
    }
    string results;
    sh.search(query,results);
    cout << results <<endl;
  }
  return 0;
}

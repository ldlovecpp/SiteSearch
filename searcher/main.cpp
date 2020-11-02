#include"./search.h"
int main()
{
  searcher::Index index;
  bool ret =index.build("../data/tmp/raw_input");
  if(!ret)
  {
    cout << "索引构建失败!!"<<endl;
    return 1;
  }
  auto* inverted_list  = index.Get_Inverted_DocInfo("filesystem");
  for(int i=0;i<(*inverted_list).size();i++)
  {
    cout << (*inverted_list)[i].doc_id <<endl;
    auto* info = index.GetDocInfo((*inverted_list)[i].doc_id);
    cout << info->title <<endl;
    cout << info->url;
    cout << endl;
    cout << info->context <<endl;
  }
  return 0;
}

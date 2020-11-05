#include<iostream>
#include<fstream>
#include<vector>
#include<unordered_map>
#include<string>
#include<boost/filesystem/operations.hpp>
#include<boost/filesystem/path.hpp>
#include"../common/common.h"
using namespace std;
string g_input_path  = "../data/input/";
string g_output_path = "../data/tmp/raw_input";
struct DocInfo
{
  //文件的标题
  string title;
  //文件的url
  string url;
  //文件的正文
  string context;
};
bool parse_title(const string& html,DocInfo& doc_info)
{
   size_t begin = html.find("<title>");
   if(begin==string::npos)
   {
     cout << "标题未找到"<<endl;
     return false;
   }
   size_t end = html.find("</title>");
   if(end==string::npos)
   {
     cout << "标题未找到" <<endl;
     return false;
   }
   begin+=string("<title>").size();
   if(begin>=end)
   {
     cout << "标题格式不合法 "<<endl;
     return false;
   }
   doc_info.title = html.substr(begin,end-begin);
   return true;
}
bool parse_url(const string& file_name,DocInfo& doc_info)
{
  string url_head = "https://www.boost.org/doc/libs/1_53_0/doc/html/";
  string url_tail = file_name.substr(g_input_path.size());
  doc_info.url=url_head+url_tail;
  return true;
}
bool parse_context(const string& html,DocInfo& doc_info)
{
  bool is_context = true;
  for(auto c : html)
  {
   if(is_context)
   {
    if(c=='<')
    {
     is_context = false;
    }
    else 
    {
      if(c=='\n')
      {
        c=' ';
      }
      doc_info.context.push_back(c);
    }
   }
   else 
   {
     if(c=='>')
     {
      is_context=true;
     }
   }
  }
  return true;
}
//解析
//1.读取所有文件内容
//2.解析文件名的标题
//3.解析文件的url
//4.解析文件的正文
bool parser(const string& file_path,DocInfo& doc_info)
{
    //读取内容 
    string html;
    if(!Util::Read(file_path,html))
    {
      cout << "读取文件失败"<<endl;
      return false;
    }
    //解析标题
    if(!parse_title(html,doc_info))
    {
     cout << "解析标题失败" <<endl;
     return false;
    }
    //解析url
    if(!parse_url(file_path,doc_info))
    {
     cout << "解析url 失败"  <<endl;
     return false;
    }
    //解析正文
    if(!parse_context(html,doc_info))
    {
    cout << "解析正文失败" <<endl;
    return false;
    }
    return true;
}
//枚举所有文档的文档名称
bool enum_file(const string& input_path,vector<string>& file_list)
{
   //把boost::filesystem这个命名空间定义个别名(方便使用,因为它实在是太长了)
   namespace fs  = boost::filesystem;
   fs::path root_path(input_path); //绑定搜索的路径
   if(fs::is_empty(input_path))
   {
     return false;
   }
   //使用boost提供的递归遍历迭代器对文件结构进行递归遍历
   //把迭代器的默认构造函数生成的迭代器作为一个哨兵进行使用
   fs::recursive_directory_iterator end_iter;
   for(fs::recursive_directory_iterator iter(root_path);iter!=end_iter;iter++ )
   {
    //不要目录文件
    if(fs::is_directory(*iter))
    {
      continue;
    }
    //如果普通文件不是以.html结尾,不要
    if(iter->path().extension()!=".html")
    {
      continue;
    }
    file_list.push_back(iter->path().string());
   }
   return true;
}
bool WriteOutPutFile(const DocInfo& doc_info,ofstream& ofs)
{
   ofs<<doc_info.title<<'\3'<<doc_info.url<<'\3'<<doc_info.context <<endl;
   return true;
}
int main()
{
  vector<string> file_list;
  if(!enum_file(g_input_path,file_list))
  {
    cout << "枚举文件失败" <<endl;
  }
  ofstream ofs(g_output_path.c_str());
  if(!ofs.is_open())
  {
     cout << "打开out_put文件失败" <<endl;
     return 1;
  }
  for(const auto & file_path : file_list)
  {
    cout << file_path <<endl;
    DocInfo doc_info;
    if(!parser(file_path,doc_info))
    {
      cout << "该文件解析失败" <<endl;
      continue;
    }
    WriteOutPutFile(doc_info,ofs);
  }
  ofs.close();
  return 0;
}

#include<iostream>
#include<algorithm>
#include<fstream>
#include<jsoncpp/json/json.h>
#include<stdint.h>
#include<unordered_map>
#include<vector>
#include<string>
#include"../common/common.h"
#include"../cppjieba/Jieba.hpp"
using namespace std;

//索引模块
//正排索引信息
namespace searcher
{
struct DocInfo{
  int64_t doc_id;
  string title;
  string url;
  string context;
};
//倒排索引信息
struct Weight
{
  int doc_id; //文件id
  int64_t weight; //权重
  string word; //词
};
//整体索引结构
class Index
{
public:
   Index();
   const DocInfo* GetDocInfo(int64_t doc_id);
   const vector<Weight>* Get_Inverted_DocInfo(const string& key);
   bool build(const string& input_path);
   void CurtWord(const string& input,vector<string>& output);
private:
   DocInfo* Build_Doc_Info(string& line);
   void Build_Inverted_DocInfo(const DocInfo& doc_info);
private:
  //正排索引
  //数组下表对应相应的doc_id
  vector<DocInfo>forword_index;
  //倒排索引
  map<string,vector<Weight>>inverted_index;
  //分词
  cppjieba::Jieba jieba;
};


//搜索模块
class Searcher
{
public:
   bool search(const string& req,string& result);
   bool init(const string& input_path);
   string GenrateDesc(string content,string& word);
private:
   Index index;
};
}

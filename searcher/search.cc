#include"./search.h"
namespace searcher
{
 //字典路径
 const char* const DICT_PATH = "../dict/jieba.dict.utf8";
 const char* const HMM_PATH = "../dict/hmm_model.utf8";
 const char* const USER_DICT_PATH = "../dict/user.dict.utf8";
 const char* const IDF_PATH = "../dict/idf.utf8";
 const char* const STOP_WORD_PATH = "../dict/stop_words.utf8";   
 //构造Jieba类,对输入的信息进行分词
 Index::Index()
    :jieba(DICT_PATH,
        HMM_PATH,
        USER_DICT_PATH,
        IDF_PATH,
        STOP_WORD_PATH)
  {}
  //通过正排索引返回doc_info信息 (url,context,title)
  const DocInfo* Index::GetDocInfo(int64_t doc_id)
  {
    if(doc_id<0||doc_id>=forword_index.size())
   {
      return nullptr;
    }
    return &forword_index[doc_id];
  }
  //通过倒排索引
  const vector<Weight>* Index::Get_Inverted_DocInfo(const string& key)
  {
    auto it = inverted_index.find(key);
    if(it==inverted_index.end())
    {
     return nullptr;
    }
   return &it->second;
  }
  bool Index::build(const string& input_path)
  {
     //按行读取raw_input文件
     cout << "开始构建索引" <<endl;
     ifstream file(input_path.c_str());
     if(!file.is_open())
     {
       cout << "打开raw_input文件失败" <<endl;
       return false;
     }
     string line;
     while(getline(file,line))
     {
     DocInfo* doc_info = Build_Doc_Info(line);
     //针对当前的行进行解析,解析成DocInfo的正排索引的形式
     Build_Inverted_DocInfo(*doc_info);
     //依据当前所生成的正排索引模型DocInfo,构建出倒排索引结构
     }
     cout << "构建索引完成" <<endl;
     file.close();
     return true;
  }
  //构建正排索引
  DocInfo* Index::Build_Doc_Info(string& line) 
  {
   vector<string>output;
   Util::Splite(line,"\3",output);
   if(output.size()!=3)
   {
     return nullptr;
   }
   DocInfo doc_info;
   doc_info.doc_id =  forword_index.size();
   doc_info.title= output[0];
   doc_info.url= output[1];
   doc_info.context = output[2];
   forword_index.push_back(std::move(doc_info));
   return &forword_index.back();
  }
  //构建倒排索引
  void Index::Build_Inverted_DocInfo(const DocInfo& doc_info)   
  {
     struct Word_Cnt
     {
       size_t title_cnt;
       size_t context_cnt;
       Word_Cnt()
         :title_cnt(0)
          ,context_cnt(0)
       {}
     };
     unordered_map<string,Word_Cnt>Count;
     //计算标题中各分词结果出现的次数
     vector<string>output; 
     CurtWord(doc_info.title,output);
     for(string tmp : output)
     {
       boost::to_lower(tmp);
       Count[tmp].title_cnt++;
     }
     output.clear();
     //计算正文中各分词结果出现的次数
     CurtWord(doc_info.context,output);
     for(string tmp : output)
     {
       boost::to_lower(tmp);
       Count[tmp].context_cnt++;
     }
     //构建
     unordered_map<string,Word_Cnt>::iterator p = Count.begin();
     while(p!=Count.end())
     {
     Weight weight; 
     weight.doc_id = doc_info.doc_id;
     weight.word = p->first;
     weight.weight = p->second.title_cnt*10+p->second.context_cnt;
     vector<Weight>& inverted_list = inverted_index[p->first;
     inverted_list.push_back(std::move(weight));
     ++p;
     }
  }
  void Index::CurtWord(const string& input,vector<string>&output)
  {
    jieba.Cut(input,output);
  }






  //搜索模块
  void Searcher::init(const string& input_path)
  {
     index.build(input_path);
  }
  bool Searcher::search(const string& req,string& res)
  {
      //分词
      vector<string>tokens;
      index.CurtWord(req,tokens);
      //触发
      vector<Weight>all_token_result;
      for(auto s :  tokens)
      {
        boost::to_lower(s);
        //将每个分词结果在倒排索引中进行搜索
        auto* inverted_list=index.Get_Inverted_DocInfo(s); 
        if(inverted_list==nullptr)
        {
          continue;
        }
        all_token_result.insert(all_token_result.end(),inverted_list->begin(),inverted_list->end());
      }
      //排序
      sort(tokens.begin(),tokens.end(),[](const Weight& w1,const Weight& w2) { return w1.weight>w2.weight;});
      //包装
      Json::Value results;
      for(auto weight : all_token_result) 
      {
        Json::Value result;
        auto* info = index.GetDocInfo(weight.doc_id);
        result["url"] = info->url;
        result["title"] = info->title;
        result["desc"] =GenrateDesc(info->context,weight.word);
        results.append(result);
      }
      Json::FastWriter writer;
      res=writer.write(results);
      return true;
  }
  string Searcher:: GenrateDesc(string& context,string& word)
  {
    int pos = context.find(word);
    if(pos==std::npos)
    {
      if(context.size()<160)
      {
        return context;
      }
      else 
      {
        return context.substr(0,160);
      }
    }
    int begin_pos=0;
    if(pos-60>=0)
    {
      bebe
    }
  }
};

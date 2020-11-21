# SiteSearch  
项目架构:  
1.对离线版本的html文档进行解析，将解析结果整理为一个行本文文件raw_input  
2.读取处理好的行文本文件raw_input,并对其进行分词、权重计算等操作，在内存中构造出正排索引和倒排索引。  
3.搜索模块,主要是以下几个功能:  
<1>分词  
<2>触发  
<3>内容排序  
<4>包装内容(Json格式)  
4.http服务模块  
<1>用httplib库构建一个http接口  
<2>用HTML,CSS,JavaScript写构建网页,与用户进行交互    
![image](show.jpg)



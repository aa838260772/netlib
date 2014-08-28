#include "textquery.h"
#include <sstream>
#include<iostream>
using namespace std;

void textquery::read_file(ifstream &is)
{
    store_file(is);
}

void textquery::store_file(ifstream &is)
{
    string word;
    while(getline(is, word) > 0)
    {
        lines_of_text.push_back(word);
    }//把每行的内容读入vector
    build_map();//将单词和行数写入map
}

string textquery::text_line(line_no line) const
{
    string line_string = lines_of_text[line];
    return line_string;
}

void textquery::build_map()
{
    string word;
    string line;
    for(line_no ix = 0; ix != lines_of_text.size(); ix++)
    {
        line = text_line(ix);
        istringstream sstream(line);
        
        while( sstream >> word)
        {
            word_map[word].insert(ix) ;
        }
    }
}

set<textquery::line_no> textquery::run_query(const string& word) const
{//记住此时要用const迭代器，否则会出现错误,以及返回的这个set类型
    map<string, set<line_no> >::const_iterator it;
/*   for(it = word_map.begin(); it != word_map.end(); it++)
   }
*/
    string s = word;
   // cout << word.size() <<endl;
  //  cout <<word[word.size() - 1] << endl;
   // cout << word[word.size() - 2] << endl;
    s.erase(s.size() - 2, 2);//末尾\n\0,
    it = word_map.find(s);
    if(it != word_map.end())
    {
        return it->second;
    }
    else
{
        return set<line_no>() ;
}
}

void textquery::prin( const string &word)
{
    set<line_no> s = run_query(word);
    cout << word << " occur :" << s.size() << " times" << endl;
    for(set<line_no>::iterator it = s.begin(); it != s.end(); it++)
    {
        cout << "(line" << *it + 1<<") "<< lines_of_text[ *it ] << endl;
    }
}


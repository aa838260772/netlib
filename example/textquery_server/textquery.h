#ifndef _TEXT_QUERY_H_
#define _TEXT_QUERY_H_
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <set>

class textquery
{
 public:
   typedef std::vector<std::string>::size_type line_no;
   void read_file(std::ifstream &);
   std::set<line_no> run_query(const std::string &) const;
   std::string text_line(line_no) const;
   void prin(const std::string &);
 private:
   void store_file(std::ifstream &);
   void build_map();
   std::vector<std::string> lines_of_text;
   std::map< std::string, std::set<line_no> > word_map;
};


#endif /*TEXT_QUERY_H*/ 

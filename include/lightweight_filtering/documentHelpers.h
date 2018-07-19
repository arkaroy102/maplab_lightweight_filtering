#include <rapidjson/document.h>
#include <vector>
#include <sstream>
#include <iostream>
#include <string>

#ifndef DOC_HELPER_
#define DOC_HELPER_

  inline std::vector<std::string> splitString(const std::string& s
      , char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);

    while (std::getline(tokenStream, token, delimiter)) {
      tokens.push_back(token);
    }
    return tokens;
  }
  inline rapidjson::Value::ConstMemberIterator findValueInDoc
      (const rapidjson::Document& doc, std::string val) {

    std::vector<std::string> values = splitString(val, '.');
    rapidjson::Document d;
    d.CopyFrom(doc, d.GetAllocator());

    rapidjson::Value::ConstMemberIterator itr;
    for (auto i = values.begin(); i != values.end(); ++i) {
      const char* key = (*i).c_str();

      itr = d.FindMember(key);
      if (itr->value.GetType() != 3) {
        return d.FindMember(key);
      } else {
        d.CopyFrom(itr->value, d.GetAllocator());
      }
    }
    rapidjson::Value::ConstMemberIterator v;
    return v;
  }
#endif

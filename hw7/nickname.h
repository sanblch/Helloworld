#include <experimental/string_view>
#include <forward_list>
#include <functional>
#include <iostream>
#include <numeric>
#include <string>
#include <map>
#include <vector>

using strview = std::experimental::string_view;

class Node {
  bool m_is_end{false};
  std::string m_str{};

  void split(size_t i) {
    auto str =  static_cast<strview>(m_str).substr(i);
    NodeMap moving_nodes = std::move(nodes);
    nodes.insert(str);
    nodes[str[0]].nodes = std::move(moving_nodes);
    m_str = m_str.substr(0, i);
  }
protected:
  class NodeMap : public std::map<char, Node> {
  public:
    void insert(const strview& str) {
      this->operator[](str[0]).insert(substr(str, 1));
    }
    bool find(const strview& str) {
      if (count(str[0])) {
        return this->operator[](str[0]).find(substr(str, 1));
      }
      return false;
    }
    bool remove(const strview& str) {
      if (count(str[0])) {
        return this->operator[](str[0]).remove(substr(str, 1));
      }
      return false;
    }
    void print(std::ostream& os, const std::string& str) const {
      for (const auto &p : *this)
        p.second.print(os, str + std::string(1, p.first));
    }
    void print_graph(std::ostream& os, const std::string& str, const std::string& mstr, long long links) const {
      long long count = size();
      for (const auto &p : *this) {
        std::string sstr;
        if(-1 != links)
          sstr = str.substr(0, str.size() - 1) + (links > 1 ? "| " : "  ");
        else
          sstr = std::string(str.size() + mstr.size(), ' ');
        p.second.print_graph(os, sstr + std::string(1, p.first), -1 != links ? count-- : -1);
      }
    }
  } nodes;

  static strview substr(const strview& str, size_t index) {
    try {
      return str.size() <= index ? "" : str.substr(index);
    } catch(const std::out_of_range& ex) {
      std::cerr << "Node::substr: impossible out_of_range." << std::endl;
      return "";
    }
  }

public:
  void insert(const strview& str) {
    if(m_str.empty() && nodes.empty() && !m_is_end) {
      m_str = std::string(str);
      m_is_end = true;
      return;
    }
    size_t size = std::min(str.size(), m_str.size());
    size_t i = 0;
    try {
      while (i < size) {
        if (m_str[i] != str[i]) {
          split(i);
          nodes.insert(str.substr(i));
          m_is_end = false;
          return;
        }
        i++;
      }
      if (m_str.size() > str.size()) {
        split(size);
        m_is_end = true;
      } else if (m_str.size() < str.size()) {
        nodes.insert(str.substr(size));
      }
    } catch (const std::out_of_range &ex) {
      std::cerr << "Node::insert: impossible out_of_range." << std::endl;
    }
  }

  bool remove(const strview &str) {
    if (m_str.empty() && str.empty())
      return true;
    if (m_str.size() == str.size()) {
      if (0 == static_cast<strview>(m_str).compare(str) && m_is_end) {
        m_is_end = false;
        return nodes.empty();
      }
    } else if (m_str.size() < str.size()) {
      try {
        if (0 ==
            static_cast<strview>(m_str).compare(str.substr(m_str.size()))) {
          if (nodes.remove(str.substr(m_str.size()))) {
            nodes.erase(str[m_str.size()]);
            if (nodes.size() == 1 && !m_is_end) {
              m_str += nodes.begin()->first + nodes.begin()->second.m_str;
              nodes.clear();
              m_is_end = true;
            }
          }
        }
      } catch(const std::out_of_range& ex) {
        std::cerr << "Node::remove: impossible out_of_range." << std::endl;
        return false;
      }
    }
    return false;
  }

  bool find(const strview& str) {
    if(m_str.empty() && str.empty())
      return true;
    if(m_str.size() == str.size()) {
      if(0 == static_cast<strview>(m_str).compare(str) && m_is_end) {
        return true;
      }
    } else if(m_str.size() < str.size()) {
      try {
        if (0 ==
            static_cast<strview>(m_str).compare(str.substr(0, m_str.size())) || m_str.empty()) {
          return nodes.find(str.substr(m_str.size()));
        }
      } catch(const std::out_of_range& ex) {
        std::cerr << "Node::find: impossible out_of_range." << std::endl;
        return false;
      }
    }
    return false;
  }

  void print(std::ostream& os, const std::string& str) const {
    if (!nodes.empty()) {
      nodes.print(os, str + m_str);
    }
    if (m_is_end)
      os << str + m_str << " " << str << std::endl;
  }

  void print_graph(std::ostream& os, const std::string& str, long long links) const {
    os << str.substr(0, str.size() - 1) << (-1 != links ? "+ " : "")
       << str[str.size() - 1] << m_str << (m_is_end ? "$" : "") << std::endl;
    if (!nodes.empty()) {
      nodes.print_graph(os, str, m_str, links);
    }
  }

  size_t size() const {
    size_t s = m_is_end ? 1 : 0;
    for(const auto& p : nodes)
      s += p.second.size();
    return s;
  }
};

class RadixTree : public Node {
public:
  void insert(const std::string &str) {
    if(str.empty())
      return;
    nodes.insert(str);
  }
  void remove(const std::string &str) {
    if(str.empty())
      return;
    nodes.remove(str);
  }
  bool find(const std::string &str) {
    if(str.empty())
      return false;
    return nodes.find(str);
  }
  void print(std::ostream& os) const {
    nodes.print(os, "");
  }
  void print_graph(std::ostream& os, bool links = false) const {
    long long count = nodes.size();
    for (const auto &p : nodes) {
      p.second.print_graph(os, std::string(1, p.first), links ? count-- : -1);
    }
  }
};

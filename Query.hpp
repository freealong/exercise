#ifndef QUERY
#define QUERY

#include"TextQuery.hpp"
#include<iostream>
#include<algorithm>

using namespace std;

/* class QueryBase */
class QueryBase
{
  friend class Query;
protected:
  typedef TextQuery::line_no line_no;
  virtual ~QueryBase() {};
private:
  virtual set<line_no> eval(const TextQuery&) const = 0;
  virtual ostream& display(ostream& = cout) const = 0;
};

/* class Query */
class Query
{
  friend Query operator~(const Query&);
  friend Query operator&(const Query&, const Query&);
  friend Query operator|(const Query&, const Query&);
  QueryBase *q;
  size_t *use;
  void decr_use(){
    if(--*use==0){delete q; delete use;}
  }
  Query(QueryBase *qb): q(qb), use(new size_t(1)) {};
public:
  Query(const string&);
  Query(const Query &cq): q(cq.q), use(cq.use) {++*use;}
  ~Query() {decr_use();}
  set<TextQuery::line_no> eval(const TextQuery &t) const {
    return q->eval(t);
  }
  ostream& display(ostream &os) const {return q->display(os);}
};

inline ostream& operator<<(ostream &os, const Query &q)
{
  return q.display(os);
}

/* class WordQuery */
class WordQuery: public QueryBase
{
  friend class Query;
  WordQuery(const string &s): query_word(s) {}
  set<line_no> eval(const TextQuery &tq) const {
    return tq.run_query(query_word);
  }
  ostream& display(ostream &os) const {
    return os << query_word;
  }
  string query_word;
};

Query::Query(const string &s)
{
  q = new WordQuery(s);
  use = new size_t(1);
}

/* class NotQuery */
class NotQuery: public QueryBase
{
  friend Query operator~(const Query&);
  NotQuery(Query q): query(q) {}
  set<line_no> eval(const TextQuery&) const;
  ostream& display(ostream &os) const {
    return os << "~(" << query << ")";
  }
  const Query query;
};

set<TextQuery::line_no> NotQuery::eval(const TextQuery &tq) const
{
  set<line_no> has_val = query.eval(tq);
  set<line_no> ret_lines;
  for (line_no n = 0; n!= tq.size(); ++n)
    if (has_val.find(n) == has_val.end())
      ret_lines.insert(n);
  return ret_lines;
}

/* class BinaryQuery */
class BinaryQuery: public QueryBase
{
protected:
  BinaryQuery(Query left, Query right, string op): lhs(left), rhs(right), oper(op) {}
  ostream& display(ostream &os) const{
    return os<< "("<<lhs<<")"<<oper<<"("<<rhs<<")";
  }
  const Query lhs, rhs;
  const string oper;
};

/* class AndQuery */
class AndQuery:public BinaryQuery
{
  friend Query operator&(const Query&, const Query&);
  AndQuery(Query left, Query right): BinaryQuery(left, right, "&") {}
  set<line_no> eval(const TextQuery&) const;
};

set<TextQuery::line_no> AndQuery::eval(const TextQuery &tq) const
{
  set<line_no> left = lhs.eval(tq), right = rhs.eval(tq),
               ret_lines;
  set_intersection(left.begin(), left.end(),
                   right.begin(), right.end(),
                   inserter(ret_lines, ret_lines.begin()));
  return ret_lines;
}

/* class OrQuery */
class OrQuery: public BinaryQuery
{
  friend Query operator|(const Query&, const Query&);
  OrQuery(Query left, Query right): BinaryQuery(left, right, "|") {}
  set<line_no> eval(const TextQuery&) const;
};

set<TextQuery::line_no> OrQuery::eval(const TextQuery &tq) const
{
  set<line_no> left = lhs.eval(tq),
              ret_lines = rhs.eval(tq);
  ret_lines.insert(left.begin(), left.end());
  return ret_lines;
}

inline Query operator~(const Query& cq)
{
  return new NotQuery(cq);
}

inline Query operator&(const Query &left, const Query &right)
{
  return new AndQuery(left, right);
}

inline Query operator|(const Query &left, const Query &right)
{
  return new OrQuery(left, right);
}

#endif

#ifndef _STD_CppPython_KLEVH_
#define _STD_CppPython_KLEVH_

#include "pyList.hpp"
#include <iostream>
#include <string>
#include <sstream>
using std::cout;
using std::endl;
using std::ostream;
using std::string;
using std::stringstream;
using std::cin;

// ---------------------------------------------------------------------------
//Standard function

//python's sum function
template <class T> T sum(const List<T>& l);
template <class T> T sum(T a);
template <class T, class ...U> T sum(T a, U ...args);

//python's min function
template <class T> T min(const List<T>& l);
template <class T> T min(T a);
template <class T, class ...U> T min(T a, U ...args);

//python's max function
template <class T> T max(const List<T>& l);
template <class T> T max(T a);
template <class T, class ...U> T max(T a, U ...args);

//python's print function (not exactly the same)
void print();
template <class T>
void print(T a);
template <class T> 
void print(string s,T value);
template <class T,class ...U> 
void print(string s, T value, U ...args);
template <class T,class ...U> 
void print(const char * s, T value, U ...args);
template <class T,class ...U>
void print(T value, U ...args);

// python's range
template <class T>
List<T> range(T end);
template <class T>
List<T> range(T begin, T end);
template <class T>
List<T> range(T begin,T end,T inc);

//list's for syntax constructor (l=[i for i in ... if ...])
template <class Val,class T>
List<T> For(Val valueGenerator,const List<T>& l);
template <class Val,class T,class Condition>
List<T> For(Val valueGenerator,const List<T>& l,Condition condFunc);

//python's input
string input(const string& s){
  string str;
  cout<<s;
  cin>>str;
  return str;
}
string input(){
  string str;
  cin>>str;
  return str;
}
// ---------------------------------------------------------------------------




//Standard functions
template <class T> T sum(const List<T>& l){
  T res={};
    
  for(typename List<T>::iterator it(l);!it.end();++it)
    res+=*it;
    
  return res;
}

template <class T>
T sum(T a){
  return a; 
}

template <class T, class ...U>
T sum(T a, U ...args){
  return a+sum(args...);
}

template <class T> T min(const List<T>& l){
  T m;
  if(len(l)){
    m=l[0];
    for(typename List<T>::iterator it(l);!it.end();++it)
      if(*it < m)
	m = *it;
  }else
    m={};
        
  return m;
}

template <class T> T min(T a){
  return a;
}

template <class T, class ...U> T min(T a, U ...args){
  T m = min(args...);
    
  return (m>a?a:m);
}

template <class T> T max(const List<T>& l){
  T m;
  if(len(l)){
    m=l[0];
    for(typename List<T>::iterator it(l);!it.end();++it)
      if(*it > m)
	m = *it;
  }else
    m={};
        
  return m;
}

template <class T> T max(T a){
  return a;
}

template <class T, class ...U> T max(T a, U ...args){
  T m = max(args...);
    
  return (m<a?a:m);
}

void print(){
  cout<<endl;
}

template <class T>
void print(T a){
  cout<<a<<endl;
}

template <class T> 
void print(string s,T value){
  unsigned long size=s.length(), deb=0,fin=0;
  unsigned long id;
  bool isFormated = false;
    
  id=s.find_first_of('{');
  if(id<s.size()){
    ++id;
    while(s[id]<='9' && s[id]>='0')
      ++id;
    isFormated=s[id]=='}';
  }
  if(isFormated){
    while(deb<size-1){ 
      size=s.length();
      deb=s.find_first_of('{');
      fin=deb+1;
      id=0;
      while(fin<size && s[fin]>='0' && s[fin]<='9'){
	id*=10;
	id+=s[fin]-'0';
	++fin;
      }
      if(fin<size){
	if(s[fin]=='}'){        
	  cout<< s.substr(0, deb)<<value;
	  s=s.substr(fin+1);
	}
      }
    }
    cout<<s<<endl;
  }else{
    cout<<s<<value<<endl;
  }
}

template <class T,class ...U> 
void print(string s, T value, U ...args){
  stringstream ss;
  unsigned long size=s.length(), deb=0,fin=0;
  unsigned long id,idGen=-1;
  bool findNonGen=false, isFormated = false;
    
  id=s.find_first_of('{');
  if(id<s.size()){
    ++id;
    while(s[id]<='9' && s[id]>='0')
      ++id;
    isFormated=s[id]=='}';
  }
  if(isFormated){
    while(deb<size-1){
      deb=fin;
      deb=s.find_first_of('{',deb);
      fin=deb+1;
      id=0;
      while(fin<size && s[fin]>='0' && s[fin]<='9'){
	id*=10;
	id+=s[fin]-'0';
	++fin;
      }
      if(fin<size){
	if(s[fin]=='}'){
	  ss.str("");
	  if(id){
	    ss<<id-1;
	    s=s.substr(0,deb+1)+ss.str()+s.substr(fin);
	  }else if(fin>deb+1){
	    ss<<value;
	    s=s.substr(0,deb)+ss.str()+s.substr(fin+1);
	    findNonGen=true;
	  }else if(idGen==-1){
	    idGen=deb;
	  }
	}
      }
    }
    if(!findNonGen && idGen>=0){
      deb=-1;
      do{
	deb=s.find_first_of('{',deb+1);
      }while(deb<size && (s[deb]!='{' || s[deb+1]!='}'));
      if(deb<size && s[deb]=='{' && s[deb+1]=='}'){
	ss.str("");
	ss<<value;
	s=s.substr(0,deb)+ss.str()+s.substr(deb+2);
      }
    }
    print(s,args...);
  }else{
    cout<<s<<value;
    print(args...);
  }
}

template <class T,class ...U> 
void print(const char * s, T value, U ...args){
  print(string(s),value,args...);
}

template <class T,class ...U>
void print(T value, U ...args){
  cout<<value;
  print(args...);
}

// python's range
template <class T>
List<T> range(T end){
  return range({},end);
}

template <class T>
List<T> range(T begin, T end){
  List<T> res;
    
  if(begin>end)
    for(T i=begin;i>end;--i)
      res.append(i);
  else
    for(T i=begin;i<end;++i)
      res.append(i);
    
  return res;
}

template <class T>
List<T> range(T begin,T end,T inc){
  List<T> res;
    
  if(begin>end)
    for(T i=begin;i>end;i-=inc)
      res.append(i);
  else
    for(T i=begin;i<end;i+=inc)
      res.append(i);
    
  return res;
}

//list's for syntax constructor (l=[i for i in ... if ...])
template <class Val,class T>
List<T> For(Val valueGenerator,const List<T>& l){
  List<T> res;
    
  for(auto i : l)
    res.append(valueGenerator(i));
    
  return res;
}

template <class Val,class T,class Condition>
List<T> For(Val valueGenerator,const List<T>& l,Condition condFunc){
  List<T> res;
    
  for(auto i : l)
    if(condFunc(i))
      res.append(valueGenerator(i));
    
  return res;
}
// ---------------------------------------------------------------------------

#endif

#include "../pyList.hpp"

template <class T>
void print(T s){
  cout<<s<<endl;
}
void print(){
  cout<<endl;
}

int main() {
  List<int> l,l2;
    
  print("---TESTS ON PYTHON LIST---");
  print("Creating the list l :");
  for(int i=0;i<10;++i)
    l.append(i);
  print(l);
  print();
    
  l2(1,2,3,4,l);
  print("l2(1,2,3,4,l) :");
  print(l2);
  print();

  return 0;
}

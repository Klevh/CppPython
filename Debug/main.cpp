#include "../pySTD.hpp"
#include "../pyRandom.hpp"

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
    
    print("3 <in<int>()> l ?");
    print(3 <in<int>()> l);
    print();
    
    print("-10 <in<int>()> l ?");
    print(-10 <in<int>()> l);
    print();
    
    List<int> l3(1,2,3,4,5),l4(l,0,0);
    print("List<int> l3(1,2,3,4,5) :");
    print(l3);
    print();
    
    print("List<int> l4(l,0,0) :");
    print(l4,'\n');
    
    l[0]=3;
    print("List after l[0]=3:");
    print(l,"\n");
    
    print("l[\"::-1\"] :");
    l2=l["::-1"]; //to test copy's constructor and = operator as they have nearly the same code
    //test also insert as it is used when increment is negative
    print(l2,"\n");
    
    print("3*l[\"2:-2:2\"] :");
    print(3*l["2:-2:2"],'\n');
    
    print("Empty list :");
    print(List<int>(),"\n");
    
    print("l[\"6:\"] + l[\":3\"]:");
    print(l["6:"]+l[":3"]);
    print();
    
    print("len(l) == ",len(l));
    int val=l.pop();
    print("Value poped : ",val);
    print("len(l) == ",len(l));
    print("l after pop :");
    print(l,"\n");
    
    print("len(l) == {}",len(l));
    val=l.del(3);
    print("Value gotten after l.del(3) : ",val);
    print("len(l) == ",len(l));
    print("l after del :");
    print(l,"\n");
    
    print("---TESTS ON PYTHON FUNCTIONS---");
    print("sum(1,2,3) == ",sum(1,2,3));
    print("sum(1,2,6,-3) == ",sum(1,2,6,-3));
    print("sum(l) == ",sum(l),'\n');
    
    print("min(1,2,3) == ",min(1,2,3));
    print("min(1,2,6,-3) == ",min(1,2,6,-3));
    print("min(l) == ",min(l),"\n");
    
    print("max(1,2,3) == ",max(1,2,3));
    print("max(1,2,6,-3) == ",max(1,2,6,-3));
    print("max(l) == ",max(l),"\n");
    
    l2=For([](int i){return i*i;},range(5),[](int i){return i&1;});
    print("l2 = [i*i for i in range(5) if i&1]");
    print("l2=For([](int i){return i*i;},range(5),[](int i){return i&1;}) :");
    print(l2,'\n');
    
    print("---TESTS ON RANDOM FUNCTIONS---");
    for(int i=0;i<5;++i)
	print("randint(-5,5) == ",Random::randint(-5,5));
    print();
    
    for(int i=0;i<5;++i)
	print("choice(l) == ",Random::choice(l));
    cout<<endl;
    
    for(int i=0;i<5;++i)
	print("randrange(7) == ",Random::randrange(7));
    print();
    
    for(int i=0;i<5;++i)
	print("randrange(2,6) == ",Random::randrange(2,6));
    print();
    
    for(int i=0;i<5;++i)
	print("randrange(0,20,3) == ",Random::randrange(0,20,3));
    print();
    
    for(int i=0;i<5;++i){
	print("after shuffle(l) :");
	Random::shuffle(l);
	print("l == ",l);
    }
    print();
    
    print("----TESTS OF PYTHON FOR LOOP----");
    print("Going through l :");
    for(auto i : l)
	print(i);
    print();
    
    print("Values of range(5) :");
    for(auto i:range(5))
	print(i);
    print();
    
    print("Values of range(5,2) :");
    for(auto i:range(5,2))
	print(i);
    print();
    
    print("Values of range(0,5,2) :");
    for(auto i:range(0,5,2))
	print(i);
    print();

    print("----TESTS OF PYTHON FILES----");
    File f("test.txt","w");
    f.write("my hobbie is\n");
    f.write(55);
    f.close();
    f.open("test.txt","r");
    for(auto i:f)
	print(i);
    print();
    
    return 0;
}

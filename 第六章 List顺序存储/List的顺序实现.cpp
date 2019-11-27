#include<iostream>
#define max_list 100
using namespace std;

typedef int List_entry;

enum Error_code{success,overflow,underflow};

class List{
protected:
    int count;
    List_entry entry[max_list];
public:
    List();
    int size() const;
    bool full() const;
    bool empty() const;
    void clear();
    void traverse(void (*visit)(List_entry &));
    Error_code retrieve(int position, List_entry &x) const;
    Error_code replace(int position, const List_entry &x);
    Error_code remove(int position, List_entry &x);
    Error_code insert(int position, const List_entry &x);

    Error_code push_front(const List_entry &x);
    Error_code push_back(const List_entry &x);
    Error_code pop_front();
    Error_code pop_back();
    List_entry front();
    List_entry back();
};

List::List()
{
    count=0;
}

int List::size() const
{
    return count;
}

bool List::full() const
{
    return count==max_list;
}

bool List::empty() const
{
    return count==0;
}

void List::clear()
{
    count=0;
}

Error_code List::push_front(const List_entry &x)
{
    if(full()) return overflow;
    insert(0,x);
    return success;
}

Error_code List::push_back(const List_entry &x)
{
    if(full()) return overflow;
    entry[count]=x;
    count++;
    return success;
}

Error_code List::pop_front()
{
    if(empty()) return underflow;
    int x;
    remove(0,x);
    return success;
}

Error_code List::pop_back()
{
    if(empty()) return underflow;
    count--;
    return success;
}

List_entry List::front()
{
    return entry[0];
}

List_entry List::back()
{
    return entry[count-1];
}

Error_code List::insert(int position, const List_entry &x)
{
    if(full()) return overflow;
    if(position<0) return underflow;
    else if(position>=max_list) return overflow;
    for(int i=count;i>position;i--)
        entry[i]=entry[i-1];
    entry[position]=x;
    count++;
    return success;
}

Error_code List::remove(int position, List_entry &x)
{
    if(empty()) return underflow;
    if(position<0) return underflow;
    else if(position>=max_list) return overflow;
    x=entry[position];
    for(int i=position;i<count-1;i++)
        entry[i]=entry[i+1];
    count--;
    return success;
}

Error_code List::replace(int position, const List_entry &x)
{
    if(position<0) return underflow;
    else if(position>=max_list) return overflow;
    entry[position]=x;
    return success;
}

Error_code List::retrieve(int position, List_entry &x) const
{
    if(position<0) return underflow;
    else if(position>=max_list) return overflow;
    x=entry[position];
    return success;
}

void List::traverse(void (*visit)(List_entry &))
{
    for(int i=0;i<count;i++){
        (*visit)(entry[i]);
    }
    cout<<endl;
}

void print(List_entry &x)
{
    cout<<x<<' ';
}

int main()
{
    List p;
    List_entry num;
    void (*ptr)(List_entry &)=print;
    while(cin>>num&&num!=-1)
        p.push_back(num);
    // while(!p.empty()){
    //     cout<<p.front()<<' ';
    //     p.pop_front();
    // }
    p.traverse(ptr);
    return 0;
}

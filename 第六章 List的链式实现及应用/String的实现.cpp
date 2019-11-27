#include <iostream>
#include <cstring>
#include <list>
using namespace std;

class String {
public: // methods of the string ADT
	String( );
	~String( );
	String (const String &copy); // copy constructor
	String (const char * copy); // conversion from C-string
	// String (list<char> &copy); // conversion from list 
	void operator = (const String &copy);
	void operator = (const char *copy);
	const char *c_str( ) const; // conversion to C-style string
	int size();
protected:
	char *entries;
	int length;
};

String::String(){
	entries=NULL;
	length=0;
}

String::~String(){
	delete entries;
}

String::String(const char* in_string){
	length=strlen(in_string);
	entries=new char[length+1];
	strcpy(entries,in_string);
}

// String::String(list<char> &in_list){
// 	length=in_list.size();
// 	entries=new char[length+1];
// 	for(int i=0;i<length;i++)
// 		in_list.retrieve(i,entries[i]);
// 	entries[length]='\0';
// }

String::String(const String &copy){
	const char *pcopy=copy.c_str();
	length=strlen(pcopy);
	entries=new char[strlen(pcopy)+1];
	strcpy(entries,pcopy);
}

void String::operator = (const String &copy){
	const char *pcopy=copy.c_str();
	length=strlen(pcopy);
	entries=new char[strlen(pcopy)+1];
	strcpy(entries,pcopy);
}

void String::operator = (const char *copy){
	length=strlen(copy);
	entries=new char[strlen(copy)+1];
	strcpy(entries,copy);
}

int String::size(){
	return length;
}

const char* String::c_str() const{
	return (const char*) entries;
}

bool operator == (const String &first, const String &second){
	return strcmp(first.c_str(),second.c_str())==0;
}

bool operator > (const String &first, const String &second){
	return strcmp(first.c_str(),second.c_str())>0;
}

bool operator < (const String &first, const String &second){
	return strcmp(first.c_str(),second.c_str())<0;
}

bool operator >= (const String &first, const String &second){
	return strcmp(first.c_str(),second.c_str())>=0;
}

bool operator <= (const String &first, const String &second){
	return strcmp(first.c_str(),second.c_str())<=0;
}

bool operator != (const String &first, const String &second){
	return strcmp(first.c_str(),second.c_str())!=0;
}

void strncpy(String &to, const String &from, int n){
	const char *second=from.c_str();
	char *copy=new char[n+1];
	for(int i=0;i<n;i++)
		*(copy+i)=*(second+i);
	*(copy+n)='\0';
	to=copy;
	delete [] copy;
}

void strcat(String &add_to, const String &add_on){
	const char *cfirst=add_to.c_str();
	const char *csecond=add_on.c_str();
	char *copy=new char[strlen(cfirst)+strlen(csecond)+1];
	strcpy(copy,cfirst);
	strcat(copy,csecond);
	add_to=copy;
	delete [] copy;
}

int strstr(const String &text, const String &target){
	const char *cfirst=text.c_str();
	const char *csecond=target.c_str();
	if(strstr(cfirst,csecond)==NULL) return -1;
	return strstr(cfirst,csecond)-cfirst;
}

ostream &operator <<(ostream &output, String s1){
	output<<s1.c_str();
	return output;
}

bool cmp(const String &first, const String &second){
	return first<second;
}

int main()
{
	int n,i;
	char str[1005];
	list<String> test;
	cin>>n;
	for(i=0;i<n;i++){
		cin>>str;
		test.push_back(str);
	}
	int a,b;
	// advance(it,1);
	// cout<<*it<<endl;
	while(cin>>a>>b&&!(a==-1&&b==-1)){
		list<String>::iterator it1=test.begin();
		list<String>::iterator it2=test.begin();
		String first,second;
		advance(it1,a);
		first=*it1;
		advance(it2,b);
		second=*it2;
		cout<<strstr(second,first)<<' ';
	}
	cout<<endl;
	test.sort(cmp);
	for(i=0;i<n;i++){
		cout<<test.front()<<' ';
		test.pop_front();
	}
	cout<<endl;
	return 0;
}


#include <iostream>
#include <string>
#include <regex>
#include <exception>

using namespace std;


int main()
{
	try {
		cout << "before"<<endl;
		regex re("\\+");
		cout << "after re"<<endl;
	} catch (exception& e) {
		cout << "exception happens"<<endl;
		cout << e.what() << endl;
		throw e;
	}

	string path="  /       ";
	// "/"  --> ""
	// ""  --> 空
	//
	regex re("/+");
//	sregex_iterator pos(path.cbegin(),path.cend(),re);
//	sregex_iterator end;
//
	cout << "original string is \""<<path<<"\""<<endl;
//
//	for(;pos!=end;++pos)
//	{
//		cout << "match: "<<pos->str() << endl;
//		cout << "tag:  "<<pos->str(1) << endl;
//		cout << "value: " << pos->str(2) << endl;
//	}
//
	smatch allmatch;
//
//	regex_search(path,allmatch,re);
//	cout<<"str="<<allmatch.str()<<endl;
//	cout << "length="<<allmatch.length()<<endl;
//	cout << "size="<<allmatch.size()<<endl;
//
//	for(int i=0;i<allmatch.size();++i)
//	{
//		cout << "i="<<i<<endl;
//		cout << "str(i)="<<allmatch.str(i)<<endl;
//		cout << "length(i)="<<allmatch.length(i)<<endl;
//		cout << "position(i)="<<allmatch.position(i)<<endl;
//
//	}

	cout << "print all splited"<<endl;
	const string::const_iterator begin=path.cbegin();
	auto itBeg=begin;
	vector<string> res;
	while(itBeg!=path.end() && regex_search(itBeg,path.cend(),allmatch,re))
	{
		// pos,len 每次迭代时，当还有时,应将beg~pos之间保留，然后beg变换到length之后
		res.push_back(path.substr(itBeg - begin, allmatch.position()));
		auto len=allmatch.length() + allmatch.position();
		if(path.cend() - itBeg <= len) //超出范围
			break;
		itBeg += len;
	}
	for(string& s:res)
		cout << "\""<<s <<"\""<< endl;



	return 0;
}

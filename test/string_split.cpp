#include <string>
#include <vector>
#include <iostream>
using namespace std;
/**
 * 假设全都以空格分隔
 */
vector<string> split(const string& s)
		{
			string::size_type start=0;
			vector<string> res;
			while(start<s.size() && start>=0)
			{
				while(s.at(start)==' ' && start<s.size())start++;//定位到第一个非空
				if(start>=s.size())break;
				auto end=s.find(' ',start);
				res.push_back(s.substr(start,end-start));
				start=end+1;
			}

			return std::move(res);

		}

int main()
{
	string s=" hello world ";
	vector<string> res=split(s);
	for(auto v_s:res)
		cout << "\""<<v_s<<"\""<<endl;
	return 0;
}

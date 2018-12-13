#include <bits/stdc++.h>
#include "method.h"
using namespace std;
/*
 * int main()
 * {
 *	 string s;
 *   string t;
 *   getline(cin,s);
 *   getline(cin,t);
 *   string token;
 *   int pos=0;
 *   while (stringtoken(s,pos,token,' '))
 *     cout<<token<<endl;
 *   return 0;
 * }
 */
bool Method::stringtoken(string s,int &pos,string &token,char match)
{
	int bufpos=0;
	while (pos<s.length() && s[pos]==match) pos++;
	for (;pos<s.length();pos++)
	{
		if (s[pos]==match) break;
		buf[bufpos++]=s[pos];
	}
	if (bufpos)
	{
		buf[bufpos]='\0';
		token=buf;
		return true;
	}
	return false;
}

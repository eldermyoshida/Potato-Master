#pragma once

/// Result Class

#include <string>
#include <sstream>
#include <cstdio>
#include <vector>
#include <cstdlib>

using std::vector;
using std::string;

typedef string::size_type stringpos;


// Escape \ to \\ and ' to \'.
string EscapeSingleQuotes(const string& S);

// HTML escape.
string HTMLEscape(const string& S);

// Escape attribute strings.
string AttributeEscape(const string& S);

// Integer to string.
inline string ItoS(int I)
{
	std::stringstream S;
	S << I;
	return S.str();
}

// Unsigned integer to string.
inline string UItoS(unsigned int I)
{
	std::stringstream S;
	S << I;
	return S.str();
}

// Unsigned long long to string.
inline string ULLtoS(unsigned long long I)
{
	char out[128];
	sprintf(out, "%lld", I);
	return out;
}

// String to integer, returns Fail on fail.
inline int StoI(const string& S, int Fail = 0)
{
	char* EP;
	const char* P = S.c_str();
	int R = strtol(P, &EP, 0);
	if (EP == P)
		return Fail;
	return R;
}

// String to unsigned integer, returns Fail on fail.
inline unsigned int StoUI(const string& S, unsigned int Fail = 0)
{
	char* EP;
	const char* P = S.c_str();
	int R = strtoul(P, &EP, 0);
	if (EP == P)
		return Fail;
	return R;
}

// String to unsigned integer, returns Fail on fail.
inline unsigned int StoULL(const string& S, unsigned long long Fail = 0)
{
	char* EP;
	const char* P = S.c_str();
	int R = strtoull(P, &EP, 0);
	if (EP == P)
		return Fail;
	return R;
}

// Get an environmental variable.
inline string GetEnv(const string& Var)
{
	char* V = getenv(Var.c_str());
	if (!V)
		return "";
	return V;
}

// Split a string.
inline vector<string> Split(const string& str, const string& delim)
{
	vector<string> ret;
	
	unsigned int offset = 0;
	
	for (stringpos delimIndex = str.find(delim, offset); delimIndex != string::npos;
	     delimIndex = str.find(delim, offset))
	{
		ret.push_back(str.substr(offset, delimIndex - offset));
		offset += delimIndex - offset + delim.length();
	}
	
	ret.push_back(str.substr(offset));
	
	return ret;
}

// Trim leading and trailing whitespace.
inline string Trim(const string& text)
{
	for (unsigned int i = 0; i < text.length(); ++i)
	{
		if (!isspace(text[i]))
		{
			for (unsigned int j = text.length()-1; j > i; --j)
			{
				if (!isspace(text[j]))
				{
					return text.substr(i, j-i + 1);
				}
			}
			
			// Probably a better way - can't be bothered to look it up though.
			return string(&(text[i]), 1);
		}
	}
	return string();
}

// Case insensitive string comparison.
inline bool iequals(const string& a, const string& b)
{
	unsigned int sz = a.size();
	if (b.size() != sz)
		return false;
	for (unsigned int i = 0; i < sz; ++i)
		if (tolower(a[i]) != tolower(b[i]))
			return false;
	return true;
}

inline bool StartsWith(const string& a, const string& b)
{
	return a.size() >= b.size() && a.substr(0, b.size()) == b;
}
inline bool EndsWith(const string& a, const string& b)
{
	return a.size() >= b.size() && a.substr(a.size()-b.size(), b.size()) == b;
}

#include "Dictionary.hpp"
#include<string>


// constructor to create dictionary
Dictionary :: Dictionary()
{
        wordend=0;
        count=0;
        for(int i=0;i<26;i++)
        next[i]=NULL;
}

// insert function to add string in dictionary
void Dictionary :: insert(Dictionary* dict, string &s)
{
    Dictionary* t=dict;
    for(int i=0;i<s.length();i++)
    {
    	char c=s[i];
        int index=c-'a';
        if(t->next[index]==NULL)
        {
            t->next[index]=new Dictionary();
        }
        t=t->next[index];
    }
    t->count=t->count+1;
    t->wordend=1;
}

// work when autocomplete string present in dictionary and return vector of all string which have prefix string of autocomplete string
void Dictionary :: help(Dictionary* t,string s,vector<pair<string,int>> &v)
{
    if(t->count>0 && t->wordend==1)
    {
        v.push_back({s,t->count});
    }
    for(int i=0;i<26;i++)
    {
        if(t->next[i]!=NULL)
        {
            char c='a'+i;
            string str=s+c;
            help(t->next[i],str,v);
        }
    }

}

// return string for autocomplete
vector<pair<string,int>> Dictionary :: wordsuggestion(Dictionary* dict,string &s)
{
    vector<pair<string,int>> v;
    Dictionary* t=dict;
    int n=s.length(),i,index;
    for(i=0;i<n;i++)
    {
        index=s[i]-'a';
        t=t->next[index];
        // return null vector if  auto complete string not present in dictionary 
        if(t==NULL)
        return v;
    }
    help(t,s,v);
    return v;
}
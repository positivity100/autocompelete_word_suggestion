using namespace std;

#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>

#include "Dictionary.hpp"

bool compare(pair<string,int> a,pair<string,int> b)
{
    return a.second>b.second;
}

int main(int argc,char* argv[])
{
    if(argc!=2)
    {
        cout<<"Usage: ./main.exe  <path_to_text_file> ";
        return 0;
    }
    ifstream in(argv[1]);
    string s;

    //creating object of class 
    Dictionary dict;

    //traversing and storing file in class dictionary object dict 
    while(getline(in,s))
    {
        string word="";
        char last_char='\0';
        char c;
        //cout<<s<<"\n";
        for(int i=0;i<s.length();i++)
        {
        	c=s[i];
            switch(c)
            {
                case ' ':
                case ',':
                case '.':
                case '?':
                case  '!':
                          if((last_char <='Z' && last_char>='A') ||(last_char<='z' && last_char>='a'))
                        {
                            //cout<<word<<" ";
                            //insert string word in dict 
                            dict.insert(&dict,word);
                              word.clear();
                        }
                        break;
                default:
                if((c<='Z' && c>='A') ||( c <='z' && c>='a'))
                {
                    c=tolower(c);
                    word.push_back(c);
                }
            }
            last_char=c;
        }
        if(word.length()>0 && ((last_char <='Z' && last_char>='A') ||(last_char<='z' && last_char>='a')))
        {
            //cout<<word<<" ";
            //insert word in dict 
            dict.insert(&dict,word);
            word.clear();
        }
        //cout<<"\n";
    }

    char c;
    // word prediction of autocomplete
    do
    {
        string input;
        cout<<"Enter the string : ";
        cin>>input;
        vector<pair<string,int>> v=dict.wordsuggestion(&dict,input);
        sort(v.begin(),v.end(),compare);
        if(v.size()==0)
        {
            cout<<"No word in database starting with  "<<input<<"\n"; 
        }
        for(auto x : v)
        cout<<x.first<<"    freq_count :  "<<x.second<<"\n";

        cout<<"\nWant to enter more word Y/N : ";
        cin>>c;
    }while(tolower(c)=='y');
    return 0;
}

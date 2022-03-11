// delete a used element from set
#include <set>
#include <iostream>
using namespace std;
 
void printSet(set<int> st){
	set<int>:: iterator it;
	cout<<"Set contents are:\n";
	for(it=st.begin();it!=st.end();it++)
		cout<<*it<<" ";
	cout<<endl;
}
 
int main(){
	cout<<"Example of find function\n";
	set<int> st;
	set<int>:: iterator it;
	cout<<"inserting 4\n";
	st.insert(4);
	cout<<"inserting 6\n";
	st.insert(6);
	cout<<"inserting 10\n";
	st.insert(10);
 
	printSet(st); //printing current set
 
	//finding element 6
 
	if(st.find(6)!=st.end())
		cout<<"6 is present\n";
	else
		cout<<"6 is not present\n";
	
	// delete the used data
	st.erase(6); 
	if(st.find(6)!=st.end())
		cout<<"6 is present zyc\n";
	else
		cout<<"6 is not present zyc\n"; 
	
	//finding element 9
	if(st.find(9)!=st.end())
		cout<<"9 is present\n";
	else
		cout<<"9 is not present\n";
 
	return 0;
}



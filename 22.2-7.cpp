/*
Solution to the problem in the following page:
http://courses.missouristate.edu/EricShade/325/h5.html
by Yingcheng Sun
11/11/2014
*/

//the "pragma" decalaration is to avoid useless "warning" in the console
#pragma  warning(disable:4786)
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <list>
using namespace std;

struct GraphNode{
	string name;
	int depth;
	//The key value of map structure is not allowed to be changed once added in by default unless we use the keyword "mutable"
	mutable string color;
	/*The inequality sign < has to be overrided, since the key values(first values) in map structure are ordered stored
	 so the compiler needs to know which one is bigger when comparing two "GraphNode"s it has never seen */
	bool operator < (const GraphNode &g)const{
		return name<g.name;
	}

};
int main(){
	string s1,s2;
	GraphNode node1,node2;
	//Notice! There should be a blank space between tow angle brackets.
	map<GraphNode, list<GraphNode> > m;
	map<GraphNode, list<GraphNode> >::iterator Mit;
	list<GraphNode>::iterator Lit;
	ifstream fin("D:\\input.txt");

	//Initialization, available to both undirected and directed graphs
	while(fin>>s1>>s2){
		node1.name=s1;
		node2.name=s2;
		node1.depth=node2.depth=0;
		node1.color=node2.color="WHITE";

		Mit=m.find(node1);
		if(Mit!=m.end()){
			(*Mit).second.push_back(node2);
			m[node1]=(*Mit).second;
		}
		else{
			list<GraphNode> nodeList;
			nodeList.push_back(node2);
			m[node1]=nodeList;
		}	
		
		Mit=m.find(node2);
		if(Mit!=m.end()){
			(*Mit).second.push_back(node1);
			m[node2]=(*Mit).second;
		}
		else{
			list<GraphNode> nodeList;
			nodeList.push_back(node1);
			m[node2]=nodeList;
		}	
		
	}

	//BFS
	list<GraphNode> queue;
	GraphNode n=(*(m.begin())).first;
	n.color="GRAY";
	queue.push_back(n);
	while(!queue.empty()){
		n=*(queue.begin());	
		/*The condition "m.count(n)" is useful when the graph is undirected, since there maybe no node equals to "n" 
		  in the first value of "map" m. If the graph is directed, this condition can be deleted*/
		if((n.color!="BLACK")&&(m.count(n))){
			Mit=m.find(n);
			Lit=(*Mit).second.begin();
			while(Lit!=(*Mit).second.end()){
				if((*Lit).color=="WHITE"){
					(*Lit).color="GRAY";
					(*Lit).depth=n.depth+1;
					queue.push_back(*Lit);
				}
				Lit++;
			}
		}

		/*There may be more than one node equals to n in the adjacent list, 
		  so we have to change the color of each of them to "BLACK" */
		for(Mit=m.begin();Mit!=m.end();Mit++){
			if((*Mit).first.name==n.name)
				(*Mit).first.color="BLACK";
			for(Lit=(*Mit).second.begin();Lit!=(*Mit).second.end();Lit++)
				if((*Lit).name==n.name)
					(*Lit).color="BLACK";
		}		
		queue.pop_front();
	}

	/*Divide set into BABYFACES and HEELS.
	  Since all the nodes have been colored "BLACK", so I just use "BLACK" to represent the meaning of "WHITE" 
	  and "WHITE" to represent the meaning of "BLACK" in the BFS above. Of course we can also initialize every node's color to 
	  "WHITE" easily */
	n=(*(m.begin())).first;
	n.color="GRAY";
	queue.push_back(n);
	/*the second string value of the map makes no sense in fact, I use map to store the BABYFACES and HEELS just because 
	  the output should be ordered according to the requirement: "Output the babyfaces and heels in sorted order" */
	map<string,string> BABYFACES, HEELS;
	while(!queue.empty()){
		n=*(queue.begin());	
		if ((n.depth%2)==0)
			BABYFACES[n.name]="BABYFACES";
		else
			HEELS[n.name]="HEELS";
		if((n.color!="WHITE")&&(m.count(n))){
			Mit=m.find(n);
			Lit=(*Mit).second.begin();
			while(Lit!=(*Mit).second.end()){
				//The color of one node is gray means that there exists an edge between two nodes in the same layer
				if((*Lit).color=="GRAY"){
					cout<<"IMPOSSIBLE"<<endl;
					return 0;
				}
				if((*Lit).color=="BLACK"){
					(*Lit).color="GRAY";
					(*Lit).depth=n.depth+1;
					queue.push_back(*Lit);
				}
				Lit++;
			}
		}
		for(Mit=m.begin();Mit!=m.end();Mit++){
			if((*Mit).first.name==n.name)
				(*Mit).first.color="WHITE";
			for(Lit=(*Mit).second.begin();Lit!=(*Mit).second.end();Lit++)
				if((*Lit).name==n.name)
					(*Lit).color="WHITE";
		}		
		queue.pop_front();
	}

	//Print the information of BABYFACES and HEELS
	cout<<"BABYFACES"<<endl;
	for(map<string,string>::iterator lsit=BABYFACES.begin();lsit!=BABYFACES.end();lsit++)
		cout<<(*lsit).first<<endl;
	cout<<"HEELS"<<endl;
	for(lsit=HEELS.begin();lsit!=HEELS.end();lsit++)
		cout<<(*lsit).first<<endl;
	cout<<endl;

	/*Print the information of all the graph nodes
	  You can see some depth of nodes are 0. That's exactly right! It shows that each node of the graph is visited only once!
	  So the running time of our algorithm is O(m + n). */
	for(Mit=m.begin();Mit!=m.end();Mit++){
		cout<<(*Mit).first.name<<" "<<(*Mit).first.color<<" "<<(*Mit).first.depth<<" ";
		for(Lit=(*Mit).second.begin();Lit!=(*Mit).second.end();Lit++)
			cout<<(*Lit).name<<" "<<(*Lit).color<<" "<<(*Lit).depth<<" ";
		cout<<endl;
	}

return 0;
}


//Third Version
/*
int main(){
	string s1,s2;
	GraphNode node1,node2;
	//Notice! There should be a blank space between tow angle brackets.
	map<GraphNode, list<GraphNode> > m;
	map<GraphNode, list<GraphNode> >::iterator Mit;
	list<GraphNode>::iterator Lit;
	ifstream fin("D:\\tt.txt");

	while(fin>>s1>>s2){
		node1.name=s1;
		node2.name=s2;
		node1.depth=node2.depth=0;;
		node1.color=node2.color="White";

		Mit=m.find(node1);
		if(Mit!=m.end()){
			(*Mit).second.push_back(node2);
			m[node1]=(*Mit).second;
		}
		else{
			list<GraphNode> nodeList;
			nodeList.push_back(node2);
			m[node1]=nodeList;
		}	
		
		Mit=m.find(node2);
		if(Mit!=m.end()){
			(*Mit).second.push_back(node1);
			m[node2]=(*Mit).second;
		}
		else{
			list<GraphNode> nodeList;
			nodeList.push_back(node1);
			m[node2]=nodeList;
		}	
		
	}

	//BFS
	list<GraphNode> queue;
	GraphNode n=(*(m.begin())).first;
	queue.push_back(n);
	while(!queue.empty()){
		n=*(queue.begin());				
		if((n.color!="Black")&&(m.count(n))){
			Mit=m.find(n);
			Lit=(*Mit).second.begin();
			while(Lit!=(*Mit).second.end()){
				if((*Lit).color=="White"){
					(*Lit).color="Gray";
					(*Lit).depth=n.depth+1;
					queue.push_back(*Lit);
				}
				Lit++;
			}
		}

			
		for(Mit=m.begin();Mit!=m.end();Mit++){
			if((*Mit).first.name==n.name)
				(*Mit).first.color="Black";
			for(Lit=(*Mit).second.begin();Lit!=(*Mit).second.end();Lit++)
				if((*Lit).name==n.name)
					(*Lit).color="Black";
		}		
		queue.pop_front();
	}

	//Divide the wrestlers and heels
	n=(*(m.begin())).first;
	queue.push_back(n);
	while(!queue.empty()){
		n=*(queue.begin());				
		if((n.color!="White")&&(m.count(n))){
			Mit=m.find(n);
			Lit=(*Mit).second.begin();
			while(Lit!=(*Mit).second.end()){
				if((*Lit).color=="Gray"){
					cout<<"IMPOSSIBLE"<<endl;
					return 0;
				}
				if((*Lit).color=="Black"){
					(*Lit).color="Gray";
					(*Lit).depth=n.depth+1;
					queue.push_back(*Lit);
				}
				Lit++;
			}
		}
		for(Mit=m.begin();Mit!=m.end();Mit++){
			if((*Mit).first.name==n.name)
				(*Mit).first.color="White";
			for(Lit=(*Mit).second.begin();Lit!=(*Mit).second.end();Lit++)
				if((*Lit).name==n.name)
					(*Lit).color="White";
		}		
		queue.pop_front();
	}

	//print the information of all the graph nodes
	for(Mit=m.begin();Mit!=m.end();Mit++){
		cout<<(*Mit).first.name<<" "<<(*Mit).first.color<<" "<<(*Mit).first.depth<<" ";
		for(Lit=(*Mit).second.begin();Lit!=(*Mit).second.end();Lit++)
			cout<<(*Lit).name<<" "<<(*Lit).color<<" "<<(*Lit).depth<<" ";
		cout<<endl;
	}


return 0;
}
*/


//Second version
/*
struct GraphNode{
	string name;
	int depth;
	string father;
	mutable string color;
	bool operator < (const GraphNode &g)const{
		return name<g.name;
	}

};

int main(){
	string s1,s2;
	GraphNode node1,node2;
	list<GraphNode> l;
	//Notice! There should be a blank space between tow angle brackets.
	map<GraphNode, list<GraphNode> > m;
	map<GraphNode, list<GraphNode> >::iterator Mit;
	list<GraphNode>::iterator Lit;
	ifstream fin("D:\\tt.txt");
	ofstream fout("D:\\test.txt");

	while(fin>>s1>>s2){
		node1.name=s1;
		node2.name=s2;
		node1.depth=node2.depth=0;;
		node1.color=node2.color="White";

		Mit=m.find(node1);
		/* if the first value of the input pair already exists in the graph, then find it
		and add the second value of the input pair to the back of this adjacent list 
		if(Mit!=m.end()){
			(*Mit).second.push_back(node2);
			m[node1]=(*Mit).second;
		}
		else{
			list<GraphNode> nodeList;
			nodeList.push_back(node2);
			m[node1]=nodeList;
		}	
	}

	//BFS
	list<GraphNode> queue;
	int depth=0;
	GraphNode n=(*(m.begin())).first;
	map<GraphNode, list<GraphNode> >::iterator mit;
	queue.push_back(n);
	while(!queue.empty()){
		n=*(queue.begin());				
		if((n.color!="Black")&&(m.count(n))){
			mit=m.find(n);
			Lit=(*mit).second.begin();
			depth=n.depth+1;
			while(Lit!=(*mit).second.end()){
				(*Lit).color="Gray";
				(*Lit).depth=depth;
				(*Lit).father=(*mit).first.name;
				queue.push_back(*Lit);
				Lit++;
			}
		}
		Mit=m.find(n);
		if (Mit!=m.end())
			(*Mit).first.color="Black";

		else{
			GraphNode g;
			g.name=n.father;
			Mit=m.find(g);
			Lit=(*Mit).second.begin();
			while(Lit!=(*Mit).second.end()){
				if((*Lit).name==n.name)
					(*Lit).color="Black";
				Lit++;
			}
		}
		queue.pop_front();
	}

	//print the information of all the graph nodes
	for(Mit=m.begin();Mit!=m.end();Mit++){
		cout<<(*Mit).first.name<<" "<<(*Mit).first.color<<" "<<(*Mit).first.depth<<" ";
		l=(*Mit).second;
		for(Lit=l.begin();Lit!=l.end();Lit++)
			cout<<(*Lit).name<<" "<<(*Lit).color<<" "<<(*Lit).depth<<" ";
		cout<<endl;
	}

return 0;
}

*/




//First Version, do not consider that every value in the adjacent list is the node of graph
//That means the first value of "map" should be a "GraphNode" type
/*
int main(){
	string s1,s2;
	GraphNode node;
	list<GraphNode> l;
	//Notice! There should be a blank space between tow angle brackets.
	map<string, list<GraphNode> > m;
	map<string, list<GraphNode> >::iterator Mit;
	list<GraphNode>::iterator Lit;
	ifstream fin("D:\\tt.txt");
	ofstream fout("D:\\test.txt");

	while(fin>>s1>>s2){
		Mit=m.find(s1);
		node.name=s2;
		node.depth=0;
		node.color="White";
		//if the first value of the input pair already exists in the graph, then find it
		//and add the second value of the input pair to the back of this adjacent list 
		if(m.find(s1)!=m.end()){
			(*Mit).second.push_back(node);
			m[s1]=(*Mit).second;
		}
		else{
			list<GraphNode> nodeList;
			nodeList.push_back(node);
			m[s1]=nodeList;
		}	
	}

	//print the information of all the graph nodes
	for(Mit=m.begin();Mit!=m.end();Mit++){
		cout<<(*Mit).first<<" ";
		l=(*Mit).second;
		for(Lit=l.begin();Lit!=l.end();Lit++)
			cout<<(*Lit).name<<" ";
		cout<<endl;
	}

	//BFS
	list<GraphNode> l2;
	GraphNode n=*((*(m.begin())).second.begin());
	l2.push_back(n);
	while(!l2.empty()){
		cout<<(*(l2.begin())).color;	
		l2.pop_front();
	}
return 0;
}

*/







/*#include <hash_map>
using namespace std;
using namespace stdext;

#include <string>

#include <iostream>

void main()
{//简单的一个列子，其使用方法和map是一样的。
hash_map<int,string> hmap;//定义一个实例
//hmap.insert(pair<int,string>(10,"sfsfd"));//插入一个pair对象，
//hmap.insert(hash_map<int,string>::value_type(34,"sddsf"));//value_type就是pair类型的

hmap[23] = "23";
hmap[33] = "33";
hmap[-1] = "-1";
hash_map<int,string>::iterator it = hmap.begin();
while(it!=hmap.end())//遍历
   cout<<it->first<<"\t"<<it++->second<<endl;
it = hmap.find(23);//查找
if(it!=hmap.end())
  cout<<it->first<<"\t"<<it++->second<<endl;
cout<<hmap.size()<<endl;
cout<<hmap.count(58)<<endl;
cout<<hmap.empty()<<endl;
//hash_map<int,string>::const_reverse_iterator cit = hmap.rend();
//PRINT(cit);
}




/*
#include <iostream>
#include <list>
#include <string>
#include <fstream>

using namespace std;

/*void print(list<string> lst, char * name)  
{  
    list<string>::iterator it;  
    cout << name << ": ";  
    for(it = lst.begin(); it != lst.end(); ++it)  
        cout << *it << " ";  
    cout << endl;  
}  

int main(){
	list< list<string> > graph;
	list<string> row;
	list<list<string>>::iterator it;

	ifstream fin("D:\\name.txt");
	string s;
	while ( fin >> s )
	{   
		row.push_back(s);
     }
	graph.push_back(row);
	//for(it = graph.begin(); it != graph.end(); it++)
		//print(*it, "row");
return 0;
}
	  /*
	list< list<int> > graph;
	list<int> row;
	int len;
	int s1;
	int i;
	list<list<int>>::iterator it;

	cin>>len;
	for(i=1;i<=len;i++){
		cin>>s1;
		list1.push_back(s1);
	}



	graph.push_back(list1);

	for(it2d = graph.begin(); it2d != graph.end(); it2d++)
		print(*it2d, "row");



/*	//p[0]=
	delete[]   p; 
//	list<int> = new ;
	list1.push_back(1);
	list<int> list2;
	list2.push_back(2);
	list2.push_back(3);


graph.push_back(list1);
graph.push_back(list2);


list< list<int> >::iterator it2d;
for(it2d = graph.begin(); it2d != graph.end(); it2d++)
	 print(*it2d, "row");
return 0;
}

/*
#include <iostream>
#include <string>
#include <tr1/unordered_map>
using namespace std::tr1;
int main ()
{
  std::unordered_map<std::string,std::string> mymap;

  mymap.emplace ("NCC-1701", "J.T. Kirk");
  mymap.emplace ("NCC-1701-D", "J.L. Picard");
  mymap.emplace ("NCC-74656", "K. Janeway");

  std::cout << "mymap contains:" << std::endl;
  for (auto& x: mymap)
    std::cout << x.first << ": " << x.second << std::endl;

  std::cout << std::endl;
  return 0;
}
*/
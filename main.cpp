/*
Name: Jack Knapp, 302.7
Purpose: Build a modified DFS alg
Description: Program to keep us in the shade from TBE to SU
Input: Buildings and their distances from text files
What to do?:  Use the inputs to build a graph; then perform a modified dfs to see whether 
    we can get to our target building with the amount of stamina provided
Output: The pass fail results, printed to terminal with the path (if successful)
*/
#include <string>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <list>
#include <vector>

using namespace std;

//struct for future use
struct vertexType {
    string id;
    int length;
};

/* 
 * dfs : A modified depth first search that traverses a provided graph while updating some vars
 * parameters: a string with the current node, a string with the end or target node, an int with current stamina,
 *      an unordered map that holds our adjacency list, another unordered map to keep track of shortest paths to all nodes,
 *      and an unordered map to keep track of predecessors by shortest path 
 * return value: A bool to represent whether the end can be reached with the given stamina
 */
bool dfs(string curr, string end, int stamina, unordered_map<string, list<vertexType>> &adjList, unordered_map<string,int> &visited, unordered_map<string, string> &predecessor)  {

    //base case
    if (curr == end && stamina > 0) {
        return true;
    }

    //if we already have a shorter path to the node, return to caller
    if (stamina < visited[curr]) {
        return false;
    }

    //cout << curr << endl;   //print for testing

    //update value in visited map with new stamina value
    visited[curr] = stamina;

    //check and traverse neighbors of curr node
    for (auto &item : adjList[curr]) {
        //cout << "\t" << item.id << endl;

        //check whether the current path to a node is shorter than prev paths
        int modStam = stamina - item.length;
        if (modStam > visited[item.id]) {
            
            //update shortest paths and predecessors
            visited[item.id] = modStam;
            predecessor[item.id] = curr;

            //recursive call
            bool recCall = dfs(item.id, end, modStam, adjList, visited, predecessor);

            //break if recursive call is successful
            if (recCall == true) {
                return true;
            }
        }
    }

    //default failure return
    return false;
}

//its main bb
int main () {

    //set dfs call vars
    int stamina = 0;
    string snode = "", enode = "";
    unordered_map<string, list<vertexType> > adjList;
    unordered_map<string, string> predecessor;
    unordered_map<string,int> visited;

    //set vars for parsing
    string input = "";
    cin >> snode >> enode >> input;       //store the first line
    stamina = stoi(input);

    //vars for main parsing loop
    string fn,tn, dist;
    int distance;
    while(!cin.eof()) {
        //check for valid input
        getline(cin,input);
        if (input == "") {
            continue;
        }

        //parse the line
        stringstream s(input);
        s >> fn >> tn >> dist;
        distance = stoi(dist);

        //add data into the adjList
        adjList[fn].push_back({tn,distance});
    }

    //function call
    bool valPath = dfs(snode, enode, stamina, adjList, visited, predecessor); 

    //output
    if (valPath) {
        cout << "Time to cool off !\n" << "Path : ";

        //declare vars
        string temp = enode;
        vector<string> prints;
        prints.push_back(temp);

        //use a vector as a queue to reverse print order
        while (temp != snode) {
            temp = predecessor[temp];
            prints.push_back(temp);
        }
        while (!prints.empty()) {
            cout << prints.back() << " ";
            prints.pop_back();
        }
    }
    else {
        cout << "This is going to be a long summer ...\n";
    }

    return 0;
}
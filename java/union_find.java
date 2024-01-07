/*
Problem: Union Find - https://open.kattis.com/problems/unionfind
Author: Emil Säll
The code is written in Java and is using the Google style guide.

This code is used to solve the Union Find problem. The problem is getting a query of either
joining two sets containing the two given nodes or to check if the two given nodes are in
the same set. 

The time complexity of the program is O(nr_elements + nr_queries * log(nr_elements)) since
the initialization first takes nr_elements and then every query takes nr_queries * log(nr_elements). 

The input starts with a line containing two integers seperated by a space:

>> nr_elements nr_queries

Then nr_queries lines follow with the queries that start with a char 'o' which is either '=' or '?' 
and follow with two integers 'a', 'b' separated by a space:

>> o a b

where '=' will tell you to join the sets containing 'a' and 'b', and '?' will tell you to check if
'a' and 'b' belong to the same set.

The output is from each '?'-query with 'yes' if they belong to the same set and 'no' if they 
do not. An example of input and output is showned below. 


Input:
10 4
? 1 3
= 1 8
= 3 8
? 1 3

Output:
no
yes

*/

import java.util.*;
import java.io.*;

class Union{
  int[] parent;

  // Constructor where a set for each element is created.
  Union(int nr_elements){
    parent = new int[nr_elements];
    for(int i = 0; i < nr_elements; i++){
      init_root(i);
    }
  }

  // Initialize a set with root. 
  void init_root(int node){
    parent[node] = node;
  }

  // Iterate until the root is reached, make all nodes have root as 
  // parent. 
  int check_set(int node){
    if(node == parent[node]){
      return node;
    } else{
      return parent[node] = check_set(parent[node]);
    }
  }

  // Find the roots of of a and b, if the roots are the same nothing 
  // is done. Otherwise they are merged. 
  void merge(int a, int b){
    int a_root = check_set(a);
    int b_root = check_set(b);
    if(a_root != b_root){
      parent[b_root] = a_root;
    }
  }

  // Check if a and b is in the same set. 
  Boolean in_same_set(int a, int b){
    Boolean same = check_set(a) == check_set(b);
    return same;
  }
}


public class union_find{

  public static void main(String[] args) throws IOException {
    FastIO io = new FastIO();
    
    int nr_elements = io.nextInt();
    int nr_operations = io.nextInt();
    Union union = new Union(nr_elements);
    
    for(int i = 0; i < nr_operations; i++){
      char o = io.next().charAt(0);
      int a = io.nextInt();
      int b = io.nextInt();

      if(o == '?'){
        if(union.in_same_set(a, b)){
          io.println("yes");
        } else{
          io.println("no");
        }
      } else if(o == '='){
        union.merge(a, b);
      }
    }
    io.close();
  }
}


// Code to get faster IO
// Source: https://medium.com/@russellsaerang/the-ultimate-kattis-i-o-guide-566be942447f 
class FastIO extends PrintWriter { 
    BufferedReader br; 
    StringTokenizer st;
    public FastIO() { 
        super(new BufferedOutputStream(System.out)); 
        br = new BufferedReader(new InputStreamReader(System.in));
    } 
    String next() { 
        while (st == null || ! st.hasMoreElements()) { 
            try { st = new StringTokenizer(br.readLine()); } 
            catch (IOException  e) { e.printStackTrace(); } 
        } 
        return st.nextToken(); 
    } 
    int nextInt() { return Integer.parseInt(next()); } 
    long nextLong() { return Long.parseLong(next()); } 
    double nextDouble() { return Double.parseDouble(next()); } 
    String nextLine() { 
        String str = ""; 
        try { str = br.readLine(); } 
        catch (IOException e) { e.printStackTrace(); } 
        return str; 
    } 
}
import java.util.*;
import java.io.*;

// Make a class for an edge. 
class Edge{
  public int u;
  public int v;
  public int w;

  public Edge(int a, int b, int c){
    u = a;
    v = b;
    w = c;
  }
}

public class mincut{
  // If the residual graph has a path from source to sink it returns true, fills parent_list aswell.
  private static boolean bfs(int[][] resids, int source, int sink, int[] parent_list){
    boolean[] visited_list = new boolean[resids.length];

    Queue<Integer> q = new LinkedList<Integer>();
    q.add(source);
    visited_list[source] = true;
    parent_list[source] = -1; 

    // The BFS-loop (Breadth First Search)
    while (!q.isEmpty()) {
      int v = q.poll();
      for (int i = 0; i < resids.length; i++){
        if (resids[v][i] > 0 && !visited_list[i]){
          q.offer(i);
          visited_list[i] = true;
          parent_list[i] = v;
        }
      }
    }
    return(visited_list[sink] == true);
  }

  // Depth First Search that finds all reachable nodes from the source, marks true if reachable.
  private static void dfs(int[][] resids, int source, boolean[] visited){
    visited[source] = true;
    for(int i = 0; i < resids.length; i++){
      if(resids[source][i] > 0 && !visited[i]){
        dfs(resids, i, visited);
      }
    }
  }


  private static boolean[] mc(int[][] adj_matrix, int source, int sink){
    int u, v;
    // Make residual matrix. Basically copy the adjacency matrix. 
    // Time complexity ~ O(nr_node^2)
    int[][] resids = new int[adj_matrix.length][adj_matrix.length];
    for (int i = 0; i < adj_matrix.length; i++){
      for(int j = 0; j < adj_matrix.length; j++) {
        resids[i][j] = adj_matrix[i][j];
      }
    }

    // Create parent list for the nodes.
    int[] parent_list = new int[adj_matrix.length];

    // As long as there is a flow from source to sink
    while(bfs(resids, source, sink, parent_list)){

      // Find the max-flow
      int flow = 2147483647;        
      for (v = sink; v != source; v = parent_list[v]){
          u = parent_list[v];
          flow = Math.min(flow, resids[u][v]);
      }
        
      // Update the residual capacities 
      for (v = sink; v != source; v = parent_list[v]) {
          u = parent_list[v];
          resids[u][v] = resids[u][v] - flow;
          resids[v][u] = resids[v][u] + flow;
      }
    }

    boolean[] visited = new boolean[adj_matrix.length];    
    dfs(resids, source, visited);
    return(visited);
  }


  public static void main(String[] args) throws IOException {
    Reader io = new Reader();
    int nr_nodes = io.nextInt();
    int nr_edges = io.nextInt();
    int source = io.nextInt();
    int sink = io.nextInt();

    int[][] adj_matrix = new int[nr_nodes][nr_nodes];

    for(int i = 0; i < nr_edges; i++){
      int u = io.nextInt();
      int v = io.nextInt();
      int w = io.nextInt();
      adj_matrix[u][v] = w;
    }


    boolean[] visited = mc(adj_matrix, source, sink);
    int sum = 0;
    for(boolean b : visited){
      sum += b ? 1 : 0;
    }
    System.out.println(sum);
    for(int i = 0; i < visited.length; i++){
      if(visited[i] == true){
        System.out.println(i);
      }
    }
    io.close();
  }
}


// Code to get faster IO
// Source: https://medium.com/@russellsaerang/the-ultimate-kattis-i-o-guide-566be942447f 
class Reader { 
    final private int BUFFER_SIZE = 1 << 16; 
    private DataInputStream din; 
    private byte[] buffer; 
    private int bufferPointer, bytesRead; 

    public Reader() 
    { 
        din = new DataInputStream(System.in); 
        buffer = new byte[BUFFER_SIZE]; 
        bufferPointer = bytesRead = 0; 
    } 

    public Reader(String file_name) throws IOException 
    { 
        din = new DataInputStream( 
            new FileInputStream(file_name)); 
        buffer = new byte[BUFFER_SIZE]; 
        bufferPointer = bytesRead = 0; 
    } 

    public String readLine() throws IOException 
    { 
        byte[] buf = new byte[64]; // line length 
        int cnt = 0, c; 
        while ((c = read()) != -1) { 
            if (c == '\n') { 
                if (cnt != 0) { 
                    break; 
                } 
                else { 
                    continue; 
                } 
            } 
            buf[cnt++] = (byte)c; 
        } 
        return new String(buf, 0, cnt); 
    } 

    public int nextInt() throws IOException 
    { 
        int ret = 0; 
        byte c = read(); 
        while (c <= ' ') { 
            c = read(); 
        } 
        boolean neg = (c == '-'); 
        if (neg) 
            c = read(); 
        do { 
            ret = ret * 10 + c - '0'; 
        } while ((c = read()) >= '0' && c <= '9'); 

        if (neg) 
            return -ret; 
        return ret; 
    } 

    public long nextLong() throws IOException 
    { 
        long ret = 0; 
        byte c = read(); 
        while (c <= ' ') 
            c = read(); 
        boolean neg = (c == '-'); 
        if (neg) 
            c = read(); 
        do { 
            ret = ret * 10 + c - '0'; 
        } while ((c = read()) >= '0' && c <= '9'); 
        if (neg) 
            return -ret; 
        return ret; 
    } 

    public double nextDouble() throws IOException 
    { 
        double ret = 0, div = 1; 
        byte c = read(); 
        while (c <= ' ') 
            c = read(); 
        boolean neg = (c == '-'); 
        if (neg) 
            c = read(); 

        do { 
            ret = ret * 10 + c - '0'; 
        } while ((c = read()) >= '0' && c <= '9'); 

        if (c == '.') { 
            while ((c = read()) >= '0' && c <= '9') { 
                ret += (c - '0') / (div *= 10); 
            } 
        } 

        if (neg) 
            return -ret; 
        return ret; 
    } 

    private void fillBuffer() throws IOException 
    { 
        bytesRead = din.read(buffer, bufferPointer = 0, 
                              BUFFER_SIZE); 
        if (bytesRead == -1) 
            buffer[0] = -1; 
    } 

    private byte read() throws IOException 
    { 
        if (bufferPointer == bytesRead) 
            fillBuffer(); 
        return buffer[bufferPointer++]; 
    } 

    public void close() throws IOException 
    { 
        if (din == null) 
            return; 
        din.close(); 
    } 
} 
/*
Problem: Cold-puter Science - https://open.kattis.com/problems/cold
Author: Emil Säll
The code is written in C++ and is using the Google C++ style guide.
*/
import java.util.*;
public class coldputerscience{
  public static void main(String[] args){
    Scanner in = new Scanner(System.in);
    int n = in.nextInt();
    int count = 0;
    for(int i = 0; i < n; i++){
      int x = in.nextInt();
      if(x < 0){
        count++;
      }
    }

    System.out.println(count);
  }
}

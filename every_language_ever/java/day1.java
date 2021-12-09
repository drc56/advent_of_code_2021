import java.util.*;
import java.io.File;
import java.io.FileNotFoundException;
import java.lang.Integer;

public class Day1AdventCode {

    public static void main(String[] args) {
        // Prints "Hello, World" to the terminal window.
        System.out.println("Hello, World");
        try {
            Scanner scanner = new Scanner(new File("input.txt"));
            boolean have_first_val = false;
            int prev = 0;
            int total_increases = 0;
            while(scanner.hasNextLine()){
                String line = scanner.nextLine();
                int cur = Integer.parseInt(line);
                if(have_first_val){
                    if(cur > prev){
                        total_increases++;
                    }
                }
                else{   
                    have_first_val = true;  
                }
                prev = cur;
            }
            System.out.println(total_increases);
        } catch (FileNotFoundException ex) {
            System.out.println("did you forget to put the file there dumbass?");
        }

    }

}
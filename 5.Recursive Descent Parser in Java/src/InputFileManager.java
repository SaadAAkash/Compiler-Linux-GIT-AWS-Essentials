import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;


public class InputFileManager {

	FileReader input = null;
    PrintWriter output = null;
    
	public InputFileManager()
    {
    	try{
    		input = new FileReader("input.txt");
       }
       catch(FileNotFoundException ex){
            System.out.println("no inp file");
       }
        
    	//Scanner inp = new Scanner(System.in);
    	Scanner inpp = new Scanner( input );
        
	    try
	    {
	    	output = new PrintWriter("output.txt", "UTF-8");
	        
	    } catch (IOException e) 
	    {
	        System.out.println("no output.");
	    }  
    }
}

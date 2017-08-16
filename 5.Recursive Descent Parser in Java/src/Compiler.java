import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayDeque;
import java.util.Queue;
import java.util.Scanner;

/*
 * grammer:
 * goal -> expr
 * expr -> term expr2
 * expr2 -> + term expr2 | - term expr2 | E
 * term -> fact term2
 * term2 -> * fact term2 | / fact term2 | E
 * fact -> num | id | (expr)
 */
/*********************************
	IF NOT EPSILON
********************/

public class Compiler 
{
	FileReader input = null;
    PrintWriter output = null;
    
    ///////////
    Queue<String> myQueue = new ArrayDeque<>();
    ///////////
    
    char test,tok;
    String str1, str2, S, S1, S2;
    char[] charArr;
    int level, position, step;
    
    Compiler()
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
    
	//while( inpp.hasNextLine() ) 
    while( inpp.hasNextLine() )
    {
    	S = inpp.nextLine();
        S= S.replaceAll("\\s+","");
        ///////////////////
        output.println("Taken input from file : " + S);
        output.println("Generated output :");
        ///////////////////
        
        charArr = S.toCharArray();
        
        position = 0; level = 0; step = 0;
        
        tok = moveCursor();
        
        step++;
        
        myQueue.add("Step "+level+" : goal -> expr with token '"+tok+"'");
        
        // 1st ta goal -> expr 
        if(expr(level) == true && tok == 0)
        {
            printAll();
            myQueue.clear();
            output.println();
            output.println("\n*************Success!****************\n");
            //output.println("Steps:"+step+"\n");
            output.println();
        }
        else 
        {
            if(tok != 0)
            {
                myQueue.clear();
                output.println("\n No other produ left! \n");
                output.println();
            }
            else
            {
                myQueue.clear();
                output.println("\n Failure! \n");
                output.println();
            }
        }
    }
    output.close();

    }
/////////////////////////////////////////
    char moveCursor()
    {
        char temp1;
        if(position< charArr.length)
        {
        	temp1 = charArr[ position ];
        	position++;
        }
        
        else
        {
        	temp1 = 0;
        }
            return temp1;
    }
  ////////////////////////////////////
    boolean expr(int level2)
    {
        level2++;
        String indent = "";
        /////
        step++; //this is also a step of process 
        /////
        for(int m = level2 ; m>0 ; m-- )
        {
            indent = indent+'\t';
        }
        myQueue.add(indent+"Step no. "+level2+" : expr -> term expr2. The Processing token is: '"+tok+"'");
        if( term(level2) && expr2(level2))
        {
            return true;
        }
        else
        {
            output.println("Didn't execute this step: "+level2+" : Here, production expr -> term expr2 not matched");
            return false;
        }
            
        
    }
    /////////////////////////////////////////
    void printAll()
    {
        String answer = null;
        while(!myQueue.isEmpty())
        {
        	answer = myQueue.poll();
            output.println( answer );
        }
    }
    /////////////////////////////////////////
    boolean expr2(int steps)
    {
       step++;
       steps++;
       /*********************************
       	IF NOT EPSILON
       ********************/
       if(tok == '+' || tok == '-')
       {
            if(tok == '+')
            {
                String indent = "";
                for(int m = steps ; m>0 ; m-- )
                {
                    indent = indent+'\t';
                }
                myQueue.add(indent+"Step "+steps+" : expr2 -> + term expr2. The Processing token is: '"+tok+"'");
            }
                
            else if (tok == '-')
            {
                String indent = "";
                for(int m = steps ; m>0 ; m-- )
                {
                    indent = indent+'\t';
                }
                myQueue.add(indent+"Step "+steps+" : expr2 -> - term expr2. The Processing token is: '"+tok+"'");
            }
           tok = moveCursor();
                   
           if(term(steps))
           {
               return expr2(steps);
           }
           else 
               return false;
       }
       
       //EPSILON
       
       else
       {
            String indent = "";
            for(int m = steps ; m>0 ; m-- )
            {
                indent = indent+'\t';
            }
            myQueue.add(indent+"Step "+steps+" : expr2 -> E. The Processing token is: 'eps'");
            return true;
       }
   }
  // term -> fact term2
   boolean term(int steps)
   {
       step++;
        steps++;
        String indent = "";
        for(int m = steps ; m>0 ; m-- )
        {
            indent = indent+'\t';
        }
        myQueue.add(indent+"Step "+steps+" : term -> factor term2. The Processing token is: '"+tok+"'");
        if( isFact(steps) && term2(steps))
        { 
           return true;
        }
       else
       {
           output.println("Failed at step "+steps+" : production term -> factor term2 mismatched");
           return false;
       }
   }
  ////////////////////////////
    boolean term2(int steps)
   {
       step++;
       steps++;
       /*********************************
   		IF NOT EPSILON
        ********************/
       if(tok == '*' || tok == '/')
       {
            if(tok == '*')
            {
                String indent = "";
                for(int m = steps ; m>0 ; m-- )
                {
                    indent = indent+'\t';
                }
                myQueue.add(indent+"Step "+steps+" : term2 -> * factor term2. The Processing token is: "+tok);
            }
            else if (tok == '/')
            {
                String indent = "";
                for(int m = steps ; m>0 ; m-- )
                {
                    indent = indent+'\t';
                }
                myQueue.add(indent+"Step "+steps+" : expr2 -> - / factor term2. The Processing token is: '"+tok+"'");
            }
           tok = moveCursor();
           if( isFact(steps) )
           {
               return term2(steps);
           }
           else 
               return false;
       }
       /*********************************
   		IF EPSILON
        ********************/
       else
       {    
            String indent = "";
            for(int m = steps ; m>0 ; m-- )
            {
                indent = indent+'\t';
            }
            myQueue.add(indent+"Step "+steps+" : term2 ->E. The Processing token is: 'eps'");
            return true;
       }
   }
   ///////////////////////////
   boolean isFact(int steps)
   {
	   /***********************
	   		GRAM for isFact:
		   	fact -> num | id | (expr)
	    ******************************/
	   step++;
       steps++;
       boolean isNum = false;
       boolean isId = false;
       if(tok == '(')
       {
            String indent = "";
            for(int m = steps ; m>0 ; m-- )
            {
                indent = indent+'\t';
            }
            myQueue.add(indent+"Step "+steps+" : factor -> ( expr ). The Processing token is:'"+tok+"'");
            tok = moveCursor();
            if(expr(steps) && tok == ')' )
            {
                tok = moveCursor();
                return true;
            }
            else
            {
               output.println("(-) problem here! "+steps);
               return false;
           }
       }
       
        if( (tok >= '0' && tok <= '9') || (tok >= 'A' && tok <= 'Z') || (tok >= 'a' && tok <= 'z') )
        {
            if((tok >= '0' && tok <= '9'))
            {
                String indent = "";
                for(int m = steps ; m>0 ; m-- )
                {
                    indent = indent+'\t';
                }
                myQueue.add(indent+"Step "+steps+" : factor -> number with token '"+tok+"'");
                tok = moveCursor();
                isNum = true;
                return true;
            }
            else if((tok >= 'a' && tok <= 'z')  || (tok >= 'A' && tok <= 'Z'))
            {
                String indent = "";
                for(int m = steps ; m>0 ; m-- )
                {
                    indent = indent+'\t';
                }
                myQueue.add(indent+"Step "+steps+" : factor -> id with token '"+tok+"'");
                tok = moveCursor();
                isId = true;
                return true;
            }
        }

        else
        {
            if(isNum)
                output.println("Number Error here! Step is :"+steps+" factor -> number. The processing token is: '"+tok+"' .");
            else if(isId)
                output.println("Id char error here! Step is :"+steps+" factor -> id with token '"+tok+"' Illigal Character");
        }
        return false;
           
   }
   //////////////////////////////
    public static void main(String[] args) 
    {
        Compiler comp = new Compiler();
    }
    
}
/*
 * (A+ B)
A+5
5 + (5+c)* 6
((((A+B)()))
AA
A))
( 9 * &
(1 + 5 * (e /9))
1* 3
*/

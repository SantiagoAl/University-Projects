// Alex Santiago
// Created June 11, 2019

// Practicing something with the StringBuilder for the Pathfinder assignment

import java.util.*;
import java.io.*;

public class Practice
{
    private static final char depth = 'd';
    private static final char width = 'u';
    
    public void printStringBuilder()
    {
        StringBuilder name = new StringBuilder();
        
        int kid = 5;
        int friend = kid + 1;
        
        if (friend != kid)
        {
            name.append((friend > 0) ? depth : width);
            System.out.println(name);
        }
        else
        {
            System.out.println("hey");
        }
    }
    
    public static void main(String [] args)
    {
        Practice g = new Practice();
        
        g.printStringBuilder();
    }
}

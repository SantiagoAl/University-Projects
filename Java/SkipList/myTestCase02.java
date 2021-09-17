// Alex Santiago
// Created June 27, 2019

// I am creating this test case so I can do some empirical runtime analysis on my
// insertion method for the SkipList programming assignment, which should turn out to
// be O(logn)

import java.io.*;
import java.util.*;

public class myTestCase02
{
    public static void main(String [] args)
    {
        SkipList<Integer> list = new SkipList<Integer>();
        
        if (args.length < 1)
        {
            System.out.println("Provide command line arguments");
            System.exit(1);
        }
        
        int n = Integer.parseInt(args[0]);
        long totalTime = 0, start, end;
        
        start = System.nanoTime();
        
        for (int i = 0; i < n; i++)
        {
            list.insert(RNG.getUniqueRandomInteger());
        }
        
        end = System.nanoTime();
        
        RNG.clear();
        
        totalTime += end - start;
        
        System.out.println("n = " + n + " T(n) = " + totalTime / 1e9);
    }
}

// Alex Santiago
// COP 3503, Summer 2019
// NID: al625608

// This my final solution for SneakyKnights, programming assignment #3

import java.io.*;
import java.util.*;
import java.awt.Point;

public class SneakyKnights
{
    // The method that will determine if all the Knights placed on the chess board
    // are safe, taking a list containing the Knight's coordinates and the boardsize
    // as parameters
    public static boolean allTheKnightsAreSafe(ArrayList<String> coordinateStrings,
                                               int boardSize)
    {
        // This will calculate the initial capacity of the HashSet. Insuring that it
        // will be at least 75% larger than the number of Knights, making it prime if
        // it is even and minimizing the amount of expansions the HashSet will perform
        int capacity = (int) (coordinateStrings.size() / .70);
        
        if ((capacity % 2) == 0)
        {
            capacity += 1;
        }
        
        // Where I will Hash the Point objects, with an intial size of 'capacity'
        HashSet<Point> list = new HashSet<>(capacity);
        
        // This array will contain the column and row values of each knight
        int [] locationArray = new int[2];
        
        for (int i = 0; i < coordinateStrings.size(); i++)
        {
            // Send the Knight's location to be broken up and return the column
            // and row to the locationArray
            getKnightsLocation(coordinateStrings.get(i), locationArray);
            
            // This variable will hold the truth value of an attack
            boolean attackTruth;
            
            int columnValue = locationArray[0];
            int rowValue = locationArray[1];
            
            // Here I hash the position of the Knight to the HashSet, to then check
            // it against attack positions
            list.add(new Point(columnValue, rowValue));
            
            // Determine if the current Knight can attack another Knight. It will
            // return true if it cannot, false otherwise
            attackTruth = checkAttacks(list, columnValue, rowValue, boardSize);
            
            // If the knight can attack another knight, immediately break out and
            // and return false
            if (!attackTruth)
            {
                return false;
            }
        }
        
        return true;
    }
    
    // This is a helper method that determines the positions that the knight can
    // attack, checking if there is another knight at those positions. Taking a
    // HashSet, coordinates of the Knight and the boardSize as parameters
    private static boolean checkAttacks(HashSet<Point> list, int column, int row,
                                    int boardSize)
    {
        // The following two arrays are all of the possible moves that the Knight
        // can make. They will move the Knights row and column coordinates
        int [] X = {2, 1, -2, -1, 2, 1, -2, -1};
        int [] Y = {1, 2, -1, -2, -1, -2, 1, 2};
        
        int columnOfAttack = 0, rowOfAttack = 0;
        
        // Loop through the two arrays. Before making the move I determine if the
        // move is valid, i.e it does not go off the board.
        for (int i = 0; i < 8; i++)
        {
            if ((boardSize - column >= X[i]) && (column + X[i] > 0))
            {
                columnOfAttack = column + X[i];
            }
            else
            {
                continue;
            }
            
            if ((boardSize - row >= Y[i]) && (row + Y[i] > 0))
            {
                rowOfAttack = row + Y[i];
            }
            else
            {
                continue;
            }
            
            // If the HashSet contains this point, there is a Knight there and the
            // current Knight can atttack it. Return false
            if (list.contains(new Point(columnOfAttack, rowOfAttack)))
            {
                return false;
            }
        }
        
        return true;
    }
    
    // This is a helper method that will return our Knights location
    private static void getKnightsLocation(String location, int [] array)
    {
        StringBuilder rowLocation = new StringBuilder();
        int columnValue = 0;
        
        // Loop through the String, turn the first part of the String into the
        // column location and put the row location into the StringBuilder
        for (int i = 0; i < location.length(); i++)
        {
            if (location.charAt(i) >= 'a' && location.charAt(i) <= 'z')
            {
                columnValue = columnValue * 26 + (location.charAt(i) - ('a' - 1));
            }
            else
            {
                rowLocation.append(location.charAt(i));
            }
        }
        
        array[0] = columnValue;
        array[1] = Integer.parseInt(rowLocation.toString()); // Parse row value
    }
    
    // How difficult I found the assignment to be
    public static double difficultyRating()
    {
        return 3.0;
    }
    
    // The estimated amount of hours I spent on the assignment
    public static double hoursSpent()
    {
        return 15.0;
    }
}

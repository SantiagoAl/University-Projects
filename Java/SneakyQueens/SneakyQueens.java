// Alex Santiago
// COP 3503, Summer 2019
// NID: al625608
//
// This is my final solution for SneakyQueens programming assignment #1

import java.io.*;
import java.util.*;

public class SneakyQueens
{
    // The method called that will determine if all Queens placed on the chess
    // board are safe from an attack
    public static boolean allTheQueensAreSafe(ArrayList<String> coordinateStrings,
                                              int boardSize)
    {
        // These two arrays represent the rows and columns of the chess board
        boolean [] rowArray = new boolean[boardSize];
        boolean [] columnArray = new boolean[boardSize];
        
        // The upDiagonalArray is representing the diagonals on the chess board
        // going from left to right, while the downDiagonalArray is representing
        // the diagonals on the chess board going from right to left
        boolean [] upDiagonalArray = new boolean[boardSize * 2];
        boolean [] downDiagonalArray = new boolean[boardSize * 2];
        
        // Array to store column and row values
        int [] locationArray = new int[2];
        
        // Here the ArrayList is traversed iteratively and the Queens will be
        // placed on the board while also checking if it can attack another
        // Queen
        for (String queenLocation : coordinateStrings)
        {
            // Send the Queens location to be broken up and return the column
            // and row to the locationArray
            getQueensLocation(queenLocation, locationArray);
            
            int columnLocation = locationArray[0];
            int rowLocation = locationArray[1];
            
            // Checking the rowArray, if there is nothing there, that index will
            // be flipped to true indicating there is now a Queen in that row.
            if (rowArray[rowLocation - 1] == false)
            {
                rowArray[rowLocation - 1] = true;
            }
            else
            {
                return false;
            }
            
            // Checking the columnArray. This effectively does the same thing as
            // the rowArray above
            if (columnArray[columnLocation - 1] == false)
            {
                columnArray[columnLocation - 1] = true;
            }
            else
            {
                return false;
            }
            
            int leftRightDiagonal;
            
            // If row is <= column the Queen will be in the bottom right half of
            // the chess board, if not it will be in the upper left half
            if (rowLocation <= columnLocation)
            {
                leftRightDiagonal = (columnLocation - rowLocation) % boardSize;
            }
            else
            {
                leftRightDiagonal = rowLocation - columnLocation +
                                    boardSize - 1;
            }
            
            // This equation gets the diagonal positioning of the Queen going
            // from right to left
            int rightLeftDiagonal = columnLocation + rowLocation - 2;
            
            // The proceeding if statements check both diagonals array, if there
            // is no Queens in that diagonal, it will now be flipped to true
            // indicating that there is now a Queen in that digonal
            if (upDiagonalArray[leftRightDiagonal] == false)
            {
                upDiagonalArray[leftRightDiagonal] = true;
            }
            else
            {
                return false;
            }
            
            if (downDiagonalArray[rightLeftDiagonal] == false)
            {
                downDiagonalArray[rightLeftDiagonal] = true;
            }
            else
            {
                return false;
            }
        }
        
        // If the program reaches this point all the Queens are safe
        return true;
    }
    
    // This is a helper method that will return our Queens location
    private static void getQueensLocation(String location, int [] array)
    {
        StringBuilder rowLocation = new StringBuilder();
        int columnValue = 0;
        
        // Loop through the String, turn the first part of the String into the
        // column location and put the row location into the StringBuilder
        for (int i = 0; i < location.length(); i++)
        {
            if (location.charAt(i) >= 'a' && location.charAt(i) <= 'z')
            {
                columnValue = columnValue * 26 +
                              (location.charAt(i) - ('a' - 1));
            }
            else
            {
                rowLocation.append(location.charAt(i));
            }
        }
        
        array[0] = columnValue;
        array[1] = Integer.parseInt(rowLocation.toString()); // Parse row value
    }
    
    // How hard I believe the assignment was
    public static double difficultyRating()
    {
        return 3.0;
    }
    
    // The hours I spent on the assignment
    public static double hoursSpent()
    {
        return 16.0;
    }
}

// Alex Santiago
// COP 3503, Summer 2019
// NID: al625608

// This is final solution to programming assignment #6 Pathfinder

// As per the assignment, this code has been modified to find all possible paths to
// an exit in a maze

// The credit for the overwhelming majority of the code goes to Dr. Szumlanski

import java.io.*;
import java.util.*;

public class Pathfinder
{
	// Used to toggle "animated" output on and off (for debugging purposes).
	private static boolean animationEnabled = false;

	// "Animation" rate (frames per second).
	private static double frameRate = 4.0;
	
	// These are setters. You enable and disable the animation when debugging, and
	// set the frame rate for the animation i.e how long you want it to wait
	public static void enableAnimation() { Pathfinder.animationEnabled = true; }
	public static void disableAnimation() { Pathfinder.animationEnabled = false; }
	public static void setFrameRate(double fps) { Pathfinder.frameRate = frameRate; }

	// Maze constants.
	private static final char WALL       = '#';
	private static final char PERSON     = '@';
	private static final char EXIT       = 'e';
	private static final char BREADCRUMB = '.';  // visited
	private static final char SPACE      = ' ';  // unvisited
	
	private static final char DOWN       = 'd';
	private static final char UP         = 'u';
	private static final char LEFT       = 'l';
	private static final char RIGHT      = 'r';
	
	// This method takes a maze represented as a 2D char array and returns a HashSet
	// containing all possible paths to the exit in the maze. It assumes the maze is
	// well constructed
	public static HashSet<String> findPaths(char [][] maze)
	{
		int height = maze.length;
		int width = maze[0].length;
		
		// The visited array keeps track of visited positions, but it also will keep
		// track of the exit so it can be detected when it is reached, as it will be
		// overwritten with the '@' in the maze
		char [][] visited = new char[height][width];
		for (int i = 0; i < height; i++)
			Arrays.fill(visited[i], SPACE);

		// Find starting position (location of the '@' character).
		int startRow = -1;
		int startCol = -1;

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (maze[i][j] == PERSON)
				{
					startRow = i;
					startCol = j;
				}
			}
		}
		
		// A HashSet that contains all possible paths to the exit and an ArrayList to
		// hold the path as it is being constructed
		HashSet<String> path = new HashSet<String>();
		ArrayList<Character> directionList = new ArrayList<>();
		
		// Call the overloaded findPaths method to do the heavy lifting
		findPaths(maze, visited, startRow, startCol, height, width, path,
				  directionList);
		
		return path;
	}

	// The overloaded findPaths method that determines all possible paths to an exit
	// in a maze and returns them in a HashSet
	private static void findPaths(char [][] maze, char [][] visited,
								int currentRow, int currentCol, int height,
								int width, HashSet<String> path,
								ArrayList<Character> directionList)
	{
		// This conditional block prints the maze when a new move is made.
		if (Pathfinder.animationEnabled)
		{
			printAndWait(maze, height, width, "Searching...", Pathfinder.frameRate);
		}

		// We have found the exit
		if (visited[currentRow][currentCol] == 'e')
		{
			if (Pathfinder.animationEnabled)
			{
				for (int i = 0; i < 3; i++)
				{
					maze[currentRow][currentCol] = '*';
					printAndWait(maze, height, width, "Hooray!", Pathfinder.frameRate);

					maze[currentRow][currentCol] = PERSON;
					printAndWait(maze, height, width, "Hooray!", Pathfinder.frameRate);
				}
			}
			
			maze[currentRow][currentCol] = EXIT;
			
			// Create a StringBuilder once the exit is found
			StringBuilder pathOfPerson = new StringBuilder();
			
			// Append the path that has been constructed in the ArrayList to the end
			// of the StringBuilder
			for (int i = 0; i < directionList.size(); i++)
			{
				if (i == directionList.size() - 1)
					pathOfPerson.append(directionList.get(i));
				else
					pathOfPerson.append(directionList.get(i) + " ");
			}
			
			// Add the path to the HashSet
			path.add(pathOfPerson.toString());
			
			return;
		}

		// Moves: left, right, up, down
		int [][] moves = new int[][] {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

		for (int i = 0; i < moves.length; i++)
		{
			int newRow = currentRow + moves[i][0];
			int newCol = currentCol + moves[i][1];

			// Check move is in bounds, not a wall, and not marked as visited.
			if (!isLegalMove(maze, visited, newRow, newCol, height, width))
				continue;
			
			// Here we determine in what direction the person moved in the maze,
			// whether it be in horizontal or vertical direction
			int verticalDirection = currentRow - newRow;
			int horizontalDirection = currentCol - newCol;
			
			// Assign the correct movements depending on the direction of the person
			// and insert them in the Character ArrayList
			if (verticalDirection != 0)
				directionList.add((verticalDirection > 0) ? UP : DOWN);
			
			if (horizontalDirection != 0)
				directionList.add((horizontalDirection > 0) ? LEFT : RIGHT);
			
			// Before the person moves forward in the maze, we need to check if the
			// exit is being overwritten, if so we will save the exit in the visited
			// array
			if (maze[newRow][newCol] == EXIT)
				visited[newRow][newCol] = EXIT;

			maze[currentRow][currentCol] = BREADCRUMB;
			visited[currentRow][currentCol] = BREADCRUMB;
			maze[newRow][newCol] = PERSON;

			// Perform recursive descent.
			findPaths(maze, visited, newRow, newCol, height, width, path,
					  directionList);
			
			// Undo any state changes. The key is to insert a space in the visited
			// array at the current location to be able to generate all possible
			// paths. Leave 'e' in the visited array so that it can be detected
			if (maze[newRow][newCol] == EXIT)
				;
			else
				maze[newRow][newCol] = SPACE;
			
			visited[currentRow][currentCol] = SPACE;
			maze[currentRow][currentCol] = PERSON;
			directionList.remove(directionList.size() - 1);
			
			// This conditional block prints the maze when a move gets undone
			// (which is effectively another kind of move).
			if (Pathfinder.animationEnabled)
			{
				printAndWait(maze, height, width, "Backtracking...", frameRate);
			}
		}
		
		return;
	}

	// Returns true if moving to row and col is legal (i.e., we have not visited
	// that position before, and it's not a wall).
	private static boolean isLegalMove(char [][] maze, char [][] visited,
	                                   int row, int col, int height, int width)
	{
		int numColumns = maze[0].length;
		int numRows = maze.length;
		
		// First ensure that the person does not fall off of the maze
		if (col >= numColumns || row >= numRows || col < 0 || row < 0)
			return false;
		
		if (maze[row][col] == WALL || visited[row][col] == BREADCRUMB)
			return false;

		return true;
	}

	// This effectively pauses the program for waitTimeInSeconds seconds.
	private static void wait(double waitTimeInSeconds)
	{
		long startTime = System.nanoTime();
		long endTime = startTime + (long)(waitTimeInSeconds * 1e9);

		while (System.nanoTime() < endTime)
			;
	}

	// Prints maze and waits. frameRate is given in frames per second.
	private static void printAndWait(char [][] maze, int height, int width,
	                                 String header, double frameRate)
	{
		if (header != null && !header.equals(""))
			System.out.println(header);

		if (height < 1 || width < 1)
			return;

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				System.out.print(maze[i][j]);
			}

			System.out.println();
		}

		System.out.println();
		wait(1.0 / frameRate);
	}

	// Read maze from file. This function dangerously assumes the input file
	// exists and is well formatted according to the specification above.
	private static char [][] readMaze(String filename) throws IOException
	{
		Scanner in = new Scanner(new File(filename));

		int height = in.nextInt();
		int width = in.nextInt();

		char [][] maze = new char[height][];

		// After reading the integers, there's still a new line character we
		// need to do away with before we can continue.

		in.nextLine();

		for (int i = 0; i < height; i++)
		{
			// Explode out each line from the input file into a char array.
			maze[i] = in.nextLine().toCharArray();
		}

		return maze;
	}
	
	// How difficult I found the assignment to be
	public static double difficultyRating()
	{
		return 3.0;
	}
	
	// The estimated amount of hours I spent on the program
	public static double hoursSpent()
	{
		return 5.0;
	}
}

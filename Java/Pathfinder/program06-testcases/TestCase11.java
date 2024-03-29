// Sean Szumlanski
// COP 3503, Summer 2019

// ===========================
// Pathfinder: TestCase11.java
// ===========================
// Checks paths through maze11.txt. This test case also checks paths through
// maze01.txt, partly to determine whether the findPaths() methods works when
// called multiple times in a single test case, but also to ensure credit is
// not awarded if the pathFinder simply returns an empty set in all cases.
// (Indeed, there are no paths through maze11.txt.)


import java.io.*;
import java.util.*;

public class TestCase11
{
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

	// Read solution strings (representing paths through the maze) from input
	// file and return HashSet containing all such strings.
	private static HashSet<String> readSolutions(String filename) throws IOException
	{
		Scanner in = new Scanner(new File(filename));
		HashSet<String> solutions = new HashSet<>();

		while (in.hasNextLine())
			solutions.add(in.nextLine());

		return solutions;
	}

	private static void singleTest(String mazeFilename, String pathsFilename) throws IOException
	{
		// Load maze and solution paths from file.
		char [][] maze = readMaze(mazeFilename);
		HashSet<String> solutionPaths = readSolutions(pathsFilename);

		// Call backtracking algorithm to find all paths through maze.
		Pathfinder.disableAnimation();
		HashSet<String> yourPaths = Pathfinder.findPaths(maze);

		// Check for success. Print set contents if sets differ.
		if (yourPaths.equals(solutionPaths))
		{
			System.out.println("Hooray! Found " + yourPaths.size() + " distinct path(s)!");
		}
		else
		{
			System.out.println("Whoops! Those string sets differ!");

			System.out.println();

			System.out.println("======================");
			System.out.println("Expected Path Strings:");
			System.out.println("======================");
			for (String s : solutionPaths)
				System.out.println(s);

			System.out.println();

			System.out.println("======================");
			System.out.println("Returned Path Strings:");
			System.out.println("======================");
			for (String s : yourPaths)
				System.out.println(s);

			System.out.println();
		}
	}

	public static void main(String [] args) throws IOException
	{
		singleTest("input_files/maze03.txt", "input_files/maze03-all-paths.txt");
		singleTest("input_files/maze11.txt", "input_files/maze06-all-paths.txt");
		singleTest("input_files/maze03.txt", "input_files/maze03-all-paths.txt");
	}
}

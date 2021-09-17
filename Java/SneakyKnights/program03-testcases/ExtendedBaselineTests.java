// Sean Szumlanski
// COP 3503, Summer 2019

// =========================================
// SneakyKnights: ExtendedBaselineTests.java
// =========================================
// A suite of small tests to ensure allTheKnightsAreSafe() is not just returning
// the same value no matter what the test case is. Each large test case must
// pass these smaller test cases in order to receive credit. These are also
// designed to ensure that everyone is creating and testing small test cases in
// addition to the ones released with each assignment.
//
// This is an extension of BaselineTests.java. It includes four additional test
// cases on smaller boards, ranging from 1x1 through 3x3.


import java.io.*;
import java.util.*;

public class ExtendedBaselineTests
{
	private static boolean checkTest(boolean success)
	{
		return success;
	}

	private static boolean checkTestFromFile(String filename, boolean expectedResult)
		throws FileNotFoundException
	{
		Scanner in = new Scanner(new File("input_files/" + filename));
		ArrayList<String> list = new ArrayList<String>();

		// For these test cases, we assume the first line in the input file is the
		// board size. I'm using parseInt() here because if you try to mix calls to
		// nextInt() and next() when dealing with a Scanner, it can cause some
		// weirdness with end-of-line characters not being consumed as expected.
		int boardSize = Integer.parseInt(in.next());

		// Read each line from the input file into the ArrayList.
		while (in.hasNext())
			list.add(in.next());

		boolean success = true;

		for (int i = 0; i < 5; i++)
		{
			Collections.shuffle(list);
			success &= checkTest(SneakyKnights.allTheKnightsAreSafe(list, boardSize) == expectedResult);
		}

		if (!success)
			System.out.println("Failing on extended baseline test: " + filename);

		return success;
	}

	public static boolean runExtendedBaselineTests() throws FileNotFoundException
	{
		boolean success = BaselineTests.runBaselineTests();

		success &= checkTestFromFile("baseline09.txt", true);   // tests with a 1x1 board
		success &= checkTestFromFile("baseline10.txt", true);   // tests with a 2x2 board
		success &= checkTestFromFile("baseline11.txt", true);   // tests with a 3x3 board
		success &= checkTestFromFile("baseline12.txt", false);  // tests with a 3x3 board

		System.out.println((success ? "Passes" : "Fails") + " extended baseline tests.");

		return success;
	}

	public static void main(String [] args) throws FileNotFoundException
	{
		runExtendedBaselineTests();
	}
}

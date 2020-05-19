// Sean Szumlanski
// COP 3503, Summer 2019

// ==============================
// SneakyKnights: TestCase20.java
// ==============================
// A very large test case. All the knights are safe.

import java.io.*;
import java.util.*;

public class TestCase20
{
	private static void checkTest(boolean success)
	{
		System.out.println(success ? "Hooray!" : "fail whale :(");
	}

	public static void main(String [] args) throws Exception
	{
		// This ensures that allTheKnightsAreSafe() isn't a one-liner that just
		// always returns the same value in an attempt to pass a few test cases
		// for free. It is also designed to ensure that everyone is creating and
		// testing small test cases in addition to the ones released with each
		// assignment.
		ExtendedBaselineTests.runExtendedBaselineTests();

		Scanner in = new Scanner(new File("input_files/TestCase20-input.txt"));
		ArrayList<String> list = new ArrayList<String>();

		// Read each line from the input file into the ArrayList.
		while (in.hasNext())
			list.add(in.next());

		int boardSize;
		checkTest(SneakyKnights.allTheKnightsAreSafe(list, boardSize = Integer.MAX_VALUE) == true);
	}
}

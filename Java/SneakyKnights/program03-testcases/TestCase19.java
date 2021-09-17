// Sean Szumlanski
// COP 3503, Summer 2019

// ==============================
// SneakyKnights: TestCase19.java
// ==============================
// A very large test case. There are at two knights that can attack one another,
// one of which is at fketxdi160341859.


import java.io.*;
import java.util.*;

public class TestCase19
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

		Scanner in = new Scanner(new File("input_files/TestCase19-input.txt"));
		ArrayList<String> list = new ArrayList<String>();

		// Read each line from the input file into the ArrayList.
		while (in.hasNext())
			list.add(in.next());

		int boardSize;
		checkTest(SneakyKnights.allTheKnightsAreSafe(list, boardSize = Integer.MAX_VALUE) == false);
	}
}

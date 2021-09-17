// Sean Szumlanski
// COP 3503, Summer 2019

// =========================
// SneakyKnights: Bonus.java
// =========================
// A very large test case in which the first two knights can attack one another,
// and points are only awarded if the test case terminates very quickly. The
// idea here is that you could return 'false' as soon as you see two knights
// that can attack one another, so a very efficient implementation of
// allTheKnightsAreSafe() will have a best-case runtime of O(1).


import java.io.*;
import java.util.*;

public class Bonus
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

		Scanner in = new Scanner(new File("input_files/Bonus-input.txt"));
		ArrayList<String> list = new ArrayList<String>();

		// Read each line from the input file into the ArrayList.
		while (in.hasNext())
			list.add(in.next());

		int boardSize;
		long start = System.nanoTime();
		checkTest(SneakyKnights.allTheKnightsAreSafe(list, boardSize = Integer.MAX_VALUE) == false);
		long end = System.nanoTime();

		long reasonableRuntime = 500000;
		if (end - start > reasonableRuntime)
			System.out.println("Runtime exceeds limit. Too slow. :(");
		else
			System.out.println("Ooooh, that was super quick, like a ninja!");
	}
}

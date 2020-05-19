// Sean Szumlanski
// COP 3503, Summer 2019

// =========================
// SkipList: TestCase06.java
// =========================
// Insert lots of values, then search for a value. Check that the search runtime
// is very fast.


import java.io.*;
import java.util.*;

public class TestCase06
{
	public static void main(String [] args)
	{
		SkipList<Integer> skiplist = new SkipList<Integer>();

		// Insert lots of elements. This will take a while.
		for (int i = 0; i < 1000000; i++)
			skiplist.insert(RNG.getUniqueRandomInteger());

		long totalTime = 0, start, end, total;

		// Time how long it takes to search for an integer that is in the skip list.
		int used = RNG.getRandomUsedInteger();
		start = System.nanoTime();
		boolean success = skiplist.contains(used);
		end = System.nanoTime();
		totalTime += (end - start);

		// Time how long it takes to search for an integer that is not in the skip list.
		int unused = RNG.getRandomUnusedInteger();
		start = System.nanoTime();
		success &= !skiplist.contains(unused);
		end = System.nanoTime();
		totalTime += (end - start);

		// Check that the total search time was reasonably fast (not linear search).
		// This time limit will be unreasonable on Eustis, but will probably be
		// reasonable on your own system.
		System.out.println((success && totalTime < 500000) ? "Hooray!" : "fail whale :(");
	}
}
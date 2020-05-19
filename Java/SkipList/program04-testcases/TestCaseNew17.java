// Sean Szumlanski
// COP 3503, Summer 2019

// ============================
// SkipList: TestCaseNew17.java
// ============================
// This is an adaptation of TestCase04.java. This one inserts a lot of unique
// random elements and then checks that approximately 2 of them have height 10
// (the tallest height possible).
//
// In this test case, no duplicates are inserted into the skip list.


import java.io.*;
import java.util.*;

public class TestCaseNew17
{
	// Check that the skiplist's size and height are as expected. If not, fail whale.
	private static void checkList(SkipList<Integer> s, int expectedSize, int expectedHeight)
	{
		if (s.size() != expectedSize || s.height() != expectedHeight)
		{
			System.out.println("fail whale :(");
			System.exit(0);
		}
	}

	public static void main(String [] args)
	{
		// Probabilistically speaking, this test should succeed within 10 attempts.
		for (int i = 0; i < 10; i++)
		{
			RNG.clear();
			int numElements = 1000;

			// Insert random values into a skiplist.
			SkipList<Integer> skiplist = new SkipList<Integer>();
			for (int j = 0; j < numElements; j++)
				skiplist.insert(RNG.getUniqueRandomInteger());

			// Skim the top level (the 10th level, which is at index 9), and
			// count the nodes there.
			int level = 9;
			Node<Integer> temp = skiplist.head().next(level);
			int count = 0;
			while (temp != null)
			{
				count++;
				temp = temp.next(level);
			}

			// We expect approximately 1.953125 elements at the top level, on
			// average. This comparison allows for the total to be off by one.
			// It's reasonable to expect this case to succeed within 10
			// iterations.
			int expectedCount = 2;
			if (Math.abs(expectedCount - count) <= 1)
			{
				System.out.println("Hooray!");
				return;
			}
		}

		System.out.println("fail whale :(");
	}
}

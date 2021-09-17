// Sean Szumlanski
// COP 3503, Summer 2019

// ============================
// SkipList: TestCaseNew20.java
// ============================
// This is an adaptation of TestCase04.java. This one inserts a lot of unique
// random elements and then checks that approximately 7.8125 of them have height
// 7, and approximately 15.625 of them can be reached via the 7th level of
// references (the level of references at index 6).
//
// In this test case, no duplicates are inserted into the skip list.


import java.io.*;
import java.util.*;

public class TestCaseNew20
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
		boolean goal1 = false;
		boolean goal2 = false;

		// Probabilistically speaking, this test should succeed within 20 attempts.
		for (int i = 0; i < 10; i++)
		{
			RNG.clear();
			int numElements = 1000;

			// Insert random values into a skiplist.
			SkipList<Integer> skiplist = new SkipList<Integer>();
			for (int j = 0; j < numElements; j++)
				skiplist.insert(RNG.getUniqueRandomInteger());

			// Skim the bottom level of the skip list (so we can see every
			// node), and see how many nodes have height 7.
			int level = 0;
			Node<Integer> temp = skiplist.head().next(level);
			int count = 0;
			while (temp != null)
			{
				if (temp.height() == 7)
					count++;

				temp = temp.next(level);
			}

			// We expect approximately 8 elements with height 7, on average.
			// This comparison allows for the total to be off by 1. It's
			// reasonable to expect this case to succeed within 20 iterations.
			int expectedCount = 8;
			if (Math.abs(expectedCount - count) <= 1)
			{
				goal1 = true;
			}

			// Skim the 7th level (which is at index 6) and count how many nodes
			// we hit. We expect to see that approximately 15.625 elements are
			// are touched on this level.
			level = 6;
			temp = skiplist.head().next(level);
			count = 0;
			while (temp != null)
			{
				count++;
				temp = temp.next(level);
			}

			expectedCount = 16;
			if (Math.abs(expectedCount - count) <= 3)
			{
				goal2 = true;
			}
		}

		if (goal1 && goal2)
			System.out.println("Hooray!");
		else
			System.out.println("fail whale :(");
	}
}

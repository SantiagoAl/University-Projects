// Sean Szumlanski
// COP 3503, Summer 2019

// ============================
// SkipList: TestCaseNew18.java
// ============================
// This is an adaptation of TestCase04.java. This one inserts a lot of unique
// random elements and then checks that approximately 125 of them have height 3.
//
// In this test case, no duplicates are inserted into the skip list.


import java.io.*;
import java.util.*;

public class TestCaseNew18
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

			// Skim the bottom level of the skip list (so we can see every
			// node), and see how many nodes have height 3.
			int level = 0;
			Node<Integer> temp = skiplist.head().next(level);
			int count = 0;
			while (temp != null)
			{
				if (temp.height() == 3)
					count++;

				temp = temp.next(level);
			}

			// We expect approximately 125 elements with height 3, on average.
			// This comparison allows for the total to be off by 10. It's
			// reasonable to expect this case to succeed within 10 iterations.
			int expectedCount = 125;
			if (Math.abs(expectedCount - count) <= 10)
			{
				System.out.println("Hooray!");
				return;
			}
		}

		System.out.println("fail whale :(");
	}
}

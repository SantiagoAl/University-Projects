// Sean Szumlanski
// COP 3503, Summer 2019

// ============================
// SkipList: TestCaseNew19.java
// ============================
// This is an adaptation of TestCase04.java. This one inserts a lot of unique
// random elements and then checks that approximately 250 are reachable via the
// third level of pointers in the skip list. (I.e., approximately 250 nodes
// should have height >= 3.)
//
// In this test case, no duplicates are inserted into the skip list.


import java.io.*;
import java.util.*;

public class TestCaseNew19
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

			// Skim the 3rd level (which is at index 2) and count how many nodes
			// we hit. We expect to see that approximately 1000 - 750 = 250
			// elements are touched on this level. (The 750 comes from the fact
			// that approximately 500 nodes should be height 1, and about 250
			// nodes should be height 2. Thus, we should hit all nodes except
			// for those as we traverse the third level of the skip list.)
			int level = 2;
			Node<Integer> temp = skiplist.head().next(level);
			int count = 0;
			while (temp != null)
			{
				count++;
				temp = temp.next(level);
			}

			int expectedCount = 250;
			if (Math.abs(expectedCount - count) <= 14)
			{
				System.out.println("Hooray!");
				return;
			}
		}

		System.out.println("fail whale :(");
	}
}

// Sean Szumlanski
// COP 3503, Summer 2019

// ======================
// SkipList: Bonus02.java
// ======================
// When inserting a new node causes the skip list to grow, it should be possible
// to manually specify that the height of the new node should be that new max
// height. This test case checks whether the insertion method allows and honors
// such a request. (This expected behavior was mentioned in response to a
// question on Webcourses, and was also discussed in a post to the Facebook
// group for the course.)


import java.io.*;
import java.util.*;

public class Bonus02
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
		RNG.setMaxRandomValue(1000);

		// This must succeed for all 15 iterations in order to receive credit.
		for (int i = 0; i < 15; i++)
		{
			// 'size' and 'height' variables are used to improve readability of
			// checkList() method calls.
			int size, height, r;
			SkipList<Integer> skiplist = new SkipList<Integer>();

			skiplist.insert(RNG.getUniqueRandomInteger());
			checkList(skiplist, size = 1, height = 1);

			skiplist.insert(RNG.getUniqueRandomInteger());
			checkList(skiplist, size = 2, height = 1);

			skiplist.insert(RNG.getUniqueRandomInteger());
			checkList(skiplist, size = 3, height = 2);

			skiplist.insert(RNG.getUniqueRandomInteger());
			checkList(skiplist, size = 4, height = 2);

			// This one causes the height to grow to 3. We'll check whether it
			// honors our request for the new node to be height 3, or if it
			// thinks that height is out of range. (The desired effect is that
			// it will honor our request for a node of that height.)
			skiplist.insert(r = RNG.getUniqueRandomInteger(), height = 3);
			checkList(skiplist, size = 5, height = 3);

			// Search skip list for the most recently inserted value, r.
			Node<Integer> temp = skiplist.head().next(0);
			while (temp.value() != r)
				temp = temp.next(0);

			// Check whether r has height 3.
			if (temp.height() != 3)
			{
				System.out.println("fail whale :(");
				return;
			}
		}

		System.out.println("Hooray!");
	}
}

// Sean Szumlanski
// COP 3503, Summer 2019

// ======================
// SkipList: Bonus01.java
// ======================
// This test case checks whether the manually specified height of a new node is
// honored, even when its insertion causes the skip list to grow. The height
// should be honored (preserved) even if it is/was 1 less than the new height of
// the skip list. (That is, the new node whose height was manually specified
// should not be subject to growth right when it is inserted.)


import java.io.*;
import java.util.*;

public class Bonus01
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
			// honors our request for the new node to be height 2, or if it
			// allows the new node to grow. (The desired effect is that it will
			// honor our request.)
			skiplist.insert(r = RNG.getUniqueRandomInteger(), height = 2);
			checkList(skiplist, size = 5, height = 3);

			// Search skip list for the most recently inserted value, r.
			Node<Integer> temp = skiplist.head().next(0);
			while (temp.value() != r)
				temp = temp.next(0);

			// Check whether r has height 2.
			if (temp.height() != 2)
			{
				System.out.println("fail whale :(");
				return;
			}
		}

		System.out.println("Hooray!");
	}
}

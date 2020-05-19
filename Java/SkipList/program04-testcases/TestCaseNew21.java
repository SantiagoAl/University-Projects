// Sean Szumlanski
// COP 3503, Summer 2019

// ============================
// SkipList: TestCaseNew21.java
// ============================
// Tests functionality of the SkipList class's get() method.


import java.io.*;
import java.util.*;

public class TestCaseNew21
{
	private static boolean referenceCheck(SkipList<Integer> s, int level, int [] values)
	{
		Node<Integer> temp = s.head();

		for (int i = 0; i < values.length; i++)
		{
			temp = temp.next(level);
			if (temp.value().compareTo(values[i]) != 0)
				return false;
		}

		// One final check to ensure this is the end of the list on this level.
		if (temp.next(level) == null)
		{
			System.out.println("Reference check: PASS");
			return true;
		}

		System.out.println("Reference check: fail whale :(");
		return false;
	}

	public static void main(String [] args)
	{
		SkipList<Integer> s = new SkipList<Integer>(3);

		s.insert(30, 3);
		s.insert(40, 1);
		s.insert(20, 1);
		s.insert(10, 2);
		s.insert(50, 2);

		// Verify each level of the skip list is connected as indicated.

		int level;
		boolean success = true;

		success &= referenceCheck(s, level = 0, new int [] {10, 20, 30, 40, 50});
		success &= referenceCheck(s, level = 1, new int [] {10, 30, 50});
		success &= referenceCheck(s, level = 2, new int [] {30});
		success &= referenceCheck(s, level = 3, new int [] {});

		// Now check that the get() method returns the correct result(s).
		Node<Integer> n;

		n = s.get(30);
		success &= (n != null && n.next(0).value() == 40 && n.next(1).value() == 50 && n.next(2) == null);

		success &= (s.get(5) == null);
		success &= (s.get(15) == null);
		success &= (s.get(25) == null);
		success &= (s.get(35) == null);
		success &= (s.get(45) == null);
		success &= (s.get(55) == null);

		System.out.println(success ? "Hooray!" : "fail whale :(");
	}
}

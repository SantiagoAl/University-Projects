// Sean Szumlanski
// COP 3503, Summer 2019

// ==============================
// SneakyKnights: TestCase03.java
// ==============================
// A series of small test cases. This merely combines the following test cases that were released
// with the assignment: TestCase03.java, TestCase04.java, and TestCase05.java.


import java.io.*;
import java.util.*;

public class TestCase03
{
	private static void checkTest(boolean success)
	{
		System.out.println(success ? "Hooray!" : "fail whale :(");
	}

	public static void main(String [] args) throws Exception
	{
		ArrayList<String> list = new ArrayList<String>();

		// This is from the TestCase03 that was released with the PDF.
		list.clear();
		list.add("a4");
		list.add("a3");
		list.add("a1");
		list.add("b4");
		list.add("c1");
		list.add("d1");
		list.add("d2");
		list.add("d4");

		for (int i = 0; i < 5; i++)
		{
			Collections.shuffle(list);
			checkTest(SneakyKnights.allTheKnightsAreSafe(list, 4) == true);
		}

		// This is from the TestCase04 that was released with the PDF.
		list.clear();
		list.add("e4");
		list.add("a1");
		list.add("b2");
		list.add("d4");
		list.add("b1");
		list.add("a5");
		list.add("e5");
		list.add("b4");
		list.add("c1");
		list.add("e3");

		for (int i = 0; i < 5; i++)
		{
			Collections.shuffle(list);
			checkTest(SneakyKnights.allTheKnightsAreSafe(list, 5) == true);
		}

		// This is from the TestCase05 that was released with the PDF.
		list.clear();
		list.add("b2");
		list.add("b1");
		list.add("h6");
		list.add("f1");
		list.add("g4");
		list.add("h8");
		list.add("j6");
		list.add("c10");

		for (int i = 0; i < 5; i++)
		{
			Collections.shuffle(list);
			checkTest(SneakyKnights.allTheKnightsAreSafe(list, 10) == false);
		}
	}
}

// Sean Szumlanski
// COP 3503, Summer 2019

// ==============================
// SneakyKnights: TestCase01.java
// ==============================
// Tests that difficultyRating() is implemented correctly.


import java.io.*;
import java.util.*;

public class TestCase01
{
	public static void main(String [] args)
	{
		double difficulty = SneakyKnights.difficultyRating();
		System.out.println((difficulty < 1.0 || difficulty > 5.0) ? "fail whale :(" : "Hooray!");
	}
}

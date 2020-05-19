// Alex Santiago
// Created May 28, 2019

// This program is a part of the testcases that I am creating for CS2 programming
// assignment #2, GenericBST.java. It is a class that implements Comparable, NOTE:
// that since this we are going to be inserting objects of Double there is no need to
// implement the compareTo() method and the toString() method

public class myTestCase02
{
    public static void checkTestCase(boolean success)
    {
        System.out.println(success);
    }
    
    public static void main(String [] args)
    {
        // Create a GenericBST
        GenericBST<Double> tree = new GenericBST<>();
        
        double [] array = {32.60, 40.01, 33.60, 25.78, 27.58, 3.45, 73.67, 4.57};
        
        for (int i = 0; i < array.length; i++)
        {
            tree.insert(array[i]);
        }
        
        tree.preorder();
        tree.inorder();
        tree.postorder();
        
        checkTestCase(tree.contains(25.78));
        checkTestCase(tree.contains(45.00));
        
        tree.delete(40.01);
        
        System.out.println("\nPrinting again after deleting an elemenent");
        
        tree.preorder();
        tree.inorder();
        tree.postorder();
        
        System.out.println("Using the contains method again from the GenericBST class to "
                           + "verify the element was deleted");
        
        checkTestCase(tree.contains(40.01));
    }
}

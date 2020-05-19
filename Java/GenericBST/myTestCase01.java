// Alex Santiago
// Created May 28, 2019

// This program is a part of the testcases that I am creating for CS2 programming
// assignment #2, GenericBST.java. It is a class that implements Comparable, NOTE:
// to implement comparable if have to override the method "compareTo()" and to get
// GenericBST to print the contents of the object out in the format that we want we
// also have to implement a toString() method in this class.

// This is the class of this test case file that implements Comparable
public class myTestCase01 implements Comparable<myTestCase01>
{
    private String name;
    private int age;
    
    // A constructor that takes in name and age, then sets the 'name' and 'age' fields
    public myTestCase01(String name, int age)
    {
        this.name = name;
        this. age = age;
    }
    
    // This is the overriden compareTo() method for our class. Notice it is returning
    // -1 if the object that calls the method is less than the argument, 1 if the it
    // is greater than the argument and 0 if both the object and the argument are
    // equal. Also notice that equality will all depend on what we write in our
    // compareTo() method
    @Override
    public int compareTo(myTestCase01 rhs)
    {
        if (this.age < rhs.age)
        {
            return -1;
        }
        else if(this.age > rhs.age)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    
    // System.out.println() in another class will inheritenly call this method inside
    // of it when printing the object. If we dont override this method then in the
    // other class what will be printed is the address of the object. We need to
    // override it in order for it to print out the contents of the object in the
    // format that we want
    @Override
    public String toString()
    {
        return name + ", " + age + "\n";
    }
    
    public static void checkTestCases(boolean success)
    {
        System.out.println(success);
    }
    
    // This is the main method of the test case file
    public static void main(String [] args)
    {
        // Create a GenericBST object
        GenericBST<myTestCase01> tree = new GenericBST<>();
        
        // Create and initialize however many myTestCase01 objects we desire
        myTestCase01 p1 = new myTestCase01("Alex", 25);
        myTestCase01 p2 = new myTestCase01("Keila", 24);
        myTestCase01 p3 = new myTestCase01("Phillip", 28);
        myTestCase01 p4 = new myTestCase01("Radames", 23);
        myTestCase01 p5 = new myTestCase01("Kawhi", 26);
        myTestCase01 p6 = new myTestCase01("Maday", 21);
        myTestCase01 p7 = new myTestCase01("Caleb", 3);
        myTestCase01 p8 = new myTestCase01("Liam", 5);
        myTestCase01 p9 = new myTestCase01("Rebecca", 30);
        myTestCase01 p10 = new myTestCase01("Pedro", 27);
        
        // Insert the myTestCase01 objects into our GenericBST
        tree.insert(p1);
        tree.insert(p2);
        tree.insert(p3);
        tree.insert(p4);
        tree.insert(p5);
        tree.insert(p6);
        tree.insert(p7);
        tree.insert(p8);
        tree.insert(p9);
        tree.insert(p10);
        
        tree.preorder();
        
        System.out.println("Deleting an element");
        tree.delete(p3);
        
        System.out.println("Printing again to verify the element was deleted");
        tree.preorder();
        
        System.out.println("\nVerify that the contains method is working");
        checkTestCases(tree.contains(p4));
    }
}

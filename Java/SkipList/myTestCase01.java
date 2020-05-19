// Alex Santiago
// Created June 26, 2019

// This is the first test case that I have created to test the SkipList programming
// assignment for CS2

// This test case will test for when a node is passed with a height that will increase
// the overall height of the SkipList and also has that new max height. It will do
// some reference checks on the levels but NOT on the very top new level because it is
// is impossible to know if the program actually grew the maximally tall nodes to that
// new max height

public class myTestCase01
{
    private static boolean checkReference(SkipList<Integer> list, int level,
                                        int [] values)
    {
        Node<Integer> temp = list.head();
        
        for (int i = 0; i < values.length; i++)
        {
            temp = temp.next(level);
            
            if (temp.value().compareTo(values[i]) != 0)
                return false;
        }
        
        if (temp.next(level) == null)
        {
            System.out.println("Reference Check: Pass");
            return true;
        }
        
        System.out.println("Reference Check: Fail");
        return false;
    }
    
    public static void main(String [] args)
    {
        SkipList<Integer> list = new SkipList<Integer>(3);
        
        list.insert(2, 1);
        list.insert(3, 2);
        list.insert(4, 3);
        list.insert(5, 1);
        list.insert(6, 1);
        
        boolean success = true;
        
        success &= checkReference(list, 0, new int [] {2, 3, 4, 5, 6});
        success &= checkReference(list, 1, new int [] {3, 4});
        success &= checkReference(list, 2, new int [] {4});
        success &= checkReference(list, 3, new int [] {});
        
        System.out.println((success) ? "Hooray!" : "fail whale");
        
        list.insert(7, 1);
        list.insert(8, 2);
        list.insert(9, 3);
        list.insert(10, 4);
        
        success &= checkReference(list, 0, new int [] {2, 3, 4, 5, 6, 7, 8, 9, 10});
        success &= checkReference(list, 1, new int [] {3, 4, 8, 9, 10});
        success &= checkReference(list, 2, new int [] {4, 9, 10});
        success &= checkReference(list, 4, new int [] {});
        
        success &= (list.height() == 4);
        success &= (list.size() == 9);
        success &= (list.head().height() == 4);
        
        System.out.println((success) ? "Hooray!" : "fail whale");
    }
}

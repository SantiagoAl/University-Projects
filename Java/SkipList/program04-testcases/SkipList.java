// Alex Santiago
// COP 3503, Summer 2019
// NID: al625608

// This is my final solution to programming assignment #4, SkipList

import java.util.*;
import java.io.*;

// This is a generic Node class, that can take in any type of comparable data
class Node<T>
{
    // The following three variable hold the height of the current node, some
    // compareble data stored at this Node and a list containing references to the
    // next nodes in the SkipLsit
    private int height;
    private T data;
    private List<Node<T>> nextNodes;
    
    // The Node class constructor that sets the height and initializes the nextNode
    // list
    Node (int height)
    {
        this.height = height;
        
        this.nextNodes = new ArrayList<Node<T>>(height);
        
        // Initialize the needed indices to null, so they can be manipulated later
        for (int i = 0; i < height; i++)
            this.nextNodes.add(null);
    }
    
    // An overloaded Node class constructor that also sets the node's data
    Node (T data, int height)
    {
        this.data = data;
        this.height = height;
        
        this.nextNodes = new ArrayList<Node<T>>(height);
        
        // After creating the ArrayList to hold our 'nextNode' references, initialize
        // the indices to null so they can later be manipulated
        for (int i = 0; i < height; i++)
            this.nextNodes.add(null);
    }
    
    // A method that returns the 'data' stored in the node
    public T value ()
    {
        return this.data;
    }
    
    // This method returns the height of the current node
    public int height()
    {
        return this.height;
    }
    
    // When called this method will return a reference to the next node in the list
    // at a particular level
    public Node<T> next(int level)
    {
        if (level < 0 || level > height - 1)
            return null;
        
        return nextNodes.get(level);
    }
    
    // This method takes in a level and a reference to a node as parameters. It sets
    // a reference to a node in the the 'nextNode' ArrayList at that level
    public void setNext(int level, Node<T> node)
    {
        nextNodes.set(level, node);
    }
    
    // When called this method will grow the height of the current node by one
    public void grow()
    {
        this.height++;
        
        this.nextNodes.add(null);
    }
    
    // With a 50 percent chance this method will grow the height of the current node
    public void maybeGrow()
    {
        // This simulates a coin toss. If it is one then it will grow the height of
        // the current node
        int chanceOfGrowth = (int) (Math.random() * 2) + 1;
        
        if (chanceOfGrowth == 1)
        {
            this.height++;
            this.nextNodes.add(null);
        }
    }
    
    // When called this will trim the height of the current node until it reaches
    // the height passed in as a parameter
    public void trim(int height)
    {
        if (height() < height)
            return;
        
        for (int i = height() -  1; i > height - 1; i--)
            this.nextNodes.remove(i);
        
        this.height = height;
    }
}

// A generic SkipList class, it has the restriction that only classes that implement
// Comparable can be stored in it
public class SkipList<AnyType extends Comparable<AnyType>>
{
    // The head and size of the SkipList
    private Node<AnyType> head;
    private int size;
    
    // The next two variables are the default height of the head node and SkipList
    // when it is first created and 'logOfTwo' is used when determining the max height
    // of the SkipList
    private final int defaultHeight = 1;
    private static double logOfTwo = Math.log10(2);
    
    // A SkipList class constructor, when this is called the head node and essentially
    // the height of the SkipList are set to 'defaultHeight'
    public SkipList()
    {
        head = new Node<>(this.defaultHeight);
        this.size = 0;
    }
    
    // An overloaded SkipList constructor that takes in a height as parameter
    public SkipList(int height)
    {
        if (height < this.defaultHeight)
            head = new Node<>(this.defaultHeight);
        else
            head = new Node<>(height);
        
        this.size = 0;
    }
    
    // A method that will return the current height of the SkipList
    public int size()
    {
        return this.size;
    }
    
    // An auxiliary method to increment the size of the SkipList
    private void incrementSize()
    {
        this.size++;
    }
    
    // An auxiliary method to decrement the size of the SkipList
    private void decrementSize()
    {
        this.size--;
    }
    
    // This method will return the current height of the head node
    public int height()
    {
        return head.height();
    }
    
    // This method simply returns a reference to the head node
    public Node<AnyType> head()
    {
        return head;
    }
    
    // A method that inserts some Comparable data into the SkipList, with a randomly
    // generated height
    public void insert(AnyType data)
    {
        int currentHeight = height();
        int newNodeHeight = generateRandomHeight(currentHeight);

        // The following list will hold the previous node's node references that will
        // have to be connected to the 'newNode'
        List<Node<AnyType>> previousNodeList = createList(currentHeight);
        Node<AnyType> newNode = new Node<>(data, newNodeHeight);

        Node<AnyType> temp = head();
        int i = currentHeight - 1;

        // Iterate through the SkipList to find the insertion position
        while (i >= 0)
        {
            if (temp.next(i) == null || temp.next(i).value().compareTo(data) >= 0)
            {
                // Stores this node's nextNode reference in the ArrayList
                previousNodeList.set(i, temp.next(i));

                // Once 'i' becomes less than the height of the newNode, I will begin
                // connecting other nodes to this newNode
                if (i < newNode.height())
                {
                    temp.setNext(i, newNode);
                }

                i--;
            }
            // Value at the nextNode is less than 'data', drop down a level
            else if (temp.next(i).value().compareTo(data) < 0)
            {
                temp = temp.next(i);
            }
        }

        // Within in the loop connect the newNode to the previous node's next
        // references, from the 'previousNodeList' up until the height of the newNode
        for (int j = 0; j < newNode.height(); j++)
        {
                newNode.setNext(j, previousNodeList.get(j));
        }

        incrementSize();
        int newMaxHeight = 0;

        // The maximum height of the SkipList can be calculated once the size is
        // greater than one
        if (size() > 1)
        {
            newMaxHeight = getMaxHeight(size());

            // If inserting the node causes the max height to be greater than the
            // currentHeight, grow the SkipList
            if (newMaxHeight > currentHeight)
            {
                growList();
            }
        }
    }
    
    // This is an overloaded insert method that inserts some Comparable data and
    // initializes the height to the height parameter passed in
    public void insert(AnyType data, int height)
    {
        // Incerement the size and check for an increase in the max height before
        // inserting the 'newNode' to account for a height of ⌈log2(n + 1)⌉ being
        // passed in
        incrementSize();
        
        int possibleMax = 0;
        
        if (size() > 1)
        {
            possibleMax = getMaxHeight(size());
            
            if (possibleMax > this.height())
            {
                growList();
            }
        }
        
        int currentHeight = this.height();
        
        // This ArrayList will hold the previous node's nextNode references
        List<Node<AnyType>> previousNodeList = createList(currentHeight);
        Node<AnyType> newNode = new Node<>(data, height);
        
        Node<AnyType> temp = head();
        int i = currentHeight - 1;
        
        // Iterate through the SkipList until it finds the position to insert
        while (i >= 0)
        {
            if (temp.next(i) == null || temp.next(i).value().compareTo(data) >= 0)
            {
                // Stor the previous node's nextNode references in the ArrayList
                previousNodeList.set(i, temp.next(i));
                
                // Once 'i' becomes less than the height of the newNode, I will begin
                // connecting other nodes to this newNode
                if (i < newNode.height())
                {
                    temp.setNext(i, newNode);
                }
                
                i--;
            }
            // If the nextNode's value is less than the value being inserted, jump to
            // the next node without decrementing 'i'
            else if (temp.next(i).value().compareTo(data) < 0)
            {
                temp = temp.next(i);
            }
        }
        
        // Within this loop connect the newNode to the previous node's next
        // references, from the 'previousNodeList' up until the height of the newNode
        for (int j = 0; j < newNode.height(); j++)
        {
            if (j < currentHeight)
            {
                newNode.setNext(j, previousNodeList.get(j));
            }
            else
            {
                break;
            }
        }
    }
    
    // This method takes some Comparable data as a parameter and deletes it from the
    // SkipList. If there are multiple occurrences it will delete the first occurrence
    public void delete(AnyType data)
    {
        // This ArrayList will hold all of the nodes that have a reference pointing
        // to a node with value equal to 'data'
        List<Node<AnyType>> previousNodeList = createList(this.height());
        
        // This will indicate if deletion is possible
        boolean deletion = false;
        
        Node<AnyType> temp = head();
        int i = this.height() - 1;
        
        // Iterate through the SkipList to find 'data'. It if the nextNode is null or
        // the value is greater than 'data' drop down a level. If it is less, jump
        // forward at the same level
        while (i >= 0)
        {
            if (temp.next(i) == null)
            {
                i--;
            }
            else if (temp.next(i).value().compareTo(data) > 0)
            {
                i--;
            }
            // The value is equal to 'data' start storing nextNode references
            else if (temp.next(i).value().compareTo(data) == 0)
            {
                // Store nodes that have references to the node to be deleted
                previousNodeList.set(i, temp);
                
                // Once 'i' is equal to zero, it has definitely found the node. Set
                // temp that node, and we have also found the first occurrence
                if (i == 0)
                {
                    temp = temp.next(i);
                    deletion = true;
                }
                
                i--;
            }
            else
            {
                temp = temp.next(i);
            }
        }
        
        // Enter this if statement if deletion is possible
        if (deletion)
        {
            decrementSize();
            int maximumHeight = 0;
            
            // Check if decrementing the size of the SkipList caused a change in the
            // max height. If size is less than one, use the 'defaultHeight' else
            // calculate the max height
            if (size <= 1)
                maximumHeight = this.defaultHeight;
            else
                maximumHeight = getMaxHeight(size());
            
            // After deletion proves to be possible, connect the previous node's
            // nextNode references to that of the deleted node's
            for (int j = 0; j < temp.height(); j++)
            {
                previousNodeList.get(j).setNext(j, temp.next(j));
            }
            
            // If there is a change in the max height of the SkipList, trim the list
            if (maximumHeight < this.height())
            {
                trimSkipList(maximumHeight);
            }
        }
    }
    
    // This method returns true if the SkipList contains 'data'. False otherwise
    public boolean contains(AnyType data)
    {
        Node<AnyType> temp = head();
        
        // If the list has not been created return false
        if (temp == null)
        {
            return false;
        }
        
        int i = this.height() - 1;
        
        // Iterate through the SkipList
        while (i >= 0)
        {
            // The nextNode reference is null, drop down one level
            if (temp.next(i) == null)
            {
                i--;
            }
            // The value at the nextNode is greater than 'data', drop down one level
            else if (temp.next(i).value().compareTo(data) > 0)
            {
                i--;
            }
            // Value at the nextNode is equal to 'data', return true
            else if (temp.next(i).value().compareTo(data) == 0)
            {
                return true;
            }
            // Here the value at the nextNode is less than 'data, jump foward at the
            // same level
            else
            {
                temp = temp.next(i);
            }
        }
        
        // We have fallen of the SkipList, return false
        return false;
    }
    
    // A method that returns a reference to a node containing 'data' if it exists,
    // null otherwise
    public Node<AnyType> get(AnyType data)
    {
        Node<AnyType> temp = head();
        int i = this.head.height() - 1;
        
        // Iterate through the SkipList
        while (i >= 0)
        {
            // The nextNode is null, drop down a level
            if (temp.next(i) == null)
            {
                i--;
            }
            // The value at nextNode is greater than 'data', again drop down a level
            else if (temp.next(i).value().compareTo(data) > 0)
            {
                i--;
            }
            // The value at nextNode is equal to 'data', we have found it. Return a
            // reference to that node
            else if (temp.next(i).value().compareTo(data) == 0)
            {
                temp = temp.next(i);
                return temp;
            }
            // Value at nextNode is less than 'data', jump forward at the same level
            else
            {
                temp = temp.next(i);
            }
        }
        
        // 'data is not in the list, return null
        return null;
    }
    
    // The method that when called will grow the height of the SkipList
    private void growList()
    {
        int prevMaximumHeight = this.height() - 1;
        this.head().grow();
        
        Node<AnyType> previousNode = head();
        int newMaxHeight = this.height();
        
        Node<AnyType> nextNode;
        
        // If nextNode at the previous max height is not null, then jump to that node
        // to possibly grow it. If not, then there is no null with a chance to grow
        // to the new max, just return from the method
        if (previousNode.next(prevMaximumHeight) != null)
        {
            nextNode = previousNode.next(prevMaximumHeight);
        }
        else
        {
            return;
        }
        
        // A flag that will indicate if we can keep moving forward in the SkipList to
        // grow or not
        boolean truthValue = true;
        
        while (truthValue)
        {
            // Grow the node with a 50 percent chance
            nextNode.maybeGrow();
            
            // If the current node has a height of 'newMaxHeight' then it
            // successfulluy grew
            if (nextNode.height() == newMaxHeight)
            {
                // Set the previous node's top level to this now grown node with
                // new max height
                previousNode.setNext(newMaxHeight - 1, nextNode);
                
                // Check if we can keep moving forward at the 'prevMaximumHeight', if
                // so move everything forward,
                if (nextNode.next(prevMaximumHeight) != null)
                {
                    previousNode = nextNode;
                    nextNode = nextNode.next(prevMaximumHeight);
                }
                else
                {
                    truthValue = false;
                }
            }
            // Getting here means the current node did not grow
            else
            {
                // Move to next node in the list with 'prevMaximumHeight' if possible
                if (nextNode.next(prevMaximumHeight) != null)
                {
                    nextNode = nextNode.next(prevMaximumHeight);
                }
                // Here there is no other node with a height of 'prevMaximumHeight',
                // truthValue becomes false, break out of the loop
                else
                {
                    truthValue = false;
                }
            }
        }
    }
    
    // A method that when called will trim the height of the SkipList
    private void trimSkipList(int maximumHeight)
    {
        // Trim the head to node to the new 'maximumHeight'
        this.head.trim(maximumHeight);
        
        Node<AnyType> temp = head();
        
        // Setting 'i' to this will allow us to keep jumping forward at the same level
        int i = this.height() - 1;
        
        // Move to the next node in the list from the head node, if there is one
        // else return fromt the method
        if (temp.next(i) != null)
            temp = temp.next(i);
        else
            return;
        
        while (true)
        {
            // Check if there is another node at the same level
            if (temp.next(i) != null)
            {
                // If the current node's height is greater than 'maximumHeight' then
                // trim the nodes height and move on to the next node in the list
                if (temp.height() > maximumHeight)
                {
                    temp.trim(maximumHeight);
                    temp = temp.next(i);
                }
                // Getting here means the nodes height is less than or equal to
                // 'maximumHeight', jump to the next node
                else
                {
                    temp = temp.next(i);
                }
            }
            // Reaching this means the current node is the last node with the same
            // height as the head node, trim the nodes height and break out of the
            // loop
            else
            {
                temp.trim(maximumHeight);
                break;
            }
        }
    }
    
    // This method when called will calculate and return the max height of the
    // SkipList, taking in the size as a parameter
    private static int getMaxHeight(int n)
    {
        return (int) (Math.ceil(Math.log10(n) / logOfTwo));
    }
    
    // A method that will generate a random height for the nodes in the SkipList.
    // It does so simulating a coin toss
    private static int generateRandomHeight(int maxHeight)
    {
        // Start off with an initial height of one
        int height = 1, coinToss = (int) (Math.random() * 2);
        
        // As long as the coinToss is not head(1) and height is less than the
        // maxHeight of the SkipList, keep looping
        while (coinToss != 1 && height < maxHeight)
        {
            coinToss = (int) (Math.random() * 2);
            
            height++;
        }
        
        return height;
    }
    
    // When called this method will return a new ArrayList, with indices already
    // initialized to null
    private ArrayList<Node<AnyType>> createList(int capacity)
    {
        ArrayList<Node<AnyType>> list = new ArrayList<Node<AnyType>>(capacity);
        
        for (int i = 0; i < capacity; i++)
        {
            list.add(i, null);
        }
        
        return list;
    }
    
    // How difficult I found the assignment to be
    public static double difficultyRating()
    {
        return 4.0;
    }
    
    // The estimated amount of time I spent on the assignment
    public static double hoursSpent()
    {
        return 25.0;
    }
}

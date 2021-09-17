// Alex Santiago
// COP 3503, Summer 2019
// NID: al625608

// This is an implementation of a generic Binary Search Tree that can hold any type
// of Comparable object. It is my final solution for progamming assignment #2

import java.io.*;
import java.util.*;

// This is a generic Node class whose 'data' field can take in any type of data
class Node<T>
{
    T data;
    Node<T> left, right;

    // The constructor of the Node class that sets the 'data' field
    Node(T data)
    {
        this.data = data;
    }
}

// A generic Binary Search Tree class, it has the restriction that only classes that
// implement Comparable can be stored in it
public class GenericBST<AnyType extends Comparable<AnyType>>
{
    // Where we will store the root of our Binary Search Tree
    private Node<AnyType> root;
    
    // Insert method which takes any type of data and calls overloaded insert method
    public void insert(AnyType data)
    {
        root = insert(root, data);
    }

    // This is our overloaded insert method taking the root and some comparable data
    // as input parameters, then inserts them into the Binary Search Tree using the
    // compareTo() method for comparison
    private Node<AnyType> insert(Node<AnyType> root, AnyType data)
    {
        // If root is null create a new Node. Using the compareTo() method, if the
        // value returned is less than zero traverse to the left, if it is greater
        // than zero traverse to the right
        if (root == null)
        {
            return new Node<>(data);
        }
        else if (data.compareTo(root.data) < 0)
        {
            root.left = insert(root.left, data);
        }
        else if (data.compareTo(root.data) > 0)
        {
            root.right = insert(root.right, data);
        }
        
        return root;
    }

    // Delete method that takes anytype of data and calls an overloaded delete method
    public void delete(AnyType data)
    {
        root = delete(root, data);
    }

    // This is the overloaded delete method, that takes the root of the tree and some
    // comparable data. It deletes that node from the BST taking into account the
    // three cases when deleting from a BST
    private Node<AnyType> delete(Node<AnyType> root, AnyType data)
    {
        // If root is null, there is nothing to delete just return null
        if (root == null)
        {
            return null;
        }
        // If compareTo() returns less than 0, traverse to the left
        else if (data.compareTo(root.data) < 0)
        {
            root.left = delete(root.left, data);
        }
        // if compareTo() returns greater than 0, traverse to the right
        else if (data.compareTo(root.data) > 0)
        {
            root.right = delete(root.right, data);
        }
        else
        {
            // Here we have found the node to delete. First case: if both left and
            // right are null, simply return null
            if (root.left == null && root.right == null)
            {
                return null;
            }
            // Second case 1A: If the left child is null, and right is non-null
            // return the right child
            else if (root.left == null)
            {
                return root.right;
            }
            // Second case 1B: If the right child is null and left is non-null return
            // the left child
            else if (root.right == null)
            {
                return root.left;
            }
            // If it gets here then both children are non-null, replace this node
            // with the max value from the left sub-tree
            else
            {
                root.data = findMax(root.left);
                root.left = delete(root.left, root.data);
            }
        }
        
        return root;
    }
    
    // This method assumes root is non-null, since this is only called by
    // delete() on the left subtree, and only when that subtree is not empty
    private AnyType findMax(Node<AnyType> root)
    {
        // Continue moving right to locate the max value in the left sub-tree
        while (root.right != null)
        {
            root = root.right;
        }
        
        return root.data;
    }

    // Contains method taking in any type of data and calls overloaded Contains method
    public boolean contains(AnyType data)
    {
        return contains(root, data);
    }

    // The overloaded contains method taking the root and some comparable data as
    // input, returning true if the tree contains that data, false otherwise
    private boolean contains(Node<AnyType> root, AnyType data)
    {
        // If the root is NULL it does not contain the data. If compareTo() returns
        // less than 0 go left, greater than 0 go right, if it returns 0 just return
        // true, we have found the data
        if (root == null)
        {
            return false;
        }
        else if (data.compareTo(root.data) < 0)
        {
            return contains(root.left, data);
        }
        else if (data.compareTo(root.data) > 0)
        {
            return contains(root.right, data);
        }
        else
        {
            return true;
        }
    }

    // This is the inorder traversal method, that calls overloaded inorder
    public void inorder()
    {
        System.out.print("In-order Traversal:");
        inorder(root);
        System.out.println();
    }

    // An overloaded inorder method that prints the elements of the tree in inorder
    // fashion
    private void inorder(Node<AnyType> root)
    {
        if (root == null)
            return;
        
        inorder(root.left);
        System.out.print(" " + root.data);
        inorder(root.right);
    }

    // The preorder method that calls on the overloaded preorder method
    public void preorder()
    {
        System.out.print("Pre-order Traversal:");
        preorder(root);
        System.out.println();
    }

    // Overloaded preorder method, which takes the root of the tree as input and
    // prints out the elements in preorder fashion
    private void preorder(Node<AnyType> root)
    {
        if (root == null)
            return;
        
        System.out.print(" " + root.data);
        preorder(root.left);
        preorder(root.right);
    }

    // The postorder method that calls on the overloaded postorder method
    public void postorder()
    {
        System.out.print("Post-order Traversal:");
        postorder(root);
        System.out.println();
    }

    // Overloaded postorder method that takes the root of the tree as input and prints
    // out the elements out in postorder fashion
    private void postorder(Node<AnyType> root)
    {
        if (root == null)
            return;
        
        postorder(root.left);
        postorder(root.right);
        System.out.print(" " + root.data);
    }
    
    // How difficult I found the assignment to be
    public static double difficultyRating()
    {
        return 2.5;
    }
    
    // Approximately how many hours I spent working on the program
    public static double hoursSpent()
    {
        return 6.0;
    }
}

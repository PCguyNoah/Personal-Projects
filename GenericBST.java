// Noah Beightol, NID: no145336
//fall 2022, COP 3403
//Last Edited: 09/18/22

import java.io.*;
import java.util.*;

// Since we need to store any data type, we will use java generics
// which allows us to use any data type in our node
class Node<AnyType>
{
	AnyType data;
	Node<AnyType> left, right;

	Node(AnyType data)
	{
		this.data = data;
	}
}

// This class allows us to create Binary Search Trees of any variable type
// through the use of Generics and the Comparable super class
public class GenericBST<AnyType extends Comparable<AnyType>>
{
	private Node<AnyType> root;

	// inserting node at the root
	public void insert(AnyType data)
	{
		root = insert(root, data);
	}

	// This method inserts new nodes into our tree, either at the root
	// left or right child node
	private Node<AnyType> insert(Node<AnyType> root, AnyType data)
	{
		if (root == null)
		{
			return new Node<AnyType>(data);
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

	// deleting node
	public void delete(AnyType data)
	{
		root = delete(root, data);
	}

	// this method finds and deletes a specific node containing a value we pass in
	// or returns null if value is not in the tree
	private Node<AnyType> delete(Node<AnyType> root, AnyType data)
	{
		// null check
		if (root == null)
		{
			return null;
		}
		// if the value passed in is less than root we go left
		else if (data.compareTo(root.data) < 0)
		{
			root.left = delete(root.left, data);
		}
		// if the value passed in is less than root we go right
		else if (data.compareTo(root.data) > 0)
		{
			root.right = delete(root.right, data);
		}

		else
		{
			// if both the left and right are null, we know we reached the end of the tree
			// and the value is not in the tree
			if (root.left == null && root.right == null)
			{
				return null;
			}
			// these are true only if we reach the end of the left or right branch
			// but there are more values to check
			else if (root.left == null)
			{
				return root.right;
			}
			else if (root.right == null)
			{
				return root.left;
			}
			else
			{
				root.data = findMax(root.left);
				root.left = delete(root.left, root.data);
			}
		}

		return root;
	}

	// This method assumes root is non-null, since this is only called by
	// delete() on the left subtree, and only when that subtree is not empty.
	private AnyType findMax(Node<AnyType> root)
	{
		while (root.right != null)
		{
			root = root.right;
		}

		return root.data;
	}

	// method returns true or false depending on if a value is in the tree
	public boolean contains(AnyType data)
	{
		return contains(root, data);
	}

	// recursively searches through the tree to find the variable
	// data passed in
	private boolean contains(Node<AnyType> root, AnyType data)
	{
		// null check and recursive function terminator
		if (root == null)
		{
			return false;
		}

		// call left if value is less than current node
		else if (data.compareTo(root.data) < 0)
		{
			return contains(root.left, data);
		}

		// call right if the value greater than current node
		else if (data.compareTo(root.data) > 0)
		{
			return contains(root.right, data);
		}
		// if we get to the end we know its in the Trees
		// so we return true in the last case
		else
		{
			return true;
		}
	}

	// this method traverses through the tree through inorder
	// traversal in the form: left/node/right
	public void inorder()
	{
		System.out.print("In-order Traversal:");
		inorder(root);
		System.out.println();
	}

	private void inorder(Node<AnyType> root)
	{
		if (root == null)
			return;

		inorder(root.left);
		System.out.print(" " + root.data);
		inorder(root.right);
	}

	// this method traverses through the tree through postorder
	// traversal in the form: node/left/right
	public void preorder()
	{
		System.out.print("Pre-order Traversal:");
		preorder(root);
		System.out.println();
	}

	private void preorder(Node<AnyType> root)
	{
		if (root == null)
			return;

		System.out.print(" " + root.data);
		preorder(root.left);
		preorder(root.right);
	}

	// this method traverses through the tree through postorder
	// traversal in the form: left/right/node
	public void postorder()
	{
		System.out.print("Post-order Traversal:");
		postorder(root);
		System.out.println();
	}

	private void postorder(Node<AnyType> root)
	{
		if (root == null)
			return;
		postorder(root.left);
		postorder(root.right);
		System.out.print(" " + root.data);
	}


	// this method returns my precieved difficulty rating
	public static double difficultyRating(){
		return 2.0;
	}

	// this method returns the # of hours I spent on this Assignment
	public static double hoursSpent(){
		return 2.5;
	}
}

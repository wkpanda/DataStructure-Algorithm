import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;

import com.oracle.webservices.internal.api.EnvelopeStyle.Style;

public class binaryTree {
    /**
     * 二叉树节点
     */
    private static class TreeNode {
        int data;
        TreeNode leftChild;
        TreeNode rightChild;

        TreeNode(int data) {
            this.data = data;
        }
    }

    /**
     * 构建二叉树
     * 
     * @param inputList 输入序列
     */
    public static TreeNode createBinaryTree(LinkedList<Integer> inputList) {
        TreeNode node = null;
        if (inputList == null || inputList.isEmpty()) {
            return null;
        }
        Integer data = inputList.removeFirst();
        if (data != null) {
            node = new TreeNode(data);
            node.leftChild = createBinaryTree(inputList);
            node.rightChild = createBinaryTree(inputList);
        }
        return node;
    }

    /**
     * 二叉树前序遍历
     * @param node  二叉树节点
     */
    public static void preOrderTraveral(TreeNode node){
        if(node==null){
            return;
        }
        System.out.println(node.data);
        preOrderTraveral(node.leftChild);
        preOrderTraveral(node.rightChild);
    }

    /**
     * 二叉树中序遍历
     * @param node 二叉树节点
     */
    public static void inOrderTraveral(TreeNode node){
        if(node==null){
            return;
        }
        inOrderTraveral(node.leftChild);
        System.out.println(node.data);
        inOrderTraveral(node.rightChild);
    }

    /**
     * 二叉树后序遍历
     * @param node  二叉树节点
     */
    public static void postOrderTraveral(TreeNode node) {
        if(node==null){
            return;
        }
        postOrderTraveral(node.leftChild);
        postOrderTraveral(node.rightChild);
        System.out.println(node.data);
    }


    /**
     * 二叉树非递归前序遍历
     * 
     * @param root 二叉树根节点
     */
    public static void preOrderTRaveralWithStack(TreeNode root) {
        Stack<TreeNode> stack = new Stack<TreeNode>();
        TreeNode treeNode = root;
        while(treeNode!=null || !stack.isEmpty()){
            //迭代访问节点的左孩子，并入栈
            while(treeNode!=null){
                System.out.println(treeNode.data);
                stack.push(treeNode);
                treeNode = treeNode.leftChild;
            }
            //如果节点没有左孩子，则弹出栈顶节点，访问节点右孩子
            if(!stack.isEmpty()){
                treeNode = stack.pop();
                treeNode = treeNode.rightChild;
            }
        }
    }
    /**
     * 二叉树层序遍历
     * @param root 二叉树根节点
     */
    public static void levelOrderTraversal(TreeNode root) {
        Queue<TreeNode> queue = new LinkedList<TreeNode>();
        queue.offer(root);
        while(!queue.isEmpty()){
            TreeNode node = queue.poll();
            System.out.println(node.data);
            if(node.leftChild!=null){
                queue.offer(node.leftChild);
            }
            if(node.rightChild!=null){
                queue.offer(node.rightChild);
            }
        }
    }

    public static void main(String[] args) {
        LinkedList<Integer> inputList = new LinkedList<Integer>(Arrays.asList(new Integer[]{3,2,9,null,null,10,null,null,8,null,4}));
        TreeNode treeNode = createBinaryTree(inputList);
        System.out.println("前序遍历：");
        preOrderTraveral(treeNode);
        System.out.println("中序遍历：");
        inOrderTraveral(treeNode);
        System.out.println("后序遍历：");
        postOrderTraveral(treeNode);
    }
}
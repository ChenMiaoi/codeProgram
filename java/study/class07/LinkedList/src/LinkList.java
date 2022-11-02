class Node {
    public Node(int data) {
        this.data = data;
        this.next = null;
    }
    public int data;
    public Node next;
}

public class LinkList {
    public Node head;

    //头插法
    public void pushFront(int data) {
        Node node = new Node(data);
        if (this.head == null) { // 第一次插入
            this.head = node;
            return;
        }
        node.next = this.head;
        this.head = node;
    }
    //尾插法
    public void pushBack(int data) {
        Node newNode = new Node(data);
        if (this.head == null) {
            this.head = newNode;
            return;
        }
        Node cur = this.head;
        while (cur.next != null) {
            cur = cur.next;
        }
        cur.next = newNode;
    }
    private Node searchIndex(int index) {
        if (index < 0 || index > this.size()) {
            throw new RuntimeException("index位置不合法!");
        }
        Node cur = this.head;
        while (--index != 0) {
            cur = cur.next;
        }
        return cur;
    }
    //随机插入
    public boolean insert(int data, int index) {
        if (index >= this.size()) {
            this.pushBack(data);
        }else if (index == 0) {
            this.pushFront(data);
        }else {
            Node prev = searchIndex(index);
            Node next = prev.next;
            Node newNode = new Node(data);
            prev.next = newNode;
            newNode.next = next;
        }
        return true;
    }

    //是否包含key
    public boolean contains(int key) {
        Node cur = this.head;
        while (cur != null) {
            if (cur.data == key) {
                return true;
            }
            cur = cur.next;
        }
        return false;
    }
    private Node searchPrev(int key) {
        Node prev = this.head;
        while (prev.next != null) {
            if (prev.next.data == key) {
                return prev;
            }
            prev = prev.next;
        }
        return null;
    }
    //删除第一次出现关键字为key的节点
    public void pop(int key) {
        if (this.head == null) {
            return;
        }
        if (this.head.data == key) {
            this.head = this.head.next;
            return;
        }
        Node prev = searchPrev(key);
        if (prev == null) {
            System.out.println("Null this node");
            return;
        }
        Node del = prev.next;
        prev.next = del.next;
    }
    //删除所有为key的节点
    public void erase(int key) {
        Node prev = this.head;
        Node next = prev.next;
        while (next != null) {
            if (next.data == key) {
                prev.next = next.next;
                next = next.next;
            }else {
                prev = next;
                next = next.next;
            }
        }
        if (this.head.data == key) {
            this.head = this.head.next;
        }
    }
    //获取长度
    public int size() {
        int size = 0;
        Node cur = this.head;
        while (cur != null) {
            size++;
            cur = cur.next;
        }
        return size;
    }
    //打印链表
    public void display() {
        Node cur = this.head;
        while (cur != null) {
            System.out.print(cur.data + "->");
            cur = cur.next;
        }
        System.out.println("null");
    }
    //清空链表
    public void clear() {

    }
}


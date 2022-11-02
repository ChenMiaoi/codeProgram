public class Test {
    public static void main(String[] args) {
        LinkList linkList = new LinkList();
        linkList.pushBack(2);
        linkList.pushBack(1);
        linkList.pushBack(2);
        linkList.pushBack(2);
        linkList.pushBack(2);
        linkList.pushBack(2);
        linkList.pushBack(2);
        linkList.pushBack(3);
        linkList.display();

        linkList.erase(2);
        linkList.display();
    }
}

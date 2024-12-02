import java.util.LinkedList;
import java.util.ListIterator;
import java.util.Scanner;

public class MyList
{
    LinkedList<String> l;
    MyList()
    {
        l=new LinkedList<>();
    }
    void create()
    {
        Scanner scanner=new Scanner(System.in);
        String input;
        while(true)
        {
            input = scanner.nextLine();
            if (input.isEmpty()) { break; }
            l.add(input);
        }
        scanner.close();
    }

    void duplicate()
    {
        int size=l.size();
        int half=size/2;
        LinkedList<String>first=new LinkedList<>();
        ListIterator<String>it=l.listIterator();
        for(int i=0;i<half;i++)
        {
            first.add(it.next());
        }
        l.addAll(first);
    }

    boolean sym()
    {
        ListIterator<String>left=l.listIterator();
        ListIterator<String>right=l.listIterator(l.size());
        while(left.hasNext() && right.hasPrevious())
        {
            if(!left.next().equals(right.previous()))
                return false;
        }
        return true;
    }

    boolean remover(String target)
    {
        ListIterator<String>it=l.listIterator(l.size());
        while(it.hasPrevious())
        {
            if(it.previous().equals(target))
            {
                it.remove();
                return true;
            }
        }
        return false;
    }



    void print()
    {
        ListIterator<String> it = l.listIterator();
        while(it.hasNext())
        {
            System.out.println(it.next()+" ");
        }
    }
}
public class LinkedMain
{
    public static void main(String[] args)
    {
        MyList mylist = new MyList();
        mylist.create();
        mylist.print();
        System.out.println("~~~~");
        mylist.remover("4");
        mylist.print();
        System.out.println("~~~~");
        if(mylist.sym())
            System.out.println("e");
        else System.out.println(("n"));
        System.out.println("~~~~");
        mylist.duplicate();
        mylist.print();



    }
}

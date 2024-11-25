import java.util.List;

public class ListItem <T>
{
    private T data; //данные, которые хранятся
    private ListItem<T> prev;
    private ListItem <T> next;
     ListItem(T data)
     {
         this.data=data;
         prev=null;
         next=null;
     }
     public T getData()
     {
         return data;
     }
     public ListItem<T> getPrev()
     {
         return prev;
     }
     public ListItem<T> getNext()
     {
         return next;
     }
     public void setPrev(ListItem<T> prev)
     {
         this.prev=prev;
     }
     public void setNext(ListItem<T> next)
     {
         this.next=next;
     }
}
public class List <T>
{
    private ListItem<T> first;
    private ListItem<T> last;
    private int kol;
    List()
    {
        kol=0;
        first=last=null;
    }
    List(T data)
    {
        first=last=new ListItem<>(data);
        kol =1;
    }
    public void add(T data)
    {
        ListItem<T> t=new ListItem<T>(data);
        if(kol>0)
        {
            last.setNext(t);
            t.setPrev(last);
        }
        else {first=t;}
        last=t;
        kol++;
    }

    public ListItem<T> getFirst()
    {
        return first;
    }
    public ListItem<T> getLast()
    {
        return last;
    }
    public int getKol()
    {
        return kol;
    }
}
import java.util.Scanner;

public class ListDemo {
    public static void main(String[] args)
    {
        Scanner sc=new Scanner(System.in);
        System.out.println("N: ");
        int n= sc.nextInt();
        System.out.println("X: ");
        double x= sc.nextDouble();
        int i=(int)x;
        List<Integer> l=new List<Integer>(i);
        for(int k=1;k<n;k++)
        {
            x=sc.nextInt();
            i=(int) x;
            l.add(i);
        }
        ListItem<Integer> item=l.getFirst();
        do {
            System.out.println(item.getData()+" ");
            item=item.getNext();
        } while(item!=null);
        System.out.println();
    }
}
//метод проверки на симетричность, метод удаления первого элемента с заданным значением и удаллить элемент по его поррядковому номеру

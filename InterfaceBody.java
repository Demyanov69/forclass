import java.util.Scanner;

public class InterfaceBody {
    public static void main(String []args){
        Body []f;
        Scanner sc=new Scanner(System.in);
        System.out.println("Введите количество элементов:");
        int k=sc.nextInt();
        f=new Body[k];
        for(int i=0;i<k;i++){
            System.out.println("1-шар, 2-параллелограмм");
            int p=sc.nextInt();
            if(p==1)
            {
                System.out.println("Введите r:");
                double r=sc.nextDouble();
                Shar shar=new Shar(r);
                f[i]=shar;
            }
            if(p==2)
            {
                System.out.println("Введите 3 стороны:");
                double a=sc.nextDouble();
                double b= sc.nextDouble();
                double c=sc.nextDouble();
                Para para = new Para(a,b,c);
                f[i]=para;
            }
        }
        for(int i=0;i<k;i++)
        {
            f[i].print();
            System.out.println("S= "+f[i].S()+"  "+"V= "+f[i].V());
        }
    }
}

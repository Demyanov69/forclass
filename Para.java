public class Para implements Body {
    double a,b,c;
    Para(double a,double b,double c){
        this.a=a;
        this.b=b;
        this.c=c;
    }
    public double V(){
        return a*b*c;
    }
    public double S(){
        return 2*(a*b+b*c+a*c);
    }
    public void print(){
        System.out.println("Параллелограм: "+a+" "+b+" "+c);
    }
}

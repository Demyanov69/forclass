class Avto {
    private String marka;
    private String number;
    private String vin;
    private int year;
    private double vol;
    private int price;
    private int km;

    Avto(String marka, String number, String vin, int year, double vol, int price, int km)
    {
        this.marka=marka;
        this.number=number;
        this.vin=vin;
        this.year=year;
        this.vol=vol;
        this.price=price;
        this.km=km;
    }

    public String toString()
    {
        return "Марка: "+marka+"\n Номер: "+number+"\n Вин: "+vin+"\n Год: "+year+"\n Обьем: "+vol+"\n Цена: "+price+"\n Км: "+km;
    }

    String getMarka()
    {
        return marka;
    }
    String getNumber()
    {
        return number;
    }
    String getVin()
    {
        return vin;
    }
    int getYear(){
        return year;
    }
    double getVol()
    {
        return vol;
    }
    int getPrice()
    {
        return price;
    }
    int getKm()
    {
        return km;
    }
}

class Taxi extends Avto
 {
    private String driver;
    private  int pricekm;
    Taxi(String marka, String number, String vin, int year, double vol, int price, int km, String driver, int pricekm)
    {
         super(marka, number, vin, year, vol, price, km);
         this.driver=driver;
         this.pricekm=pricekm;
    }
    double stoim(double km)
    {
        return km*pricekm;
    }

    String getDriver()
    {
        return driver;
    }

    public String toString()
    {
        return super.toString()+"\n"+driver+"\n Водитель: "+"\n Цена за км: "+pricekm;
    }
 }

import java.util.Scanner;

public class ExtendsAvto
{
    public static void main(String[] args)
    {
        Scanner sc=new Scanner(System.in);
        System.out.println("Введите марку: ");
        String marka =sc.nextLine();
        System.out.println("Введите номер: ");
        String number =sc.nextLine();
        System.out.println("Введите вин: ");
        String vin =sc.nextLine();
        System.out.println("Введите год: ");
        int year =sc.nextInt();
        System.out.println("Введите объем: ");
        double vol =sc.nextDouble();
        System.out.println("Введите цену: ");
        int price =sc.nextInt();
        System.out.println("Введите пробег: ");
        int km =sc.nextInt();
        Avto a=new Avto(marka,number,vin,year,vol,price,km);
        System.out.println("Данные авто: ");
        System.out.println(a.toString());

        String q=sc.nextLine();
        System.out.println("ФИО водилы: ");
        String f=sc.nextLine();
        System.out.println("Стоимость за км: ");
        int pricekm=sc.nextInt();
        System.out.println("Данные авто: ");
        System.out.println(a.toString());
        Taxi t=new Taxi(marka,number,vin,year,vol,price,km,f,pricekm);
        System.out.println("Введите расстояние в км: ");
        double km1=sc.nextInt();
        System.out.println("Стоимость поездки: "+t.stoim(km1));
        System.out.println("Данные такси: ");
        System.out.println(t.toString());
    }
}

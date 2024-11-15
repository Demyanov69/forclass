public interface Pair {
    Pair add(double amount);
    Pair subtract(double amount);
    Pair multiply(double amount);
    Pair divide(double amount);
}
class Money implements Pair {
    private double amount;

    Money(double amount) {
        this.amount = amount;
    }

    public Pair add(double amount) {
        return new Money(this.amount + amount);
    }

    public Pair subtract(double amount) {
        return new Money(this.amount - amount);
    }

    public Pair multiply(double amount) {
        return new Money(this.amount * amount);
    }

    public Pair divide(double amount) {
        return new Money(this.amount / amount);
    }

    public String toString() {
        return "Money: " + amount;
    }
}
class Fraction implements Pair {
    private int numerator;
    private int denominator;

    Fraction(int numerator, int denominator) {
        this.numerator = numerator;
        this.denominator = denominator;
    }

    public Pair add(double amount) {
        int newNumerator = this.numerator * 1 + (int)(amount * this.denominator);
        int newDenominator = this.denominator;
        return new Fraction(newNumerator, newDenominator);
    }

    public Pair subtract(double amount) {
        int newNumerator = this.numerator * 1 - (int)(amount * this.denominator);
        int newDenominator = this.denominator;
        return new Fraction(newNumerator, newDenominator);
    }

    public Pair multiply(double amount) {
        return new Fraction(this.numerator * (int)amount, this.denominator);
    }

    public Pair divide(double amount) {
        return new Fraction(this.numerator, this.denominator * (int)amount);
    }

    public String toString() {
        return "Fraction: " + numerator + "/" + denominator;
    }
}
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Pair[] f;
        Scanner sc = new Scanner(System.in);
        System.out.println("Введите количество операций:");
        int n = sc.nextInt();
        f = new Pair[n];
        for (int i = 0; i < n; i++) {
            System.out.println("Введите тип (1 - Money, 2 - Fraction):");
            int type = sc.nextInt();
            if (type == 1) {
                System.out.println("Введите сумму:");
                double amount = sc.nextDouble();
                Money m=new Money(amount);
                f[i]=m;
            }
            if (type == 2) {
                System.out.println("Введите числитель и знаменатель:");
                int num = sc.nextInt();
                int denom = sc.nextInt();
                Fraction fr=new Fraction(num,denom);
                f[i]=fr;
            }
        }

        for (int i = 0; i < n; i++) {
            System.out.println("Сумма: " + f[i].add(1)); // Пример с добавлением 1
            System.out.println("Разность: " + f[i].subtract(1)); // Пример с вычитанием 1
            System.out.println("Произведение: " + f[i].multiply(2)); // Пример с умножением на 2
            System.out.println("Частное: " + f[i].divide(2)); // Пример с делением на 2
        }
    }
}

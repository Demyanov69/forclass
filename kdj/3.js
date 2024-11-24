public interface Pair {
    Pair add(Pair p);
    Pair sub(Pair p);
    Pair mul(Pair p);
    Pair div(Pair p);
    int getOne();
    int getTwo();
    void print();
}
class Money implements Pair {
    private int bills;
    private int coins;

    Money(int bills, int coins) {
        this.bills = bills;
        this.coins = coins;
    }

    public int getOne() {
        return bills;
    }

    public int getTwo() {
        return coins;
    }

    public Pair add(Pair p) {
        int newCoins = this.coins + p.getTwo();
        int newBills = this.bills + p.getOne() + newCoins / 100;
        newCoins %= 100;
        return new Money(newBills, newCoins);
    }

    public Pair sub(Pair p) {
        int newCoins = this.coins - p.getTwo();
        int newBills = this.bills - p.getOne();
        if (newCoins < 0) {
            int borrowedBills = (Math.abs(newCoins) + 99) / 100;
            if (newBills >= borrowedBills) {
                newBills -= borrowedBills;
                newCoins += borrowedBills * 100;
            } else {
                newBills = 0;
                newCoins = 0;
            }
        }
        if (newBills < 0) {
            newBills = 0;
        }
        if (newCoins < 0) {
            newCoins = 0;
        }
        return new Money(newBills, newCoins);
    }

    public Pair mul(Pair p) {
        if (p.getOne() == 0) {
            return new Money(0, this.coins * p.getTwo());
        } else if (p.getTwo() == 0) {
            return new Money(this.bills * p.getOne(), 0);
        } else {
            int newCoins = this.coins * p.getTwo();
            int newBills = this.bills * p.getOne();
            newBills += newCoins / 100;
            newCoins %= 100;
            return new Money(newBills, newCoins);
        }
    }

    public Pair div(Pair p) {
        if (p.getOne() == 0 || p.getTwo() == 0) {
            return new Money(0, 0);
        }
        int newCoins = this.coins / p.getTwo();
        int newBills = this.bills / p.getOne();
        return new Money(newBills, newCoins);
    }

    public void print() {
        System.out.println("Money: " + bills + " bills and " + coins + " coins");
    }

    @Override
    public String toString() {
        return bills + " bills and " + coins + " coins";
    }
}
class Fraction implements Pair {
    private int numerator;
    private int denominator;

    Fraction(int numerator, int denominator) {
        if (denominator == 0) {
            throw new IllegalArgumentException("Знаменатель не может быть равен нулю.");
        }
        this.numerator = numerator;
        this.denominator = denominator;
    }

    public int getOne() {
        return numerator;
    }

    public int getTwo() {
        return denominator;
    }

    public Pair add(Pair p) {
        int newNumerator = this.numerator * p.getTwo() + p.getOne() * this.denominator;
        return new Fraction(newNumerator, this.denominator * p.getTwo());
    }

    public Pair sub(Pair p) {
        int newNumerator = this.numerator * p.getTwo() - p.getOne() * this.denominator;
        return new Fraction(newNumerator, this.denominator * p.getTwo());
    }

    public Pair mul(Pair p) {
        if (p.getOne() == 0 || p.getTwo() == 0) {
            return new Fraction(0, 1);
        }
        return new Fraction(this.numerator * p.getOne(), this.denominator * p.getTwo());
    }

    public Pair div(Pair p) {
        if (p.getOne() == 0) {
            throw new IllegalArgumentException("Деление на ноль невозможно.");
        }
        return new Fraction(this.numerator * p.getTwo(), this.denominator * p.getOne());
    }

    public void print() {
        System.out.println("Fraction: " + numerator + "/" + denominator);
    }

    @Override
    public String toString() {
        return numerator + "/" + denominator;
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
                System.out.println("Введите купюры и копейки:");
                int bills = sc.nextInt();
                int coins = sc.nextInt();
                Money m = new Money(bills, coins);
                f[i] = m;
            } else if (type == 2) {
                System.out.println("Введите числитель и знаменатель:");
                int num = sc.nextInt();
                int denom = sc.nextInt();
                Fraction fr = new Fraction(num, denom);
                f[i] = fr;
            }
        }
        for (int i = 0; i < n; i++) {
            f[i].print();
            if (f[i] instanceof Money) {
                System.out.println("Сумма: " + f[i].add(new Money(1, 2)));
                System.out.println("Разность: " + f[i].sub(new Money(1, 5)));
                System.out.println("Произведение: " + f[i].mul(new Money(1, 3)));
                System.out.println("Частное: " + f[i].div(new Money(2, 1)));
            } else if (f[i] instanceof Fraction) {
                System.out.println("Сумма: " + f[i].add(new Fraction(1, 2)));
                System.out.println("Разность: " + f[i].sub(new Fraction(1, 5)));
                System.out.println("Произведение: " + f[i].mul(new Fraction(1, 3)));
                System.out.println("Частное: " + f[i].div(new Fraction(2, 1)));
            }
        }
    }
}

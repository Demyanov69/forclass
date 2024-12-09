import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class MyPanel extends JPanel
{
    JLabel l1,l2,l3,l4,l5,l6,l7;
    JTextField f1,f2,f3,f4,f5,f6;
    JButton b1,b2,b3,b4;
    MyPanel()
    {
        l1=new JLabel("Operand 1");
        add(l1);
        f1=new JTextField(10);
        add(f1);
        l2=new JLabel("i");
        add(l2);
        f2=new JTextField(10);
        add(f2);
        l3=new JLabel("Operand 2");
        add(l3);
        f3=new JTextField(10);
        add(f3);
        l4=new JLabel("i");
        add(l4);
        f4 = new JTextField(10);
        add(f4);
        l5=new JLabel("Itog: ");
        add(l5);
        f5 = new JTextField(10);
        add(f5);
        l7=new JLabel("+");
        add(l7);
        f6 = new JTextField(10);
        add(f6);
        l6=new JLabel("i");
        add(l6);
        b1=new JButton("+");
        MyListener m = new MyListener();
        b1.addActionListener(m);
        add(b1);
        b2=new JButton("-");
        MmyListener mm = new MmyListener();
        b2.addActionListener(mm);
        add(b2);
        b3=new JButton("*");
        MmmyListener mmm = new MmmyListener();
        b3.addActionListener(mmm);
        add(b3);
        b4=new JButton("/");
        MmmmyListener mmmm = new MmmmyListener();
        b4.addActionListener(mmmm);
        add(b4);
    }

    class MyListener implements ActionListener
    {
        public void actionPerformed(ActionEvent e)
        {
            int p1=Integer.parseInt(f1.getText());
            int p2=Integer.parseInt(f2.getText());
            int p3=Integer.parseInt(f3.getText());
            int p4=Integer.parseInt(f4.getText());
            int p5=(p1+p3);
            int p6=(p2+p4);
            f5.setText(String.valueOf(p5));
            f6.setText(String.valueOf(p6));
        }
    }
    class MmyListener implements ActionListener
    {
        public void actionPerformed(ActionEvent e)
        {
            int p1=Integer.parseInt(f1.getText());
            int p2=Integer.parseInt(f2.getText());
            int p3=Integer.parseInt(f3.getText());
            int p4=Integer.parseInt(f4.getText());
            int p5=(p1-p3);
            int p6=(p2-p4);
            f5.setText(String.valueOf(p5));
            f6.setText(String.valueOf(p6));
        }
    }
    class MmmyListener implements ActionListener
    {
        public void actionPerformed(ActionEvent e)
        {
            int p1=Integer.parseInt(f1.getText());
            int p2=Integer.parseInt(f2.getText());
            int p3=Integer.parseInt(f3.getText());
            int p4=Integer.parseInt(f4.getText());
            int p5=(p1*p3-p2*p4);
            int p6=(p2*p3+p1*p4);
            f5.setText(String.valueOf(p5));
            f6.setText(String.valueOf(p6));
        }
    }
    class MmmmyListener implements ActionListener
    {
        public void actionPerformed(ActionEvent e)
        {
            int p1=Integer.parseInt(f1.getText());
            int p2=Integer.parseInt(f2.getText());
            int p3=Integer.parseInt(f3.getText());
            int p4=Integer.parseInt(f4.getText());
            int p5=(p1*p3+p2*p4)/(p3*p3+p4*p4);
            int p6=(p2*p3-p1*p4)/(p3*p3+p4*p4);
            f5.setText(String.valueOf(p5));
            f6.setText(String.valueOf(p6));
        }
    }
}
import javax.swing.*;
import java.awt.*;

public class MyFrame extends JFrame
{
    MyFrame()
    {
        setSize(300,300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        MyPanel p =new MyPanel();
        add(p);
        setVisible(true);
    }
}
public class ManeForPanel
{
    public static void main(String[] args)
    {
        MyFrame p=new MyFrame();
    }
}

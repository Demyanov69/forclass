Этот код реализует приложение Java Swing, которое управляет списком книг.  Он использует классы Book и Library, а также панель MyPanel для создания графического интерфейса.import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.List;

class Book {
    String author;
    String title;

    public Book(String author, String title) {
        this.author = author;
        this.title = title;
    }

    @Override
    public String toString() {
        return "Автор: " + author + ", Название: " + title;
    }
}

class Library {
    List<Book> books;

    public Library() {
        books = new ArrayList<>();
    }

    public void addBook(Book book) {
        books.add(book);
    }

    public String getAllBooks() {
        StringBuilder sb = new StringBuilder();
        for (Book book : books) {
            sb.append(book.toString()).append("\n");
        }
        return sb.toString();
    }
}

class MyPanel extends JPanel {
    Library library;
    JTextArea bookListArea;
    JTextField titleField;
    JTextField authorField;

    public MyPanel() {
        library = new Library();
        setLayout(new BorderLayout());

        // Область вывода списка книг
        bookListArea = new JTextArea(10, 20);
        bookListArea.setEditable(false);
        JScrollPane scrollPane = new JScrollPane(bookListArea);
        add(scrollPane, BorderLayout.CENTER);

        // Панель для ввода данных
        JPanel inputPanel = new JPanel(new GridLayout(2, 2));
        inputPanel.add(new JLabel("Название:"));
        titleField = new JTextField();
        inputPanel.add(titleField);
        inputPanel.add(new JLabel("Автор:"));
        authorField = new JTextField();
        inputPanel.add(authorField);
        add(inputPanel, BorderLayout.NORTH);

        // Кнопка "Добавить"
        JButton addButton = new JButton("Добавить книгу");
        addButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String title = titleField.getText();
                String author = authorField.getText();
                if (!title.isEmpty() && !author.isEmpty()) {
                    library.addBook(new Book(author, title));
                    updateBookList();
                    titleField.setText("");
                    authorField.setText("");
                } else {
                    JOptionPane.showMessageDialog(MyPanel.this, "Пожалуйста, заполните все поля.");
                }
            }
        });
        add(addButton, BorderLayout.SOUTH);
    }

    private void updateBookList() {
        bookListArea.setText(library.getAllBooks());
    }
}


public class Main {
    public static void main(String[] args) {
        JFrame frame = new JFrame("Библиотека");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.add(new MyPanel());
        frame.pack();
        frame.setVisible(true);
    }
}

Для запуска этого кода:

1. Сохраните: Сохраните код как Main.java.
2. Компилируйте: Откройте терминал или командную строку, перейдите в директорию, где вы сохранили файл, и выполните команду javac Main.java.
3. Запустите: Выполните команду java Main.


Это создаст окно с текстовым полем для вывода списка книг, полями ввода для названия и автора, и кнопкой "Добавить книгу".  Обратите внимание на обработку ошибок (проверка на пустые поля).  Список книг обновляется после каждого добавления.

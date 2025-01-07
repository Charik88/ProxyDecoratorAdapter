/* Задание 1
 
 В программу рендеринга HTML из лекции (раздел про паттерн «Декоратор») добавьте новые классы для декорирования текста.

 class Paragraph: ...

 auto text_block = new Paragraph(new Text());
 text_block->render("Hello world");

 >>> <p>Hello world</p>

 class Reversed: ...

 auto text_block = new Reversed(new Text());
 text_block->render("Hello world");

 >>> dlrow olleH

 class Link: ...

 auto text_block = new Link(new Text());
 text_block->render("netology.ru", "Hello world");

 >>> <a href=netology.ru>Hello world</a>

 Обратите внимание

     Сигнатура метода Link::render() не совпадает с сигнатурой оригинального метода.
     Для разворота строки используйте функцию std::reverse cppreference.
 */

#include <string>
#include <iostream>
#include <algorithm> // Для std::reverse

class Text {
public:
    virtual void render(const std::string& data) const { // Метод для рендеринга текста
        std::cout << data;
    }
};

class DecoratedText : public Text { // класс для декорирования текста который наследуется от класса Text
public:
    explicit DecoratedText(Text* text) : text_(text) {} // конструктор класса
    Text* text_; // указатель на тобьект текста
};

class ItalicText : public DecoratedText { // класс для декорирования текста который наследуется от класса DecoratedText
public:
    explicit ItalicText(Text* text) : DecoratedText(text) {} // конструктор класса
    void render(const std::string& data) const override { // переопределение метода render
        std::cout << "<i>"; // открывающий тег
        text_->render(data); // вызов метода рендеринга текста
        std::cout << "</i>"; // закрывающий тег
    }
};

class BoldText : public DecoratedText { // класс для декорирования текста который наследуется от класса DecoratedText
public:
    explicit BoldText(Text* text) : DecoratedText(text) {} // конструктор класса
    void render(const std::string& data) const override { // переопределение метода render
        std::cout << "<b>";
        text_->render(data);
        std::cout << "</b>";
    }
};

// Новый класс для рендеринга параграфа
class Paragraph : public DecoratedText {
public:
    explicit Paragraph(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const override {
        std::cout << "<p>";
        text_->render(data);
        std::cout << "</p>";
    }
};

// Новый класс для рендеринга реверсированного текста
class Reversed : public DecoratedText {
public:
    explicit Reversed(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const override { // переопределение метода render
        std::string reversed_data = data; // создаем строку для реверсивного текста
        std::reverse(reversed_data.begin(), reversed_data.end()); // реверс строки
        std::cout << reversed_data; // вывод
    }
};

// Новый класс для рендеринга ссылки
class Link : public DecoratedText {
public:
    explicit Link(Text* text) : DecoratedText(text) {}

    // Переопределяем метод render, чтобы соответствовать оригинальной сигнатуре
    void render(const std::string& url) const {
        std::cout << "<a href=\"" << url << "\">";
        text_->render(url);
        std::cout << "</a>";
    }
};

int main() {
    // Пример использования класса Paragraph
    auto paragraph = new Paragraph(new Text()); // создаем обьект класса Paragraph
    paragraph->render("Hello world"); // вызываем метод render для обьекта класса Paragraph
    std::cout << std::endl; // Для разделения выводов

    // Пример использования класса Reversed
    auto reversed_text = new Reversed(new Text()); // создаем обьект класса Reversed
    reversed_text->render("Hello world");
    std::cout << std::endl; // Для разделения выводов

    // Пример использования класса Link
    auto link_text = new Link(new Text());
    link_text->render("netology.ru"); // Теперь просто передаем URL
    std::cout << std::endl; // Для разделения выводов

    // Пример использования ItalicText и BoldText
    auto styled_text = new ItalicText(new BoldText(new Text()));
    styled_text->render("Hello world");
    std::cout << std::endl; // Для разделения выводов

  // render - это метод который вызывается для рендеринга текста
    return 0;
}

/*
 
 Сигнатура метода Link::render():
     Мы изменили метод Link::render() так, что он принимает только один параметр url. Это соответствует оригинальному методу render в классе Text, где также используется один параметр. Внутри метода мы выводим тег <a> с указанным URL.

 Использование std::reverse:
     Мы используем std::reverse в классе Reversed для разворота строки, как и было указано.

 Вывод из класса Paragraph:

 auto paragraph = new Paragraph(new Text());
 paragraph->render("Hello world");

     Метод render класса Paragraph оборачивает текст в <p> теги.
     Вывод будет:

 <p>Hello world</p>

 2. Вывод из класса Reversed:

 auto reversed_text = new Reversed(new Text());
 reversed_text->render("Hello world");

     Метод render класса Reversed реверсирует строку "Hello world" и выводит её.
     Реверсированная строка будет "dlrow olleH".
     Вывод будет:

 dlrow olleH

 3. Вывод из класса Link:

 auto link_text = new Link(new Text());
 link_text->render("netology.ru");

     Метод render класса Link выводит тег <a> с указанным URL.
     Вывод будет:

 <a href="netology.ru">netology.ru</a>

 4. Вывод из классов ItalicText и BoldText:

 auto styled_text = new ItalicText(new BoldText(new Text()));
 styled_text->render("Hello world");

     Метод render класса BoldText оборачивает текст в <b> теги, а затем ItalicText оборачивает результат в <i> теги.
     Вывод будет:

 <i><b>Hello world</b></i>


 */

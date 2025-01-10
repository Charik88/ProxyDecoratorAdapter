#include <string>
#include <iostream>
#include <algorithm> // Для std::reverse
#include <memory>    // Для std::shared_ptr

class Text {
public:
    virtual void render(const std::string& data) const { // Метод для рендеринга текста
        std::cout << data;
    }

    virtual ~Text() = default; // Виртуальный деструктор для корректного освобождения ресурсов
};

class DecoratedText : public Text { // класс для декорирования текста, который наследуется от класса Text
public:
    explicit DecoratedText(std::shared_ptr<Text> text) : text_(text) {} // конструктор класса
    std::shared_ptr<Text> text_; // указатель на объект текста
};

class ItalicText : public DecoratedText { // класс для декорирования текста, который наследуется от класса DecoratedText
public:
    explicit ItalicText(std::shared_ptr<Text> text) : DecoratedText(text) {} // конструктор класса
    void render(const std::string& data) const override { // переопределение метода render
        std::cout << "<i>"; // открывающий тег
        text_->render(data); // вызов метода рендеринга текста
        std::cout << "</i>"; // закрывающий тег
    }
};

class BoldText : public DecoratedText { // класс для декорирования текста, который наследуется от класса DecoratedText
public:
    explicit BoldText(std::shared_ptr<Text> text) : DecoratedText(text) {} // конструктор класса
    void render(const std::string& data) const override { // переопределение метода render
        std::cout << "<b>";
        text_->render(data);
        std::cout << "</b>";
    }
};

// Новый класс для рендеринга параграфа
class Paragraph : public DecoratedText {
public:
    explicit Paragraph(std::shared_ptr<Text> text) : DecoratedText(text) {}
    void render(const std::string& data) const override {
        std::cout << "<p>";
        text_->render(data);
        std::cout << "</p>";
    }
};

// Новый класс для рендеринга реверсированного текста
class Reversed : public DecoratedText {
public:
    explicit Reversed(std::shared_ptr<Text> text) : DecoratedText(text) {}
    void render(const std::string& data) const override { // переопределение метода render
        std::string reversed_data = data; // создаем строку для реверсивного текста
        std::reverse(reversed_data.begin(), reversed_data.end()); // реверс строки
        std::cout << reversed_data; // вывод
    }
};

// Новый класс для рендеринга ссылки
class Link : public DecoratedText {
public:
    explicit Link(std::shared_ptr<Text> text) : DecoratedText(text) {}

    void render(const std::string& url) const { // Переопределяем метод render, чтобы соответствовать оригинальной сигнатуре
        std::cout << "<a href=\"" << url << "\">";
        text_->render(url);
        std::cout << "</a>";
    }
};

int main() {
    // Пример использования класса Paragraph
    auto paragraph = std::make_shared<Paragraph>(std::make_shared<Text>()); // создаем объект класса Paragraph
    paragraph->render("Hello world"); // вызываем метод render для объекта класса Paragraph
    std::cout << std::endl; // Для разделения выводов

    // Пример использования класса Reversed
    auto reversed_text = std::make_shared<Reversed>(std::make_shared<Text>()); // создаем объект класса Reversed
    reversed_text->render("Hello world");
    std::cout << std::endl; // Для разделения выводов

    // Пример использования класса Link
    auto link_text = std::make_shared<Link>(std::make_shared<Text>());
    link_text->render("netology.ru"); // Теперь просто передаем URL
    std::cout << std::endl; // Для разделения выводов

    // Пример использования ItalicText и BoldText
    auto styled_text = std::make_shared<ItalicText>(std::make_shared<BoldText>(std::make_shared<Text>()));
    styled_text->render("Hello world");
    std::cout << std::endl; // Для разделения выводов

    return 0; // render - это метод который вызывается для рендеринга текста
}


/*


Использование std::shared_ptr: Все указатели на объекты Text заменены на std::shared_ptr<Text>. Это позволяет автоматически управлять памятью и избегать утечек.

Виртуальный деструктор: Добавлен виртуальный деструктор в класс Text, чтобы гарантировать корректное освобождение ресурсов при удалении объектов производных классов.

Использование std::make_shared: В main для создания объектов используются std::make_shared, что является более безопасным и эффективным способом создания shared_ptr.

Использование std::reverse: В классах Reversed и Link используются std::reverse для реверсивного рендеринга текста.

*/

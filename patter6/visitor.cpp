#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Базовый класс элемента документа
class DocumentElement {
public:
    virtual void accept(class Visitor& visitor) = 0; // Метод для принятия посетителя
    virtual ~DocumentElement() {}
};

// Конкретные элементы документа
class Header : public DocumentElement {
public:
    Header(const string& text) : text(text) {}

    void accept(Visitor& visitor) override;

    string getText() const {
        return text;
    }

private:
    string text;
};

class Paragraph : public DocumentElement {
public:
    Paragraph(const string& text) : text(text) {}

    void accept(Visitor& visitor) override;

    string getText() const {
        return text;
    }

private:
    string text;
};

class Image : public DocumentElement {
public:
    Image(const string& src) : src(src) {}

    void accept(Visitor& visitor) override;

    string getSrc() const {
        return src;
    }

private:
    string src;
};

// Базовый класс посетителя
class Visitor {
public:
    virtual void visitHeader(Header& header) = 0;
    virtual void visitParagraph(Paragraph& paragraph) = 0;
    virtual void visitImage(Image& image) = 0;
    virtual ~Visitor() {}
};

// Конкретный посетитель: Экспорт в HTML
class HTMLExportVisitor : public Visitor {
public:
    void visitHeader(Header& header) override {
        cout << "<h1>" << header.getText() << "</h1>" << endl;
    }

    void visitParagraph(Paragraph& paragraph) override {
        cout << "<p>" << paragraph.getText() << "</p>" << endl;
    }

    void visitImage(Image& image) override {
        cout << "<img src=\"" << image.getSrc() << "\" />" << endl;
    }
};

// Конкретный посетитель: Экспорт в Markdown
class MarkdownExportVisitor : public Visitor {
public:
    void visitHeader(Header& header) override {
        cout << "# " << header.getText() << endl;
    }

    void visitParagraph(Paragraph& paragraph) override {
        cout << paragraph.getText() << endl;
    }

    void visitImage(Image& image) override {
        cout << "![" << image.getSrc() << "](" << image.getSrc() << ")" << endl;
    }
};

// Реализация метода accept для каждого элемента
void Header::accept(Visitor& visitor) {
    visitor.visitHeader(*this);
}

void Paragraph::accept(Visitor& visitor) {
    visitor.visitParagraph(*this);
}

void Image::accept(Visitor& visitor) {
    visitor.visitImage(*this);
}

// Класс документа
class Document {
public:
    void addElement(DocumentElement* element) {
        elements.push_back(element);
    }

    void exportTo(Visitor& visitor) {
        for (auto& element : elements) {
            element->accept(visitor);
        }
    }

    ~Document() {
        for (auto& element : elements) {
            delete element;
        }
    }

private:
    vector<DocumentElement*> elements;
};

// Клиентский код
int main() {
    // Создаем документ
    Document document;

    // Добавляем элементы в документ
    document.addElement(new Header("Welcome to the Document"));
    document.addElement(new Paragraph("This is a sample paragraph."));
    document.addElement(new Image("image.png"));

    // Экспортируем документ в HTML
    HTMLExportVisitor htmlVisitor;
    cout << "Exporting to HTML:" << endl;
    document.exportTo(htmlVisitor);

    // Экспортируем документ в Markdown
    MarkdownExportVisitor markdownVisitor;
    cout << "\nExporting to Markdown:" << endl;
    document.exportTo(markdownVisitor);

    return 0;
}
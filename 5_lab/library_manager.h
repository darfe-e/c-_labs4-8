#ifndef LIBRARY_MANAGER_H
#define LIBRARY_MANAGER_H

#include "headers/IndependentPublicationCard.h"
#include "headers/BookCard.h"
#include "headers/ArticleCard.h"
#include "headers/ArticleCollectionCard.h"
#include "headers/binryTree.h"
#include <functional>
#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include "files/file_headers/File_text.h"
#include "files/file_headers/File_binary.h"
#include "exceptions/headers/file_exceptions/file_access_exception .h"

enum CardType : int
{
    UNKNOWN = 0,
    ARTICLE_COLLECTION_CARD = 1,
    BOOK_CARD = 2,
    ARTICLE_CARD = 3
};

class SearchTemplate
{
private:
    std::string title;
    std::string author;
    std::string authorMark;
    std::string inventoryNumber;
    std::string thematicCode;
    int yearOfPublication = 0;
    std::string publisher;
    int circulation = 0;
    int pagesNamber = 0;

public:
    void setTitle(const std::string& title) { this->title = title; }
    void setAuthor(const std::string& author) { this->author = author; }
    void setAuthorMark(const std::string& mark) { this->authorMark = mark; }
    void setInventoryNumber(const std::string& inv) { this->inventoryNumber = inv; }
    void setThematicCode(const std::string& code) { this->thematicCode = code; }
    void setYearOfPublication(int year) { this->yearOfPublication = year; }
    void setPublisher(const std::string& pub) { this->publisher = pub; }
    void setCirculation(int circ) { this->circulation = circ; }
    void setPagesNamber(int pages) { this->pagesNamber = pages; }

    const std::string& getTitle() const { return title; }
    const std::string& getAuthor() const { return author; }
    const std::string& getAuthorMark() const { return authorMark; }
    const std::string& getInventoryNumber() const { return inventoryNumber; }
    const std::string& getThematicCode() const { return thematicCode; }
    int getYearOfPublication() const { return yearOfPublication; }
    const std::string& getPublisher() const { return publisher; }
    int getCirculation() const { return circulation; }
    int getPagesNamber() const { return pagesNamber; }

    bool hasCriteria() const {
        return !title.empty() || !author.empty() || !authorMark.empty() ||
               !inventoryNumber.empty() || !thematicCode.empty() ||
               yearOfPublication != 0 || !publisher.empty() ||
               circulation != 0 || pagesNamber != 0;
    }
};

template<class T>
class LibraryManager
{
private:
    binaryTree<T> tree;
    const std::string className;
    bool isRunning = true;

    void _displayMenu() const;
    int _getUserChoice();
    void _processChoice(int choice);

    typename binaryTree<T>::iterator _search_by_template(const SearchTemplate& search_template);    SearchTemplate _create_search_template();
    bool _search_independent_fields(const SearchTemplate& search_template, const T& card);

    std::function<bool(const T&, const T&)> _choose_comparator();

    // File operations
    void _writeToTextFile();
    void _readFromTextFile();
    void _writeToBinaryFile();
    void _readFromBinaryFile();

    CardType _get_card_type();
    std::string _get_card_type_string() const;

public:
    LibraryManager(const std::string& name);
    void run();
};

#endif
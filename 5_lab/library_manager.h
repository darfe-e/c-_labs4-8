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
#include "exceptions/headers/file_exceptions/FileTypeMismatchException.h"

enum CardType : int
{
    UNKNOWN = 0,
    ARTICLE_COLLECTION_CARD = 1,
    BOOK_CARD = 2,
    ARTICLE_CARD = 3
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

    treeNode<T>* _search_by_template(const T& search_template);
    T _create_search_template();
    bool _has_criterias(const T& search_template);
    bool _search_chosen(const T& templateIndependent, const T& independentCard);
    std::function<bool(const T&, const T&)> _choose_comparator();

    // File operations (заглушки)
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
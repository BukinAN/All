package com.springapp.mvc.controller;

import com.springapp.mvc.domain.Book;
import com.springapp.mvc.repository.BookRepository;
import com.springapp.mvc.validation.BookValidator;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.security.access.prepost.PreAuthorize;

import java.util.List;

@Controller
public class BookController {

    private BookRepository bookRepository;
    private BookValidator bookValidator;

    /**
     * конструктор с параметрами
     * @param bookRepository
     * @param bookValidator
     */
    @Autowired
    public BookController(BookRepository bookRepository, BookValidator bookValidator){

        this.bookRepository = bookRepository;
        this.bookValidator = bookValidator;
    }

    /**
     * возвращает книгу
     * @param model модель для jsp
     * @return index.jsp
     */
    @RequestMapping(value = "/", method = RequestMethod.GET)
    public String getBooks(Model model) {
        List<Book> books = this.bookRepository.listAll();

        model.addAttribute("books", books);

        return "index";
    }

    /**
     * добавляет книгу
     * @param model модель для jsp
     * @return addBook.jsp
     */
    @RequestMapping(value = "addBook", method = RequestMethod.GET)
    @PreAuthorize("isAuthenticated()")
    public String addBook(Model model) {
        model.addAttribute("book",new Book());

        return "addBook";
    }

    /**
     * добавление книги с проверкой на ошибки
     * @param book книга
     * @param bindingResult результат проверок
     * @return addBook.jsp либо возвращает на исходну с информацией об ошибке
     */
    @RequestMapping(value = "addBook", method = RequestMethod.POST)
    @PreAuthorize("isAuthenticated()")
    public String addBook(@ModelAttribute("book") Book book, BindingResult bindingResult){
        this.bookValidator.validate(book, bindingResult);
        if(bindingResult.hasErrors()){
            return "addBook";
        }

        this.bookRepository.addBook(book);
        return "redirect:/";
    }

    /**
     * удаление книги
     * @param id идентификатор книги
     * @return возвращает на исходный jsp
     */
    @RequestMapping(value = "deleteBook/{id}", method = RequestMethod.GET)
    @PreAuthorize("hasRole('admin')")
    public String deleteBook(@PathVariable Integer id){
        this.bookRepository.removeBook(id);

        return "redirect:/";
    }

}

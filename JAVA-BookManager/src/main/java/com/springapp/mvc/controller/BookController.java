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
     * ����������� � �����������
     * @param bookRepository
     * @param bookValidator
     */
    @Autowired
    public BookController(BookRepository bookRepository, BookValidator bookValidator){

        this.bookRepository = bookRepository;
        this.bookValidator = bookValidator;
    }

    /**
     * ���������� �����
     * @param model ������ ��� jsp
     * @return index.jsp
     */
    @RequestMapping(value = "/", method = RequestMethod.GET)
    public String getBooks(Model model) {
        List<Book> books = this.bookRepository.listAll();

        model.addAttribute("books", books);

        return "index";
    }

    /**
     * ��������� �����
     * @param model ������ ��� jsp
     * @return addBook.jsp
     */
    @RequestMapping(value = "addBook", method = RequestMethod.GET)
    @PreAuthorize("isAuthenticated()")
    public String addBook(Model model) {
        model.addAttribute("book",new Book());

        return "addBook";
    }

    /**
     * ���������� ����� � ��������� �� ������
     * @param book �����
     * @param bindingResult ��������� ��������
     * @return addBook.jsp ���� ���������� �� ������� � ����������� �� ������
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
     * �������� �����
     * @param id ������������� �����
     * @return ���������� �� �������� jsp
     */
    @RequestMapping(value = "deleteBook/{id}", method = RequestMethod.GET)
    @PreAuthorize("hasRole('admin')")
    public String deleteBook(@PathVariable Integer id){
        this.bookRepository.removeBook(id);

        return "redirect:/";
    }

}
